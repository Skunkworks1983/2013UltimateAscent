#include <math.h>
#include "JankyAngle.h"

/**
 * Slower, more accurate math.
 * @param x Inches that screw drive is extended
 * @return Angle of shooter
 */
double jankyAngle(double x) {
	double a = BACKWARDS_COSINE_LAW(x, C1, C2);
	double b = FORWARDS_COSINE_LAW(x, C3, (PI - a));
	double z1 = asin((sin(PI - a) / b) * x);
	double d = FORWARDS_COSINE_LAW(C5, b, (C8 - z1));
	double z2 = asin((sin(C8 - z1) / d) * b);
	double z3 = BACKWARDS_COSINE_LAW(C6, d, C7);
	return (z3 + z2) - (PI / 2) + C9;
}

/**
 * Faster (35 times faster!), less accurate math.
 * @param x Inches that screw drive is extended
 * @return Angle of shooter
 */
double moreJankyAngle(double x) {
	return (-0.0053 * x * x) + (0.1795 * x) - (0.6718);
}

/**
 * Fastest (Not really, only 30 times faster), WAY less accurate math.
 * Do not expect anything accurate at all past 14 inches
 * @param x Inches that screw drive is extended
 * @return Angle of shooter
 */
double mostJankyAngle(double x) {
	return (0.0842 * x) - (0.2902);
}
