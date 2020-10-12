#include "test.h"

float Calculation::dot(short* m1, short * m2) {
	float product = 0.0f;
	for (int i = 0; i < 2; i++)
		product = product + m1[i] * m2[i];
	return product;
}

short* Calculation::normalize(short* m1) {
	int sum=0;
	for (int i = 0; i < 2; i++) {
		sum += m1[i];
	}

	for (int i = 0; i < 2; i++) {
		m1[i] /= sum;
	}
	return m1;
}


