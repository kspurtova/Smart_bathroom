#include "TheAirReg.h"


TheAirReg::TheAirReg()
{

}


void TheAirReg::HeatingSystem(int count)
{
	switch (count)
	{
	case 1:
		cout << "Нагреть сильно" << endl;
		break;
	case 2:
		cout << "Нагреть" << endl;
		break;
	case 3:
		cout << "Подогреть" << endl;
		break;
	case 4:
		cout << "Оставить" << endl;
		break;
	case 5:
		cout << "Остудить" << endl;
		break;
	case 6:
		cout << "Охладить" << endl;
		break;
	case 7:
		cout << "Охладить сильно" << endl;
		break;
	}
}


int TheAirReg::Rules(int AirT)
{
	int res;
	cout << "rule #" << AirT << endl;
	switch (AirT)
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
	case 4:
		res = 4;
		break;
	case 5:
		res = 5;
		break;
	case 6:
		res = 6;
		break;
	case 7:
		res = 7;
		break;
	}
	(*this).HeatingSystem(res);
	return res;
}


TVector<double> TheAirReg::Line(int count)
{
	TVector<double> res(2);
	// [0] - min, [1] - max
	switch (count)
	{
	case 1:
		res[0] = -1;
		res[1] = 20;
		break;
	case 2:
		res[0] = 20;
		res[1] = 30;
		break;
	case 3:
		res[0] = 30;
		res[1] = 35;
		break;
	case 4:
		res[0] = 35;
		res[1] = 40;
		break;
	case 5:
		res[0] = 40;
		res[1] = 50;
		break;
	case 6:
		res[0] = 50;
		res[1] = 76;
		break;
	}
	return res;
}


int TheAirReg::LineUp(double count)
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


TVector<Object> TheAirReg::AirTemp(double AirT)
{
	takes R;
	int count = (*this).LineUp(AirT);
	TVector<Object> res(2);
	switch (count)
	{
	case 1:
		res[0].SetV(R.Trapeze(AirT, -1, 0, 10, 20, 1));
		res[0].SetN(1);
		res[1].SetV(R.Triangle(AirT, 10, 20, 30, 1));
		res[1].SetN(2);
		break;
	case 2:
		res[0].SetV(R.Triangle(AirT, 10, 20, 30, 1));
		res[0].SetN(2);
		res[1].SetV(R.Triangle(AirT, 20, 30, 35, 1));
		res[1].SetN(3);
		break;
	case 3:
		res[0].SetV(R.Triangle(AirT, 20, 30, 35, 1));
		res[0].SetN(3);
		res[1].SetV(R.Triangle(AirT, 30, 35, 40, 1));
		res[1].SetN(4);
		break;
	case 4:
		res[0].SetV(R.Triangle(AirT, 30, 35, 40, 1));
		res[0].SetN(4);
		res[1].SetV(R.Triangle(AirT, 35, 40, 50, 1));
		res[1].SetN(5);
		break;
	case 5:
		res[0].SetV(R.Triangle(AirT, 35, 40, 50, 1));
		res[0].SetN(5);
		res[1].SetV(R.Triangle(AirT, 40, 50, 60, 1));
		res[1].SetN(6);
		break;
	case 6:
		res[0].SetV(R.Triangle(AirT, 40, 50, 60, 1));
		res[0].SetN(6);
		res[1].SetV(R.Trapeze(AirT, 50, 60, 70, 76, 1));
		res[1].SetN(7);
		break;
	}
	return res;
}


double TheAirReg::Composed(double AirT)
{
	takes R;
	double res;
	TVector<Object> Air(2);
	Object c;

	Air = (*this).AirTemp(AirT);

	if (Air[1].GetV() > Air[0].GetV())
	{
		c = Air[1];
		Air[1] = Air[0];
		Air[0] = c;
	}

	// [0] - max, [1] - min

	if (Air[1].GetV() == 0)
	{
		Air[1] = Air[0];
	}

	Air[0].SetN((*this).Rules(Air[0].GetN()));
	Air[1].SetN((*this).Rules(Air[1].GetN()));

	res = R.CoG(Air, 4);

	cout << "res = " << res << endl;

	return res;
}


TheAirReg::~TheAirReg()
{

}