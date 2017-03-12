/* Разложение синуса */
/* version 1.0 */


#include <iostream>

using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

double iterative_sin(double e, double x, int& i)
{
	double sum{ 0 };
	double term{ x };

	do
	{
		sum += term;
		term *= -x * x / ((2 * i) * (2 * i + 1));
		i++;
	} while (abs(sin(x) - sum) >= e);

	return sum;
}

int main()
{
	double e;
	double x;
	cout << "Enter the accuracy ('q' for quit): ";
	while (cin >> e)
	{
		if (e > 0 && e < 1)
		{
			cout << "Enter x (from -6.28 to 6.28): ";
			if (cin >> x)
			{
				if (x >= -6.28 && x <= 6.28)
				{
					int i{ 1 };

					cout << "Sin(x) = " << sin(x) << endl;
					cout << "Sum of series = " << iterative_sin(e, x, i) << endl;
					cout << "n = " << i << endl;
				}
				else
					cout << "Incorrect x!" << endl;
			}
			else
			{
				cin.clear();
				cin.ignore(0xFFFFFFFF, '\n');
			}
		}
		else
			cout << "Incorrect accuracy!" << endl;

		cout << "Enter the accuracy ('q' for quit): ";
	}

	cout << "Terminating...";

	keep_window_open();

	return 0;
}