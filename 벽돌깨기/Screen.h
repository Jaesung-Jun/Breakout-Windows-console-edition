#pragma once
#include <string>
#include "DoubleBuffering.h"
#include "KeyboardInput.h"
#include "ColorCode.h"
#include "struct.h"
#include "BallMovement.h"
#include "Sound.h"
#include "Object.h"
#include "GetFile.h"

using namespace std;
//https://tikcode.tistory.com/4

string Color_Code_Generator(string object, short color);
void Print_Box(DoubleBuffering *dbuff, short x, short y, short size_x, short size_y, string block);

class Screen {
private:
	DoubleBuffering* dbuff;
public:
	Screen(DoubleBuffering *_dbuff);
	void Screen::Print_Player_Score(COORD score_box_xy, float score);
	void Print_Time_Limit(COORD score_box_xy, int time);
	void Print_Crashed_Block_Num(COORD score_box_xy, int score);
	void Print_Remain_Block_Num(COORD score_box_xy, int remain_blocks);
	void Print_Score_Board_Info(string str, COORD score_box_xy, COORD line_xy);
	void Print_Map_Boundary(Box box);
	void Print_Score_Board(Score_Box score_box);
};

class Main_Screen {
private:
	DoubleBuffering* dbuff;
	void Print_Main_Title(Keyboard *key, short status);
	void Print_GameOver_String(Keyboard *key, short status);
	void Print_Pause_String(Keyboard *key, short status);
public:
	Main_Screen(DoubleBuffering *_dbuff);
	void Print_Start_Screen(Keyboard *key, short status);
	void Print_Pause_Screen(Keyboard *key, short status);
	void Print_GameOver_Screen(Keyboard *key, short status);
	void Record_Save_Screen(GetConfig *getconfig, Keyboard *key, Player *player, float score, bool status);
	void Record_View_Screen(GetRecord *getrecord);
};