#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <cmath>
#include <string>
#include <limits>

using namespace std;

// Вход в программу
int entry()
{
    int choice;
    cout << "Лабораторная работа 7" << endl << "1 - Вход в программу" << endl;
    cout << "2 - Выход из программы" << endl;
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2))
        {
            cout << endl << "Ошибка! Введите 1 или 2" << endl;
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

struct Book
{
    string title;
    int pages;
    int year;
};

// Хеш-функция
int hashFunction(int key, int m)
{
    double drob, intpart, pi;
    int a;
    pi = 0.6180339887;
   // drob = modf(pi, &intpart);
    //a = (int)(drob * m);
    a = (int)(m * (key * pi - (int)(key*pi)));
    return a;
}

static void sv_add(int inf, int m, int* H)
{
    int i = hashFunction(inf, m);
    while (H[i] != -1)
    {
        i = (i + 1) % m;
    }
    H[i] = inf;
}

void sv_add2(const Book& book, int m, Book* H)
{
    int i = hashFunction(book.pages, m);
    int k = 1;
    while (H[i].pages != -1) {
        i = (i + k * k) % m;
        k++;
    }
    H[i] = book;
}

static int sv_search(int inf, int m, int H[])
{
    int i = hashFunction(inf, m);
    int start = i;
    while (H[i] != -1)
    {
        if (H[i] == inf) return i;
        i = (i + 1) % m;
        if (i == start) break;
    }
    return -1;
}

static int sv_search2(int pages, int m, const Book* H)
{
    int i = hashFunction(pages, m);
    int k = 1;
    int start = i;
    while (H[i].pages != -1)
    {
        if (H[i].pages == pages) return i;
        i = (i + k * k) % m;
        k++;
        if (i == start) break; 
    }
    return -1;
}

static void clearIn()
{
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

int menu()
{
    int choice;
    cout << "---------------------------\n";
    cout << "|           МЕНЮ          |\n";
    cout << "|1 - Задание 1            |\n";
    cout << "|2 - Задание 2            |\n";
    cout << "|0 - Выход                |\n";
    cout << "---------------------------\n";
    cout << "Ваш выбор: ";
    do
    {
        cin >> choice;
        if (cin.fail() || (choice < 0 || choice > 2))
        {
            cout << endl << "Ошибка! Введите от 0 до 2: " << endl;
            clearIn();
        }
    } while (choice < 0 || choice > 2);
    return choice;
}

int getInputMethod()
{
    int choice;
    cout << "----------------------------\n";
    cout << "|   Выбор метода ввода     |\n";
    cout << "|1 - Ввести вручную        |\n";
    cout << "|2 - Лень вводить вручную  |\n";
    cout << "----------------------------\n";
    cout << "Ваш выбор: ";
    do
    {
        cin >> choice;
        if (cin.fail() || (choice < 1 || choice > 2))
        {
            cout << endl << "Ошибка! Введите 1 или 2: " << endl;
            clearIn();
        }
    } while (choice < 1 || choice > 2);
    return choice;
}

bool isValidIntegerInput(int& input) {
    if (cin.fail() || input < 0) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    return true;
}

bool isValidYearInput(int& input) {
    if (cin.fail() || input < 0 || input > 2024) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        return false;
    }
    return true;
}

void task1()
{
    const int n = 16;
    const int m = 20;
    const int range_min = 45000;
    const int range_max = 76000;
    vector<int> mas(n);
    int input_method = getInputMethod();

    if (input_method == 1) // Ввод вручную
    {
        for (int i = 0; i < n; ++i)
        {
            cout << "Введите элемент " << i + 1 << ": ";
            cin >> mas[i];
            while (cin.fail())
            {
                cout << "Ошибка! Введите целое число: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> mas[i];
            }
        }
    }
    else // Рандом
    {
        srand(time(0));
        for (int i = 0; i < n; ++i)
        {
            mas[i] = rand() % (range_max - range_min + 1) + range_min;
        }
    }

    int H[m];
    for (int i = 0; i < m; i++)
    {
        H[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        sv_add(mas[i], m, H);
    }

    cout << "Заданный массив: ";
    for (int i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
    cout << "------------------------\n";
    cout << "Хеш-таблица:\n";
    for (int i = 0; i < m; i++)
    {
        if (H[i] == -1)
        {
            cout << i << ": None\n";
        }
        else
        {
            cout << i << ": " << H[i] << endl;
        }
    }
    cout << endl;

    int ss = 0, ii;
    while (true)
    {
        cout << "Введите значение для поиска (-1 для выхода): ";
        cin >> ss;
        if (ss == -1) break;
        ii = sv_search(ss, m, H);
        if (ii == -1)
        {
            cout << "Элемент не найден" << endl;
        }
        else
        {
            cout << "Элемент " << H[ii] << " найден под индексом " << ii << endl;
        }
    }
}

void task2()
{
    const int n = 9;
    const int m = 20;
    vector<Book> books(n);
    int input_method = getInputMethod();

    if (input_method == 1) // Ввод вручную
    {
        for (int i = 0; i < n; ++i)
        {
            cout << "Введите название книги " << i + 1 << ": ";
            clearIn(); 
            getline(cin, books[i].title);

            int pages;
            do {
                cout << "Введите количество страниц в книге " << i + 1 << ": ";
                cin >> pages;
                if (!isValidIntegerInput(pages)) {
                    cout << "Ошибка! Введите положительное целое число." << endl;
                }
            } while (!isValidIntegerInput(pages));
            books[i].pages = pages;

            int year;
            do {
                cout << "Введите год издания книги " << i + 1 << ": ";
                cin >> year;
                if (!isValidYearInput(year)) {
                    cout << "Ошибка! Введите положительное целое число до 2024." << endl;
                }
            } while (!isValidYearInput(year));
            books[i].year = year;
        }
    }
    else 
    {
        books = {
            {"1984", 150, 2010},
            {"Маленький принц", 200, 2015},
            {"Мы", 300, 2000},
            {"Мастер и Маргарита", 120, 1995},
            {"Мартин Иден", 180, 2018},
            {"Портрет Дориана Грея", 220, 2011},
            {"Сэрдца на далоні", 330, 1980},
            {"Дикая охота Короля Стаха", 145, 1985},
            {"О дивный новый мир", 175, 1999}
        };
    }

    Book H[m];
    for (int i = 0; i < m; ++i)
    {
        H[i].pages = -1;
    }

    for (int i = 0; i < n; ++i)
    {
        sv_add2(books[i], m, H);
    }

    cout << "Исходный массив книг:" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "Название: " << books[i].title << " Количество страниц: " << books[i].pages << " Год: " << books[i].year << endl;
    }
    cout << endl;

    cout << "Хеш-таблица:" << endl;
    for (int i = 0; i < m; ++i)
    {
        if (H[i].pages == -1)
        {
            cout << i << ": None" << endl;
        }
        else
        {
            cout << i << ": Название: " << H[i].title << " Количество страниц: " << H[i].pages << " Год: " << H[i].year << endl;
        }
    }
    cout << endl;

    int pages_to_search;
    while (true)
    {
        cout << "Введите количество страниц для поиска (-1 для выхода): ";
        cin >> pages_to_search;
        if (pages_to_search == -1) break;
        int index = sv_search2(pages_to_search, m, H);
        if (index == -1)
        {
            cout << "Книга с " << pages_to_search << " страницами не найдена." << endl;
        }
        else {
            cout << "Книга найдена под индексом " << index << ": Название: " << H[index].title << " Количество страниц: " << H[index].pages << " Год: " << H[index].year << endl;
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int choice;
    if (entry())
    {
        while ((choice = menu()) != 0)
        {
            switch (choice)
            {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 0:
                return 0;
            }
        }
    }
}
