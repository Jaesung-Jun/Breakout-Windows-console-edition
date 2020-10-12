#include "BallMovement.h"
Direction BallMovement::calc_direction(short* target) 
{
	short up[2] = { 0, 1 };
	short right[2] = { 1, 0 };
	short down[2] = { 0, -1 };
	short left[2] = { -1, 0 };
	short* compass[4];
	compass[0] = up; compass[1] = right;  compass[2] = down; compass[3] = left;
	Calculation cal;
	
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dot_product = cal.dot(cal.normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
/*
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

		/*******************************************************
		short diag_matrix[2][2] = { { 0, 1 },
		{ 1, 0 } };

		if (matrix[0][0] == TRUE || matrix[1][0] == TRUE) {
			//행렬곱
			for (short i = 0; i < 2; i++) {
				for (short j = 0; j < 2; j++) {
					for (short k = 0; k < 2; k++) {
						direction[i][j] += matrix[i][k] * diag_matrix[k][j];
					}
				}
			}

			//Transpose 전치행렬
			if (upbound == TRUE) {
				for (short i = 0; i < 2; i++) {
					for (short j = 0; j < 2; j++) {
						temp_matrix[i][j] = direction[i][j];
					}
				}
				for (short i = 0; i < 2; i++) {
					for (short j = 0; j < 2; j++) {
						direction[i][j] = temp_matrix[j][i];
					}
				}
			}
		}
		else if (matrix[0][1] == TRUE || matrix[1][1] == TRUE) {
			
			//전치 행렬
			for (short i = 0; i < 2; i++) {
				for (short j = 0; j < 2; j++) {
					temp_matrix[i][j] = direction[i][j];
				}
			}
			for (short i = 0; i < 2; i++) {
				for (short j = 0; j < 2; j++) {
					direction[i][j] = temp_matrix[j][i];
				}
			}

			//행렬곱
			if (upbound == TRUE) {
				for (short i = 0; i < 2; i++) {
					for (short j = 0; j < 2; j++) {
						for (short k = 0; k < 2; k++) {
							direction[i][j] += matrix[i][k] * diag_matrix[k][j];
						}
					}
				}
			}
		}*/
}