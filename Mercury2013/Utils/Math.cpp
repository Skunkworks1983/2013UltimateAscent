#include "Math.h"
#include <math.h>

float fmin(float a, float b) {
	return a < b ? a : b;
}

float fzero(float a, float b) {
	return fabs(a) < fabs(b) ? a : b;
}

float fsign(float a) {
	return a > 0 ? 1.0 : -1.0;
}

int min(int a, int b) {
	return a < b ? a : b;
}
float fmax(float a, float b) {
	return a > b ? a : b;
}
int max(int a, int b) {
	return a > b ? a : b;
}
