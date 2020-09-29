#pragma once
#include <Windows.h>
#include "struct.h"
class Keyboard {
private:
	const short direction[2][2] = { { TRUE, FALSE },
									{ FALSE, FALSE } };
public:
	void Player_X_Input(short *x) {
		if (GetAsyncKeyState(VK_LEFT) < 0) {
			*x -= 2;
		}
		if (GetAsyncKeyState(VK_RIGHT) < 0) {
			*x += 2;
		}
	}
	void Player_Ball_Input(Ball* ball) {
		if (GetAsyncKeyState(VK_SPACE) < 0) {
			ball->fall_down = FALSE;
			ball->upbound = FALSE;
			ball->speed = 1;
			ball->direction[0] = TRUE;
			ball->direction[1] = FALSE;
			ball->direction[2] = FALSE;
			ball->direction[3] = FALSE;
			ball->direction_xy = { -1, -1 };
		}
	}
};