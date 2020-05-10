#pragma once

#ifndef THEWATERREG_H
#define THEWATERREG_H

#include <iostream>
#include "Object.h"
#include "TMatrix.h"
#include "takes.h"

using namespace std;

class TheWaterReg
{
public:
	TheWaterReg();
	void TemperatureList(); // Список значений температуры
	void PressureList(); // Список значений давления
	void WaterList(int count); // Список значений для горячей и холодной воды
	TVector<int> Rules(int tem, int press); // База правил
	int Line(double Val, double ras, double start, int number); //Ищет отрезок, на котором лежит точка
	TVector<Object> Temperature(double tem); // 
	TVector<Object> Pressure(double press); //
	TVector<double> Composed(double Tem, double Press); // Выполяет весь алгоритм
	~TheWaterReg();
};

#endif