#include "Math.h"
#include <math.h>

float fmin(float a, float b) {
	return a < b ? a : b;
}

float fzero(float a, float b) {
	return fabs(a) < fabs(b) ? a : b;
}

float fsign(float a) {
	if (a == 0.0) {
		return 0.0;
	}
	return a > 0 ? 1.0 : -1.0;
}

int imin(int a, int b) {
	return a < b ? a : b;
}
float fmax(float a, float b) {
	return a > b ? a : b;
}
int imax(int a, int b) {
	return a > b ? a : b;
}
