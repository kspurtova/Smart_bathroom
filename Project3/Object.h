#pragma once

#ifndef OBJECT_H_
#define OBJECT_H_

#include <iostream>

using namespace std;

class Object
{
private:
	double Value;
	int Name;
public:
	Object();
	Object(double Val, int NM);
	//Object(const Object &a);
	//Object& operator =(const Object &a);
	void SetN(int a);
	void SetV(double a);
	double GetV();
	int GetN();
	friend istream& operator >>(istream& is, Object& a);
	friend ostream& operator <<(ostream& ios, const Object& a);
	~Object();
};

#endif