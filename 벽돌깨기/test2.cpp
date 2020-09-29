#include <iostream>
#include "Ball_Movement.h"
using namespace std;
int main(void)
{
	Ball_Movement ball;

	short matrix[4] = { FALSE, FALSE, TRUE, FALSE };

	//
	//  0  ->  0
	// ก่      ก้
	//  0  <-  0

	short* direction;

	direction = ball.vec_direction(matrix, FALSE);

	for (int i = 0; i < 4; i++) {
		cout << direction[i] << endl;
	}
}