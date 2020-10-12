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
	float dot(short* m1, short * m2);
	short* normalize(short* m1);
};