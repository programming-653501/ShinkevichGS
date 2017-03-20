#include <iomanip>
#include <string>
#include <ctime>

vector<int> rooms_list(vector<Student> student)
{
	vector<int> rooms;
	for (unsigned int i{ 0 }; i < student.size(); i++)
		rooms.push_back(student.at(i).GetRoom());
	return rooms;
}

vector<int> id_list(vector<Student> student)
{
	vector<int> id;
	for (unsigned int i{ 0 }; i < student.size(); i++)
		id.push_back(student.at(i).GetId());
	return id;
}

void set_id(vector<Student> &student, int i)
{
	vector<int> list = id_list(student);

	srand((unsigned int)time(NULL));
	int Id = rand() % 600;
	while (find(list.begin(), list.end(), Id) != list.end())
	{
		srand((unsigned int)time(NULL));
		Id = rand() % 600;
	}

	student.at(i).SetId(Id);
}

void set_name(vector<Student> &student, int i)
{
	string text;
	cout << "# Имя: ";
	while (!(cin >> text))
	{
		cout << "Неправильный ввод!" << endl;
		cout << "# Имя: ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetName(text);
}

void set_surname(vector<Student> &student, int i)
{
	string text;
	cout << "# Фамилия: ";
	while (!(cin >> text))
	{
		cout << "Неправильный ввод!" << endl;
		cout << "# Фамилия: ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetSurname(text);
}

void set_patronymic(vector<Student> &student, int i)
{
	string text;
	cout << "# Отчество: ";
	while (!(cin >> text))
	{
		cout << "Неправильный ввод!" << endl;
		cout << "# Отчество: ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetPatronymic(text);
}

void set_faculty(vector<Student> &student, int i)
{
	int number;
	cout << "# Факультет (1 - ФКП, 2 - ФИТУ, 3 - ФРЭ, 4 - ФКСиС, 5 - ФТК, 6 - ИЭФ): ";
	while (!(cin >> number) || number < 1 || number > 6)
	{
		cout << "Неправильный ввод!" << endl;
		cout << "# Факультет (1 - ФКП, 2 - ФИТУ, 3 - ФРЭ, 4 - ФКСиС, 5 - ФТК, 6 - ИЭФ): ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetFaculty(number);
}

void set_course(vector<Student> &student, int i)
{
	int number;
	cout << "# Курс (1 - 5): ";
	while (!(cin >> number) || number < 1 || number > 5)
	{
		cout << "Неправильный ввод!" << endl;
		cout << "# Курс (1 - 5): ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetCourse(number);
}

void set_group(vector<Student> &student, int i)
{
	int number;
	cout << "# Группа (100000 - 999999): ";
	while (!(cin >> number) || number < 100000 || number > 999999)
	{
		cout << "Неправильный ввод!" << endl;
		cout << "# Группа (100000 - 999999): ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetGroup(number);
}

bool stage_check(vector<Student> student, int i, int number)
{
	bool stage{ true };
	switch (student.at(i).GetFaculty())
	{
	case 1: if (number < 100 || number > 199) stage = false; break;
	case 2: if (number < 200 || number > 299) stage = false; break;
	case 3: if (number < 300 || number > 399) stage = false; break;
	case 4: if (number < 400 || number > 499) stage = false; break;
	case 5: if (number < 500 || number > 599) stage = false; break;
	case 6: if (number < 600 || number > 699) stage = false; break;
	}
	return stage;
}

void set_room(vector<Student> &student, int i)
{
	vector<int> rooms = rooms_list(student);

	int number;
	cout << "# Комната: ";
	while (!(cin >> number) || number < 100 || number > 699 ||
		find(rooms.begin(), rooms.end(), number) != rooms.end() || !stage_check(student, i, number))
	{
		if (cin.fail() || number < 100 || number > 699)
			cout << "Неправильный ввод!" << endl;
		else if (!stage_check(student, i, number))
			cout << "Неправильный этаж!" << endl;
		else if (find(rooms.begin(), rooms.end(), number) != rooms.end())
			cout << "Комната занята" << endl;

		cout << "# Комната: ";
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}

	student.at(i).SetRoom(number);
}

void violations_check(vector<Student> student, int i)
{
	if (student.at(i).GetViolations().size() > 3)
		cout << "Пора выселять этого нарушителя!" << endl;
}

void set_violations(vector<Student> &student, int i)
{
	vector<string> text = student.at(i).GetViolations();
	cout << "Нарушения: " << endl;
	for (unsigned int i{ 0 }; i < text.size(); i++)
		cout << "№ " << i + 1 << " " << text.at(i) << endl;

	violations_check(student, i);

	cout << "1. Добавить нарушение" << endl;
	cout << "2. Удалить нарушение" << endl;
	cout << "3. Выход" << endl;
	int choice;
	cout << "# Ввод: ";
	while (cin >> choice && choice != 3)
	{
		text = student.at(i).GetViolations();
		switch (choice)
		{
		case 1:
		{
			string violation;
			cout << "# Нарушение: ";
			while (!(cin >> violation))
			{
				cout << "Неправильный ввод!" << endl;
				cout << "# Нарушение: ";
				cin.clear();
				cin.ignore(0xFFFFFFFF, '\n');
			}
			text.push_back(violation);
			student.at(i).SetViolations(text);
			break;
		}
		case 2:
		{
			cout << "# Номер нарушения: ";
			unsigned int pos;
			cin >> pos;
			if (!cin.fail() && pos > 0 && pos <= text.size())
				text.erase(text.begin() + pos - 1);
			else
				cout << "Неправильный номер!" << endl;
			student.at(i).SetViolations(text);
			break;
		}
		default: cout << "Неправильный ввод!" << endl;
		}
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');

		cout << "Нарушения: " << endl;
		for (unsigned int i{ 0 }; i < text.size(); i++)
			cout << "№" << i + 1 << " " << text.at(i) << endl;

		violations_check(student, i);

		cout << "1. Добавить нарушение" << endl;
		cout << "2. Удалить нарушение" << endl;
		cout << "3. Выход" << endl;
		cout << "# Ввод: ";
	}
	cin.clear();
}

void settle(vector<Student> &student)
{
	cout << "Добавление жильца: " << endl;
	student.resize(student.size() + 1);

	set_id(student, student.size() - 1);
	set_name(student, student.size() - 1);
	set_surname(student, student.size() - 1);
	set_patronymic(student, student.size() - 1);
	set_faculty(student, student.size() - 1);
	set_course(student, student.size() - 1);
	set_group(student, student.size() - 1);
	set_room(student, student.size() - 1);

	cout << "Жилец заселён." << endl;
}

void student_info(vector<Student> student, int i)
{
	cout << "ID: " << student.at(i).GetId() << endl;
	cout << "Имя: " << student.at(i).GetName() << endl;
	cout << "Фамилия: " << student.at(i).GetSurname() << endl;
	cout << "Отчество: " << student.at(i).GetPatronymic() << endl;
	cout << "Факультет: " << student.at(i).FacultyName(student.at(i).GetFaculty()) << endl;
	cout << "Курс: " << student.at(i).GetCourse() << endl;
	cout << "Группа: " << student.at(i).GetGroup() << endl;
	cout << "Комната: " << student.at(i).GetRoom() << endl;
}

void modify(vector<Student> &student)
{
	vector<int> list = id_list(student);

	cout << "Изменение данных: " << endl;
	int id;
	cout << "# ID студента: ";
	cin >> id;	
	if (!cin.fail() && find(list.begin(), list.end(), id) != list.end())
	{
		int pos;
		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (id == student.at(i).GetId())
				pos = i;

		cout << "Студент: " << endl;
		student_info(student, pos);
		cout << "# Выберите поле (1 - Имя, 2 - Фамилия, 3 - Отчество, 4 - Факультет, 5 - Курс, ";
		cout << "6 - Группа, 7 - Комната, 8 - Нарушения): ";
		int field;
		cin >> field;
		switch (field)
		{
		case 1: set_name(student, pos); break;
		case 2: set_surname(student, pos); break;
		case 3: set_patronymic(student, pos); break;
		case 4: set_faculty(student, pos); set_room(student, pos); break;
		case 5: set_course(student, pos); break;
		case 6: set_group(student, pos); break;
		case 7: set_room(student, pos); break;
		case 8: set_violations(student, pos); break;
		default: cout << "Неправильный ввод!" << endl;
		}
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
		cout << "Редактирование завершено." << endl;
	}
	else
	{
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
		cout << "Неправильный ID!" << endl;
	}
}

void evict(vector<Student> &student)
{
	vector<int> list = id_list(student);

	cout << "Выселение: " << endl;
	int id;
	cout << "# ID студента: ";
	cin >> id;
	if (!cin.fail() && find(list.begin(), list.end(), id) != list.end())
	{
		int pos;
		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (id == student.at(i).GetId())
				pos = i;

		cout << "Студент: " << endl;
		student_info(student, pos);
		int confirm;
		cout << "# Хотите выселить этого студента? (1 - Да, 0 - Нет): ";
		cin >> confirm;
		if (confirm)
		{
			student.erase(student.begin() + pos);
			cout << "Студент выселен!" << endl;
		}
	}
	else
	{
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
		cout << "Неправильный ID!" << endl;
	}
}

void student_list(vector<Student> student, int i)
{
	cout << setw(4) << i + 1 << setw(f_size) << student.at(i).GetName();
	cout << setw(f_size) << student.at(i).GetSurname();
	cout << setw(f_size) << student.at(i).GetPatronymic();
	cout << setw(f_size) << student.at(i).FacultyName(student.at(i).GetFaculty());
	cout << setw(f_size) << student.at(i).GetCourse();
	cout << setw(f_size) << student.at(i).GetGroup();
	cout << setw(f_size) << student.at(i).GetRoom();
	cout << setw(f_size) << student.at(i).GetId();
	cout << endl;
}

void search_field(vector<Student> student, string p, int val)
{
	if (p == "id")
	{
		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (val == student.at(i).GetId())
				student_info(student, i);
	}
	else if (p == "room")
	{
		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (val == student.at(i).GetRoom())
				student_info(student, i);
	}
	else if (p == "faculty")
	{
		cout << setw(4) << "№" << setw(f_size) << "Имя" << setw(f_size) << "Фамилия" << setw(f_size) << "Отчество";
		cout << setw(f_size) << "Факультет" << setw(f_size) << "Курс" << setw(f_size) << "Группа";
		cout << setw(f_size) << "Комната" << setw(f_size) << "ID" << endl;

		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (val == student.at(i).GetFaculty())
				student_list(student, i);
	}
	else if (p == "course")
	{
		cout << setw(4) << "№" << setw(f_size) << "Имя" << setw(f_size) << "Фамилия" << setw(f_size) << "Отчество";
		cout << setw(f_size) << "Факультет" << setw(f_size) << "Курс" << setw(f_size) << "Группа";
		cout << setw(f_size) << "Комната" << setw(f_size) << "ID" << endl;

		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (val == student.at(i).GetCourse())
				student_list(student, i);
	}
	else if (p == "group")
	{
		cout << setw(4) << "№" << setw(f_size) << "Имя" << setw(f_size) << "Фамилия" << setw(f_size) << "Отчество";
		cout << setw(f_size) << "Факультет" << setw(f_size) << "Курс" << setw(f_size) << "Группа";
		cout << setw(f_size) << "Комната" << setw(f_size) << "ID" << endl;

		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (val == student.at(i).GetGroup())
				student_list(student, i);
	}
}

void search_field(vector<Student> student, string p, string val)
{
	if (p == "surname")
	{
		for (unsigned int i{ 0 }; i < student.size(); i++)
			if (val == student.at(i).GetSurname())
				student_info(student, i);
	}
}

void search(vector<Student> student)
{
	int field;
	cout << "Поиск: " << endl;
	cout << "# Выберите поле (1 - ID, 2 - Фамилия, 3 - Комната, 4 - Факультет, 5 - Курс, 6 - Группа): ";
	cin >> field;
	switch (field)
	{
	case 1:
	{
		int id;
		cout << "# ID: ";
		if (cin >> id)
		{
			cout << "Результаты: " << endl;
			search_field(student, "id", id);
		}
		cin.clear();
		break;
	}
	case 2:
	{
		string surname;
		cout << "# Фамилия: ";
		if (cin >> surname)
		{
			cout << "Результаты: " << endl;
			search_field(student, "surname", surname);
		}
		cin.clear();
		break;
	}
	case 3:
	{
		int room;
		cout << "# Комната: ";
		if (cin >> room)
		{
			cout << "Результаты: " << endl;
			search_field(student, "room", room);
		}
		cin.clear();
		break;
	}
	case 4:
	{
		int faculty;
		cout << "# Факультет (1 - ФКП, 2 - ФИТУ, 3 - ФРЭ, 4 - ФКСиС, 5 - ФТК, 6 - ИЭФ): ";
		if (cin >> faculty)
		{
			cout << "Результаты: " << endl;
			search_field(student, "faculty", faculty);
		}
		cin.clear();
		break;
	}
	case 5:
	{
		int course;
		cout << "# Курс: ";
		if (cin >> course)
		{
			cout << "Результаты: " << endl;
			search_field(student, "course", course);
		}
		cin.clear();
		break;
	}
	case 6:
	{
		int group;
		cout << "# Группа: ";
		if (cin >> group)
		{
			cout << "Результаты: " << endl;
			search_field(student, "group", group);
		}
		cin.clear();
		break;
	}
	default: cout << "Неправильный ввод!" << endl;
	}
	cin.clear();
	cin.ignore(0xFFFFFFFF, '\n');
	cout << "Поиск завершен." << endl;
}

void full_info(vector<Student> student)
{
	cout << "Список жильцов: " << endl;
	cout << setw(4) << "№" << setw(f_size) << "Имя" << setw(f_size) << "Фамилия" << setw(f_size) << "Отчество";
	cout << setw(f_size) << "Факультет" << setw(f_size) << "Курс" << setw(f_size) << "Группа";
	cout << setw(f_size) << "Комната" << setw(f_size) << "ID" << endl;

	for (unsigned int i{ 0 }; i < student.size(); i++)
		student_list(student, i);
}

void report(vector<Student> student)
{
	cout << "Отчёт: " << endl;
	cout << "Количество жильцов: " << student.size() << endl;
	cout << "Количество свободных мест: " << 600 - student.size() << endl;

	cout << "1. Посмотреть по факультетам" << endl;
	cout << "2. Выход" << endl;
	int choice;
	cout << "# Ввод: ";
	if (cin >> choice && choice != 2)
	{
		switch (choice)
		{
		case 1:
		{
			vector<int> faculties(6, 0);
			for (unsigned int i{ 0 }; i < student.size(); i++)
			{
				switch (student.at(i).GetFaculty())
				{
				case 1: faculties.at(0)++; break;
				case 2: faculties.at(1)++; break;
				case 3: faculties.at(2)++; break;
				case 4: faculties.at(3)++; break;
				case 5: faculties.at(4)++; break;
				case 6: faculties.at(5)++; break;
				}
			}
			cout << "Занято ФКП: " << faculties.at(0) << endl;
			cout << "Свободно для ФКП: " << 100 - faculties.at(0) << endl;
			cout << "Занято ФИТУ: " << faculties.at(1) << endl;
			cout << "Свободно для ФИТУ: " << 100 - faculties.at(1) << endl;
			cout << "Занято ФРЭ: " << faculties.at(2) << endl;
			cout << "Свободно для ФРЭ: " << 100 - faculties.at(2) << endl;
			cout << "Занято ФКСиС: " << faculties.at(3) << endl;
			cout << "Свободно для ФКСиС: " << 100 - faculties.at(3) << endl;
			cout << "Занято ФТК: " << faculties.at(4) << endl;
			cout << "Свободно для ФТК: " << 100 - faculties.at(4) << endl;
			cout << "Занято ИЭФ: " << faculties.at(5) << endl;
			cout << "Свободно для ИЭФ: " << 100 - faculties.at(5) << endl;
			cout << "Конец отчёта." << endl;
			break;
		}
		default: cout << "Неверный ввод!" << endl;
		}
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}
	else
	{
		cin.clear();
		cin.ignore(0xFFFFFFFF, '\n');
	}
}