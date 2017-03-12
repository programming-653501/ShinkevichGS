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
	text = regex_replace(text, regex("Жы"), "Жи");
	text = regex_replace(text, regex("шы"), "ши");
	text = regex_replace(text, regex("Шы"), "Ши");
	text = regex_replace(text, regex("чя"), "ча");
	text = regex_replace(text, regex("Чя"), "Ча");
	text = regex_replace(text, regex("щя"), "ща");
	text = regex_replace(text, regex("Щя"), "Ща");
	text = regex_replace(text, regex("чю"), "чу");
	text = regex_replace(text, regex("Чю"), "Чу");
	text = regex_replace(text, regex("щю"), "щу");
	text = regex_replace(text, regex("Щю"), "Щу");

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

	cout << "Введите текст: " << endl;
	string text;
	while (getline(cin, text) && text != "#")
	{
		if (!text.empty())
		{
			if (diff(text, fix(text)))
			{
				cout << "\nИсправленный текст:\n" << fix(text) << endl;
				cout << "Количество ошибок: " << diff(text, fix(text)) << endl << endl;
			}
			else
				cout << "Нет ошибок." << endl << endl;
			cout << "Введите текст ('#' для выхода): " << endl;
		}
		else
		{
			cout << "Вы ничего не ввели, введите что-нибудь: " << endl;
		}
	}

	cout << "Выход...";

	keep_window_open();

	return 0;
}