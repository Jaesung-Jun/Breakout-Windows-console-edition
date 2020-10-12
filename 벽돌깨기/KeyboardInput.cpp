#include "KeyboardInput.h"

void Keyboard::Player_X_Input(short *x) {
	if (GetAsyncKeyState(VK_LEFT) < 0) {
		*x -= 2;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0) {
		*x += 2;
	}
}

void Keyboard::Player_Ball_Input(Ball *ball) {
	if (GetAsyncKeyState(VK_SPACE) < 0) {
		ball->fall_down = FALSE;
		ball->upbound = FALSE;
		ball->speed = 1;
		ball->direction[0] = 1;
		ball->direction[1] = 1;
	}
}