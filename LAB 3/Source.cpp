/* Решение системы линейных уравнений методом Гаусса */
/* version 1.0 (kostyl edition)*/


#include <iostream>
#include <vector>

using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

void in_matrix(vector< vector<double> >& matrix, int dim)
{

	cout << "Enter the matrix: " << endl;
	for (int i{ 0 }; i < dim; i++)
		for (int j{ 0 }; j < dim; j++)
			cin >> matrix.at(i).at(j);

	cout << "Enter the column of absolute terms: " << endl;
	for (int i{ 0 }; i < dim; i++)
		cin >> matrix.at(i).at(dim);
	cout << endl;
}

void out_matrix(vector< vector<double> > matrix)
{
	int dim = matrix.size();
	cout << "Matrix: " << endl;
	for (int i{0}; i < dim; i++) 
	{
		for (int j{ 0 }; j < dim + 1; j++)
		{
			cout << matrix.at(i).at(j) << "\t";
			if (j == dim - 1)
				cout << "|  ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<double> gauss(vector< vector<double> > matrix) 
{
	int dim = matrix.size();

	for (int i{ 0 }; i < dim; i++) 
	{
		// Поиск максимума в столбце
		double max_el{ abs(matrix.at(i).at(i)) };
		int max_row{ i };
		for (int j{ i + 1 }; j < dim; j++)
		{
			if (abs(matrix.at(j).at(i)) > max_el) 
			{
				max_el = abs(matrix.at(j).at(i));
				max_row = j;
			}
		}

		// Поменять местами максимальную и текущую строку
		for (int j{ i }; j < dim + 1; j++) 
		{
			double temp{ matrix.at(max_row).at(j) };
			matrix.at(max_row).at(j) = matrix.at(i).at(j);
			matrix.at(i).at(j) = temp;
		}

		// Приведение к треугольному виду
		for (int k{ i + 1 }; k < dim; k++)
		{
			double c{ -matrix.at(k).at(i) / matrix.at(i).at(i) };
			for (int j{ i }; j < dim + 1; j++) 
			{
				if (i == j)
					matrix.at(k).at(j) = 0;
				else 
					matrix.at(k).at(j) += c * matrix.at(i).at(j);
			}
		}
	}

	// Проверка на совместность и определнность
	for (int i{ 0 }; i < dim; i++)
	{
		bool zero_row{ true };
		for (int j{ 0 }; j < dim; j++)
		{
			if (matrix.at(i).at(j) != 0)
				zero_row = false;
		}
		if (zero_row && matrix.at(i).at(dim) != 0)
		{
			vector<double> r(dim + 1, 0);
			return r;
		}
		else if (zero_row && matrix.at(i).at(dim) == 0)
		{
			vector<double> r(dim + 1, -1);
			return r;
		}
	}


	// Решение системы для верхней треугольной матрицы
	vector<double> x(dim);
	for (int i{ dim - 1 }; i >= 0; i--)
	{
		x.at(i) = matrix.at(i).at(dim) / matrix.at(i).at(i);
		for (int j{ i - 1 }; j >= 0; j--)
			matrix.at(j).at(dim) -= matrix.at(j).at(i) * x.at(i);
	}
	return x;
}

int main()
{
	int dim;
	cout << "Enter the number of dimensions ('q' for quit): ";
	while (cin >> dim)
	{
		if (dim > 0)
		{

			vector<double> line(dim + 1, 0);
			vector< vector<double> > matrix(dim, line);

			in_matrix(matrix, dim);
			out_matrix(matrix);

			vector<double> null(dim + 1, 0);
			vector<double> minus(dim + 1, -1);

			if (gauss(matrix) != null && gauss(matrix) != minus)
			{
				cout << "Result: ";
				for (int i{ 0 }; i < dim; i++)
					cout << "x" << i + 1 << " = " << gauss(matrix).at(i) << " ";
			}
			else if (gauss(matrix) == null)
				cout << "No solutions!";
			else if (gauss(matrix) == minus)
				cout << "Infinite solutions!";

			cout << endl << endl;
		}
		cout << "Enter the number of dimensions ('q' for quit): ";
	}

	cout << "Terminating...";

	keep_window_open();

	return 0;
}