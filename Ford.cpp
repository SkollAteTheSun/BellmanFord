// Help.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include"pch.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "locale.h" 
#include "time.h"
#define INF 1000000000

int vopros()
{  
   /*
   Функция, определяющая способ ввода информации о графе.
   Локальные переменные: v - переменная, в которой хранится число, в зависимости от которого
   определяется способ ввода информации.
   */
	int v = 0;
	do
	{
		printf("Выбере способ ввода информации о графе \n 1 - с клавиатуры\n 2 - с файла\n");
		scanf_s("%d", &v);
		printf("\n");
	} while (v != 1 && v != 2);
	return(v);
}

void output(int CountApex, int* Result, int StartApex, int FinishApex)
{
   /*
   Функция вывода информациии.
   Входные параметры: 
   int CountApex - переменная, в которой хранится число, определяющее количество вершин в графе;
   int* Result - указатель на массив, в которм хранятся данные
   определяющие кратчайшее растояния между вершинами;
   int StartApex - переменная, которая хранит номер начальной вершины S;
   int FinishApex - переменная, которая хранит номер конечной вершины T;
   Локальные переменные: v - переменная, в которой хранится число, в зависимости от которого
   определяется дальнейшая работа программы.
   */
	int v=0;
	printf("Форд-Беллман:\n");

	if (Result[FinishApex] < INF)//Если путь существует
		printf("Минимальное расстояние между вершинами S и T = %d\n", Result[FinishApex]);
	else
		printf("Из вершины S в вершину T нет пути\n");
	printf("\n");
	
		do
		{
			printf("Выбере дальнейшее действие \n 1 - для продолжения с полученными данными \n 2 - для завершения\n");
			scanf_s("%d", &v);
			printf("\n");
		} while (v != 1 && v != 2);

		if (v == 1)
		{
			printf("Введите номер вершины S, от которой ведем отсчет: %d\n", StartApex);
			printf("Введите номер вершины T, до которой ведем отсчет: ");
			scanf_s("%d", &FinishApex);
			if (FinishApex < CountApex)//Проверяем кореектность ввода конечной вершины
			{

				output(CountApex, Result, StartApex, FinishApex);
			}
			else
			{
				printf("Ввведн неверный номер вершины\n");

			}
		}
		else
		{
			system("pause");
			exit(0);
		}

}

void Ford(int CountApex, int CountWay, int** Matrix)
{
	/*
	Функция, реализующая алгоритм Форда.
	Входные параметры: 
   int CountApex - переменная, в которой хранится число, определяющее количество вершин в графе;
   int CountApex - переменная, в которой хранится число, определяющее количество ребер в графе;
   int** Matrix - указатель на массив, в которм хранятся данные о графе, в виде матрицы смежности;
   Локальные переменные: 
int StartApex - переменная, которая хранит номер начальной вершины S;
   int FinishApex - переменная, которая хранит номер конечной вершины T;
   int *Min - указатель на массив кратчайших путей;
   int *Test - указатель на массив кратчайших путей, для сравнения с *Min
   int i, j, k - переменные, используемые для цикла с параметром.
	*/
	int *Min, *Test; 
	int StartApex, FinishApex;
	int i, j, k;
	bool Ex;
	Min = (int*)malloc(CountApex * sizeof(int));
	Test = (int*)malloc(CountApex * sizeof(int)); 

	printf("Нумерация вершин начинается с 0\n");
	printf("Введите номер вершины S, от которой ведем отсчет: ");
	scanf_s("%d", &StartApex);
	printf("Введите номер вершины T, до которой ведем отсчет: ");
	scanf_s("%d", &FinishApex);

	for (i = 0; i < CountApex; i++)
	{
		Min[i] = INF;
		Test[i] = INF;
	}

	Min[StartApex] = 0;
	Test[StartApex] = 0;
	for (k = 0; k < CountApex; k++)
	{
		for (i = 0; i < CountApex; ++i)
		{
			for (j = 0; j < CountApex; ++j)
			{
				if (Matrix[i][j] != INF) 
				{
					if (Min[j] > (Min[i] + Matrix[i][j]))
						Min[j] = Min[i] + Matrix[i][j];
					
				}
			}
		}

	}
	for (k = 0; k < CountApex - 1; ++k)//проверка на наличие цикла отрицательного веса
	{
		for (i = 0; i < CountApex; ++i)
		{
			
			for (j = 0; j < CountApex; ++j)
			{
				if (Matrix[i][j] != INF) //если вершину не посещали
				{
					if (Test[j] > (Test[i] + Matrix[i][j]))
						Test[j] = Test[i] + Matrix[i][j];
				
				}
			}
		
		}
	}
		j = 0;
	for (i = 0; i < CountApex; ++i)
	{
		if (Min[i] < Test[i])
		{
			j++; 
		}
		
	}
	if (j != 0)
	{
		printf("Mатрица содержит цикл отрицательного веса \n");
		system("pause");
		exit(0);
	}
	output(CountApex, Min, StartApex, FinishApex);
}

void File_Input(int CountApex, int CountWay, int** Mass)
{
	/*
	Функция, реализующая считывание данных о графе из файла.
	Входные параметры:
   int CountApex - переменная, в которой хранится число, определяющее количество вершин в графе;
   int CountApex - переменная, в которой хранится число, определяющее количество ребер в графе;
   int** Mass - указатель на массив, в которм хранятся данные о графе, в виде матрицы смежности;
   Локальные переменные:
   File *in - объявляем входной файл;
   int *Test - указатель на массив кратчайших путей, для сравнения с *Min;
   int i, j, k - переменные, используемые для цикла с параметром;
   bool w - переменная, определяющая считан ли файл,
   0 - не считан,
   1 - считан;
   int vid - переменная, определяющая вид графа,
   0 - ориентированный,
   1 - неориентированный;
   int otr - переменная, используеммая как счетчик отрицательных вершин;
   char filename[20] - переменная, которая хранит имя файла.
	*/
	FILE *in;
	bool w = 0;
	int i = 0, j = 0, k = 0, vid=0;
	int otr = 0;
	char filename[20];
	do
	{
		printf("Введите путь к файлу: ");
		scanf_s("%s", filename, 20);
		fopen_s(&in, filename, "r");

		if (!in)
			printf("Ошибка! Файл не прочитан \n");
		else
		{
			printf("Читаем файл!\n");
			w = 1;
		}
	} while (w == 0);

	fscanf_s(in, "%d", &CountApex);


	Mass = (int **)malloc(CountApex * sizeof(int *));
	for (int i = 0; i < CountApex; i++)
	{
		Mass[i] = (int *)malloc(CountApex * sizeof(int));
	}

	fscanf_s(in, "%d", &CountWay);

	for (i = 0; i < CountApex; i++)
	{
		for (j = 0; j < CountApex; j++)
			Mass[i][j] = INF;
	}
	Mass[0][0] = 0;

	fscanf_s(in, "%d", &vid);

	for (k = 0; k < CountWay; k++)
	{
		fscanf_s(in, "%d", &i);
		fscanf_s(in, "%d", &j);
		fscanf_s(in, "%d", &Mass[i][j]);
		if (vid == 1)//если граф неориентированный, то матрица смежности примет симметричный вид
			Mass[j][i] = Mass[i][j];
		if (vid != 0 && vid != 1)
			printf("Ошибка при определении типа графа :\n");
		if (Mass[i][j] < 0)
			otr++;
	}

	printf("Файл считан\n\n");
	if (otr != 0 && vid != 0)
	{
		printf("Граф неориентированный, матрица содержит ребра с отрицательным весом => кратчайший путь определить нельзя\n");
		system("pause");
		exit(0);
	}
	Ford(CountApex, CountWay, Mass);
}

///
void Keyboard_Input(int CountApex, int CountWay, int** Mass)
{
	/*
	Функция, реализующая считывание данных о графе с клавиатуры.
	Входные параметры:
   int CountApex - переменная, в которой хранится число, определяющее количество вершин в графе;
   int CountApex - переменная, в которой хранится число, определяющее количество ребер в графе;
   int** Mass - указатель на массив, в которм хранятся данные о графе, в виде матрицы смежности;
   Локальные переменные:
   i,j - переменные, используемые для цикла с параметром;
   n,m - переменные, считывающие номера вершин введенных с клавиатуры;
   bool w - переменная, определяющая считан ли файл,
   0 - не считан,
   1 - считан;
   int vid - переменная, определяющая вид графа,
   0 - ориентированный;
   1 - неориентированный;
   int otr - переменная, используеммая как счетчик отрицательных вершин;
	*/
	int n = 0, m = 0, j = 0, otr = 0, vid=0;
	bool  w = 0;


	printf("Введите количество вершин: ");
	scanf_s("%d", &CountApex);

	Mass = (int **)malloc(CountApex * sizeof(int *));
	for (int i = 0; i < CountApex; i++) {
		Mass[i] = (int *)malloc(CountApex * sizeof(int));
	}

	for (int i = 0; i < CountApex; i++)
	{
		for (int j = 0; j < CountApex; j++)
		{
			Mass[i][j] = INF;
		}
	}
	Mass[0][0] = 0;

	printf("Введите количество ребер: ");
	scanf_s("%d", &CountWay);
	printf("\n");

	do
	{
		printf("Выберете тип графа :\n 0 - ориентированный\n 1 - неориентированный\n");
		scanf_s("%d", &vid);
		printf("\n");
	} while (vid != 0 && vid != 1);

	printf("Нумерация вершин начинается с 0\n");
	printf("Заполните таблицу рёбер в виде : \n[номер вершины 1][номер вершины 2][расстояние между ними]\n");

	for (int i = 0; i < CountWay; i++)
	{

		scanf_s("%d", &n);
		scanf_s("%d", &m);
		scanf_s("%d", &Mass[n][m]);
		if (vid == 1)
			Mass[m][n] = Mass[n][m];
		if (Mass[n][m] < 0)
			otr++;

	}
	printf("Граф считан\n\n");
	if (otr != 0 && vid != 0)// если есть ребра с отр.весом и граф неориентированный
	{
		printf("Граф неориентированный, матрица содержит ребра с отрицательным весом => кратчайший путь определить нельзя\n");
		system("pause");
		exit(0);
	}

	
	Ford(CountApex, CountWay, Mass);
}

int main(int arg, char* argv)
{
	/*
	Функция, обеспечивающая запуск или завершение программы.
	Входные данные:
	const int argc – количество параметров командной строки;
	const char *argv[] массив строк, содержащий параметры командной строки.
	Первый элемент массива строк (argv[0]) всегда содержит строку, 
	использованную для запуска программы (либо пустую строку).
	Следующие элементы (от 1 до argc – 1) содержат параметры командной строки, если они есть.
	Элемент массива строк argv[argc] всегда должен содержать 0.
	Локальные переменные:
   int CountApex - переменная, в которой хранится число, определяющее количество вершин в графе;
   int CountApex - переменная, в которой хранится число, определяющее количество ребер в графе;
   int** Mass - указатель на массив, в которм хранятся данные о графе, в виде матрицы смежности;
   int StartApex - переменная, которая хранит номер начальной вершины S;
   int FinishApex - переменная, которая хранит номер конечной вершины T;
   int Flag - переменная, определяющая запускать или завершать программу.
	*/
	int StartApex = 0;
	int CountApex = 0;
	int CountWay = 0;
	int FinishApex = 0;
	int **Mass;
	int Flag = 1;


	setlocale(LC_ALL, "Rus");
	Mass = 0;
	while (Flag == 1)
	{
		if (Flag == 1)
		{
			if (vopros() == 1)
			{
				Keyboard_Input(CountApex, CountWay, Mass);
			}
			else
			{
				File_Input(CountApex, CountWay, Mass);
			}
		}
		printf("Выберите дальнейшее действие, нажмите \n 1 - для повторения программы\n 2 - для завершения программы\n");
		scanf_s("%d", &Flag);
		printf("\n");
	}
	system("pause");
}

