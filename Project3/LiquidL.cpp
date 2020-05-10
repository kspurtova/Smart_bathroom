#include "LiquidL.h"


LiquidL::LiquidL()
{

}


void LiquidL::Inflow(int count)
{
	switch (count)
	{
	case 1:
		cout << "Малый приток" << endl;
		break;
	case 2:
		cout << "Средний приток" << endl;
		break;
	case 3:
		cout << "Большой приток" << endl;
		break;
	}
}


int LiquidL::Rules(int Expend, int Level)
{
	int res;
	cout << "rule #" << (Level - 1) * 3 + (4 - Expend) << endl;
	switch (Level)
	{
	case 1:
		switch (Expend)
		{
		case 3:
			res = 3;
			break;
		case 2:
			res = 3;
			break;
		case 1:
			res = 2;
			break;
		}
		break;
	case 2:
		switch (Level)
		{
		case 3:
			res = 3;
			break;
		case 2:
			res = 2;
			break;
		case 1:
			res = 2;
			break;
		}
		break;
	case 3:
		switch (Level)
		{
		case 3:
			res = 2;
			break;
		case 2:
			res = 1;
			break;
		case 1:
			res = 1;
			break;
		}
		break;
	}
	(*this).Inflow(res);
	return res;
}


TVector<double> LiquidL::Line(int LineNumber, int count)
{
	TVector<double> res(2);
	//res[0] - min, res[1] - max
	// 1 - Расход воды, 2 - Уровень воды
	switch (LineNumber)
	{
	case 1:
		switch (count)
		{
		case 1:
			res[0] = -1;
			res[1] = 0.3;
			break;
		case 2:
			res[0] = 0.3;
			res[1] = 0.5;
			break;
		}
		break;
	case 2:
		switch (count)
		{
		case 1:
			res[0] = -5.556;
			res[1] = 33.33;
			break;
		case 2:
			res[0] = 33.33;
			res[1] = 61.11;
			break;
		}
		break;
	}
	return res;
}


int LiquidL::LineUp(int LineNumber, double count)
{
	int i = 1;
	TVector<double> mul(2);
	while (i < 10)
	{
		mul = (*this).Line(LineNumber, i);
		if ((count >= mul[0]) && (count <= mul[1]))
			break;
		i++;
	}
	return i;
}


TVector<Object> LiquidL::LevelW(double lev)
{
	takes S;
	TVector<Object> res(2);
	int count = LineUp(2, lev);
	switch (count)
	{
	case 1:
		res[0].SetV(S.Trapeze(lev, -5.556, 0, 11.11, 22.22, 1));
		res[0].SetN(1);
		res[1].SetV(S.Trapeze(lev, 11.11, 22.22, 33.33, 44.44, 1));
		res[1].SetN(2);
		break;
	case 2:
		res[0].SetV(S.Trapeze(lev, 11.11, 22.22, 33.33, 44.44, 1));
		res[0].SetN(2);
		res[1].SetV(S.Trapeze(lev, 33.33, 44.44, 55.56, 61.11, 1));
		res[1].SetN(3);
		break;
	}
	return res;
}


TVector<Object> LiquidL::ExpenditureW(double exp)
{
	takes S;
	TVector<Object> res(2);
	int count = LineUp(1, exp);
	switch (count)
	{
	case 1:
		res[0].SetV(S.Trapeze(exp, -1, 0, 0.2, 0.3, 1));
		res[0].SetN(1);
		res[1].SetV(S.Trapeze(exp, 0.2, 0.25, 0.35, 0.4, 1));
		res[1].SetN(2);
		break;
	case 2:
		res[0].SetV(S.Trapeze(exp, 0.2, 0.25, 0.35, 0.4, 1));
		res[0].SetN(2);
		res[1].SetV(S.Trapeze(exp, 0.3, 0.4, 0.45, 0.5, 1));
		res[1].SetN(3);
		break;
	}
	return res;
}


double LiquidL::Composed(double Level, double Expend)
{
	takes S;
	double res;
	TVector<Object> lev(2), exp(2);
	double max, min;
	int rule1, rule2;
	Object c;

	lev = (*this).LevelW(Level);
	exp = (*this).ExpenditureW(Expend);

	if (lev[1].GetV() > lev[0].GetV())
	{
		c = lev[1];
		lev[1] = lev[0];
		lev[0] = c;
	}

	if (exp[1].GetV() > exp[0].GetV())
	{
		c = exp[1];
		exp[1] = exp[0];
		exp[0] = c;
	}

	if (lev[1].GetV() == 0)
	{
		lev[1] = lev[0];
	}
	if (exp[1].GetV() == 0)
	{
		exp[1] = exp[0];
	}

	max = S.Min(lev[0].GetV(), exp[0].GetV());
	min = S.Min(lev[1].GetV(), exp[1].GetV());

	rule1 = (*this).Rules(exp[0].GetN(), lev[0].GetN());
	rule2 = (*this).Rules(exp[1].GetN(), lev[1].GetN());

	exp[0].SetV(max);
	exp[0].SetN(rule1);
	exp[1].SetV(min);
	exp[1].SetN(rule2);

	res = S.CoG(exp, 2);

	return res;
}


LiquidL::~LiquidL()
{

}