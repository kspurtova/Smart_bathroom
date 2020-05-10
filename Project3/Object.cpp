#include "Object.h"


Object::Object()
{
	Value = 0;
	Name = 0;
}


/*
Object::Object(const Object &a)
{
	Value = a.Value;
	Name = a.Name;
}


Object& Object::operator =(const Object &a)
{
	if (this != &a)
	{
		Value = a.Value;
		Name = a.Name;
	}
	return *this;
}
*/


Object::Object(double Val, int NM)
{
	Value = Val;
	Name = NM;
}


void Object::SetN(int a)
{
	Name = a;
}


void Object::SetV(double a)
{
	Value = a;
}


double Object::GetV()
{
	return Value;
}


int Object::GetN()
{
	return Name;
}


istream& operator >>(istream& is, Object& a)
{
	is >> a.Value;
	is >> a.Name;
	return is;
}


ostream& operator <<(ostream& os, const Object& a)
{
	os << a.Value << endl;
	os << a.Name << endl;
	return os;
}


Object::~Object()
{

}