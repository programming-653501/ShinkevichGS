class Student
{
	string name;
	string surname;
	string patronymic;
	int faculty;
	int course;
	int group;
	vector<string> violations;
	int room;
	int id;

public:
	Student();
	void SetName(string);
	void SetSurname(string);
	void SetPatronymic(string);
	void SetFaculty(int);
	string FacultyName(int);
	void SetCourse(int);
	void SetGroup(int);
	void SetViolations(vector<string>);
	void SetRoom(int);
	void SetId(int);
	string GetName() { return name; }
	string GetSurname() { return surname; }
	string GetPatronymic() { return patronymic; }
	int GetFaculty() { return faculty; }
	int GetCourse() { return course; }
	int GetGroup() { return group; }
	vector<string> GetViolations() { return violations; }
	int GetRoom() { return room; }
	int GetId() { return id; }
};

Student::Student()
{
	name = "";
	surname = "";
	patronymic = "";
	faculty = 0;
	course = 0;
	group = 0;
	violations = {};
	room = 0;
	id = 0;
}

string Student::FacultyName(int faculty)
{
	switch (faculty)
	{
	case 1: return "‘ œ"; break;
	case 2: return "‘»“”"; break;
	case 3: return "‘–›"; break;
	case 4: return "‘ —Ë—"; break;
	case 5: return "‘“ "; break;
	case 6: return "»›‘"; break;
	default: return "¬ÓÂÌÍ‡"; break;
	}
}

void Student::SetName(string Name)
{
	name = Name;
}

void Student::SetSurname(string Surname)
{
	surname = Surname;
}

void Student::SetPatronymic(string Patronymic)
{
	patronymic = Patronymic;
}

void Student::SetFaculty(int Faculty)
{
	faculty = Faculty;
}

void Student::SetCourse(int Course)
{
	course = Course;
}

void Student::SetGroup(int Group)
{
	group = Group;
}

void Student::SetViolations(vector<string> Violations)
{
	violations = Violations;
}

void Student::SetRoom(int Room)
{
	room = Room;
}

void Student::SetId(int Id)
{
	id = Id;
}