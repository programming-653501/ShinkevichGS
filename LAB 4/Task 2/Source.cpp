/* Поиск максимальной и минимальной даты в файле "Example.txt" */
/* version 1.0 */
/* Принимается любая подходящая дата в формате dd.mm.yyyy (01.01.0001 - 31.12.9999)*/


#include <iostream>
#include <fstream>
#include <regex>
#include <functional>

using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

vector<string> splitString(string input, string delimiter)
{
	vector<string> output;
	size_t start{ 0 };
	size_t end{ 0 };

	while (start != string::npos && end != string::npos)
	{
		start = input.find_first_not_of(delimiter, end);

		if (start != string::npos)
		{
			end = input.find_first_of(delimiter, start);

			if (end != string::npos)
				output.push_back(input.substr(start, end - start));
			else
				output.push_back(input.substr(start));
		}
	}

	return output;

}

int main()
{
	vector< vector<int> > date_int;
	vector< vector<string> > date_string;

	string text;

	ifstream file("Example.txt");
	if (file.is_open())
	{
		while (getline(file, text, '\0'))
		{
			smatch match;
			regex expression("[0-9]{2}.[0-9]{2}.[0-9]{4}");
			for (unsigned i{ 0 }; regex_search(text, match, expression); i++)
			{
				date_string.resize(i + 1);
				date_int.resize(i + 1);

				vector<string> splitted_date;
				splitted_date = { splitString(match.str(0), ".") };
				for (unsigned j{ 0 }; j < splitted_date.size(); j++)
				{
					date_int.at(i).resize(splitted_date.size());
					date_string.at(i).resize(splitted_date.size());
					date_int.at(i).at(j) = stoi(splitted_date.at(j), nullptr, 10);
					date_string.at(i) = splitted_date;
				}
				text = match.suffix().str();
			}

			if (!date_int.empty())
			{

				for (unsigned int i{ 0 }; i < date_int.size(); i++)
				{
					if (date_int.at(i).at(1) <= 0 || date_int.at(i).at(1) > 12 ||
						date_int.at(i).at(0) <= 0 || date_int.at(i).at(0) > 31 || date_int.at(i).at(2) <= 0)
					{
						date_int.erase(date_int.begin() + i);
						date_string.erase(date_string.begin() + i);
					}
				}

				vector<int> date_sum;
				for (unsigned int i{ 0 }; i < date_int.size(); i++)
					date_sum.push_back(date_int.at(i).at(0) + date_int.at(i).at(1) * 100 + date_int.at(i).at(2) * 10000);

				if (adjacent_find(date_sum.cbegin(), date_sum.cend(), not_equal_to<int>()) != date_sum.cend())
				{
					cout << "Max date in file: ";
					for (unsigned int i{ 0 }; i < date_int.at(0).size(); i++)
						cout << date_string.at(distance(date_sum.begin(), max_element(date_sum.begin(), date_sum.end()))).at(i) << ".";
					cout << endl;

					cout << "Min date in file: ";
					for (unsigned int i{ 0 }; i < date_int.at(0).size(); i++)
						cout << date_string.at(distance(date_sum.begin(), min_element(date_sum.begin(), date_sum.end()))).at(i) << ".";
					cout << endl;
				}
				else
				{
					cout << "Only one date - ";
					for (unsigned int i{ 0 }; i < date_int.at(0).size(); i++)
						cout << date_string.at(0).at(i) << ".";
					cout << endl;
				}
			}
			else
				cout << "Dates not found." << endl;

		}
		file.close();
	}
	else
		cout << "Reading error!" << endl;

	cout << "Terminating...";

	keep_window_open();

	return 0;
}