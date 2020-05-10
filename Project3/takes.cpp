#include "takes.h"


takes::takes()
{

}


double takes::Triangle(double x, double a, double b, double c, double up)
{
	double temp;
	if ((x >= a) && (x <= b))
	{
		temp = up - ((b - x) / (b - a));
	}
	else
		if ((x >= b) && (x <= c))
		{
			temp = up - ((x - b) / (c - b));
		}
		else temp = 0;
	return temp;
}


double takes::Trapeze(double x, double a, double b, double c, double d, double up)
{
	double temp;
	if ((x >= a) && (x <= b))
	{
		temp = up - ((b - x) / (b - a));
	}
	else
		if ((x >= b) && (x <= c))
		{
			temp = up;
		}
		else
			if ((x >= c) && (x <= d))
			{
				temp = up - ((x - c) / (d - c));
			}
			else temp = 0;
	return temp;
}


double takes::Min(double a, double b)
{
	if (a > b)
		return b;
	else return a;
}


double takes::CoG(TVector<Object> cut, int Special)
{
	takes H;
	//[0] - max уровень, [1] - min уровень
	double res = 0, area = 0, help = 0;
	TVector<double> a(2), b(2), c(2), d(2), kas(4), a1(2), b1(2), c1(2), d1(2);
	double max = cut[0].GetV(), min = cut[1].GetV();

	for (int i = 0; i < 2; i++)
	{
		kas = Line(Special, cut[i].GetN());
		//cout << "kas[0] = " << kas[0] << endl;
		res = (kas[3] - kas[2]) / (kas[1] - kas[0]);
		kas[2] = (kas[3] - kas[0]) * (1 - cut[i].GetV());
		area = (kas[3] - kas[0]) - kas[2];
		a[i] = kas[0];
		d[i] = kas[3];
		c[i] = d[i] - area * res / (res + 1);
		b[i] = c[i] - kas[2];
		if ((kas[1] - kas[0]) == 0)
		{
			a[i] = kas[0];
			b[i] = kas[0];
			d[i] = kas[3];
			c[i] = d[i] - kas[2];
		}
		a1[i] = a[i];
		b1[i] = b[i];
		c1[i] = c[i];
		d1[i] = d[i];
	}

	if ((max == min) && ((cut[0].GetN() - cut[1].GetN()) == -1))
	{
		res = (c[0] + b[1]) / 2;
		if ((*this).Trapeze(res, a[1], b[1], c[1], d[1], min) == min)
		{
			c[0] = c[1];
			d[0] = d[1];
			a[1] = 0;
			b[1] = 0;
			c[1] = 0;
			d[1] = 0;
		}
		else
		{
			d1[0] = (c[0] * (b[1] - a[1]) + b[1] * (d[0] - c[0])) / (d[0] - c[0] + b[1] - a[1]);
			a1[1] = d1[0];
		}
	}

	if ((max == min) && ((cut[0].GetN() - cut[1].GetN()) == 1))
	{
		res = (c[1] + b[0]) / 2;
		if ((*this).Trapeze(res, a[1], b[1], c[1], d[1], min) == min)
		{
			a[0] = a[1];
			b[0] = b[1];
			a[1] = 0;
			b[1] = 0;
			c[1] = 0;
			d[1] = 0;
		}
		else
		{
			a1[0] = (b[0] * (d[1] - c[1]) + c[1] * (b[0] - a[0])) / (b[0] - a[0] + d[1] - c[1]);
			d1[1] = a1[0];
		}
	}

	if (max != min)
	{
		if ((cut[0].GetN() - cut[1].GetN()) == 1)
		{
			a1[0] = b[0] + (min - max) * (b[0] - a[0]);
			if ((*this).Trapeze(a1[0], a[1], b[1], c[1], d[1], min) == min)
			{
				c1[1] = a1[0];
				d1[1] = a1[0];
			}
			else
			{
				a1[0] = ((min - max) * (d[1] - c[1]) * (b[0] - a[0]) + b[0] * (d[1] - c[1]) + c[1] * (b[0] - a[0])) / (b[0] - a[0] + d[1] - c[1]);
				d1[1] = a1[0];
			}
		}
		if ((cut[0].GetN() - cut[1].GetN()) == -1)
		{
			d1[0] = (max - min) * (d[0] - c[0]) + c[0];
			if ((*this).Trapeze(d1[0], a[1], b[1], c[1], d[1], min) == min)
			{
				a1[1] = d1[0];
				b1[1] = d1[0];
			}
			else
			{
				d1[0] = ((max - min) * (b[1] - a[1]) * (d[0] - c[0]) + c[0] * (b[1] - a[1]) + b[1] * (d[0] - c[0])) / (d[0] - c[0] + b[1] - a[1]);
				a1[1] = d1[0];
			}

		}
	}

	if ((cut[0].GetN() - cut[1].GetN()) == 0)
	{
		a[1] = 0;
		b[1] = 0;
		c[1] = 0;
		d[1] = 0;
	}

	res = 0;
	area = 0;

	for (int i = 0; i < 2; i++)
	{
		max = cut[i].GetV();

		res += H.Integral(a[i], b[i], c[i], d[i], a1[i], b1[i], c1[i], d1[i], max);
		area += H.Area(a[i], b[i], c[i], d[i], a1[i], b1[i], c1[i], d1[i], max);
	}

	res = res / area;

	return res;
}


double takes::Integral(double a, double b, double c, double d, double a1, double b1, double c1, double d1, double up)
{
	double res;
	if (((b - a) != 0) && ((d - c) != 0))
	{
		res = ((up - b / (b - a)) / 2) * (pow(b1, 2) - pow(a1, 2)) + (pow(b1, 3) - pow(a1, 3)) / (3 * (b - a));
		res += (up / 2) * (pow(c1, 2) - pow(b1, 2));
		res += ((up + c / (d - c)) / 2) * (pow(d1, 2) - pow(c1, 2)) + (pow(c1, 3) - pow(d1, 3)) / (3 * (d - c));
	}
	else
		if (((b - a) == 0) && ((d - c) != 0))
		{
			res = (up / 2) * (pow(c1, 2) - pow(b1, 2));
			res += ((up + c / (d - c)) / 2) * (pow(d1, 2) - pow(c1, 2)) + (pow(c1, 3) - pow(d1, 3)) / (3 * (d - c));
		}
		else
			if (((d - c) == 0) && ((b - a) != 0))
			{
				res = ((up - b / (b - a)) / 2) * (pow(b1, 2) - pow(a1, 2)) + (pow(b1, 3) - pow(a1, 3)) / (3 * (b - a));
				res += (up / 2) * (pow(c1, 2) - pow(b1, 2));
			}
			else {
				res = 0;
			}
	return res;
}


double takes::Area(double a, double b, double c, double d, double a1, double b1, double c1, double d1, double up)
{
	double res;
	if (((b - a) != 0) && ((d - c) != 0))
	{
		res = (up - b / (b - a)) * (b1 - a1) + (pow(b1, 2) - pow(a1, 2)) / (2 * (b - a));
		res += up * (c1 - b1);
		res += (up + c / (d - c)) * (d1 - c1) + (pow(c1, 2) - pow(d1, 2)) / (2 * (d - c));
	}
	else
		if (((b - a) == 0) && ((d - c) != 0))
		{
			res = up * (c1 - b1);
			res += (up + c / (d - c)) * (d1 - c1) + (pow(c1, 2) - pow(d1, 2)) / (2 * (d - c));
		}
		else
			if (((d - c) == 0) && ((b - a) != 0))
			{
				res = (up - b / (b - a)) * (b1 - a1) + (pow(b1, 2) - pow(a1, 2)) / (2 * (b - a));
				res += up * (c1 - b1);
			}
			else {
				res = 0;
			}
	return res;
}


TVector<double> takes::Line(int Special, int count)
{
	TVector<double> res(4);
	//res[0] - a, res[1] - b, res[2] - c, res[3] - d
	// 1 - Регулятор температуры воды, 2 - Регулятор жидкости
	// 3 - Регулятор влажности, 4 - Регулятор температуры воздуха 
	switch (Special)
	{
	case 1:
		res[0] = 0 + 0.4 * (count - 1);
		res[1] = 0.4 + 0.4 * (count - 1);
		res[2] = 0.4 + 0.4 * (count - 1);
		res[3] = 0.8 + 0.4 * (count - 1);
		break;
	case 2:
		switch (count)
		{
		case 1:
			res[0] = 0;
			res[1] = 0;
			res[2] = 0.2;
			res[3] = 0.3;
			break;
		case 2:
			res[0] = 0.15;
			res[1] = 0.25;
			res[2] = 0.35;
			res[3] = 0.45;
			break;
		case 3:
			res[0] = 0.3;
			res[1] = 0.4;
			res[2] = 0.45;
			res[3] = 0.45;
			break;
		}
		break;
	case 3:
		switch (count)
		{
		case 1:
			res[0] = -50;
			res[1] = -40;
			res[2] = -40;
			res[3] = 0;
			break;
		case 2:
			res[0] = -10;
			res[1] = 0;
			res[2] = 0;
			res[3] = 10;
			break;
		case 3:
			res[0] = 0;
			res[1] = 40;
			res[2] = 40;
			res[3] = 50;
			break;
		}
		break;
	case 4:
		switch (count)
		{
		case 1:
			res[0] = -40;
			res[1] = -25;
			res[2] = -25;
			res[3] = -15;
			break;
		case 2:
			res[0] = -25;
			res[1] = -10;
			res[2] = -10;
			res[3] = -5;
			break;
		case 3:
			res[0] = -15;
			res[1] = -5;
			res[2] = -5;
			res[3] = 0;
			break;
		case 4:
			res[0] = -5;
			res[1] = 0;
			res[2] = 0;
			res[3] = 5;
			break;
		case 5:
			res[0] = 0;
			res[1] = 5;
			res[2] = 5;
			res[3] = 15;
			break;
		case 6:
			res[0] = 5;
			res[1] = 15;
			res[2] = 15;
			res[3] = 25;
			break;
		case 7:
			res[0] = 15;
			res[1] = 25;
			res[2] = 25;
			res[3] = 40;
			break;
		}
		break;
	}
	return res;
}


takes::~takes()
{

}