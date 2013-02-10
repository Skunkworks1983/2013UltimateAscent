#ifndef __MATH_H
#define __MATH_H

/**
 * Returns the floating point value that is the smallest.
 * @param a
 * @param b
 * @return the minimum of the two numbers
 */
float fmin(float a, float b);
/**
 * Returns the floating point value that is the closest to zero.
 * @param a
 * @param b
 * @return the number closest to zero
 */
float fzero(float a, float b);
/**
 * Returns the sign of the floating point number.
 * @param a
 * @return the sign, [-1,0,1]
 */
float fsign(float a);
/**
 * Returns the minimum of two numbers
 * @param a
 * @param b
 * @return the minimum
 */
int min(int a, int b);
/**
 * Returns the maximum of two numbers
 * @param a
 * @param b
 * @return the maximum
 */
int max(int a, int b);
/**
 * Returns the maximum of two floating point numbers
 * @param a
 * @param b
 * @return the maximum
 */
float fmax(float a, float b);

#endif
