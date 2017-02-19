/* Расчёт стоимости оклейки обоев в комнате */
/* version 1.0 */


#include <iostream>

using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

void size_input(double& length, double& width)
{
	do
	{
		cout << "Enter the length of the room: ";
		cin >> length;
		if (cin.fail())
			break;
	} while (length <= 0.0);
	do
	{
		cout << "Enter the width of the room: ";
		cin >> width;
		if (cin.fail())
			break;
	} while (width <= 0.0);
	return;
}

void windows_input(int& win)
{
	do
	{
		cout << "Enter the number of windows: ";
		cin >> win;
		if (cin.fail())
			break;
	} while (win <= 0);
	return;
}

void doorways_input(int& dw)
{
	do
	{
		cout << "Enter the number of doorways: ";
		cin >> dw;
		if (cin.fail())
			break;
	} while (dw <= 0);
	return;
}

void tubecost_input(double& tube)
{
	do
	{
		cout << "Enter the cost of wallpaper tube: ";
		cin >> tube;
		if (cin.fail())
			break;
	} while (tube <= 0.0);
	return;
}

double square_calc(double length, double width, int win, int dw)
{
	constexpr double win_size{ 2.15 * 1.5 };
	constexpr double dw_size{ 0.9 * 2.05 };
	constexpr double h{ 2.6 };

	if (length > 0 && width > 0 && dw > 0)
	{
		double square{ 0.0 };
		double room_s{ 2 * (length + width) * h };
		double skip_s{ win * win_size + dw * dw_size };
		if (room_s > skip_s)
		{
			square = room_s - skip_s;
			return square;
		}
		else
		{
			cout << "Incorrect size! ";
			return 0;
		}
	}
	else
		return 0;
}

int tubes_calc(double square)
{
	constexpr double w_tube{ 0.5 };
	constexpr double l_tube{ 10.0 };

	if (square > 0)
	{
		int tubes{ 0 };
		tubes = int(square / (w_tube * l_tube)) + 1;
		return tubes;
	}
	else
		return 0;
}

double papering_cost(double tube_cost, int tubes)
{
	constexpr double glue_cost{ 2.5 };

	if (tubes > 0 && tube_cost > 0)
	{
		double cost{ 0.0 };
		cost = tubes * tube_cost + glue_cost * (double)((tubes % 5) ? (tubes / 5 + 1) : (tubes / 5));
		return cost;
	}
	else
		return 0;
}

int main()
{
	double length{ 0.0 };
	double width{ 0.0 };
	int win{ 0 };
	int dw{ 0 };
	double tube{ 0.0 };

	cout << "Selection menu:\n";
	cout << "1. Input length and width of room.\t";
	cout << "5. Square of papering calculation.\n";
	cout << "2. Input number of windows.\t\t";
	cout << "6. Number of wallpaper tubes calculation.\n";
	cout << "3. Input number of doorways.\t\t";
	cout << "7. Cost of papering calculation.\n";
	cout << "4. Input cost of wallpaper tube.\t";
	cout << "8. Quit.\n";

	short choice;
	cout << "Input: ";
	while (cin >> choice && choice != 8)
	{
		switch (choice)
		{
		case 1: size_input(length, width); break;
		case 2: windows_input(win); break;
		case 3: doorways_input(dw); break;
		case 4: tubecost_input(tube); break;
		case 5: {
			if (square_calc(length, width, win, dw) > 0)
				cout << "Square of papering = " << square_calc(length, width, win, dw) << endl;
			else
				cout << "You need to input data!" << endl;
			break;
		}
		case 6: {
			if (tubes_calc(square_calc(length, width, win, dw)) > 0)
				cout << "You need " << tubes_calc(square_calc(length, width, win, dw)) << " tubes" << endl;
			else
				cout << "You need to input data!" << endl;
			break;
		}
		case 7: {
			if (papering_cost(tube, tubes_calc(square_calc(length, width, win, dw))) > 0)
				cout << "Papering cost = " << papering_cost(tube, tubes_calc(square_calc(length, width, win, dw))) << endl;
			else
				cout << "You need to input data!" << endl;
			break;
		}
		default: cout << "Incorrect input" << endl; break;
		}
		cout << "Input: ";
	}

	cout << "Terminating...";

	keep_window_open();

	return 0;
}