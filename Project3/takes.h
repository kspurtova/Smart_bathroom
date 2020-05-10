#pragma once

#ifndef TAKES_H
#define TAKES_H

#include <iostream>
#include "Object.h"
#include "TMatrix.h"
#include <cmath>

using namespace std;

class takes
{
private:

public:
	takes();
	double Triangle(double x, double a, double b, double c, double up); // Функция треугольника
	double Trapeze(double x, double a, double b, double c, double d, double up); // Функция трапеции
	double Min(double a, double b); // Ищет минимум значений
	double Integral(double a, double b, double c, double d, double a1, double b1, double c1, double d1, double up); // Интеграл числителя
	double Area(double a, double b, double c, double d, double a1, double b1, double c1, double d1, double up); // Интеграл знаменателя
	double CoG(TVector<Object> cut, int Special); // Метод поиска центра тяжести
	TVector<double> Line(int Special, int count);
	~takes();
};

#endif