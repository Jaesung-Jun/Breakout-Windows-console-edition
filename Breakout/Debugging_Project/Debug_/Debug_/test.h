#pragma once
#pragma once
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

class Calculation {
public:
	float dot(float* m1, float* m2);
	float* normalize(float *m1);
};