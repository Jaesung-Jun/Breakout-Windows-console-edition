#include "BallMovement.h"

void BallMovement::calc_direction(Ball *ball, bool opposite)
{
	short direction[4] = {};

	if (!ball->upbound) {
		if (!opposite) {
			for (int i = 0; i < 4; i++) {
				if (i == 3) {
					direction[0] = ball->direction[i];
				}
				else {
					direction[i + 1] = ball->direction[i];
				}
			}
		}
		else if (opposite) {
			for (int i = 3; i > 0; i--) {
				if (i == 0) {
					direction[3] = ball->direction[i];
				}
				else {
					direction[i - 1] = ball->direction[i];
				}
			}
		}

	}
	else if (ball->upbound) {
		for (int i = 0; i < 4; i++) {

			if (i + 2 > 3) {
				direction[(i + 2) % 2] = ball->direction[i];
			}
			else {
				direction[i + 2] = ball->direction[i];
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		ball->direction[i] = *(direction + i);
	}
}

void BallMovement::find_direction(Ball* ball) {

	if (ball->direction[0] == 1) // 1 0 | 0 0
	{
		ball->direction_xy.X = -1;
		ball->direction_xy.Y = -1;
	}
	else if (ball->direction[1] == 1) //0 1 | 0 0 완료
	{
		ball->direction_xy.X = 1;
		ball->direction_xy.Y = -1;
	}
	else if (ball->direction[2] == 1) // 0 0 | 1 0 완료
	{
		ball->direction_xy.X = -1;
		ball->direction_xy.Y = 1;
	}
	else if (ball->direction[3] == 1) // 0 0 | 0 1
	{
		ball->direction_xy.X = 1;
		ball->direction_xy.Y = 1;
	}
}

void BallMovement::vec_direction(Ball *ball, bool opposite) {
	calc_direction(ball, opposite);
	find_direction(ball);
}