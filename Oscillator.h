#pragma once
#include <iostream>
#include "math.h"
#include "olcNoiseMaker.h"

#define PI_2 6.28318530717959


class Oscillator
{
public:
	//Constructor and destructor
	Oscillator(double dTime);
	~Oscillator();

	//return the current sample
	double getSample();
	// go to next sample
	void setFrequency(double frequency);
	double getFrequency();


	virtual double calculate(double dTime);
	double frequency;
	double dTime;
	double sample;
};
