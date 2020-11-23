#pragma once
#include <Windows.h>
#include <conio.h>
#include <string>
#include "struct.h"
using namespace std;

#define KBHIT_ARROW 224;
#define KBHIT_UP 72
#define KBHIT_DOWN 80
#define KBHIT_LEFT 75
#define KBHIT_RIGHT 77

class Keyboard {
private:
	const short direction[2][2] = { { TRUE, FALSE },
									{ FALSE, FALSE } };
public:
	void Player_X_Input(short *x);
	void Player_Ball_Input(Ball* ball);
	short Game_Status_Choose(short status, int end_num);
	bool Game_Status_Choose_Check();
	bool Game_Pause_Check();
	char Input_Alphabet();
};