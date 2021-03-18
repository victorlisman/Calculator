#include "cFunctions.h"


cFunctions::cFunctions()
{

}

cFunctions::~cFunctions()
{

}

float cFunctions::power(float a, float b)
{
	if (b == 0)
		return 1;

	if (a == 0)
		return 0;

	float r = 1.0f;

	for (int i = 1; i <= b; i++)
		r *= a;

	return r;
}

float cFunctions::root2(float a)
{
	float temp = 0.0f, sqrt;
	sqrt = a / 2;

	while (sqrt != temp)
	{
		temp = sqrt;
		sqrt = (a / temp + temp) / 2;
	}

	return sqrt;
}

float cFunctions::mod(float a)
{
	if (a >= 0)
		return a;

	if (a < 0)
		return a * -1;

}

/*uint16_t log2(uint32_t a)
{
	if (!a)
		return -1;
	uint16_t logValue = -1;

	while (a)
	{
		logValue++;

		a >>= 1;
	}

	return logValue;
}

uint32_t cFunctions::log(uint32_t a, uint32_t b)
{
	return log2(a) / log2(b);
} 
*/