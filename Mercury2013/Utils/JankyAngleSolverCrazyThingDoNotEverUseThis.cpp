#include <math.h>
#include "JankyAngleSolverCrazyThingDoNotEverUseThis.h"

double jankyAngle(double x) {
	double a = BACKWARDS_COSINE_LAW(x, C1, C2);
	double b = FORWARDS_COSINE_LAW(x, C3, (PI - a));
	double z1 = asin((sin(PI - a) / b) * x);
	double d = FORWARDS_COSINE_LAW(C5, b, (C8 - z1));
	double z2 = asin((sin(C8 - z1) / d) * b);
	double z3 = BACKWARDS_COSINE_LAW(C6, d, C7);
	return (z3 + z2) - (PI / 2);
}
