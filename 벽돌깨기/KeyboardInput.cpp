#include "KeyboardInput.h"
void Keyboard::Player_X_Input(short *x) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		*x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		*x += 2;
	}
}

short Keyboard::Game_Status_Choose(short status) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		Sleep(70);
		if (status == 0) {
			status = 0;
		}
		else {
			status--;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) < 0) {
		Sleep(70);
		if (status == 2) {
			status = 2;
		}
		else {
			status++;
		}
	}
	return status;
}

bool Keyboard::Game_Status_Choose_Check() {
	if (GetAsyncKeyState(VK_RETURN) < 0) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void Keyboard::Player_Ball_Input(Ball* ball) {
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