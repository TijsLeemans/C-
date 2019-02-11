#include "Triangle.h"
#include "olcNoiseMaker.h"

Triangle::Triangle(double dTime) :
	Oscillator(dTime)
{

}

Triangle::~Triangle()
{

}

double Triangle::calculate(double dTime)
{
	return 0.5 * asin(sin(frequency * PI_2) * dTime) * (2.0 / PI);

}