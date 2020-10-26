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

	SetConsoleTitle(L"Plz Destroy Me.");

	bool game_over = TRUE;
	bool exit_game = FALSE;

	const COORD default_ball_xy = { (player.xy.X + (player.length / 2)), player.xy.Y - 1 };

	swall = obj.Config_Wall(&wall, box);

	while (!exit_game) {

		screen.Print(&dbuff,box, score_box);
		obj.Print_Player(&dbuff, &player, key, box);
		obj.Print_Ball(&dbuff, &ball, box, player, key);
		obj.Print_Wall(&dbuff, &wall, swall, box);
		obj.Crash_Wall(&ball, &wall, swall);
		dbuff.Flip_Buffer(0);
		dbuff.CleanUp_Buffer(MAIN_SCREEN_X, MAIN_SCREEN_Y);
	}
	delete swall;
}