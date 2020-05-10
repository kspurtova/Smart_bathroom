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
	double Triangle(double x, double a, double b, double c, double up); // ������� ������������
	double Trapeze(double x, double a, double b, double c, double d, double up); // ������� ��������
	double Min(double a, double b); // ���� ������� ��������
	double Integral(double a, double b, double c, double d, double a1, double b1, double c1, double d1, double up); // �������� ���������
	double Area(double a, double b, double c, double d, double a1, double b1, double c1, double d1, double up); // �������� �����������
	double CoG(TVector<Object> cut, int Special); // ����� ������ ������ �������
	TVector<double> Line(int Special, int count);
	~takes();
};

#endif