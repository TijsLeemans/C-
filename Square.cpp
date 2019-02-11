#include "Square.h"
#include "olcNoiseMaker.h"

Square::Square(double dTime) :
	Oscillator(dTime)
{

}

Square::~Square()
{

}

double Square::calculate(double dTime)
{
	double sinOut = 0.5 * sin(frequency * PI_2 * dTime);

	if (sinOut > 0.0)
		return 0.01;
	else
		return -0.01;
}