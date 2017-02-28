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
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");
	text = regex_replace(text, regex("��"), "��");

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

	cout << "������� �����: " << endl;
	string text;
	while (getline(cin, text) && text != "#")
	{
		if (!text.empty())
		{
			if (diff(text, fix(text)))
			{
				cout << "\n������������ �����:\n" << fix(text) << endl;
				cout << "���������� ������: " << diff(text, fix(text)) << endl << endl;
			}
			else
				cout << "��� ������." << endl << endl;
			cout << "������� ����� ('#' ��� ������): " << endl;
		}
		else
		{
			cout << "�� ������ �� �����, ������� ���-������: " << endl;
		}
	}

	cout << "�����...";

	keep_window_open();

	return 0;
}