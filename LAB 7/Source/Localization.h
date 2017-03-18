#include <Windows.h>
#include <clocale>  

void localization()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}
