#include "Screen.h"

/*************************************************************************
*									!NOTICE!
* 
*		Game_Over, Game_Start Screens are wroted in Screen_Status.cpp!
* 
*		Function Name : Main_Screen::Print_Main_Title,
*						Main_Screen::Print_GameOver_Screen
*		
**************************************************************************/

string Repeat_Str(string s, int n) {
	string s1 = s;
	for (int i = 0; i < n; i++) {
		s += s1;
	}
	return s;
}

short Color_Set(short color) {
	if (color > 9) {
		color = 1;
	}
	else {
		color++;
	}
	return color;
}

string Color_Code_Generator(string object, short color) {
	string color_code = "\x1b[3" + std::to_string(color) + "m" + object + "\x1b[0m";
	return color_code;
}

Screen::Screen(DoubleBuffering* dbuff) {
	
}

void Screen::Print_Time_Limit(DoubleBuffering* dbuff, COORD score_box_xy, int time_limit) {
	if (time_limit/30 > 10) {
		Print_Score_Board_Info(dbuff, "남은 시간 : " + std::to_string((time_limit / 30)) + "초", score_box_xy, { 7, 5 });
	}
	else {
		Print_Score_Board_Info(dbuff, "남은 시간 : " + Color_Code_Generator(std::to_string(time_limit / 30), 1) + "초", score_box_xy, { 7, 5 });
	}
}

void Screen::Print_Crashed_Block_Num(DoubleBuffering* dbuff, COORD score_box_xy, int score) {
	Print_Score_Board_Info(dbuff, "점수 : " + std::to_string(score), score_box_xy, { 7, 7 });
}

void Screen::Print_Remain_Block_Num(DoubleBuffering* dbuff, COORD score_box_xy, SWall* swall, int size) {
	int remain_blocks = 0;
	for (int i = 0; i < size; i++) {
		if (swall[i].is_crashed == FALSE) {
			remain_blocks++;
		}
	}
	Print_Score_Board_Info(dbuff, "남은 블럭 : " + std::to_string(remain_blocks), score_box_xy, { 7, 8 });
}

void Screen::Print_Score_Board_Info(DoubleBuffering* dbuff, string str, COORD score_box_xy, COORD line_xy) {
	dbuff->Write_Buffer({ score_box_xy.X + line_xy.X, score_box_xy.Y + line_xy.Y }, str);
}

void Screen::Print_Map_Boundary(DoubleBuffering* dbuff, Box box) {
	for (short i = 0; i < box.size.X * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + box.xy.X, box.xy.Y }, WALL_ANSI_COLOR_CYAN);
	}
	for (short i = 1; i < box.size.Y; i++) {
		dbuff->Write_Buffer({ box.xy.X, i + box.xy.Y }, WALL_ANSI_COLOR_CYAN);
	}
	for (short i = 0; i < box.size.X * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + box.xy.X, box.size.Y + box.xy.Y }, WALL_ANSI_COLOR_CYAN);
	}
	for (short i = 1; i < box.size.Y; i++) {
		dbuff->Write_Buffer({ (box.size.X * 2 - 2 + box.xy.X), i + box.xy.Y }, WALL_ANSI_COLOR_CYAN);
	}
}

void Screen::Print_Score_Board(DoubleBuffering* dbuff, Score_Box score_box) {
	for (short i = 0; i < score_box.size.X * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + score_box.xy.X, score_box.xy.Y }, WALL);
	}
	for (short i = 1; i < score_box.size.Y; i++) {
		dbuff->Write_Buffer({ score_box.xy.X, i + score_box.xy.Y }, WALL);
	}
	for (short i = 0; i < score_box.size.X * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + score_box.xy.X, score_box.size.Y + score_box.xy.Y }, WALL);
	}
	for (short i = 1; i < score_box.size.Y; i++) {
		dbuff->Write_Buffer({ (score_box.size.X * 2 - 2 + score_box.xy.X), i + score_box.xy.Y }, WALL);
	}
}


void Object::Print_Reset_Ball(DoubleBuffering* dbuff, Keyboard key, Ball* ball) {
	dbuff->Write_Buffer({ ball->xy.X, ball->xy.Y }, BALL);
	key.Player_Ball_Input(ball); //Space키를 입력받으면 ball.fall_down을 FALSE로 바꾸고 기본 세팅까지 완료함.
}

void Object::Print_Player(DoubleBuffering* dbuff, Player *player, Keyboard key, Box box) {

	key.Player_X_Input(&(player->xy.X));

	if ((player->xy.X + player->length) >= box.size.X * 2 + box.xy.X+1) {
		player->xy.X -= 2;
	}
	else if ((player->xy.X) <= box.xy.X-1) {
		player->xy.X += 2;
	}

	for (short i = 0; i < player->length; i++) {
		dbuff->Write_Buffer({ player->xy.X + i, player->xy.Y }, PLAYER);
	}
}
void Object::Print_Wall(DoubleBuffering* dbuff, Wall* wall, SWall* swall, Box box) {
	char* color_wall = DESTROYABLE_WALL;

	for (short i = 0; i < wall->nblocks; i++) {
		//default_color = color_set(default_color);
		if (swall[i].is_crashed == FALSE) {
			dbuff->Write_Buffer({ swall[i].xy.X, swall[i].xy.Y }, Repeat_Str(Color_Code_Generator(DESTROYABLE_WALL, swall[i].color), swall[i].length));
		}
	}

	/////////////////////////////////////////////////////////
	//std::string debug5 = std::to_string(wall->nblocks);
	//dbuff->Write_Buffer({ 150, 34 }, debug5);
	////////////////////////////////////////////////////////
}

void Object::Crash_Wall(Ball* ball, Wall* wall, SWall* swall, Player* player){
	Sound sound;
	BallMovement ball_move;
	for (short i = 0; i < wall->nblocks; i++) {
		if (swall[i].is_crashed == FALSE) {
			if (ball->xy.X <= (swall[i].xy.X + swall[i].length) && ball->xy.X >= swall[i].xy.X && swall[i].xy.Y <= ball->xy.Y && swall[i].xy.Y >= ball->xy.Y) { //if crashed
				if ((swall[i].xy.X + wall->block_length == swall[i + 1].xy.X) || (swall[i].xy.X - wall->block_length == swall[i - 1].xy.X)) { //Horizontal Collision Resolution
					swall[i].is_crashed = TRUE;
					ball->upbound = TRUE;
					ball_move.vec_direction(ball);
					sound.down_pitch_play(200, 10, 1);
				}
				else if ((swall[i].xy.X + wall->block_length != swall[i + 1].xy.X) || (swall[i].xy.X - wall->block_length != swall[i - 1].xy.X)) { //Vertical Collision Resolution
					swall[i].is_crashed = TRUE;
					ball->upbound = FALSE;
					ball_move.vec_direction(ball);
				}
				player->score++;
			}
		}
	}
	std::string debug1 = std::to_string(wall->nblocks);
}

SWall* Object::Config_Wall(Wall* wall, Box box) {
	/*
	wall->nblocks = (((box.size.X * 2) / wall->block_length)) * (wall->height);
	wall->width = (((box.size.X * 2) / wall->block_length));

	char** wall_set = new char*[wall->width];

	for (int i = 0; i < wall->height; i++) {
		wall_set[i] = new char[wall->height];
	}

	wall_set = {};

	SWall* swall = new SWall[wall->nblocks]();
	*/
	/*
	for (short i = 0; i < wall->width; i++) {
		for (short j = 0; i < wall->height; k++) {
			swall[num_blocks].xy = { (box.xy.X - 3) + wall->block_length, i + wall->y };
			swall[num_blocks].length = wall->block_length;
			num_blocks++;
		}
	}*/
	
	wall->nblocks = ((box.size.X * 2) / wall->block_length) * (wall->height);
	SWall* swall = new SWall[wall->nblocks]{}; //delete 부분

	int l = 0;
	short color = 0;
	short tmp_block_size;
	for (short i = wall->y; i < wall->height + wall->y; i++) {
		for (short j = box.xy.X + 2; j < ((box.size.X * 2) + (box.xy.X + 2)); j += wall->block_length) {
			if (j+wall->block_length > ((box.size.X * 2 - 5) + (box.xy.X + 2))) {
				tmp_block_size = ((box.size.X * 2 - 5) % wall->block_length);
				swall[l].xy = { j, i };
				swall[l].length = tmp_block_size;
				swall[l].color = Color_Set(color);
				color++;
				l++;
			}
			else{
				swall[l].xy = { j, i };						//Buffer OverRun Bug Detected!
				swall[l].length = wall->block_length;
				swall[l].color = Color_Set(color);
				l++;
			}
		}
	}
	
	return swall;
}
void Object::Print_Ball(DoubleBuffering* dbuff, Ball *ball, Box box, Player* player, Keyboard key) {

	Sound sound;

	if (ball->fall_down) {
		ball->xy = { (player->xy.X + (player->length / 2)), player->xy.Y-1};
		Print_Reset_Ball(dbuff, key, ball);
	}
	else if (!ball->fall_down) {
		BallMovement ball_move;

		if ((ball->xy.X) >= box.size.X * 2 + box.xy.X - 3) { //오른쪽벽
			ball->xy.X -= ball->speed;
			ball->upbound = FALSE;
			ball_move.vec_direction(ball, TRUE);
		}

		else if (ball->xy.X <= box.xy.X + 1) { //왼쪽벽
			ball->xy.X += ball->speed;
			ball->upbound = FALSE;
			ball_move.vec_direction(ball);
		}

		if (ball->xy.Y <= box.xy.Y + 1) { //위쪽 벽에 부딪치면
			ball->xy.Y += ball->speed;
			ball->upbound = TRUE;
			ball_move.vec_direction(ball);
		}
		/*
		if (ball->xy.Y >= player.xy.Y - 1 && ball->xy.X <= (player.xy.X + player.length) && ball->xy.X >= (player.xy.X)) {
			ball->xy.Y -= ball->speed;
			ball->upbound = TRUE;
			ball_move.vec_direction(ball);
			Beep(523, 50);
		}*/
		if (ball->xy.X <= (player->xy.X + player->length) && ball->xy.X >= (player->xy.X)) {
			if (ball->xy.Y >= player->xy.Y - 1 && !(ball->xy.Y >= player->xy.Y + 1)) {
				ball->xy.Y -= ball->speed;
				ball->upbound = TRUE;
				ball_move.vec_direction(ball);
				sound.up_pitch_play(50, 50, 1);
				}
			}
		if ((ball->xy.Y) >= box.size.Y + box.xy.Y) { //아래쪽 벽에 
			player->score -= 10;
			if (player->score < 0)
				player->score = 0;
			ball->xy.Y -= ball->speed;
			ball->fall_down = TRUE;
			//ptr_direction = ball_move.vec_direction(ball->direction, ball->upbound, FALSE);
			//ball_move.find_direction(ball, ptr_direction);
		}

		ball->xy.X = (ball->xy.X + (ball->direction_xy.X * ball->speed));
		ball->xy.Y = (ball->xy.Y + (ball->direction_xy.Y * ball->speed));

		
		//////////////////////////////////////////////////////////////////////////
		/*std::string debug1 = std::to_string(ball->xy.X) + ", " + std::to_string(ball->xy.Y);
		std::string debug2 = std::to_string(ball->direction[0]) + std::to_string(ball->direction[1]) + "," + std::to_string(ball->direction[2]) + std::to_string(ball->direction[3]);
		std::string debug3 = std::to_string(ball->direction_xy.X) + std::to_string(ball->direction_xy.Y);
		std::string debug4 = std::to_string(ball->upbound);
		dbuff->Write_Buffer({ 150, 30 }, debug1);
		dbuff->Write_Buffer({ 150, 31 }, debug2);
		dbuff->Write_Buffer({ 150, 32 }, debug3);
		dbuff->Write_Buffer({ 150, 33 }, debug4);*/
		/////////////////////////////////////////////////////////////////////////

		dbuff->Write_Buffer({ ball->xy.X, ball->xy.Y }, BALL);
		}


}

void Main_Screen::Print_Main_Screen(DoubleBuffering *dbuff, Box box, Score_Box score_box) {
	Print_Map_Boundary(dbuff, box);
	Print_Score_Board(dbuff, score_box);
}

void Main_Screen::Print_Start_Screen(DoubleBuffering *dbuff, Keyboard *key, short status) {
	for (short i = 0; i < 131; i++) {
		dbuff->Write_Buffer({ i, 0 }, WALL_ANSI_COLOR_GREEN);
	}
	for (short i = 1; i < 60; i++) {
		dbuff->Write_Buffer({ 0, i }, WALL_ANSI_COLOR_GREEN);
	}
	for (short i = 0; i < 131; i++) {
		dbuff->Write_Buffer({ i, 59 }, WALL_ANSI_COLOR_GREEN);
	}
	for (short i = 1; i < 60; i++) {
		dbuff->Write_Buffer({130, i}, WALL_ANSI_COLOR_GREEN);
	}
	Print_Main_Title(dbuff, key, status);
}


void Main_Screen::Print_GameOver_Screen(DoubleBuffering *dbuff, Keyboard *key) {

}