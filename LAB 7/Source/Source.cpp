/* Общежитие БГУИР */
/* version 1.0 */


#include <iostream>
#include <vector>

using namespace std;
extern constexpr int f_size = 14; // Ширина поля для имени, фамилии, отчества

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
	cout << "Список служащих: " << endl;
	cout << "Заведующая: Трухуцкая Галина Фадеевна" << endl;
	cout << "Паспортистка: Минаева Ольга Валентайновна" << endl;
	cout << "Психолог: Добродушная Надежда Гинтаева" << endl;
	cout << "Главный воспитатель: Миронова Ольга Дмитриевна" << endl;
	cout << "Комендант: Шинкевич Глеб Сергеевич" << endl;
	cout << "Горячая линия: (8)800-355-35-35" << endl;
}

void menu()
{
	cout << "Меню (Введите '0' для показа меню): " << endl;
	cout << "1. Прочитать из файла\t";
	cout << "6. Список жильцов" << endl;
	cout << "2. Заселить\t\t";
	cout << "7. Отчёт" << endl;
	cout << "3. Выселить\t\t";
	cout << "8. Список служащих" << endl;
	cout << "4. Изменить данные\t";
	cout << "9. Записать в файл" << endl;
	cout << "5. Поиск\t\t";
	cout << "10. Выход" << endl;
}

int main()
{
	localization();

	vector<Student> student;

	cout << "ОБЩЕЖИТИЕ БГУИР" << endl;
	menu();
	int choice;
	cout << "$ Ввод: ";
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
		default: cout << "Неправильный ввод!" << endl; break;
		}
		cout << "$ Ввод: ";
	}

	keep_window_open();
}