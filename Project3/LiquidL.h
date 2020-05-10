#pragma once

#ifndef LIQUIDL_H
#define LIQUIDL_H
#include <iostream>
#include "TMatrix.h"
#include "Object.h"
#include "takes.h"

using namespace std;

class LiquidL
{
public:
	LiquidL();
	void Inflow(int count);
	int Rules(int Expend, int Level);
	TVector<double> Line(int LineNumber, int count);
	int LineUp(int LineNumber, double count);
	TVector<Object> LevelW(double lev);
	TVector<Object> ExpenditureW(double exp);
	double Composed(double Level, double Expend);
	~LiquidL();
};

#endif