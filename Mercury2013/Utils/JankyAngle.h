#ifndef _JASCTDNEUT_H
#define _JASCTDNEUT_H

#define PI (3.14159265358979)

#define C1 (17.807)
#define C2 (14) 
#define C3 (1.327) 
#define C5 (10.267) 
#define C6 (18.253) 
#define C7 (14) 
#define C8 ((112.29 / 180.0) * PI) 
#define C9 ((14.07 / 180.0) * PI)

#define FORWARDS_COSINE_LAW(a, b, C) (sqrt((a * a) + (b * b) - (2 * a * b * cos(C))))
#define BACKWARDS_COSINE_LAW(a, b, c) (acos(((a * a) + (b * b) - (c * c)) / (2 * a * b)))

double jankyAngle(double x);

double moreJankyAngle(double x);

double mostJankyAngle(double x);

#endif
