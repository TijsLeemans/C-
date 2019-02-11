#include <iostream>
using namespace std;

#include "olcNoiseMaker.h"
#include "Oscillator.h"

Oscillator::Oscillator(double dTime) :
dTime(dTime)
{

}

Oscillator::~Oscillator()
{

}

double Oscillator::getSample()
{
	return sample;
}

double Oscillator::calculate(double dTime)
{
	return 0;
}

void Oscillator::setFrequency(double frequency)
{
		this->frequency = frequency;
}

double Oscillator::getFrequency()
{
	return frequency;
}