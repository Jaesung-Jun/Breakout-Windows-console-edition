#include "test.h"
#include <algorithm>
using namespace std;

float Calculation::dot(float* m1, float* m2) {
	float product = 0.0f;
	for (int i = 0; i < 2; i++)
		product = product + m1[i] * m2[i];
	return product;
}

float* Calculation::normalize(float *m1) {
	float sum=0;

	for (int i = 0; i < 2; i++) {
		sum += m1[i];
	}
	for (int i = 0; i < 2; i++) {
  		m1[i] /= sum;
	}
	return m1;
}


