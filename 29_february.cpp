/* Напишите программу, которая проверяет, является ли год високосным (кратным 4) в пределах от 2000 лет
до нашей эры и до 2000 лет нашей эры. */

#include <iostream>
#include <Windows.h> // для использования кириллицы
#include <sstream>   // для использования потоковых классов для строк
#include <string>

using std::cout; using std::cin; using std::endl;
using std::string;

// пытается превратить строку в число (год), выдаёт false, если не получилось
inline bool is_natural_number(const string& str, int& year)
{
	std::istringstream istream(str);
	return (istream >> year) ? true : false;
}

// получает внятный ответ от пользователя и превращает его в год
int get_year()
{
	const short maximum_year = 2020;

	cout << "Введите год и эру: ";
	while (true)
	{
		string answer;
		getline(cin, answer);

		// извлекаем ответ в потоковую переменную
		std::stringstream answer_stream;
		answer_stream << answer;

		// получаем из потоковой переменной данные до пробела, это должен быть год
		int year{ 0 };
		string may_be_year;
		answer_stream >> may_be_year;

		// если в начале действительно целое число
		if (is_natural_number(may_be_year, year))
		{
			// проверяем, что год больше нуля и меньше нашего максимального года
			if ((year <= 0) || (year > maximum_year))
				cout << "Год должен быть натуральным числом до " << maximum_year << " ";
			else // год в заданных рамках
			{
				string era;
				getline(answer_stream, era); // извлекаем всё оставшееся
				// если пользователь дал понять, что это наша эра
				if ((era == " год нашей эры") || (era == " год н.э.") || (era == " нашей эры") || (era == " н.э.") || (era == " год н э") || (era == " н э"))
					return year; // получили год и он положительный, выходим из программы
				// если пользователь дал понять, что год до нашей эры
				if ((era == " год до нашей эры") || (era == " год до н.э.") || (era == " до нашей эры") || (era == " до н.э.") || (era == " год до н э") || (era == " до н э"))
					return -year; // получили год и делаем его отрицательным, выходим из программы
				// иначе
				cout << "Что Вы имели в виду под " << era << "? ";
			}
		}
		// не удалось распознать пользовательский ответ до пробела как целое число
		else
			cout << "Не удалось получить год! ";

		cin.clear();
		cout << "Введите год и эру ещё раз: ";
	}
}

// возвращает истину, если год - високосный
bool is_leap_year(const int year)
{
	if (year % 400 == 0) 
		return true;
	// если не делится на 400, но делится на 100
	if (year % 100 == 0)
		return false;
	// если просто делится на 4 без остатка (но не делится на 100 и 400)
	if (year % 4 == 0)
		return true;
	// иначе не делится на 4 без остатка
	return false;
}

int main()
{
	// подключаем кириллицу:
	SetConsoleCP(1251); SetConsoleOutputCP(1251);

    cout << "Программа определяет, является ли заданный год високосным\n" << endl;
	while (true)
	{ 
		int year{ get_year() };
		if (is_leap_year(year))
			cout << "Этот год является високосным" << endl << endl;
		else 
			cout << "Этот год не високосный" << endl << endl;
	}
}
