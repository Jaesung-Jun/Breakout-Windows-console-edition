#pragma once
#include <Windows.h>
#include "struct.h"
class Keyboard {
private:
	const short direction[2][2] = { { TRUE, FALSE },
									{ FALSE, FALSE } };
public:
	void Player_X_Input(short *x);
	void Player_Ball_Input(Ball* ball);
};