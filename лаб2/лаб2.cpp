#include <iostream>
#include <stack>
#include <random>
#include <Windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct Stack
{
	int info;
	Stack* next;
} *Begin;

int answer();

Stack* InStack(Stack* p, int in)//���������� ��������� � ����
{
	Stack* t = new Stack;
	t->info = in;
	t->next = p;
	return t;
}

void View(Stack* p)//����� �� �����
{
	Stack* t = p;
	while (t != NULL)
	{
		cout << t->info << "  ";
		t = t->next;
	}
}

void Del_All(Stack** p)//�������� ��������� �����
{
	Stack* t;
	while (*p != NULL)
	{
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

int Task(Stack** p);//�������� ������� � ��������

int Sort_p(Stack** p);//�������� ������� � ����������� 1

int Sort_info(Stack* p);//�������� ������� � ����������� 2

int Sort();//�������� ����� ������� ���������� ��� ����

int begin()//���� � ���������
{
	int choice;
	cout << endl << "1 - ���� � ���������" << endl;
	cout << "2 - ����� �� ���������" << endl;
	do
	{
		cin >> choice;
		while (cin.fail()) //�������� �� ������������ �����
		{
			cout << endl << "������!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return begin();
		}
	} while (choice > 1 && choice < 2);
	switch (choice)
	{
	case 1:
		system("cls");
		return 1;
	case 2:
		return 0;
	default:
	{
		cout << endl << "������! ������� ����� �� 1 �� 2" << endl;
		return begin();
	}
	}
}

int menu()//����
{
	srand(time(NULL));
	int i, in, n, kod;
	while (true)
	{
		cout << "\t����\n1 - ������� ����\n2 - �������� �������� � ����\n";
		cout << "3 - ������� ���� �� �����\n4 - �������� ����\n5 - ������� ��������, �������������� �� 5\n6 - C��������� �����\n0 - �����\n��� ����� : ";
		scanf_s("%d", &kod);
		switch (kod)
		{
		case 1: case 2:
			if (kod == 1 && Begin != NULL)
			{
				// ���� ������� ����� ����, ������ ���������� ������, ������� ����������
				cout << "\n�������� ������" << endl;
				cout << "\n��� ����������� ������� �� ����� �������...";
				_getch();
				break;
			}
			else
				cout << "\n������� ���������� ��������� �����, ������� �� ������ �������� = ";
			cin >> n;
			int choice_in;
			cout << "\n1 - ���� ��������� �����\n2 - ���� � ����������\n��� �����: ";
			cin >> choice_in;
			for (i = 1; i <= abs(n); i++)
			{
				if (choice_in == 1)
				in = -20 + rand() % 41;
				else if (choice_in == 2)
				{
					cout << i << "-� �������: ";
					cin >> in;
				}
				Begin = InStack(Begin, in);
			}
			if (kod == 1) cout << "���� ������� ������\n" << endl;
			else cout << "\n� ���� ��������� ��������" << endl;
			answer();
			cout << "\n��� ����������� ������� �� ����� �������...";
			_getch();
			break;
		case 3:
			if (!Begin)
			{
				cout << "\n���� ����!" << endl;
				return menu();
				break;
			}
			cout << "\n--- ���� ---" << endl;
			View(Begin);
			cout << "\n��� ����������� ������� �� ����� �������...";
			_getch();
			break;
		case 4:
			Del_All(&Begin);
			cout << "������ �������!" << endl;
			cout << "\n��� ����������� ������� �� ����� �������...";
			_getch();
			break;
		case 5:
			Task(&Begin);
			cout << "\n��� ����������� ������� �� ����� �������...";
			_getch();
			break;
		case 6:
			Sort();
			cout << "\n��� ����������� ������� �� ����� �������...";
			_getch();
			break;
		case 0:
			if (Begin != NULL)
				Del_All(&Begin);
			system("cls");
			return 0;
		default: {cout << "������! ������� ����� �� 0 �� 6" << endl; return menu(); }
		}
		system("cls");
	}
}

int Sort()//����� ������� ���������� ��� ����
{
	cout << "\n1 - ���������� ����� ������������ ������� ���� �������� ���������\n";
	cout << "2 - ���������� ����� ����� ����������� ����� ������� � ��������� ����������\n";
	cout << "3 - ������� ����\n";
	cout << "��� �����: ";
	int choice_sort;
	cin >> choice_sort;
	switch (choice_sort)
	{
	case 1: cout << Sort_p(&Begin); break;
	case 2: cout << Sort_info(Begin); break;
	case 3: system("cls"); return menu();
	}
}

int Sort_p(Stack** p)//���������� 1
{
	if (*p == nullptr)
	{
		cout << "���� ����!" << endl;
		//return menu();
	}
	if (*p == NULL || (*p)->next == NULL) return 0;
	Stack* temp = new Stack;
	//��������� �������
	temp->info = 0;
	temp->next = *p;
	*p = temp;
	Stack* t = NULL, * t1, * r;
	do {
		for (t1 = *p; t1->next->next != t; t1 = t1->next) {
			if (t1->next->info > t1->next->next->info) {
				r = t1->next->next;
				t1->next->next = r->next;
				r->next = t1->next;
				t1->next = r;
			}
		}
		t = t1->next;
	} while ((*p)->next->next != t);
	temp = *p;
	*p = (*p)->next;
	delete temp;
	"\n���������� ���������";
	answer();
}

int Sort_info(Stack* p)//���������� 2 
{
	Stack* t = NULL, * t1;
	int r;
	if (!Begin)
	{
		cout << "\n���� ����!" << endl;
		return menu();
		//break;
	}
	else
	{
		do {
			for (t1 = p; t1->next != t; t1 = t1->next)
			{
				if (t1->info > t1->next->info) {
					r = t1->info;
					t1->info = t1->next->info;
					t1->next->info = r;
				}
			}
			t = t1;
		} while (p->next != t);
		"\n���������� ���������";
		answer();
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (begin())
	{
		menu();
	}
}

int Task(Stack** p)
{
	if (*p == nullptr)
	{
		cout << "���� ����!" << endl;
		return menu();
	}
	cout << "\n--- ����������� ���� ---" << endl;
	View(Begin);
	Stack* prev = nullptr;
	Stack* current = *p;
	while (current != nullptr)
	{
		// ���������, ������������� �� ������� ������� �� 5
		if (abs(current->info) % 10 == 5)
		{
			// ���� ��� ������ ������� � ������
			if (current == *p)
			{
				*p = (*p)->next;
				delete current;
				current = *p;
			}
			else
			{
				// ���� ��� �� ������ ������� � ������
				prev->next = current->next;
				delete current;
				current = prev->next;
			}
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	cout << "\n������ �������� �������!\n������� ���������� �� ����� ����? \n�� - 1.\n��� - 2." << endl;
	cout << "____________\n��� �����: ";
	int choice;
	do
	{
		cin >> choice;
		while (cin.fail()) //�������� �� ������������ �����
		{
			cout << endl << "������!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return main();
		}
	} while (choice > 1 && choice < 2);
	switch (choice)
	{
	case 1:
		cout << "\n--- ����� ���� ---" << endl;
		View(Begin);
		break;
	case 2:
		system("cls");
		return menu();
	default:
	{
		cout << endl << "������!" << endl;
		return menu();
	}
	}
}

int answer()
{
	cout << "\n������� ���������� �� ����? \n�� - 1.\n��� - 2." << endl;
	cout << "____________\n��� �����: ";
	int choice;
	do
	{
		cin >> choice;
		while (cin.fail()) //�������� �� ������������ �����
		{
			cout << endl << "������!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return main();
		}
	} while (choice > 1 && choice < 2);
	switch (choice)
	{
	case 1:
		cout << "\n--- C��� ---" << endl;
		View(Begin);
		break;
	case 2:
		system("cls");
		return menu();
	default:
	{
		cout << endl << "������!" << endl;
		return menu();
	}
	}
}