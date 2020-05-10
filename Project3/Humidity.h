#pragma once

#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <iostream>
#include "TMatrix.h"
#include "takes.h"

using namespace std;

class Humidity
{
public:
	Humidity();
	void Fan(int count);
	int Rules(int Hum);
	TVector<double> Line(int count);
	int LineUp(double count);
	TVector<Object> HumidityLev(double Hum);
	double Composed(double Hum);
	~Humidity();
};

#endif