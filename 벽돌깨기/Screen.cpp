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

Screen::Screen(DoubleBuffering *dbuff) {
	this->dbuff = dbuff;
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

void Screen::Print_Remain_Block_Num(COORD score_box_xy, SWall* swall, int size) {
	int remain_blocks = 0;
	for (int i = 0; i < size; i++) {
		if (swall[i].is_crashed == FALSE) {
			remain_blocks++;
		}
	}
	Print_Score_Board_Info("남은 블럭 : " + std::to_string(remain_blocks), score_box_xy, { 7, 8 });
}

void Screen::Print_Score_Board_Info(string str, COORD score_box_xy, COORD line_xy) {
	dbuff->Write_Buffer({ score_box_xy.X + line_xy.X, score_box_xy.Y + line_xy.Y }, str);
}

void Screen::Print_Map_Boundary(Box box) {
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

void Screen::Print_Score_Board(Score_Box score_box) {
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