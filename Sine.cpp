#include "Sine.h"
#include "olcNoiseMaker.h"

Sine::Sine(double dTime) :
	Oscillator(dTime)
{

}

Sine::~Sine()
{

}

double Sine::calculate(double dTime)
{
	return 0.5 * sin(frequency * PI_2 * dTime);

}