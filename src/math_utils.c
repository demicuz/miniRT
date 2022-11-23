#include <math.h>

#include <miniRT.h>

float	lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}

float	clamp(float x, float lower, float upper)
{
	return fminf(upper, fmaxf(x, lower));
}
