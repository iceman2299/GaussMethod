#include <iostream>
#include <clocale>
#include <iomanip>
#include <algorithm>
using namespace std;


int col, row; //число строк и столбцов для ввода

//Блок используемых функций:

//Функция инициализации матрицы
double** matrix()
{
	int colzn = col + 1;
	double** a;
	a = new double* [colzn];
	for (int i = 0; i < colzn; i++)
	{
		a[i] = new double[row];
	}
	return a;
};

//Функция инициализации значений
double* xses()
{
	double* x;
	x = new double[row];
	return x;
}

//Функция ввода матрицы с клавиатуры
void inputK(double** a)
{
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			cout << "Введите \x1b[32m" << j + 1 << "-e \x1b[0mчисло \x1b[32m" << i + 1 << "-го \x1b[0mстолбца\n";
			cin >> a[i][j];
		}
		cout << "Введите значение \x1b[36m" << j + 1 << "-й \x1b[0mстроки\n";
		cin >> a[col][j];
	}
}

//Функция ввода иксов
void importX(double** a, double* x)
{
	for (int j = 0; j < row; j++)
	{
		x[j] = a[col][j];
	}
}
//Функция вывода матрицы на экран
void moutputS(double** a)
{
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < col; i++)
		{
			cout << setw(15) << a[i][j] << " ";
		}
		cout << setw(15) << "|" << a[col][j];
		cout << "\n";
	}
}

//Функция вывода значений на экран
void xoutputS(double* x)
{
	for (int j = 0; j < row; j++)
	{
		cout << "x" << j + 1 << " = " << x[j];
		cout << "\n";
	}
}

//Функция прямого хода метода гаусса
int strway(double** a)
{
	double koef=1;
	int k = min(col, row);
	for (int j = 0; j < k; j++)
	{
		koef = a[j][j];//Коэффициент деления строки
		for (int i = 0; i < col+1; i++)
		{
			if (a[j][j] != 0)
			{
				a[i][j] = (a[i][j] / koef) + 0.0;
			}
			else
			{
				return 1;
			}
		}
		for (int l = j + 1; l < row; l++)
		{
			double koef2 = a[j][l];//Коэффициент вычитания строки из нижних для неё
			for (int m = 0; m < col+1; m++)
			{
				a[m][l] = (a[m][l] - (a[m][j] * koef2));
			}
		}
	}
	for (int j = k-1; j >= 0; j--)
	{
		for (int l = j-1 ; l >= 0; l--)
		{
			double koef3 = a[j][l];//Коэффициент вычитания строки из верхних для неё
			for (int m = col; m >= 0; m--)
			{
				a[m][l] = (a[m][l] - (a[m][j] * koef3));
			}
		}
	}
	return 0;
}

//Функция обратного хода метода гаусса
int bckway(double* x, double** b)
{
	for (int j = 0; j < row; j++)
	{
		double bufsum = 0;
		for (int i = 0; i < col; i++)
		{
			bufsum = bufsum + (x[i] * b[i][j]);
		}
		//if (fabs(bufsum - b[col][j]) > 0.001)
		if (bufsum - b[col][j] != 0)
		{
			return 4;
		}
	}
	return 0;
}

//Функция копирования матриц
double** matrixcpy(double** a)
{
	double** tempmatr = matrix();
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i <= col; i++)
		{
			tempmatr[i][j] = a[i][j];
		}
	}
	return tempmatr;
}

//Функция проверки на несовместность и параметричность
int checkreal(double** a)
{
	if (col > row)
	{
		for (int j = 0; j < row; j++)
		{
			for (int i = 0; i < col; i++)
			{
				if (i != j && a[i][j] != 0 && a[col][j]!=0)
				{
					return 2;
				}
			}
		}
	}
	if (row > col)
	{
		for (int j = 0; j < row; j++)
		{
			for (int i = 0; i < col; i++)
			{
				double checkingsum = 0;
				if (i != j)
				{
					checkingsum = checkingsum + a[i][j];
					if (checkingsum == 0 && a[i][j] == 0 && a[col][j] != 0)
					{
						return 3;
					}
				}
				
			}
		}
	}
	return 0;
}


//Конец блока функций



int main()
{
	setlocale(LC_ALL, "RUS");
	cout << "\x1b[1;36mПрограмма вычисления неизвестных в системе линейных алгебраических уравнений методом гаусса.\x1b[0m\n";
	cout << "\x1b[1;32mВведите количество столбцов матрицы коэффициентов\x1b[0m\n";
	cin >> col;
	cout << "\x1b[1;32mВведите количество строк матрицы коэффициентов\x1b[0m\n";
	cin >> row;
	double** a = matrix();
	inputK(a);//Заполняем матрицу числами
	double** b = matrixcpy(a);//Копия оригинальной матрицы, потом пригодится
	system("cls");
	cout << "Исходная матрица:\n";
	moutputS(a);
	int kod = strway(a);
	if (kod == 1)
	{
		system("cls");
		cerr << "Во время преобразований на главной диагонали найден ноль, я такого не умею.\n";
		return 1;
	}
	cout << "Итоговая матрица после преобразований:\n";
	moutputS(a);
	double* x = xses();
	importX(a, x);
	kod = checkreal(a);
	switch (kod)
	{
	case 2:
	{
		cerr << "Неизвестные данной системы задаются параметрически, считай сам.\n";
		return 0;
	}
	case 3:
	{
		cerr << "Система несовместна.\n";
		return 0;
	}
	}

	free(a);
	kod = bckway(x, b);
	switch (kod)
	{
	case 4:
	{
		cerr << "Ошибка вычисления программы.\n";
		return 0;
	}
	case 0:
	{
		cout << "Неизвестные данной системы уравнений равны:\n";
		xoutputS(x);
	}
	}
}//Конец программы
