#pragma once
#define FALSE 0
#define TRUE 1
#include <iostream>
#include "struct.h"

using namespace std;
class BallMovement {
private:
	void calc_direction(Ball *ball, bool opposite);
	void find_direction(Ball* ball);
public:
	void vec_direction(Ball *ball, bool opposite = FALSE);
};
