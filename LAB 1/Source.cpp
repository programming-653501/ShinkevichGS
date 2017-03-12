/* Проверка на возрастание/убывание цифр введенного натурального числа*/
/* version 1.0 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

int main()
{
	vector<int> digits;
	int num;
	cout << "Enter the natural number ('q' for quit): ";
	while (cin >> num)
	{
		if (num > 0)
		{
			while (num != 0)
			{
				digits.push_back(num % 10);
				num /= 10;
			}

			if (digits.size() > 1)
			{
				if (adjacent_find(digits.cbegin(), digits.cend(), not_equal_to<int>()) != digits.cend())
				{
					if (is_sorted(digits.cbegin(), digits.cend()))
						cout << "Descending order" << endl;
					else if (is_sorted(digits.crbegin(), digits.crend()))
						cout << "Ascending order" << endl;
					else
						cout << "Not ordered" << endl;
				}
				else
					cout << "All the digits are equal" << endl;
			}
			else
				cout << "Too few digits" << endl;
		}
		else
			cout << "Not natural number" << endl;

		digits.clear();

		cout << "Enter the next number ('q' for quit): ";
	}

	cout << "Terminating...";
	
	keep_window_open();

	return 0;
}