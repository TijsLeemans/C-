#pragma once
#include <iostream>
#include "math.h"
#include "oscillator.h"
#include "olcNoiseMaker.h"

#define PI_2 6.28318530717959

class Square : public Oscillator
{
public:
	Square(double dTime);
	~Square();

	double getsample;

	double calculate(double dTime);

};