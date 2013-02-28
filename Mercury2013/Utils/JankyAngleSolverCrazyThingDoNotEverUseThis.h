#ifndef _JASCTDNEUT_H
#define _JASCTDNEUT_H

#define PI (3.14159265358979)

#define C1 (1) /* TODO */
#define C2 (2) /* TODO */
#define C3 (3) /* TODO */
#define C4 (4) /* TODO */
#define C5 (5) /* TODO */
#define C6 (6) /* TODO */
#define C7 (7) /* TODO */
#define C8 (8) /* TODO */

#define FORWARDS_COSINE_LAW(a, b, C) (sqrt((a * a) + (b * b) - (2 * a * b * cos(C))))
#define BACKWARDS_COSINE_LAW(a, b, c) (acos(((a * a) + (b * b) - (c * c)) / (2 * a * b)))

double jankyAngle(double x);

#endif
