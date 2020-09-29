#pragma once
#define FALSE 0
#define TRUE 1
#include <Windows.h>
#include <iostream>
#include "struct.h"

using namespace std;
class Ball_Movement {
private:

	void calc_direction(Ball *ball, bool opposite)
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

		/*
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

	void find_direction(Ball* ball) {

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
public:
	
	void vec_direction(Ball *ball, bool opposite = FALSE){
		calc_direction(ball, opposite);
		find_direction(ball);
	}
};
