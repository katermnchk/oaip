#include <iostream>
#include <stack>
#include <random>
#include <Windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

struct Spis2
{
    int info;
    Spis2* next, * prev;
} *Begin, * End, * t;

void CreateSpis2(Spis2**, Spis2**, int);
void AddSpis2(int, Spis2**, Spis2**, int);
void ViewSpis2(int, Spis2*);
void DelAll(Spis2**);
int Task(Spis2**);

int begin()//вход в программу
{
    int choice;
    cout << "Лабораторная работа 3" << endl << "1 - Вход в программу" << endl;
    cout << "2 - Выход из программы" << endl;
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) //проверка на корректность ввода
        {
            cout << endl << "Ошибка! Введите 1 или 2" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (choice != 1 && choice != 2);
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

static int menu()//меню
{
    srand(time(NULL));
    int kod, kod1;
    char Str[2][14] = { "начало ", "конец " };
    while (true)
    {
        cout << "\tМеню\nСоздать список - 1\nДобавить элементы - 2\nПосмотреть список - 3\nУдалить все элементы - 4\nУдалить элементы, оканчивающиеся на 5 - 5\nВыход - 0\nВаш выбор: ";
        cin >> kod;
        if (cin.fail() || (kod < 0 || kod > 5)) //проверка на корректность ввода
        {
            cout << "Ошибка! Введите число от 0 до 5\n" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        switch (kod)
        {
        case 1:
            if (Begin != NULL)
            {
                cout << "Очистите память!" << endl;
                cout << endl << "Нажмите на любую клавишу для продолжения...";
                _getch();
                break;
            }
            int n;
            cout << "\nВведите количество элементов списка = ";
            cin >> n;
            if (cin.fail())
            {
                cout << "Ошибка! Введите целое число" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            CreateSpis2(&Begin, &End, n);
            cout << endl << "Нажмите на любую клавишу для продолжения...";
            _getch();
            break;
        case 2:
            if (Begin == NULL)
            {
                cout << "Создайте список!" << endl;
                cout << endl << "Нажмите на любую клавишу для продолжения...";
                _getch();
                break;
            }
            int n_add;
            cout << "\nВведите количество элементов, которые хотите добавить: = ";
            cin >> n_add;
            if (cin.fail())
            {
                cout << "Ошибка! Введите целое число" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            cout << "Добавить в начало - 0\nДобавить в конец - 1\nВаш выбор: ";
            cin >> kod1;
            if (cin.fail() || (kod1 != 0 && kod1 != 1))
            {
                cout << "Ошибка! Введите 0 или 1" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            AddSpis2(kod1, &Begin, &End, n_add);
            if (kod1 == 0) t = Begin;
            else t = End;
            cout << "Добавлено в " << Str[kod1] << n_add << " элементов" << endl;
            cout << endl << "Нажмите на любую клавишу для продолжения...";
            _getch();
            break;
        case 3:
            if (!Begin)
            {
                cout << endl << "Список пуст!" << endl;
                cout << endl << "Нажмите на любую клавишу для продолжения...";
                _getch();
                break;
            }
            int kod1;
            cout << "Посмотреть с начала - 0\nПосмотреть с конца - 1\nВаш выбор: ";
            cin >> kod1;
            if (cin.fail() || (kod1 != 0 && kod1 != 1))
            {
                cout << "Ошибка! Введите 0 или 1" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            if (kod1 == 0)
            {
                t = Begin;
                cout << "-- Начало --" << endl;
            }
            else
            {
                t = End;
                cout << "--- Конец --" << endl;
            }
            ViewSpis2(kod1, t);
            cout << endl << "Нажмите на любую клавишу для продолжения...";
            _getch();
            break;
        case 4:
            DelAll(&Begin);
            cout << "Память очищена!" << endl;
            cout << endl << "Нажмите на любую клавишу для продолжения...";
            _getch();
            break;
        case 5:
            Task(&Begin);
            cout << endl << "Нажмите на любую клавишу для продолжения...";
            _getch();
            break;
        case 0:
            if (Begin != NULL) DelAll(&Begin);
            return 0;
        default:
            cout << "Ошибка! Введите цифру от 0 до 5" << endl;
            cout << endl << "Нажмите на любую клавишу для продолжения...";
            _getch();
        }
        system("cls");
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (begin())
    {
        return menu();
    }
}

void CreateSpis2(Spis2** b, Spis2** e, int n)
{
    while (n <= 0) 
    {
        cout << "Ошибка! Нельзя создать список с неположительным количеством элементов. \nВведите положительное число: ";
        cin >> n;
    }
    int in, choice_in;
    t = new Spis2;
    cout << "\n1 - Ввод случайных чисел\n2 - Ввод с клавиатуры\nВаш выбор: ";
			cin >> choice_in;
            while (cin.fail() || (choice_in != 1 && choice_in != 2)) // Проверка на корректность ввода
            {
                cout << "Ошибка! Введите 1 или 2: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> choice_in;
            }
            if (choice_in == 1)
            {
                in = -20 + rand() % 50;
                t->info = in;
                t->prev = NULL;
                *b = t;
                for (int i = 1; i < n; i++)
                {
                    t->next = new Spis2;
                    t->next->prev = t;
                    t = t->next;
                    in = -20 + rand() % 50;
                    t->info = in;

                }
                t->next = NULL;
                *e = t;
            }
            else 
            {
                cout << "1-й элемент: ";
                cin >> in;
                t->info = in;
                t->prev = NULL;
                *b = t;
                for (int i = 2; i <= n; i++)
                {
                    t->next = new Spis2;
                    t->next->prev = t;
                    t = t->next;
                    cout << i << "-й элемент: ";
                    cin >> in;
                    t->info = in;

                }
                t->next = NULL;
                *e = t;
            }
            cout << "Создан список из " << n << " элементов" << endl;
}

void AddSpis2(int kod, Spis2** b, Spis2** e, int n)
{
    while (n <= 0)
    {
        cout << "Ошибка! Нельзя создать стек с неположительным количеством элементов. \nВведите положительное число: ";
        cin >> n;
    }
        int in, choice_in;
        if (kod == 0)
        {
            cout << "\n1 - Ввод случайных чисел\n2 - Ввод с клавиатуры\nВаш выбор: ";
            cin >> choice_in;
            while (cin.fail() || (choice_in != 1 && choice_in != 2)) // Проверка на корректность ввода
            {
                cout << "Ошибка! Введите 1 или 2: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> choice_in;
            }
            for (int i = 1; i <= n; i++)
            {
                t = new Spis2;
                if (choice_in == 1)
                in = -20 + rand() % 50;
                else
                {
                    cout << i << "-й элемент: ";
                    cin >> in;
                }
                t->info = in;
                t->next = *b;
                if (*b != nullptr)
                    (*b)->prev = t;
                else
                    *e = t;
                t->prev = nullptr;
                *b = t;
            }
        }
        else
        {
            cout << "\n1 - Ввод случайных чисел\n2 - Ввод с клавиатуры\nВаш выбор: ";
            cin >> choice_in;
            for (int i = 1; i <= n; i++)
            {
                t = new Spis2;
                if (choice_in == 1)
                    in = -20 + rand() % 50;
                else
                {
                    cout << i << "-й элемент: ";
                    cin >> in;
                }
                t->info = in;
                t->prev = *e;
                if (*e != nullptr)
                    (*e)->next = t;
                else
                    *b = t;
                t->next = nullptr;
                *e = t;
            }
        }
}

void ViewSpis2(int kod, Spis2* t)
{
    if (kod == 0)
    {
        while (t != NULL)
        {
            cout << t->info << " ";
            t = t->next;
        }
    }
    else
    {
        while (t != NULL)
        {
            cout << t->info << " ";
            t = t->prev;
        }
    }
}

void DelAll(Spis2** p)
{
    Spis2* t;
    while (*p != NULL)
    {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
}

int Task(Spis2** p)
{
    if (*p == nullptr)
    {
        cout << "Список пуст!" << endl;
        return menu();
    }
    cout << "\n--- Изначальный стек ---" << endl;
    ViewSpis2(0, *p);
    Spis2* prev = nullptr;
    Spis2* current = *p;
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
    cin >> choice;
    if (cin.fail() || (choice != 1 && choice != 2))
    {
        cout << endl << "Ошибка!" << endl;
        return menu();
    }
    switch (choice)
    {
    case 1:
        cout << "\n--- Новый стек ---" << endl;
        ViewSpis2(0, *p);
        break;
    case 2:
        system("cls");
        return menu();
    default:
        cout << endl << "Ошибка!" << endl;
        return menu();
    }
}
