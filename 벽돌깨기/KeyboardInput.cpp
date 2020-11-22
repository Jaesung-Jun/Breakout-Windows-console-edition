#include "KeyboardInput.h"
void Keyboard::Player_X_Input(short *x) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		*x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		*x += 2;
	}
}

short Keyboard::Game_Status_Choose(short status, int end_num) {
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
		if (status == end_num) {
			status = end_num;
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
	}
}