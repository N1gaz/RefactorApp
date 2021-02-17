#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int** init_matrix(int col_count, int row_count);
void fill_matrix_manually(int** Matrix, int col_count, int row_count);
void fill_matrix_randomly(int** Matrix, int col_count, int row_count);
void show_matrix(int** Matrix, int col_count, int row_count);
int** create_normalized_matrix(int** Source_matrix, int dimension, int col_count, int row_count);
int** create_submatrix(int** Source_matrix, int beg_col, int end_col, int beg_row, int end_row);

void main()
{
	srand(time(NULL));
	system("chcp 1251");
	cout << "Вас приветствует программа" << endl <<
		"быстрого перемножения матриц методом Штрассена\n\n";

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Ввод размеров матрицы пользователем////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int col_count1, col_count2, row_count1, row_count2;

	do
	{
		cout << "Введите размеры первой матрицы\n";
		cin >> col_count1 >> row_count1;
	} while (col_count1 <= 0 || row_count1 <= 0);
	do
	{
		cout << "Введите размеры второй матрицы\n";
		cin >> col_count2 >> row_count2;
	} while (col_count2 <= 0 || row_count2 <= 0);

	int** M1 = init_matrix(col_count1, row_count1);
	int** M2 = init_matrix(col_count2, row_count2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выбор способа заполнения и заполнение матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////

	int selector = 0;

	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> selector;
	} while (selector < 1 || selector > 2);
	switch (selector)
	{
	case 1:
		fill_matrix_manually(M1, col_count1, row_count1);
		fill_matrix_manually(M2, col_count2, row_count2);

		cout << "\nМатрица 1\n\n";
		show_matrix(M1, col_count1, row_count1);
		cout << "\nМатрица 2\n\n";
		show_matrix(M2, col_count2, row_count2);
		break;
	case 2:
		fill_matrix_randomly(M1, col_count1, row_count1);
		fill_matrix_randomly(M2, col_count2, row_count2);

		cout << "\nМатрица 1\n\n";
		show_matrix(M1, col_count1, row_count1);
		cout << "\nМатрица 2\n\n";
		show_matrix(M2, col_count2, row_count2);
		break;
	}

	///////////////////////////////////////////////////////////////////////////////
	/////////////////Приведение матриц к требуемому размеру////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int dimension = 2;

	while (dimension < col_count1 || dimension < col_count2 || dimension < row_count1 || dimension < row_count2)
		dimension *= 2;
	int** M3 = create_normalized_matrix(M1, dimension, col_count1, row_count1);
	int** M4 = create_normalized_matrix(M2, dimension, col_count2, row_count2);

	cout << "Приведенные матрицы\n";
	cout << "\nМатрица 1\n\n";
	show_matrix(M3, dimension, dimension);
	cout << "\nМатрица 2\n\n";
	show_matrix(M4, dimension, dimension);
	///////////////////////////////////////////////////////////////////////////////
	///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** mat1 = create_submatrix(M3, 0, dimension / 2, 0, dimension / 2);
	int** mat2 = create_submatrix(M3, 0, dimension / 2, dimension / 2, dimension);
	int** mat3 = create_submatrix(M3, dimension / 2, dimension, 0, dimension / 2);
	int** mat4 = create_submatrix(M3, dimension / 2, dimension, dimension / 2, dimension);
	int** mat5 = create_submatrix(M4, 0, dimension / 2, 0, dimension / 2);
	int** mat6 = create_submatrix(M4, 0, dimension / 2, dimension / 2, dimension);
	int** mat7 = create_submatrix(M4, dimension / 2, dimension, 0, dimension / 2);
	int** mat8 = create_submatrix(M4, dimension / 2, dimension, dimension / 2, dimension);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////////Создание промежуточных матриц//////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** p1 = init_matrix(dimension / 2, dimension / 2);
	int** p2 = init_matrix(dimension / 2, dimension / 2);
	int** p3 = init_matrix(dimension / 2, dimension / 2);
	int** p4 = init_matrix(dimension / 2, dimension / 2);
	int** p5 = init_matrix(dimension / 2, dimension / 2);
	int** p6 = init_matrix(dimension / 2, dimension / 2);
	int** p7 = init_matrix(dimension / 2, dimension / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////////////Вычисление значений промежуточных матриц///////////////////
	///////////////////////////////////////////////////////////////////////////////
	///TODO///Maybe///
	for (int i = 0; i < dimension / 2; i++)
	{
		for (int j = 0; j < dimension / 2; j++)
		{
			p1[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p1[i][j] += (mat1[i][z] + mat4[i][z]) * (mat5[z][j] + mat8[z][j]);
			}

			p2[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p2[i][j] += (mat3[i][z] + mat4[i][z]) * mat5[z][j];
			}

			p3[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p3[i][j] += mat1[i][z] * (mat6[z][j] - mat8[z][j]);
			}

			p4[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p4[i][j] += mat4[i][z] * (mat7[z][j] - mat5[z][j]);
			}

			p5[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p5[i][j] += (mat1[i][z] + mat2[i][z]) * mat8[z][j];
			}

			p6[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p6[i][j] += (mat3[i][z] - mat1[i][z]) * (mat5[z][j] + mat6[z][j]);
			}

			p7[i][j] = 0;
			for (int z = 0; z < dimension / 2; z++)
			{
				p7[i][j] += (mat2[i][z] - mat4[i][z]) * (mat7[z][j] + mat8[z][j]);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////Создание вспомогательных матриц/////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** mat9 = init_matrix(dimension / 2, dimension / 2);
	int** mat10 = init_matrix(dimension / 2, dimension / 2);
	int** mat11 = init_matrix(dimension / 2, dimension / 2);
	int** mat12 = init_matrix(dimension / 2, dimension / 2);

	///////////////////////////////////////////////////////////////////////////////
	////////////Подсчет значений вспомогательных матриц из промежуточных///////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < dimension / 2; i++)
	{
		for (int j = 0; j < dimension / 2; j++)
		{
			mat9[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			mat10[i][j] = p3[i][j] + p5[i][j];
			mat11[i][j] = p2[i][j] + p4[i][j];
			mat12[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Создание результирующей матрицы/////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	int** M5 = init_matrix(dimension, dimension);

	///////////////////////////////////////////////////////////////////////////////
	///////Занесение информации из вспомогательных матриц в результирующую/////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < dimension / 2; i++)
	{
		for (int j = 0; j < dimension / 2; j++)
		{
			M5[i][j] = mat9[i][j];
			M5[i][j + dimension / 2] = mat10[i][j];
			M5[i + dimension / 2][j] = mat11[i][j];
			M5[i + dimension / 2][j + dimension / 2] = mat12[i][j];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	////////////////Выравнивание границ результирующей матрицы/////////////////////
	///////////////////////////////////////////////////////////////////////////////
	///TODO///Maybe///
	int x = 0, f = 100, s = 100;
	for (int i = 0; i < dimension; i++)
	{
		x = 0;
		for (int j = 0; j < dimension; j++)
		{
			if (M5[i][j] != 0)
			{
				x++;
				f = 100;
			}
		}
		if (x == 0 && i < f)
		{
			f = i;
		}
	}
	for (int i = 0; i < dimension; i++)
	{
		x = 0;
		for (int j = 0; j < dimension; j++)
		{
			if (M5[j][i] != 0)
			{
				x++;
				s = 100;
			}
		}
		if (x == 0 && i < s)
		{
			s = i;
		}
	}

	int** M6 = new int* [f];
	for (int i = 0; i < f; i++)
	{
		M6[i] = new int[s];
		for (int j = 0; j < s; j++)
			M6[i][j] = M5[i][j];
	}

	///////////////////////////////////////////////////////////////////////////////
	///////////////////Вывод результирующей матрицы////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	cout << "\nРезультирующая матрица\n\n";
	show_matrix(M6, f, s);
	system("pause");

	///////////////////////////////////////////////////////////////////////////////
	/////////////////////Очистка динамической памяти///////////////////////////////
	///////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < col_count1; i++)
		delete[] M1[i];
	for (int i = 0; i < col_count2; i++)
		delete[] M2[i];
	for (int i = 0; i < dimension; i++)
	{
		delete[] M3[i];
		delete[] M4[i];
		delete[] M5[i];
	}
	for (int i = 0; i < f; i++)
		delete[] M6[i];
	for (int i = 0; i < dimension / 2; i++)
	{
		delete[] mat1[i];
		delete[] mat2[i];
		delete[] mat3[i];
		delete[] mat4[i];
		delete[] mat5[i];
		delete[] mat6[i];
		delete[] mat7[i];
		delete[] mat8[i];
		delete[] mat9[i];
		delete[] mat10[i];
		delete[] mat11[i];
		delete[] mat12[i];
		delete[] p1[i];
		delete[] p2[i];
		delete[] p3[i];
		delete[] p4[i];
		delete[] p5[i];
		delete[] p6[i];
		delete[] p7[i];
	}
	delete[] M1, M2, M3, M4, M5, M6;
	delete[] mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12;
	delete[] p1, p2, p3, p4, p5, p6, p7;
}

int** init_matrix(int col_count, int row_count)
{
	int** Result = new int* [col_count];

	for (int i = 0; i < col_count; i++)
	{
		Result[i] = new int[row_count];
	}

	return Result;
}

void fill_matrix_manually(int** Matrix, int col_count, int row_count)
{
	for (int i = 0; i < col_count; i++)
	{
		for (int j = 0; j < row_count; j++)
		{
			cin >> Matrix[i][j];
		}
	}
}

void fill_matrix_randomly(int** Matrix, int col_count, int row_count)
{
	for (int i = 0; i < col_count; i++)
	{
		for (int j = 0; j < row_count; j++)
		{
			Matrix[i][j] = rand() % 10;
		}
	}
}

void show_matrix(int** Matrix, int col_count, int row_count)
{
	for (int i = 0; i < col_count; i++)
	{
		for (int j = 0; j < row_count; j++)
		{
			cout << Matrix[i][j] << "\t";
		}
		cout << endl;
	}
}

int** create_normalized_matrix(int** Source_matrix, int dimension, int col_count, int row_count)
{
	int** Result = new int* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		Result[i] = new int[dimension];
		for (int j = 0; j < dimension; j++)
		{
			Result[i][j] = 0;
		}
	}

	for (int i = 0; i < col_count; i++)
	{
		for (int j = 0; j < row_count; j++)
		{
			Result[i][j] = Source_matrix[i][j];
		}
	}

	return Result;
}

int** create_submatrix(int** Source_matrix, int beg_col, int end_col, int beg_row, int end_row)
{
	int** Result = new int* [end_col - beg_col];
	for (int i = 0; i < (end_col - beg_col); i++)
	{
		Result[i] = new int[end_row - beg_row];
	}

	for (int i = beg_col; i < end_col; i++)
	{
		for (int j = beg_row; j < end_row; j++)
		{
			Result[i - beg_col][j - beg_row] = Source_matrix[i][j];
		}
	}

	return Result;
}
