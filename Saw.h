#pragma once
#include <iostream>
#include "math.h"
#include "oscillator.h"
#include "olcNoiseMaker.h"

#define PI_2 6.28318530717959

class Saw : public Oscillator
{
public:
	Saw(double dTime);
	~Saw();

	double getsample;

	double calculate(double dTime);

};
