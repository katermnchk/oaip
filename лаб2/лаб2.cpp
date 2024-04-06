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

Stack* InStack(Stack* p, int in)//добавление элементов в стек
{
	Stack* t = new Stack;
	t->info = in;
	t->next = p;
	return t;
}

void View(Stack* p)//вывод на экран
{
	Stack* t = p;
	while (t != NULL)
	{
		cout << t->info << "  ";
		t = t->next;
	}
}

void Del_All(Stack** p)//удаление элементов стека
{
	Stack* t;
	while (*p != NULL)
	{
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

int Task(Stack** p);//прототип функции с заданием

int Sort_p(Stack** p);//прототип функции с сортировкой 1

int Sort_info(Stack* p);//прототип функции с сортировкой 2

int Sort();//прототип общей функции сортировки для меню

int begin()//вход в программу
{
	int choice;
	cout << endl << "1 - Вход в программу" << endl;
	cout << "2 - Выход из программы" << endl;
	do
	{
		cin >> choice;
		while (cin.fail()) //проверка на корректность ввода
		{
			cout << endl << "Ошибка!" << endl;
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
		cout << endl << "Ошибка! Введите число от 1 до 2" << endl;
		return begin();
	}
	}
}

int menu()//меню
{
	srand(time(NULL));
	int i, in, n, kod;
	while (true)
	{
		cout << "\tМеню\n1 - Создать стек\n2 - Добавить элементы в стек\n";
		cout << "3 - Вывести стек на экран\n4 - Очистить стек\n5 - Удалить элементы, оканчивающиеся на 5\n6 - Cортировка стека\n0 - Выход\nВаш выбор : ";
		scanf_s("%d", &kod);
		switch (kod)
		{
		case 1: case 2:
			if (kod == 1 && Begin != NULL)
			{
				// Если создаем новый стек, должны освободить память, занятую предыдущим
				cout << "\nОчистите память" << endl;
				cout << "\nДля продолжения нажмите на любую клавишу...";
				_getch();
				break;
			}
			else
				cout << "\nВведите количество элементов стека, которые вы хотите добавить = ";
			cin >> n;
			int choice_in;
			cout << "\n1 - Ввод случайных чисел\n2 - Ввод с клавиатуры\nВаш выбор: ";
			cin >> choice_in;
			for (i = 1; i <= abs(n); i++)
			{
				if (choice_in == 1)
				in = -20 + rand() % 41;
				else if (choice_in == 2)
				{
					cout << i << "-й элемент: ";
					cin >> in;
				}
				Begin = InStack(Begin, in);
			}
			if (kod == 1) cout << "Стек успешно создан\n" << endl;
			else cout << "\nВ стек добавлено элементы" << endl;
			answer();
			cout << "\nДля продолжения нажмите на любую клавишу...";
			_getch();
			break;
		case 3:
			if (!Begin)
			{
				cout << "\nСтек пуст!" << endl;
				return menu();
				break;
			}
			cout << "\n--- Стек ---" << endl;
			View(Begin);
			cout << "\nДля продолжения нажмите на любую клавишу...";
			_getch();
			break;
		case 4:
			Del_All(&Begin);
			cout << "Память очищена!" << endl;
			cout << "\nДля продолжения нажмите на любую клавишу...";
			_getch();
			break;
		case 5:
			Task(&Begin);
			cout << "\nДля продолжения нажмите на любую клавишу...";
			_getch();
			break;
		case 6:
			Sort();
			cout << "\nДля продолжения нажмите на любую клавишу...";
			_getch();
			break;
		case 0:
			if (Begin != NULL)
				Del_All(&Begin);
			system("cls");
			return 0;
		default: {cout << "Ошибка! Введите цифру от 0 до 6" << endl; return menu(); }
		}
		system("cls");
	}
}

int Sort()//общая функция сортировки для меню
{
	cout << "\n1 - Сортировка через перестановку адресов двух соседних элементов\n";
	cout << "2 - Сортировка через обмен информацией между текущим и следующим элементами\n";
	cout << "3 - Главное меню\n";
	cout << "Ваш выбор: ";
	int choice_sort;
	cin >> choice_sort;
	switch (choice_sort)
	{
	case 1: cout << Sort_p(&Begin); break;
	case 2: cout << Sort_info(Begin); break;
	case 3: system("cls"); return menu();
	}
}

int Sort_p(Stack** p)//сортировка 1
{
	if (*p == nullptr)
	{
		cout << "Стек пуст!" << endl;
		//return menu();
	}
	if (*p == NULL || (*p)->next == NULL) return 0;
	Stack* temp = new Stack;
	//временный элемент
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
	"\nСортировка выполнена";
	answer();
}

int Sort_info(Stack* p)//сортировка 2 
{
	Stack* t = NULL, * t1;
	int r;
	if (!Begin)
	{
		cout << "\nСтек пуст!" << endl;
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
		"\nСортировка выполнена";
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
		cout << "Стек пуст!" << endl;
		return menu();
	}
	cout << "\n--- Изначальный стек ---" << endl;
	View(Begin);
	Stack* prev = nullptr;
	Stack* current = *p;
	while (current != nullptr)
	{
		// Проверяем, заканчивается ли текущий элемент на 5
		if (abs(current->info) % 10 == 5)
		{
			// Если это первый элемент в списке
			if (current == *p)
			{
				*p = (*p)->next;
				delete current;
				current = *p;
			}
			else
			{
				// Если это не первый элемент в списке
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
	cout << "\nЛишние значения удалены!\nЖелаете посмотреть на новый стек? \nДа - 1.\nНет - 2." << endl;
	cout << "____________\nВаш выбор: ";
	int choice;
	do
	{
		cin >> choice;
		while (cin.fail()) //проверка на корректность ввода
		{
			cout << endl << "Ошибка!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return main();
		}
	} while (choice > 1 && choice < 2);
	switch (choice)
	{
	case 1:
		cout << "\n--- Новый стек ---" << endl;
		View(Begin);
		break;
	case 2:
		system("cls");
		return menu();
	default:
	{
		cout << endl << "Ошибка!" << endl;
		return menu();
	}
	}
}

int answer()
{
	cout << "\nЖелаете посмотреть на стек? \nДа - 1.\nНет - 2." << endl;
	cout << "____________\nВаш выбор: ";
	int choice;
	do
	{
		cin >> choice;
		while (cin.fail()) //проверка на корректность ввода
		{
			cout << endl << "Ошибка!" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return main();
		}
	} while (choice > 1 && choice < 2);
	switch (choice)
	{
	case 1:
		cout << "\n--- Cтек ---" << endl;
		View(Begin);
		break;
	case 2:
		system("cls");
		return menu();
	default:
	{
		cout << endl << "Ошибка!" << endl;
		return menu();
	}
	}
}