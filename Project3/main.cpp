#include <iostream>
#include <conio.h>
#include "TheWaterReg.h"
#include "TheAirReg.h"
#include "Humidity.h"
#include "LiquidL.h"
#include "TMatrix.h"

using namespace std;

int main()
{
	int res;
	double tem, press, AirT, Hum, Lev, Expend;
	TVector<double> result;
	TheWaterReg Compl1;
	TheAirReg Compl2;
	Humidity Compl3;
	LiquidL Compl4;

	system("chcp 1251");
	system("cls");

	do
	{
		cout << "������� ����������� ����" << endl;
		cin >> tem;
	} while ((tem > 80) || (tem < 0));
	do
	{
		cout << "������� �������� ����" << endl;
		cin >> press;
	} while ((press > 4) || (press < 0));
	do
	{
		cout << "������� ���������" << endl;
		cin >> Hum;
	} while ((Hum < 10) || (Hum > 90));
	do
	{
		cout << "������� ����������� �������" << endl;
		cin >> AirT;
	} while ((AirT < 0) || (AirT > 60));
	do
	{
		cout << "������� ������ ����" << endl;
		cin >> Expend;
	} while ((Expend < 0) || (Expend > 0.45));
	do
	{
		cout << "������� ������� ����" << endl;
		cin >> Lev;
	} while ((Lev < 0) || (Lev > 50));

	while (!_kbhit())
	{
		cout << "---------------------- \n";
		result = Compl1.Composed(tem, press);
		// [0] - �������, [1] - ��������
		tem = (10 * result[1] + 70 * result[0]) / (result[1] + result[0]);
		res = (int)tem;
		cout << " ����������� ���� = " << res << endl;
		press = result[0] + result[1];
		if ((tem > 55) || (tem < 25))
		{
			cout << "1234ERROR" << endl;
			break;
		}
		if (press > 2.5)
			press /= 2;
		do
		{
			tem += rand() % 35 - 10;
		} while ((tem > 80) || (tem < 0));
		do
		{
			press += rand() % 1 - 0.2;
		} while ((press > 4) || (press < 0));

		cout << "---------------------- \n";
		res = Hum - (int)Compl3.Composed(Hum);
		cout << "��������� = " << res << endl;
		Hum = res;
		if ((Hum > 70) || (Hum < 40))
		{
			cout << "1234ERROR" << endl;
			break;
		}
		do
		{
			Hum = rand() % 30 + 40;
		} while ((Hum < 10) || (Hum > 90));


		cout << "---------------------- \n";
		res = AirT - Compl2.Composed(AirT);
		cout << " ����������� ������� = " << res << endl;
		AirT = res;
		if ((AirT > 40) || (AirT < 30))
		{
			cout << "1234ERROR" << endl;
			break;
		}
		do
		{
			AirT = rand() % 50 + 10;
			cout << "AirT = " << AirT << endl;
		} while ((AirT < 0) || (AirT > 60));


		cout << "---------------------- \n";
		Expend = Compl4.Composed(Lev, Expend);
		cout << "����������� ������ ���� = " << Expend << endl;
		if ((Expend > 0.45) || (Expend < 0.15))
		{
			cout << "1234ERROR" << endl;
			break;
		}
		do
		{
			Expend = rand() % 1 + 0.45;
		} while ((Expend < 0) || (Expend > 0.45));
		do
		{
			Lev = rand() % 20 - 5;
		} while ((Lev < 0) || (Lev > 50));
	}
	system("pause");
	return 0;
}