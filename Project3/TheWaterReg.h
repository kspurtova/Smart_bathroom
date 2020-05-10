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
	void TemperatureList(); // ������ �������� �����������
	void PressureList(); // ������ �������� ��������
	void WaterList(int count); // ������ �������� ��� ������� � �������� ����
	TVector<int> Rules(int tem, int press); // ���� ������
	int Line(double Val, double ras, double start, int number); //���� �������, �� ������� ����� �����
	TVector<Object> Temperature(double tem); // 
	TVector<Object> Pressure(double press); //
	TVector<double> Composed(double Tem, double Press); // �������� ���� ��������
	~TheWaterReg();
};

#endif