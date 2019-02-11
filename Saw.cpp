#include "Saw.h"
#include "olcNoiseMaker.h"

Saw::Saw(double dTime) :
	Oscillator(dTime)
{

}

Saw::~Saw()
{

}

double Saw::calculate(double dTime)
{
	double Output = 0.0;

	for (double n = 1.0; n < 40.0; n++)
		Output += (sin(n * PI_2 * dTime)) / n;

	return Output * (2.0 / PI);

}