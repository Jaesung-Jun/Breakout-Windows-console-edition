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

void Print_Box(DoubleBuffering *dbuff, short x, short y, short size_x, short size_y, string block) {
	for (short i = 0; i < size_x * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + x, y }, block);
	}
	for (short i = 1; i < size_y; i++) {
		dbuff->Write_Buffer({ x, i + y }, block);
	}
	for (short i = 0; i < size_x * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + x, size_y + y }, block);
	}
	for (short i = 1; i < size_y; i++) {
		dbuff->Write_Buffer({ (size_x * 2 - 2 + x), i + y }, block);
	}
}

string Color_Code_Generator(string object, short color) {
	string color_code = "\x1b[3" + std::to_string(color) + "m" + object + "\x1b[0m";
	return color_code;
}

Screen::Screen(DoubleBuffering *_dbuff) {
	dbuff = _dbuff;
}

void Screen::Print_Time_Limit(COORD score_box_xy, int time_limit) {
	if (time_limit/30 > 10) {
		Print_Score_Board_Info("남은 시간 : " + std::to_string((time_limit / 30)) + "초", score_box_xy, { 7, 5 });
	}
	else {
		Print_Score_Board_Info("남은 시간 : " + Color_Code_Generator(std::to_string(time_limit / 30), 1) + "초", score_box_xy, { 7, 5 });
	}
}

void Screen::Print_Crashed_Block_Num(COORD score_box_xy, int score) {
	Print_Score_Board_Info("점수 : " + std::to_string(score), score_box_xy, { 7, 7 });
}

void Screen::Print_Remain_Block_Num(COORD score_box_xy, int remain_blocks) {
	Print_Score_Board_Info("남은 블럭 : " + std::to_string(remain_blocks), score_box_xy, { 7, 8 });
}

void Screen::Print_Score_Board_Info(string str, COORD score_box_xy, COORD line_xy) {
	dbuff->Write_Buffer({ score_box_xy.X + line_xy.X, score_box_xy.Y + line_xy.Y }, str);
}

void Screen::Print_Map_Boundary(Box box) {
	/*
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
	}*/
	Print_Box(dbuff, box.xy.X, box.xy.Y, box.size.X, box.size.Y, WALL_ANSI_COLOR_CYAN);
}

void Screen::Print_Score_Board(Score_Box score_box) {
	/*for (short i = 0; i < score_box.size.X * 2 - 1; i++) {
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
	}*/
	Print_Box(dbuff, score_box.xy.X, score_box.xy.Y, score_box.size.X, score_box.size.Y, WALL);
}

void Main_Screen::Print_Start_Screen(Keyboard *key, short status) {
	/*for (short i = 0; i < MAIN_SCREEN_X+1; i++) {
		dbuff->Write_Buffer({ i, 0 }, WALL_ANSI_COLOR_GREEN);
	}
	for (short i = 1; i < MAIN_SCREEN_Y-1; i++) {
		dbuff->Write_Buffer({ 0, i }, WALL_ANSI_COLOR_GREEN);
	}
	for (short i = 0; i < MAIN_SCREEN_X+1; i++) {
		dbuff->Write_Buffer({ i, MAIN_SCREEN_Y-2 }, WALL_ANSI_COLOR_GREEN);
	}
	for (short i = 1; i < MAIN_SCREEN_Y - 1; i++) {
		dbuff->Write_Buffer({ MAIN_SCREEN_X, i }, WALL_ANSI_COLOR_GREEN);
	}*/
	Print_Box(dbuff, 0, 0, MAIN_SCREEN_X/2+1, MAIN_SCREEN_Y-2, WALL_ANSI_COLOR_GREEN);
	Print_Main_Title(key, status);
}


void Main_Screen::Print_GameOver_Screen(Keyboard *key, short status) {
	//size X : 40, size Y = 10
	//X : 45, Y : 25
	/*
	for (short i = 0; i < GAME_OVER_SIZE_X * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + GAME_OVER_X, GAME_OVER_Y }, WALL);
	}
	for (short i = 1; i < GAME_OVER_SIZE_Y; i++) {
		dbuff->Write_Buffer({ GAME_OVER_X, i + GAME_OVER_Y }, WALL);
	}
	for (short i = 0; i < GAME_OVER_SIZE_X * 2 - 1; i++) {
		dbuff->Write_Buffer({ i + GAME_OVER_X,GAME_OVER_SIZE_Y + GAME_OVER_Y}, WALL);
	}
	for (short i = 1; i < GAME_OVER_SIZE_Y; i++) {
		dbuff->Write_Buffer({ (GAME_OVER_SIZE_X * 2 - 2 + GAME_OVER_X), i + GAME_OVER_Y }, WALL);
	}*/
	Print_Box(dbuff, GAME_OVER_X, GAME_OVER_Y, GAME_OVER_SIZE_X, GAME_OVER_SIZE_Y, WALL_ANSI_COLOR_GREEN);
	Print_GameOver_String(key, status);
}

Main_Screen::Main_Screen(DoubleBuffering *_dbuff) {
	dbuff = _dbuff;
}
