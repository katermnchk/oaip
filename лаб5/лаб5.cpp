#include <iostream>
#include <string.h>
#include <windows.h>
#include <fstream>
#include <map>;
#include <vector>;
#include <sstream >;
#include <stdexcept>

using namespace std;

int entry();
int add();
int answer();
int menu();
void display();

struct date
{
	int day;
	int month;
	int year;
	date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {}
	void setDate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}
	void getDate() const
	{
		cout << ((day < 10) ? "0" : "") << day << "." << ((month < 10) ? "0" : "") << month << ".";
		if (year < 10) cout << "200";
		else if (year > 10 && year < 100) cout << "20";
		cout << year;
	}
};

struct Time
{
	int hours;
	int minutes;
	int seconds;
	Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}
	void setTime(int h, int m, int s)
	{
		hours = (h >= 0 && h < 24) ? h : 0;
		minutes = (m >= 0 && m < 60) ? m : 0;
		seconds = (s >= 0 && s < 60) ? s : 0;
	}
	void getTime() const
	{
		cout << ((hours < 10) ? "0" : "") << hours << ":" << ((minutes < 10) ? "0" : "") << minutes <<
			":" << ((seconds < 10) ? "0" : "") << seconds;
	}
};

struct call
{
	date date;
	Time time;
	string code;
	string town;
	string tarife;
	string numberPhone, numberAbonent;
};

void readCallsFromFile(vector<call>& calls) {
	ifstream file("data.txt");
	if (!file.is_open()) {
		cout << "������ �������� �����" << endl;
		return;
	}

	call callData;
	while (file >> callData.date.day >> callData.date.month >> callData.date.year
		>> callData.time.hours >> callData.time.minutes >> callData.time.seconds
		>> callData.code >> callData.town >> callData.tarife
		>> callData.numberPhone >> callData.numberAbonent) {
		calls.push_back(callData);
	}

	file.close();
}

void writeCallsToFile(const vector<call>& calls)
{
	ofstream file("data.txt");
	if (!file.is_open())
	{
		cout << "������ �������� ����� ��� ������" << endl;
		return;
	}

	for (const auto& call : calls) 
	{
		file << call.date.day << ' ' << call.date.month << ' ' << call.date.year << ' '
			<< call.time.hours << ' ' << call.time.minutes << ' ' << call.time.seconds << ' '
			<< call.code << ' ' << call.town << ' ' << call.tarife << ' '
			<< call.numberPhone << ' ' << call.numberAbonent << '\n';
	}

	file.close();
}

void displayCall(const Time& totalTime)
{
	cout << "����� ����� ����������: ";
	cout << totalTime.hours << " �����, ";
	cout << totalTime.minutes << " �����, ";
	cout << totalTime.seconds << " ������" << endl;
}

void calculateTotalTime()
{
	ifstream file("data.txt");
	if (!file.is_open()) {
		cout << "������ �������� �����" << endl;
		return;
	}

	map<string, Time> totalTimeMap; // ���� - �������� ������, �������� - ����� ����� ����������

	string line;
	Time totalSum; // ����� ����� ������� ����������
	while (getline(file, line))
	{
		stringstream ss(line);
		call callData;

		// ������ ������ �� ������
		ss >> callData.date.day >> callData.date.month >> callData.date.year
			>> callData.time.hours >> callData.time.minutes >> callData.time.seconds
			>> callData.code >> callData.town >> callData.tarife
			>> callData.numberPhone >> callData.numberAbonent;

		// ���������� ������� ��������� � ������ ������� ��� ������� ������
		Time& totalTime = totalTimeMap[callData.town];
		totalTime.hours += callData.time.hours;
		totalTime.minutes += callData.time.minutes;
		totalTime.seconds += callData.time.seconds;

		// ������������� �������
		while (totalTime.seconds >= 60) {
			totalTime.minutes++;
			totalTime.seconds -= 60;
		}
		while (totalTime.minutes >= 60) {
			totalTime.hours++;
			totalTime.minutes -= 60;
		}

		// ���������� ������� ��������� � ����� ����� �������
		totalSum.hours += callData.time.hours;
		totalSum.minutes += callData.time.minutes;
		totalSum.seconds += callData.time.seconds;

		// ������������� ������� ��� ����� �����
		while (totalSum.seconds >= 60) {
			totalSum.minutes++;
			totalSum.seconds -= 60;
		}
		while (totalSum.minutes >= 60) {
			totalSum.hours++;
			totalSum.minutes -= 60;
		}
	}

	// ����� �����������
	cout << "����� ����� ���������� �� �������:" << endl;
	for (const auto& pair : totalTimeMap) {
		cout << pair.first << ": ";
		cout << pair.second.hours << " �����, ";
		cout << pair.second.minutes << " �����, ";
		cout << pair.second.seconds << " ������" << endl;
	}

	// ����� ����� ����� ������� ����������
	cout << "\n����� ����� ������� ����������: ";
	cout << totalSum.hours << " �����, ";
	cout << totalSum.minutes << " �����, ";
	cout << totalSum.seconds << " ������" << endl;

	file.close();
}

static bool isLeapYear(int year)//�������� �� ���������� ���
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Time linearSearch(const string& searchCode)
{
	ifstream file("data.txt");
	if (!file.is_open())
	{
		cout << "������ �������� �����" << endl;
		return Time();
	}

	Time totalTime;
	call callData;
	vector<call> calls;

	while (file >> callData.date.day >> callData.date.month >> callData.date.year
		>> callData.time.hours >> callData.time.minutes >> callData.time.seconds
		>> callData.code >> callData.town >> callData.tarife
		>> callData.numberPhone >> callData.numberAbonent)
	{
		calls.push_back(callData);
	}

	file.close();

	for (const auto& call : calls)
	{
		if (call.code == searchCode)
		{
			totalTime.hours += call.time.hours;
			totalTime.minutes += call.time.minutes;
			totalTime.seconds += call.time.seconds;

			// ������������� �������
			while (totalTime.seconds >= 60)
			{
				totalTime.minutes++;
				totalTime.seconds -= 60;
			}
			while (totalTime.minutes >= 60)
			{
				totalTime.hours++;
				totalTime.minutes -= 60;
			}
		}
	}

	return totalTime;
}

void selectionSortByTotalTime(vector<call>& calls)
{
	for (size_t i = 0; i < calls.size() - 1; ++i)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < calls.size(); ++j)
		{
			if (calls[j].time.hours < calls[minIndex].time.hours ||
				(calls[j].time.hours == calls[minIndex].time.hours && calls[j].time.minutes < calls[minIndex].time.minutes) ||
				(calls[j].time.hours == calls[minIndex].time.hours && calls[j].time.minutes == calls[minIndex].time.minutes && calls[j].time.seconds < calls[minIndex].time.seconds))
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(calls[i], calls[minIndex]);
		}
	}
}

int compareCalls(const call& a, const call& b)
{
	Time totalTimeA = a.time;
	Time totalTimeB = b.time;

	// ����������� ����� � ������� ��� ���������
	int totalSecondsA = totalTimeA.hours * 3600 + totalTimeA.minutes * 60 + totalTimeA.seconds;
	int totalSecondsB = totalTimeB.hours * 3600 + totalTimeB.minutes * 60 + totalTimeB.seconds;

	return totalSecondsA < totalSecondsB;
}

int partition(vector<call>& calls, int low, int high)
{
	call pivot = calls[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (compareCalls(calls[j], pivot))
		{
			i++;
			swap(calls[i], calls[j]);
		}
	}
	swap(calls[i + 1], calls[high]);
	return (i + 1);
}

void quickSortByTotalTime(vector<call>& calls, int low, int high)
{
	if (low < high)
	{
		int pi = partition(calls, low, high);

		quickSortByTotalTime(calls, low, pi - 1);
		quickSortByTotalTime(calls, pi + 1, high);
	}
}

// ����� ��������������� ������ �� �����
void displaySortedCalls(const vector<call>& calls)
{
	Time totalSum; // ����� ����� ������� ����������

	for (const auto& call : calls)
	{
		cout << "����: " << call.date.day << '.' << call.date.month << '.' << call.date.year << '\n'
			<< "�����: " << call.time.hours << ':' << call.time.minutes << ':' << call.time.seconds << '\n'
			<< "���: " << call.code << '\n'
			<< "�����: " << call.town << '\n'
			<< "�����: " << call.tarife << '\n'
			<< "�������: " << call.numberPhone << '\n'
			<< "�������: " << call.numberAbonent << '\n'
			<< "----------------------------------------------------\n";

		totalSum.hours += call.time.hours;
		totalSum.minutes += call.time.minutes;
		totalSum.seconds += call.time.seconds;

		// ������������� ������� ��� ����� �����
		while (totalSum.seconds >= 60)
		{
			totalSum.minutes++;
			totalSum.seconds -= 60;
		}
		while (totalSum.minutes >= 60)
		{
			totalSum.hours++;
			totalSum.minutes -= 60;
		}
	}

	// ����� ����� ����� ������� ����������
	cout << "\n����� ����� ������� ����������: ";
	cout << totalSum.hours << " �����, ";
	cout << totalSum.minutes << " �����, ";
	cout << totalSum.seconds << " ������" << std::endl;
}

Time binarySearch(const vector<call>& calls, const string& searchCode) {
	int left = 0;
	int right = calls.size() - 1;
	Time totalTime;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (calls[mid].code == searchCode) {
			totalTime.hours += calls[mid].time.hours;
			totalTime.minutes += calls[mid].time.minutes;
			totalTime.seconds += calls[mid].time.seconds;

			// ������������� �������
			while (totalTime.seconds >= 60) {
				totalTime.minutes++;
				totalTime.seconds -= 60;
			}
			while (totalTime.minutes >= 60) {
				totalTime.hours++;
				totalTime.minutes -= 60;
			}
			return totalTime;
		}
		else if (calls[mid].code < searchCode) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return Time(); // ���������� ������ �����, ���� ��� �� ������
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice = 0;
	string searchCode;
	vector<call> calls;

	if (entry())
	{
		while ((choice = menu()) != 9) {
			switch (choice) {
			case 1:
				add();
				break;
			case 2:
				display();
				break;
			case 3:
			{
				ofstream file("data.txt", ios::trunc);
				if (file.is_open())
				{
					file.close();
					cout << "������ � ����� ������� �������!" << endl;
				}
				else
				{
					cout << "������ �������� �����" << endl;
				}
				break;
			}
			case 4:
				cout << "������� ��� ������ ��� ��������� ������: ";
				cin >> searchCode;
				displayCall(linearSearch(searchCode));
				break;
			case 5:
				readCallsFromFile(calls);
				selectionSortByTotalTime(calls);
				displaySortedCalls(calls);
				break;
			case 6:
				readCallsFromFile(calls);
				quickSortByTotalTime(calls, 0, calls.size() - 1);
				displaySortedCalls(calls);
				break;

			case 7:
				cout << "������� ��� ������ ��� ��������� ������: ";
				cin >> searchCode;
				readCallsFromFile(calls);
				displayCall(binarySearch(calls, searchCode));
				break;
			case 8:
				calculateTotalTime();
				break;
			default:
				cout << "�������� �����, ����������, ��������� �������." << endl;
				break;
			}
		}
	}

	cout << "�� ��������!" << endl;
	return 0;
}

int entry()//���� � ���������
{
	int choice;
	cout << "������������ ������ 5" << endl << "1 - ���� � ���������" << endl;
	cout << "2 - ����� �� ���������" << endl;
	do
	{
		cin >> choice;
		if (cin.fail() || (choice != 1 && choice != 2))
		{
			cout << endl << "������! ������� 1 ��� 2" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (choice != 1 && choice != 2);
	cin.ignore(INT_MAX, '\n');
	if (choice == 1)
	{
		system("cls");
		return 1;
	}
	else
	{
		return 0;
	}
}

int menu() {
	int choice;
	cout << "----------------------------------------------------\n";
	cout << "|                      ����                        |\n";
	cout << "|1 - �������� ������ � ����                        |\n";
	cout << "|2 - �������� ������ �� ����� � ������� �� �����   |\n";
	cout << "|3 - �������� ����                                 |\n";
	cout << "|4 - �������� ����� � �����                        |\n";
	cout << "|5 - ���������� ����� ������� ������� ������       |\n";
	cout << "|6 - ���������� ����� ������� QuickSort            |\n";
	cout << "|7 - �������� ����� � ��������������� �����        |\n";
	cout << "|8 - ��������� ����� ����� �������                 |\n";
	cout << "|9 - �����                                         |\n";
	cout << "----------------------------------------------------\n";
	cout << "��� �����: ";
	do {
		cin >> choice;
		if (cin.fail() || (choice < 1 || choice > 9)) {
			cout << endl << "������! ������� �� 1 �� 9" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (choice < 1 || choice > 9);
	cin.ignore();
	return choice;
}

int add()
{
	call callData;
	int day, month, year, hours, minutes, seconds;
	string code, town, tarife, numberPhone, numberAbonent;

	cout << "������� ���� ������ (���� ����� ��� ����� ������): ";
	while (!(cin >> day >> month >> year) || day < 1 || month < 1 || year < 1 || year > 2025 || month > 12 ||
		((month == 2 && day > (isLeapYear(year) ? 29 : 28)) ||
			((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || ((month == 1 || month == 3 || month == 5 ||
				month == 7 || month == 8 || month == 10 || month == 12) && day > 31)))
	{
		cout << "�������� ����. ����������, ������� �����: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	while (true) {
	    cout << "������� ��� ������ (3 �����): ";
		cin >> code;

		try {
			int codeAsInt = stoi(code);
			// ���� ��������� ����� �������� ����� ��� �����
			if (code.length() == 3) {
				break; 
			}
			else {
				cout << "������! ��� ������ ������ �������� ����� �� ���� ����." << std::endl;
			}
		}
		catch (const invalid_argument&) {
			cout << "������! ������� ������ �����." << std::endl;
		}
	}
	cout << "������� �������� ������: "; cin >> town;
	cout << "������� ����� ��������� (���� ������ ������� ����� ������): ";
	while (!(cin >> hours >> minutes >> seconds) || hours < 0 || hours > 23
		|| minutes < 0 || minutes > 59 || seconds < 0 || seconds > 59)
	{
		cout << "�������� ����. ����������, ������� �����: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}
	cout << "������� ����� (1 - ������������, 2 - �������������): "; cin >> tarife;
	cout << "������� ����� � ���� ������: 8" << code << " "; cin >> numberPhone;
	cout << "������� ����� �������� ��������: ";  cin >> numberAbonent;

	callData.date.setDate(day, month, year);
	callData.time.setTime(hours, minutes, seconds);
	callData.code = code;
	callData.town = town;
	callData.tarife = tarife;
	callData.numberPhone = numberPhone;
	callData.numberAbonent = numberAbonent;

	ofstream file("data.txt", ios::app);
	if (file.is_open()) 
	{
		
		file << callData.date.day << ' ' << callData.date.month << ' ' << callData.date.year << ' '
			<< callData.time.hours << ' ' << callData.time.minutes << ' ' << callData.time.seconds << ' '
			<< callData.code << ' ' << callData.town << ' ' << callData.tarife << ' '
			<< callData.numberPhone << ' ' << callData.numberAbonent << '\n';
		cout << "������ ������� ��������� � ����!" << endl;
		file.close();
	}
	else 
	{
		cout << "������ �������� �����" << endl;
	}

	return 0;
}

void display()
{
	ifstream file("data.txt");
	if (file.is_open())
	{
		call callData;
		bool hasRecords = false;

		while (file >> callData.date.day >> callData.date.month >> callData.date.year
			>> callData.time.hours >> callData.time.minutes >> callData.time.seconds
			>> callData.code >> callData.town >> callData.tarife
			>> callData.numberPhone >> callData.numberAbonent)
		{
			hasRecords = true;

			cout << "\n����: ";
			callData.date.getDate();
			cout << "\n�����: ";
			callData.time.getTime();

			cout << "\n���: " << callData.code
				<< "\n�����: " << callData.town
				<< "\n�����: " << callData.tarife
				<< "\n�������: " << callData.numberPhone
				<< "\n�������: " << callData.numberAbonent << endl;
			cout << "----------------------------------------------------\n";
		}

		file.close();

		if (!hasRecords)
		{
			cout << "������� � ����� ���." << endl;
		}
	}
	else
	{
		cout << "������ �������� �����" << endl;
	}
}