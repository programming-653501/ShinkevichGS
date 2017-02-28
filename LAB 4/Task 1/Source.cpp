#include <iostream>
#include <string>
#include <regex>
#include "Localization.h"

using namespace std;

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

string fix(string text)
{
	text = regex_replace(text, regex("жы"), "жи");
	text = regex_replace(text, regex("∆ы"), "∆и");
	text = regex_replace(text, regex("шы"), "ши");
	text = regex_replace(text, regex("Ўы"), "Ўи");
	text = regex_replace(text, regex("ч€"), "ча");
	text = regex_replace(text, regex("„€"), "„а");
	text = regex_replace(text, regex("щ€"), "ща");
	text = regex_replace(text, regex("ў€"), "ўа");
	text = regex_replace(text, regex("чю"), "чу");
	text = regex_replace(text, regex("„ю"), "„у");
	text = regex_replace(text, regex("щю"), "щу");
	text = regex_replace(text, regex("ўю"), "ўу");

	return text;
}

unsigned int diff(string text, string fixed_text)
{
	unsigned int len = text.length();
	unsigned int mismatches{ 0 };
	if (len > fixed_text.length())
		len = fixed_text.length();
	for (unsigned int i{ 0 }; i < len; i++)
	{
		if (text.at(i) != fixed_text.at(i))
			mismatches++;
	}
	return mismatches;
}

int main()
{
	localization();

	cout << "¬ведите текст: " << endl;
	string text;
	while (getline(cin, text) && text != "#")
	{
		if (!text.empty())
		{
			if (diff(text, fix(text)))
			{
				cout << "\n»справленный текст:\n" << fix(text) << endl;
				cout << " оличество ошибок: " << diff(text, fix(text)) << endl << endl;
			}
			else
				cout << "Ќет ошибок." << endl << endl;
			cout << "¬ведите текст ('#' дл€ выхода): " << endl;
		}
		else
		{
			cout << "¬ы ничего не ввели, введите что-нибудь: " << endl;
		}
	}

	cout << "¬ыход...";

	keep_window_open();

	return 0;
}