#include "Screen.h"
#include "GetFile.h"

using namespace std;

void reset_game(bool *game_over, bool *game_start_trigger, Player *player, Ball *ball){
	*game_over = FALSE;
	*game_start_trigger = TRUE;
	ball->speed = 1;		//Ball move again.
	ball->direction[0] = TRUE;		//Ball Direction Default Setting
	ball->direction[1] = FALSE;
	ball->direction[2] = FALSE;
	ball->direction[3] = FALSE;
	ball->direction_xy = { -1, -1 };
	ball->fall_down = TRUE;
	player->score = 0;				//Score to zero
	player->destroyed_block = 0;
}



int main() {

	bool game_over = FALSE;
	bool game_start = FALSE;
	///////////////////////////////
	int time_limit = 30;
	bool game_start_trigger = TRUE;
	bool game_pause = FALSE;
	int game_status = 1;
	short game_over_status = 0;
	short game_pause_status = 0;
	string name;
	//////////////////////////////

	/********************** Struct **********************/

	Box box;
	Score_Box score_box;

	Ball ball;
	//Ball ball2;

	Wall wall;

	Player player;

	/******************* Get Config ***********************/
	GetConfig config = GetConfig(&player, &time_limit, &wall);
	GetRecord record = GetRecord();

	PutRecord putrecord = PutRecord();

	/********************** Class *************************/

	DoubleBuffering dbuff = DoubleBuffering(MAIN_SCREEN_X, MAIN_SCREEN_Y);

	Keyboard key;

	Main_Screen main_screen = Main_Screen(&dbuff);
	Screen screen = Screen(&dbuff);
	Screen* score_board_language = NULL;

	if (player.language == "eng") {
		score_board_language = new Score_Board_Info_Eng(&dbuff);
	}
	else if (player.language == "jpn") {
		score_board_language = new Score_Board_Info_Jpn(&dbuff);
	}
	else {
		score_board_language = &screen;
	}

	/********************** Object *********************/

	obj_Player obj_player = obj_Player(&dbuff, &player);
	//obj_Ball obj_ball2 = obj_Ball(&dbuff, &ball2);
	obj_Ball obj_ball = obj_Ball(&dbuff, &ball);
	obj_Destroyable_Wall obj_destroyable_wall = obj_Destroyable_Wall(&dbuff, &wall, box);

	/******************************************************/
	SetConsoleTitle(L"Break Out");
	const COORD default_ball_xy = { (player.xy.X + (player.length / 2)), player.xy.Y - 1 };

	while (1) {				//Main loop
		while (!game_start) {
			game_status = key.Game_Status_Choose(game_status, 2);
			main_screen.Print_Start_Screen(&key, game_status);

			if (game_status == 0 && key.Game_Status_Choose_Check()) {
				//RESET CONFIGs
				reset_game(&game_over, &game_start_trigger, &player, &ball);
				config = GetConfig(&player, &time_limit, &wall);

				//DESTROYABLE WALL RESET
				obj_destroyable_wall.Delete_Swall();
				obj_destroyable_wall = obj_Destroyable_Wall(&dbuff, &wall, box);

				while (1) {					//Game Start!!
					FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));			//flush getch() buffer;
					if (GetAsyncKeyState(VK_SPACE) < 0) {
						game_start_trigger = FALSE;
					}
					if (game_over == FALSE && key.Game_Pause_Check()) { //Pause Game
						bool goto_main = FALSE;
						while (1) {
							FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
							screen.Print_Map_Boundary(box);
							screen.Print_Score_Board(score_box);
							obj_destroyable_wall.Print_Wall(&wall, box);
							//obj_player.Print_Player(key, box);
							//obj_ball.Print_Ball(&ball, box, &player, key);

							//Print score board info
							score_board_language->Print_Time_Limit(score_box.xy, time_limit);
							score_board_language->Print_Crashed_Block_Num(score_box.xy, player.destroyed_block);
							score_board_language->Print_Player_Score(score_box.xy, player.score);
							score_board_language->Print_Remain_Block_Num(score_box.xy, wall.nblocks - player.destroyed_block);

							game_pause_status = key.Game_Status_Choose(game_pause_status, 1);
							main_screen.Print_Pause_Screen(&key, game_pause_status);
							dbuff.Flip_Buffer(1);
							dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);

							if (game_pause_status == 0 && key.Game_Status_Choose_Check()) {
								break;
							}
							else if (game_pause_status == 1 && key.Game_Status_Choose_Check()) {
								game_status = -1;
								goto_main = TRUE;
								break;
							}

						}
						if (goto_main == TRUE) {
							goto_main = FALSE;
							break;
						}
					}
					screen.Print_Map_Boundary(box);
					screen.Print_Score_Board(score_box);

					//print score board info
					score_board_language->Print_Time_Limit(score_box.xy, time_limit);
					score_board_language->Print_Crashed_Block_Num(score_box.xy, player.destroyed_block);
					score_board_language->Print_Player_Score(score_box.xy, player.score);
					score_board_language->Print_Remain_Block_Num(score_box.xy, wall.nblocks - player.destroyed_block);

					obj_player.Print_Player(key, box);
					obj_ball.Print_Ball(&ball, box, &player, key);

					//obj_ball2.Print_Ball(&ball2, box, &player, key);
					obj_destroyable_wall.Print_Wall(&wall, box);
					obj_destroyable_wall.Crash_Wall(&ball, &wall, &player);

					//Player Score Setting (Decimal Point Round)
					player.score = (((float)player.destroyed_block / (float)config.Read_Config_Time_Limit()) * 100);
					player.score = player.score + (float)0.05;
					player.score = (float)(int)(player.score * 10);
					player.score = player.score / 10;

					//obj_destroyable_wall.Crash_Wall(&ball2, &wall, &player);

					if (!game_start_trigger) {
						time_limit--;
					}
					if (time_limit < 0) {
						game_over = TRUE;
					}

					if (game_over == TRUE) {		//Game Over
						game_over_status = key.Game_Status_Choose(game_over_status, 2);
						time_limit++; //stop stopwatch
						ball.speed = 0;
						ball.xy = { 0, 0 };
						player.xy.X = (DEFAULT_BOX_SIZE_X + DEFAULT_BOX_X * 2) / 2;
						main_screen.Print_GameOver_Screen(&key, game_over_status);			

						if (game_over_status == 0 && key.Game_Status_Choose_Check()) {		//retry
							//RESET CONFIGs
							reset_game(&game_over, &game_start_trigger, &player, &ball);
							config = GetConfig(&player, &time_limit, &wall);

							//DESTROYABLE WALL RESET
							obj_destroyable_wall.Delete_Swall();
							obj_destroyable_wall = obj_Destroyable_Wall(&dbuff, &wall, box);
						}

						else if (game_over_status == 1) {	//record
							bool save_or_not = key.Game_Status_Choose_Check();
							main_screen.Record_Save_Screen(&config, &key, &player, player.score, save_or_not);
							if (save_or_not == TRUE) {
								//Save Record
								putrecord.Put(player.name, player.destroyed_block, player.score, config.Read_Config_Time_Limit(), config.Read_Config_Player_Length());
								game_status = -1;	//Choose Nothing
								break;
							}
						}
						else if (game_over_status == 2 && key.Game_Status_Choose_Check()) {	//EXIT TO MAIN SCREEN
							game_status = -1; //Choose Nothing
							break;
						}
					}
					dbuff.Flip_Buffer(1);
					dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);
				}
			}
			else if (game_status == 1 && key.Game_Status_Choose_Check()) {			//GAME EXIT
				obj_destroyable_wall.Delete_Swall();
				cout << "bye bye~" << endl;
				//record.Delete_Records();
				if (score_board_language != NULL) {
					delete score_board_language;
				}
				return 0;
			}
			else if (game_status == 2 && key.Game_Status_Choose_Check()) {			//RECORD VIEW
				Sleep(100);
				while (1) {
					record = GetRecord();
					main_screen.Record_View_Screen(&record);
					if (key.Game_Status_Choose_Check()) {
						Sleep(100);
						game_status = -1;
						break;
					}
					dbuff.Flip_Buffer(1);
					dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);
				}
			}
			dbuff.Flip_Buffer(1);
			dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);
		}								
	}
	obj_destroyable_wall.Delete_Swall();
	//record.Delete_Records();
	if (score_board_language != NULL) {
		delete score_board_language;
	}
	return 0;
}