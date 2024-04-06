#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int Akkerman_rec(int, int);
int Akkerman(int, int);
int begin();
void output(int, int);


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int m, n;
    while (begin())
    {
        cout << endl <<"Введите число m(от 0 до 3): "; cin >> m;
        cout << "Введите число n(от 0 до 9): "; cin >> n;
        if (m < 0 || n < 0 || m > 3 || n > 9)
        {
            cout << "Введите другие числа!\n" << endl;
            return main();
        }
        else 
        {
            output(m, n);
        }
    }
}

int begin()
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

void output(int m, int n)
{
cout << endl << "1 - с рекурсией" << endl << "2 - без рекурсии" << endl << "3 - главное меню" << endl;
int flag;
cin >> flag;
switch (flag)
{
case 1: cout << endl << "Ответ: " << Akkerman_rec(m, n) << endl; return output(m, n);  break;
case 2: cout << endl << "Ответ: " << Akkerman(m, n) << endl; return output(m, n);  break;
case 3: return; break;
} }

/*Условие: A(0, n) = n + 1;
A(m, 0) = A(m–1, 1); при m > 0;
A(m, n) = A(m–1, A(m, n–1)); при m > 0 и n > 0.*/
int Akkerman_rec(int m, int n) 
{
        if (m == 0)
        {
            return n + 1;
        }
        else if (m > 0 && n == 0)
        {
            return Akkerman_rec(m - 1, 1);
        }
        else if (m > 0 && n > 0)
        {
            return Akkerman_rec(m - 1, Akkerman_rec(m, n - 1));
        }    
}

int Akkerman(int m, int n) {
    vector<int> s(2);
    s[0] = m; //m
    s[1] = n; //n
    for (int i = 1; i != 0;) //указывает на текущую позицию
    {
        if (s[i - 1] == 0) // если m = 0
        {
            s[i] = s[--i + 1] + 1; // i уменьшаю на 1 (s[0] - ответ), а s[i] (т.е. n) увеличиваю на 1
        }
        else if (s[i] == 0) // если n = 0
        {
            s[i] = 1; // n = 1
            --s[i - 1]; // m = m - 1
        }
        else 
        {
            if (s.size() == i + 1) s.resize(s.size() + 1); //изменяю размер вектора
            s[i + 1] = s[i] - 1; // т.к. n = A(m, n–1), то надо запомнить начальное n
            s[i] = s[i - 1]; //n = n - 1
            --s[i++ - 1]; //m = m - 1
        }
    }
    return s[0];
}

