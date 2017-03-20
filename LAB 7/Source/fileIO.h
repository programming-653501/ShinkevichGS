#include <fstream>
#include <locale>

void write(vector<Student> student)
{
	cout << "Запись в файл: " << endl;
	cout << "# Имя файла: ";
	string name;
	cin >> name;
	ofstream db{ name };

	locale lc("");
	db.imbue(lc);

	if (db.is_open())
	{
		for (unsigned int i{ 0 }; i < student.size(); i++)
		{
			db << student.at(i).GetName() << " ";
			db << student.at(i).GetSurname() << " ";
			db << student.at(i).GetPatronymic() << " ";
			db << student.at(i).GetFaculty() << " ";
			db << student.at(i).GetCourse() << " ";
			db << student.at(i).GetGroup() << " ";
			db << student.at(i).GetRoom() << " ";
			db << student.at(i).GetId() << " ";
			vector<string> violations = student.at(i).GetViolations();
			for (unsigned i{ 0 }; i < violations.size(); i++)
				db << violations.at(i) << " ";
			db << ")";
			db << endl;
		}
		cout << "Запись прошла успешно." << endl;
	}
	else
		cout << "Ошибка записи!" << endl;
}

unsigned int lines_count(string name)
{
	ifstream db{ name };

	unsigned int lines = 0;
	string line;
	while (getline(db, line))
		++lines;

	return lines;
}

void read(vector<Student> &student)
{
	cout << "Открытие файла: " << endl;
	cout << "# Имя файла: ";
	string name;
	cin >> name;
	ifstream db{ name };

	locale lc("");
	db.imbue(lc);

	if (db.is_open())
	{
		unsigned int lines = lines_count(name);
		student.resize(lines);
		for (unsigned int i{ 0 }; i < lines; i++)
		{
			string Name;
			string Surname;
			string Patronymic;
			int Faculty;
			int Course;
			int Group;
			int Room;
			int Id;
			vector<string> Violations = student.at(i).GetViolations();

			db >> Name >> Surname >> Patronymic >> Faculty >> Course >> Group >> Room >> Id;
			string Violation;
			for (unsigned int i{ 0 }; Violation != ")"; i++)
			{
				db >> Violation;
				Violations.push_back(Violation);
			}
			Violations.pop_back();

			student.at(i).SetName(Name);
			student.at(i).SetSurname(Surname);
			student.at(i).SetPatronymic(Patronymic);
			student.at(i).SetFaculty(Faculty);
			student.at(i).SetCourse(Course);
			student.at(i).SetGroup(Group);
			student.at(i).SetRoom(Room);
			student.at(i).SetId(Id);
			student.at(i).SetViolations(Violations);
		}
		cout << "Файл успешно открыт." << endl;
	}
	else
		cout << "Ошибка чтения!" << endl;
}