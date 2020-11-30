#include "Screen.h"
#include <stdio.h>
#include "to_string_modified.h"
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
	Print_Score_Board_Info("■■■■■■■■■■■■■■", score_box_xy, { 2, 9 });
	if (time_limit / 30 > 10) {
		Print_Score_Board_Info(Color_Code_Generator("남은 시간 : ", 3) + std::to_string((time_limit / 30)) + "초", score_box_xy, { 7, 12 });
	}
	else {
		Print_Score_Board_Info(Color_Code_Generator("남은 시간 : ", 3) + Color_Code_Generator(std::to_string(time_limit / 30), 1) + "초", score_box_xy, { 7, 12 });
	}
}

void Screen::Print_Crashed_Block_Num(COORD score_box_xy, int destroyed_blocks) {
	Print_Score_Board_Info("부순 블럭 : " + std::to_string(destroyed_blocks), score_box_xy, { 7, 3 });
}

void Screen::Print_Player_Score(COORD score_box_xy, float score) {
	Print_Score_Board_Info("점수 : " + to_string_with_precision(score, 0), score_box_xy, { 7, 5 });
}

void Screen::Print_Remain_Block_Num(COORD score_box_xy, int remain_blocks) {
	Print_Score_Board_Info("남은 블럭 : " + std::to_string(remain_blocks), score_box_xy, { 7, 7 });
}

void Screen::Print_Score_Board_Info(string str, COORD score_box_xy, COORD line_xy) {
	dbuff->Write_Buffer({ score_box_xy.X + line_xy.X, score_box_xy.Y + line_xy.Y }, str);
}

Score_Board_Info_Jpn::Score_Board_Info_Jpn(DoubleBuffering *_dbuff) : Screen(_dbuff) {};

void Score_Board_Info_Jpn::Print_Crashed_Block_Num(COORD score_box_xy, int destroyed_blocks) {
	Print_Score_Board_Info("衝突ブロック : " + std::to_string(destroyed_blocks), score_box_xy, { 7, 3 });
}

void Score_Board_Info_Jpn::Print_Player_Score(COORD score_box_xy, float score) {
	Print_Score_Board_Info("スコア : " + to_string_with_precision(score, 0), score_box_xy, { 7, 5 });
}

void Score_Board_Info_Jpn::Print_Remain_Block_Num(COORD score_box_xy, int remain_blocks) {
	Print_Score_Board_Info("のこりのブロック : " + std::to_string(remain_blocks), score_box_xy, { 4, 7 });
}

void Score_Board_Info_Jpn::Print_Time_Limit(COORD score_box_xy, int time_limit) {
	Print_Score_Board_Info("■■■■■■■■■■■■■■", score_box_xy, { 2, 9 });
	if (time_limit / 30 > 10) {
		Print_Score_Board_Info(Color_Code_Generator("のこり時間 : ", 3) + std::to_string((time_limit / 30)) + " 秒", score_box_xy, { 7, 12 });
	}
	else {
		Print_Score_Board_Info(Color_Code_Generator("のこり時間 : ", 3) + Color_Code_Generator(std::to_string(time_limit / 30), 1) + " 秒", score_box_xy, { 7, 12 });
	}
}

Score_Board_Info_Eng::Score_Board_Info_Eng(DoubleBuffering *_dbuff) : Screen(_dbuff) {};

void Score_Board_Info_Eng::Print_Crashed_Block_Num(COORD score_box_xy, int destroyed_blocks) {
	Print_Score_Board_Info("Destroyed Block(s) : " + std::to_string(destroyed_blocks), score_box_xy, { 4, 3 });
}

void Score_Board_Info_Eng::Print_Player_Score(COORD score_box_xy, float score) {
	Print_Score_Board_Info("Score : " + to_string_with_precision(score, 0), score_box_xy, { 7, 5 });
}

void Score_Board_Info_Eng::Print_Remain_Block_Num(COORD score_box_xy, int remain_blocks) {
	Print_Score_Board_Info("Remain Block(s) : " + std::to_string(remain_blocks), score_box_xy, { 4, 7 });
}

void Score_Board_Info_Eng::Print_Time_Limit(COORD score_box_xy, int time_limit) {
	Print_Score_Board_Info("■■■■■■■■■■■■■■", score_box_xy, { 2, 9 });
	if (time_limit / 30 > 10) {
		Print_Score_Board_Info(Color_Code_Generator("Time Limit: ", 3) + std::to_string((time_limit / 30)) + " second(s)", score_box_xy, { 4, 12 });
	}
	else {
		Print_Score_Board_Info(Color_Code_Generator("Time Limit : ", 3) + Color_Code_Generator(std::to_string(time_limit / 30), 1) + " second(s)", score_box_xy, { 4, 12 });
	}
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

void Main_Screen::Print_Pause_Screen(Keyboard *key, short status) {
	Print_Box(dbuff, GAME_OVER_X, GAME_OVER_Y, GAME_OVER_SIZE_X, GAME_OVER_SIZE_Y, WALL_ANSI_COLOR_GREEN);
	Print_Pause_String(key, status);
}

void Main_Screen::Record_Save_Screen(GetConfig *getconfig, Keyboard *key, Player *player, float score, bool status) {
	Print_Box(dbuff, 100, GAME_OVER_Y, 15, 15, WALL_ANSI_COLOR_MAGENTA);
	dbuff->Write_Buffer({ 106, GAME_OVER_Y + 2 }, "Record Save Window");
	dbuff->Write_Buffer({ 102, GAME_OVER_Y + 4 }, Color_Code_Generator("◆◆◆◆◆◆◆◆◆◆◆◆◆", 5));
	dbuff->Write_Buffer({ 104, GAME_OVER_Y + 6 }, "Name : " + player->name);
	dbuff->Write_Buffer({ 104, GAME_OVER_Y + 8 }, "Destroyed Blocks : " + to_string(player->destroyed_block));
	dbuff->Write_Buffer({ 104, GAME_OVER_Y + 10 }, "Score : " + to_string_with_precision(score, 0));
	if (status == TRUE) {
		dbuff->Write_Buffer({ 112, GAME_OVER_Y + 13 }, Color_Code_Generator("Saved!", 1));
		dbuff->Flip_Buffer();
		Sleep(1000);
	}
	else if (status == FALSE) {
		dbuff->Write_Buffer({ 106, GAME_OVER_Y + 13 }, Color_Code_Generator("Enter Key -> Save!", 1));
	}

	char key_s = key->Input_Alphabet();
	if (key_s == 8) {
		dbuff->Flip_Buffer();
		player->name.clear();
	}
	else if (key_s == 'KM' || key_s == 'MK') {
		if (player->name.length() != 0) {
			player->name = getconfig->Read_Config_Player_Name();
		}
	}
	else if (key_s == '\a' || player->name.size() > 9) { }
	else {
		player->name += key_s;
	}
}

void Main_Screen::Record_View_Screen(GetRecord *getrecord) {
	Print_Box(dbuff, 0, 0, MAIN_SCREEN_X / 2 + 1, MAIN_SCREEN_Y - 9, WALL_ANSI_COLOR_GREEN);
	dbuff->Write_Buffer({ 10, 2 }, "[No.]\t|\t[UserName]\t[Destroyed Walls]\t[Score]\t\t[Time limit]\t[Player Length]");
	dbuff->Write_Buffer({ 10, 3 }, "=======================================================================================================");
	string *infos = getrecord->Read_Records();			//52개까지 
	//dbuff->Write_Buffer({ 10, 3 }, to_string(getrecord->Read_Records_Num()));
	short i = 0;
	for (int j = 1; j < getrecord->Read_Records_Num(); j+=5) {
		dbuff->Write_Buffer({ 10, i + 4 }, to_string(i+1) + "\t|");
		dbuff->Write_Buffer({ 24, i + 4 }, infos[j - 1]);
		dbuff->Write_Buffer({ 40, i + 4 }, infos[j]);
		dbuff->Write_Buffer({ 64, i + 4 }, infos[j + 1]);
		dbuff->Write_Buffer({ 80, i + 4 }, infos[j + 2]);
		dbuff->Write_Buffer({ 96, i + 4 }, infos[j + 3]);
		i++;
		if (j/5 > 43) {
			dbuff->Write_Buffer({ 40, i + 4 }, Color_Code_Generator("Too Many Records....... :(", 3));
			break;
		}
	}
	dbuff->Write_Buffer({ 45, MAIN_SCREEN_Y - 5 }, Color_Code_Generator("Press ENTER key to go main menu.....", 6));
}

Main_Screen::Main_Screen(DoubleBuffering *_dbuff) {
	dbuff = _dbuff;
}
