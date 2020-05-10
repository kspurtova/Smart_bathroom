#include "TheWaterReg.h"


TheWaterReg::TheWaterReg()
{

}


void TheWaterReg::TemperatureList()
{
	cout << " 1 - Very_Cold " << endl;
	cout << " 2 - Cold " << endl;
	cout << " 3 - Warm " << endl;
	cout << " 4 - Hot " << endl;
	cout << " 5 - Very_Hot " << endl;
}


void TheWaterReg::PressureList()
{
	cout << " 1 - Very_Low " << endl;
	cout << " 2 - Low " << endl;
	cout << " 3 - Normal " << endl;
	cout << " 4 - High " << endl;
	cout << " 5 - Very_High " << endl;
}


void TheWaterReg::WaterList(int count)
{
	switch (count)
	{
	case 1:
		cout << " 1 - Закрыть очень много " << endl;
		break;
	case 2:
		cout << " 2 - Закрыть много " << endl;
		break;
	case 3:
		cout << " 3 - Закрыть мало " << endl;
		break;
	case 4:
		cout << " 4 - Закрыть очень мало " << endl;
		break;
	case 5:
		cout << " 5 - Оставить " << endl;
		break;
	case 6:
		cout << " 6 - Открыть очень мало " << endl;
		break;
	case 7:
		cout << " 7 - Открыть мало " << endl;
		break;
	case 8:
		cout << " 8 - Открыть много " << endl;
		break;
	case 9:
		cout << " 9 - Открыть очень много " << endl;
		break;
	}
}


TVector<int> TheWaterReg::Rules(int tem, int press)
{
	TVector<int> res(2);
	//res[0]-HotWater, res[1]-ColdWater
	cout << "rule #" << (tem - 1) * 5 + press << endl;
	switch (tem)
	{
	case 1:
		switch (press)
		{
		case 1:
			res[0] = 9;
			res[1] = 7;
			break;
		case 2:
			res[0] = 9;
			res[1] = 6;
			break;
		case 3:
			res[0] = 7;
			res[1] = 3;
			break;
		case 4:
			res[0] = 4;
			res[1] = 2;
			break;
		case 5:
			res[0] = 4;
			res[1] = 9;
			break;
		}
		break;
	case 2:
		switch (press)
		{
		case 1:
			res[0] = 8;
			res[1] = 7;
			break;
		case 2:
			res[0] = 8;
			res[1] = 6;
			break;
		case 3:
			res[0] = 7;
			res[1] = 4;
			break;
		case 4:
			res[0] = 3;
			res[1] = 2;
			break;
		case 5:
			res[0] = 3;
			res[1] = 1;
			break;
		}
		break;
	case 3:
		switch (press)
		{
		case 1:
			res[0] = 7;
			res[1] = 7;
			break;
		case 2:
			res[0] = 6;
			res[1] = 6;
			break;
		case 3:
			res[0] = 5;
			res[1] = 5;
			break;
		case 4:
			res[0] = 4;
			res[1] = 4;
			break;
		case 5:
			res[0] = 3;
			res[1] = 3;
			break;
		}
		break;
	case 4:
		switch (press)
		{
		case 1:
			res[0] = 7;
			res[1] = 9;
			break;
		case 2:
			res[0] = 6;
			res[1] = 8;
			break;
		case 3:
			res[0] = 3;
			res[1] = 7;
			break;
		case 4:
			res[0] = 2;
			res[1] = 3;
			break;
		case 5:
			res[0] = 1;
			res[1] = 3;
			break;
		}
		break;
	case 5:
		switch (press)
		{
		case 1:
			res[0] = 7;
			res[1] = 9;
			break;
		case 2:
			res[0] = 6;
			res[1] = 6;
			break;
		case 3:
			res[0] = 3;
			res[1] = 8;
			break;
		case 4:
			res[0] = 2;
			res[1] = 4;
			break;
		case 5:
			res[0] = 2;
			res[1] = 3;
			break;
		}
		break;
	}
	(*this).WaterList(res[0]);
	(*this).WaterList(res[1]);
	return res;
}


int TheWaterReg::Line(double Val, double ras, double start, int number)
{
	double up, down, n;
	int i = number;
	up = start;
	down = start - ras;
	n = -1000;
	while (n == -1000)
	{
		if (Val > up)
		{
			up += ras;
			down += ras;
			i++;
		}
		else
			if (Val < down)
			{
				up -= ras;
				down -= ras;
				i--;
			}
			else n = up;

	}
	return i;
}


TVector<Object> TheWaterReg::Temperature(double tem)
{
	takes H;
	TVector<Object> Res(2);
	int count = (*this).Line(tem, 15, 40, 2);
	if (count < 1)
		count = 1;
	if (count > 4)
		count = 4;
	switch (count)
	{
	case 1:
		Res[0].SetV(H.Trapeze(tem, -30, 0, 10, 25, 1));
		Res[0].SetN(1);
		Res[1].SetV(H.Triangle(tem, 10, 25, 40, 1));
		Res[1].SetN(2);
		break;
	case 4:
		Res[0].SetV(H.Triangle(tem, 40, 55, 70, 1));
		Res[0].SetN(4);
		Res[1].SetV(H.Trapeze(tem, 55, 70, 80, 100, 1));
		Res[1].SetN(5);
		break;
	default:
		Res[0].SetV(H.Triangle(tem, 10 + (count - 2) * 15, 25 + (count - 2) * 15, 40 + (count - 2) * 15, 1));
		Res[0].SetN(count);
		Res[1].SetV(H.Triangle(tem, 10 + (count - 1) * 15, 25 + (count - 1) * 15, 40 + (count - 1) * 15, 1));
		Res[1].SetN(count + 1);
		break;
	}
	return Res;
}


TVector<Object> TheWaterReg::Pressure(double press)
{
	takes H;
	TVector<Object> Res(2);
	int count = (*this).Line(press, 0.75, 2, 2);
	if (count < 1)
		count = 1;
	if (count > 4)
		count = 4;
	switch (count)
	{
	case 1:
		Res[0].SetV(H.Trapeze(press, -1.5, -0.167, 0.5, 1.25, 1));
		Res[0].SetN(1);
		Res[1].SetV(H.Triangle(press, 0.5, 1.25, 2, 1));
		Res[1].SetN(2);
		break;
	case 4:
		Res[0].SetV(H.Triangle(press, 2, 2.75, 3.5, 1));
		Res[0].SetN(4);
		Res[1].SetV(H.Trapeze(press, 2.75, 3.5, 4, 5.15, 1));
		Res[1].SetN(5);
		break;
	default:
		Res[0].SetV(H.Triangle(press, 0.5 + (count - 2) * 0.75, 1.25 + (count - 2) * 0.75, 2 + (count - 2) * 0.75, 1));
		Res[0].SetN(count);
		Res[1].SetV(H.Triangle(press, 0.5 + (count - 1) * 0.75, 1.25 + (count - 1) * 0.75, 2 + (count - 1) * 0.75, 1));
		Res[1].SetN(count + 1);
		break;
	}
	return Res;
}


TVector<double> TheWaterReg::Composed(double Tem, double Press)
{
	takes H;
	TVector<Object> tem(2), press(2);
	tem = (*this).Temperature(Tem);
	press = (*this).Pressure(Press);

	TVector<double> res(2);
	TVector<int> temp1(2), temp2(2);
	double max, min;
	Object c;
	if (tem[1].GetV() > tem[0].GetV())
	{
		c = tem[1];
		tem[1] = tem[0];
		tem[0] = c;
	}

	if (press[1].GetV() > press[0].GetV())
	{
		c = press[1];
		press[1] = press[0];
		press[0] = c;
	}

	if (tem[1].GetV() == 0)
	{
		tem[1] = tem[0];
	}
	if (press[1].GetV() == 0)
	{
		press[1] = press[0];
	}

	max = H.Min(tem[0].GetV(), press[0].GetV());
	min = H.Min(tem[1].GetV(), press[1].GetV());

	temp1 = (*this).Rules(tem[0].GetN(), press[0].GetN()); //Срезаем на уровне max
	temp2 = (*this).Rules(tem[1].GetN(), press[1].GetN()); //Срезаем на уровне min

	// tempX[0] - горячая, tempX[1] - холодная
	tem[0].SetV(max);
	tem[0].SetN(temp1[0]);
	tem[1].SetV(min);
	tem[1].SetN(temp2[0]);

	press[0].SetV(max);
	press[0].SetN(temp1[1]);
	press[1].SetV(min);
	press[1].SetN(temp2[1]);

	res[0] = H.CoG(tem, 1); // Для горячей воды (Max)
	res[1] = H.CoG(press, 1); // Для холодной воды (Min)

	cout << "pHot = " << res[0] << endl;
	cout << "pCold = " << res[1] << endl;
	return res;
}


TheWaterReg::~TheWaterReg()
{

}