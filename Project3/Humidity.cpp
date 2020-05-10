#include "Humidity.h"


Humidity::Humidity()
{

}


void Humidity::Fan(int count)
{
	switch (count)
	{
	case 1:
		cout << "Выключить" << endl;
		break;
	case 2:
		cout << "Открыть немного" << endl;
		break;
	case 3:
		cout << "Открыть " << endl;
		break;
	}
}


int Humidity::Rules(int Hum)
{
	int res;
	cout << "rule #" << Hum << endl;
	switch (Hum)
	{
	case 1:
		res = 1;
		break;
	case 2:
		res = 2;
		break;
	case 3:
		res = 3;
		break;
	}
	(*this).Fan(res);
	return res;
}


TVector<double> Humidity::Line(int count)
{
	TVector<double> res(2);
	// [0] - min, [1] - max
	switch (count)
	{
	case 1:
		res[0] = 0;
		res[1] = 55;
		break;
	case 2:
		res[0] = 55;
		res[1] = 100;
		break;
	}
	return res;
}


int Humidity::LineUp(double count)
{
	int i = 1;
	TVector<double> mul(2);
	while (i < 10)
	{
		mul = (*this).Line(i);
		if ((count >= mul[0]) && (count <= mul[1]))
			break;
		i++;
	}
	return i;
}


TVector<Object> Humidity::HumidityLev(double Hum)
{
	takes R;
	int count = (*this).LineUp(Hum);
	TVector<Object> res(2);
	switch (count)
	{
	case 1:
		res[0].SetV(R.Trapeze(Hum, 0, 10, 40, 55, 1));
		res[0].SetN(1);
		res[1].SetV(R.Triangle(Hum, 40, 55, 70, 1));
		res[1].SetN(2);
		break;
	case 2:
		res[0].SetV(R.Triangle(Hum, 40, 55, 70, 1));
		res[0].SetN(2);
		res[1].SetV(R.Trapeze(Hum, 55, 70, 90, 100, 1));
		res[1].SetN(3);
		break;
	}
	return res;
}


double Humidity::Composed(double Hum)
{
	takes R;
	double res;
	TVector<Object> humid(2);
	Object c;

	humid = (*this).HumidityLev(Hum);

	if (humid[1].GetV() > humid[0].GetV())
	{
		c = humid[1];
		humid[1] = humid[0];
		humid[0] = c;
	}

	// [0] - max, [1] - min

	if (humid[1].GetV() == 0)
	{
		humid[1] = humid[0];
	}

	humid[0].SetN((*this).Rules(humid[0].GetN()));
	humid[1].SetN((*this).Rules(humid[1].GetN()));

	res = R.CoG(humid, 3);

	cout << "res = " << res << endl;

	return res;
}


Humidity::~Humidity()
{

}