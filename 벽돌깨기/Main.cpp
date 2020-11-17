#include "Screen.h"

using namespace std;

int main() {

	DoubleBuffering dbuff = DoubleBuffering(MAIN_SCREEN_X, MAIN_SCREEN_Y);

	Object obj;
	Keyboard key;
	
	Main_Screen screen;
	Player player;
	
	Box box;
	Score_Box score_box;

	Ball ball;
	Wall wall;
	
	SWall* swall;

	SetConsoleTitle(L"Break Out");

	bool game_over = FALSE;
	bool game_start = FALSE;
	///////////////////////////////
	int time_limit = 5;
	bool game_start_trigger = TRUE;
	int game_status = 1;
	//////////////////////////////

	const COORD default_ball_xy = { (player.xy.X + (player.length / 2)), player.xy.Y - 1 };

	swall = obj.Config_Wall(&wall, box);

	time_limit *= 30;

	
	while (1) {
		while (!game_start) {
			game_status = key.Game_Status_Choose(game_status);
			screen.Print_Start_Screen(&dbuff, &key, game_status);
			if (game_status == 0 && key.Game_Status_Choose_Check()) {
				while (!game_over) {					//Game Start!!
					if (GetAsyncKeyState(VK_SPACE) < 0) {
						game_start_trigger = FALSE;
					}
					screen.Print_Main_Screen(&dbuff, box, score_box);
					screen.Print_Time_Limit(&dbuff, score_box.xy, time_limit);
					screen.Print_Crashed_Block_Num(&dbuff, score_box.xy, player.score);
					screen.Print_Remain_Block_Num(&dbuff, score_box.xy, swall, wall.nblocks);

					obj.Print_Player(&dbuff, &player, key, box);
					obj.Print_Ball(&dbuff, &ball, box, &player, key);
					obj.Print_Wall(&dbuff, &wall, swall, box);
					obj.Crash_Wall(&ball, &wall, swall, &player);

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
				delete swall;
				return 0;
			}
			else if (game_status == 2) {

			}
			dbuff.Flip_Buffer(1);
			dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);
		}								
	}
	delete swall;
	return 0;
}