#include "Screen.h"

using namespace std;

int main() {


	/********************** Struct **********************/

	Box box;
	Score_Box score_box;

	Ball ball;
	Wall wall;

	Player player;

	/******************** Class *************************/

	DoubleBuffering dbuff = DoubleBuffering(MAIN_SCREEN_X, MAIN_SCREEN_Y);

	Keyboard key;

	Main_Screen main_screen = Main_Screen(&dbuff);
	Screen screen = Screen(&dbuff);

	/********************** Object *********************/

	Object obj = Object(&dbuff);

	obj_Player obj_player = obj_Player(&player);
	short default_direction[4] = { TRUE, FALSE, FALSE, FALSE };
	COORD default_direction_xy = { -1, -1 };
	obj_Ball obj_ball = obj_Ball(&ball, default_direction, default_direction_xy, 1);
	obj_Destroyable_Wall obj_destroyable_wall = obj_Destroyable_Wall(&wall, box);

	/****************************************************/

	SetConsoleTitle(L"Break Out");

	bool game_over = FALSE;
	bool game_start = FALSE;
	///////////////////////////////
	int time_limit = 5;
	bool game_start_trigger = TRUE;
	int game_status = 1;
	//////////////////////////////

	const COORD default_ball_xy = { (player.xy.X + (player.length / 2)), player.xy.Y - 1 };

	time_limit *= 30;

	
	while (1) {
		while (!game_start) {
			game_status = key.Game_Status_Choose(game_status);
			main_screen.Print_Start_Screen(&key, game_status);
			if (game_status == 0 && key.Game_Status_Choose_Check()) {
				while (!game_over) {					//Game Start!!
					if (GetAsyncKeyState(VK_SPACE) < 0) {
						game_start_trigger = FALSE;
					}
					screen.Print_Map_Boundary(box);
					screen.Print_Score_Board(score_box);

					screen.Print_Time_Limit(score_box.xy, time_limit);
					screen.Print_Crashed_Block_Num(score_box.xy, player.score);
					screen.Print_Remain_Block_Num(score_box.xy, wall.nblocks);

					obj_player.Print_Player(key, box);
					obj_ball.Print_Ball(&ball, box, &player, key);
					obj_destroyable_wall.Print_Wall(&wall, box);
					obj_destroyable_wall.Crash_Wall(&ball, &wall, &player);

					dbuff.Flip_Buffer(1);
					dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);

					if (!game_start_trigger) {
						time_limit--;
					}
					if (time_limit < 0) {
						game_over = TRUE;
					}							
												//Game Over
		
												//Game score record

												//Continue?!
				}
				game_over = FALSE;
				time_limit = 30;
				time_limit *= 30;
			}
			else if (game_status == 1 && key.Game_Status_Choose_Check()) {
				obj_destroyable_wall.Delete_Swall();
				return 0;
			}
			else if (game_status == 2) {

			}
			dbuff.Flip_Buffer(1);
			dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);
		}								
	}
	obj_destroyable_wall.Delete_Swall();
	return 0;
}