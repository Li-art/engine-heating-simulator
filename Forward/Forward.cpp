#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
	setlocale(LC_CTYPE, "rus");

	class Test 
	{
	public:
		float tempDv;
		int time;
		float getTime()
		{ 
			cout << "Время: " << time << " сек.\n" << "Температура двигателя: " << tempDv << " С\n"; 
			return 0;
		}
		int getTimeO()
		{
			cout << "\nДвигатель остановлен из-за перегрева.\n" << "Время остановки: " << time << " сек.\n";
			return 0;
		}
	};

	float temp;
	cout << "Для тестирования двигателя введите температуру окружающей среды.\n\n";
	cin >> temp;
	cout << "\n";

	ifstream data;
	data.open("data.txt"); //Файл с данными находится в папке проекта

	if (data.fail())
	{
		cout << "Файл с исходными данными не найден.\n";
	}

	float inerc, tempPer, Hm, Hv, C;
	data >> inerc >> tempPer >> Hm >> Hv >> C;

	data.close();

	float M[6] = { 20, 75, 100, 105, 75, 0 };
	float V[6] = { 0, 75, 150, 200, 250, 300 };

	Test obj;
	obj.tempDv = temp;
	obj.time = 0;

	if (obj.tempDv < tempPer)
	{
		for (float k = M[0]; k < M[1]; k += M[0] / inerc) //начало работы до крутящего момента = 75
		{
			obj.time++;
			float Vm = M[0] * Hm + V[0] * Hv;
			float Vc = C * (temp - obj.tempDv);
			obj.tempDv += Vm - Vc;
			obj.getTime();
			if (obj.tempDv > tempPer)
			{
				obj.getTimeO();
				return 0;
			}
		}

		for (float j = M[1]; j < M[2]; j += M[1] / inerc) //крутящий момент с 75 до 100
		{
			obj.time++;
			float Vm = M[1] * Hm + V[1] * Hv;
			float Vc = C * (temp - obj.tempDv);
			obj.tempDv += Vm - Vc;
			obj.getTime();
			if (obj.tempDv > tempPer)
			{
				obj.getTimeO();
				return 0;
			}
		}

		for (float i = M[2]; i < M[3]; i += M[2] / inerc) //крутящий момент со 100 до 105
		{
			obj.time++;
			float Vm = M[2] * Hm + V[2] * Hv;
			float Vc = C * (temp - obj.tempDv);
			obj.tempDv += Vm - Vc;
			obj.getTime();
			if (obj.tempDv > tempPer)
			{
				obj.getTimeO();
				return 0;
			}
		}

		for (float i = M[3]; i > M[4]; i -= M[3] / inerc) //крутящий момент со 105 до 75
		{
			obj.time++;
			float Vm = M[3] * Hm + V[3] * Hv;
			float Vc = C * (temp - obj.tempDv);
			obj.tempDv += Vm - Vc;
			obj.getTime();
			if (obj.tempDv > tempPer)
			{
				obj.getTimeO();
				return 0;
			}
		}

		for (float i = M[4]; i > M[5]; i -= M[4] / inerc) //крутящий момент с 75 до 0
		{
			obj.time++;
			float Vm = M[4] * Hm + V[4] * Hv;
			float Vc = C * (temp - obj.tempDv);
			obj.tempDv += Vm - Vc;
			obj.getTime();
			if (obj.tempDv > tempPer)
			{
				obj.getTimeO();
				return 0;
			}
		}

		for (float i = M[5]; i == M[5]; i = M[5]) //крутящий момент в конечной точке кусочно-линейной зависимости
		{
			obj.time++;
			float Vm = M[5] * Hm + V[5] * Hv;
			float Vc = C * (temp - obj.tempDv);
			obj.tempDv += Vm - Vc;
			obj.getTime();
			if (obj.tempDv > tempPer)
			{
				obj.getTimeO();
				return 0;
			}
		}

		if (obj.tempDv < tempPer)
		{
			cout << "\nДвигатель не перегрелся.\n";
		}
	}
	else
	{
		cout << "Введены некорректные данные, попробуйте еще раз.\n";
	}
}
