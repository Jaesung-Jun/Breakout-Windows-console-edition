#include <iostream>
#include "test.h"
using namespace std;
int main(void) {

	float target[2] = { 1, -1 };

	float up[2] = { 0, 1 };
	float right[2] = { 1, 0 };
	float down[2] = { 0, -1 };
	float left[2] = { -1, 0 };
	float* compass[4];
	compass[0] = up; compass[1] = right;  compass[2] = down; compass[3] = left;
	Calculation cal;

	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		cout << target[0] << ", " << target[1] << endl;
		float dot_product = cal.dot(cal.normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	int return_v = (Direction)best_match;
	cout << return_v << endl;
	cout << target[0] << ", " << target[1] << endl;
	return 0;
}

