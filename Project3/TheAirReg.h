#pragma once

#ifndef THEAIRREG_H
#define THEAIRREG_H

#include <iostream>
#include "TMatrix.h"
#include "takes.h"

using namespace std;

class TheAirReg
{
public:
	TheAirReg();
	void HeatingSystem(int count);
	int Rules(int AirT);
	TVector<double> Line(int count);
	int LineUp(double count);
	TVector<Object> AirTemp(double AirT);
	double Composed(double AirT);
	~TheAirReg();
};

#endif