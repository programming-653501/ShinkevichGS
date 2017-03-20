/* ��������� ����� */
/* version 1.0 */


#include <iostream>
#include <vector>

using namespace std;
extern constexpr int f_size = 14; // ������ ���� ��� �����, �������, ��������

#include "Localization.h"
#include "Student.h"
#include "tenants.h"
#include "fileIO.h"

void keep_window_open()
{
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cin.get();
}

void stuff_list()
{
	cout << "������ ��������: " << endl;
	cout << "����������: ��������� ������ ��������" << endl;
	cout << "������������: ������� ����� �������������" << endl;
	cout << "��������: ����������� ������� ��������" << endl;
	cout << "������� �����������: �������� ����� ����������" << endl;
	cout << "���������: �������� ���� ���������" << endl;
	cout << "������� �����: (8)800-355-35-35" << endl;
}

void menu()
{
	cout << "���� (������� '0' ��� ������ ����): " << endl;
	cout << "1. ��������� �� �����\t";
	cout << "6. ������ �������" << endl;
	cout << "2. ��������\t\t";
	cout << "7. �����" << endl;
	cout << "3. ��������\t\t";
	cout << "8. ������ ��������" << endl;
	cout << "4. �������� ������\t";
	cout << "9. �������� � ����" << endl;
	cout << "5. �����\t\t";
	cout << "10. �����" << endl;
}

int main()
{
	localization();

	vector<Student> student;

	cout << "��������� �����" << endl;
	menu();
	int choice;
	cout << "$ ����: ";
	while (cin >> choice && choice != 10)
	{
		switch (choice)
		{
		case 0: menu(); break;
		case 1: read(student); break;
		case 2: settle(student); break;
		case 3: evict(student); break;
		case 4: modify(student); break;
		case 5: search(student); break;
		case 6: full_info(student); break;
		case 7: report(student); break;
		case 8: stuff_list(); break;
		case 9: write(student); break;
		default: cout << "������������ ����!" << endl; break;
		}
		cout << "$ ����: ";
	}

	keep_window_open();
}