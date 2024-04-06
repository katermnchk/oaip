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

int begin()//���� � ���������
{
    int choice;
    cout << "������������ ������ 3" << endl << "1 - ���� � ���������" << endl;
    cout << "2 - ����� �� ���������" << endl;
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) //�������� �� ������������ �����
        {
            cout << endl << "������! ������� 1 ��� 2" << endl;
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

static int menu()//����
{
    srand(time(NULL));
    int kod, kod1;
    char Str[2][14] = { "������ ", "����� " };
    while (true)
    {
        cout << "\t����\n������� ������ - 1\n�������� �������� - 2\n���������� ������ - 3\n������� ��� �������� - 4\n������� ��������, �������������� �� 5 - 5\n����� - 0\n��� �����: ";
        cin >> kod;
        if (cin.fail() || (kod < 0 || kod > 5)) //�������� �� ������������ �����
        {
            cout << "������! ������� ����� �� 0 �� 5\n" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        switch (kod)
        {
        case 1:
            if (Begin != NULL)
            {
                cout << "�������� ������!" << endl;
                cout << endl << "������� �� ����� ������� ��� �����������...";
                _getch();
                break;
            }
            int n;
            cout << "\n������� ���������� ��������� ������ = ";
            cin >> n;
            if (cin.fail())
            {
                cout << "������! ������� ����� �����" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            CreateSpis2(&Begin, &End, n);
            cout << endl << "������� �� ����� ������� ��� �����������...";
            _getch();
            break;
        case 2:
            if (Begin == NULL)
            {
                cout << "�������� ������!" << endl;
                cout << endl << "������� �� ����� ������� ��� �����������...";
                _getch();
                break;
            }
            int n_add;
            cout << "\n������� ���������� ���������, ������� ������ ��������: = ";
            cin >> n_add;
            if (cin.fail())
            {
                cout << "������! ������� ����� �����" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            cout << "�������� � ������ - 0\n�������� � ����� - 1\n��� �����: ";
            cin >> kod1;
            if (cin.fail() || (kod1 != 0 && kod1 != 1))
            {
                cout << "������! ������� 0 ��� 1" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            AddSpis2(kod1, &Begin, &End, n_add);
            if (kod1 == 0) t = Begin;
            else t = End;
            cout << "��������� � " << Str[kod1] << n_add << " ���������" << endl;
            cout << endl << "������� �� ����� ������� ��� �����������...";
            _getch();
            break;
        case 3:
            if (!Begin)
            {
                cout << endl << "������ ����!" << endl;
                cout << endl << "������� �� ����� ������� ��� �����������...";
                _getch();
                break;
            }
            int kod1;
            cout << "���������� � ������ - 0\n���������� � ����� - 1\n��� �����: ";
            cin >> kod1;
            if (cin.fail() || (kod1 != 0 && kod1 != 1))
            {
                cout << "������! ������� 0 ��� 1" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                break;
            }
            if (kod1 == 0)
            {
                t = Begin;
                cout << "-- ������ --" << endl;
            }
            else
            {
                t = End;
                cout << "--- ����� --" << endl;
            }
            ViewSpis2(kod1, t);
            cout << endl << "������� �� ����� ������� ��� �����������...";
            _getch();
            break;
        case 4:
            DelAll(&Begin);
            cout << "������ �������!" << endl;
            cout << endl << "������� �� ����� ������� ��� �����������...";
            _getch();
            break;
        case 5:
            Task(&Begin);
            cout << endl << "������� �� ����� ������� ��� �����������...";
            _getch();
            break;
        case 0:
            if (Begin != NULL) DelAll(&Begin);
            return 0;
        default:
            cout << "������! ������� ����� �� 0 �� 5" << endl;
            cout << endl << "������� �� ����� ������� ��� �����������...";
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
        cout << "������! ������ ������� ������ � ��������������� ����������� ���������. \n������� ������������� �����: ";
        cin >> n;
    }
    int in, choice_in;
    t = new Spis2;
    cout << "\n1 - ���� ��������� �����\n2 - ���� � ����������\n��� �����: ";
			cin >> choice_in;
            while (cin.fail() || (choice_in != 1 && choice_in != 2)) // �������� �� ������������ �����
            {
                cout << "������! ������� 1 ��� 2: ";
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
                cout << "1-� �������: ";
                cin >> in;
                t->info = in;
                t->prev = NULL;
                *b = t;
                for (int i = 2; i <= n; i++)
                {
                    t->next = new Spis2;
                    t->next->prev = t;
                    t = t->next;
                    cout << i << "-� �������: ";
                    cin >> in;
                    t->info = in;

                }
                t->next = NULL;
                *e = t;
            }
            cout << "������ ������ �� " << n << " ���������" << endl;
}

void AddSpis2(int kod, Spis2** b, Spis2** e, int n)
{
    while (n <= 0)
    {
        cout << "������! ������ ������� ���� � ��������������� ����������� ���������. \n������� ������������� �����: ";
        cin >> n;
    }
        int in, choice_in;
        if (kod == 0)
        {
            cout << "\n1 - ���� ��������� �����\n2 - ���� � ����������\n��� �����: ";
            cin >> choice_in;
            while (cin.fail() || (choice_in != 1 && choice_in != 2)) // �������� �� ������������ �����
            {
                cout << "������! ������� 1 ��� 2: ";
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
                    cout << i << "-� �������: ";
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
            cout << "\n1 - ���� ��������� �����\n2 - ���� � ����������\n��� �����: ";
            cin >> choice_in;
            for (int i = 1; i <= n; i++)
            {
                t = new Spis2;
                if (choice_in == 1)
                    in = -20 + rand() % 50;
                else
                {
                    cout << i << "-� �������: ";
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
        cout << "������ ����!" << endl;
        return menu();
    }
    cout << "\n--- ����������� ���� ---" << endl;
    ViewSpis2(0, *p);
    Spis2* prev = nullptr;
    Spis2* current = *p;
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
    cin >> choice;
    if (cin.fail() || (choice != 1 && choice != 2))
    {
        cout << endl << "������!" << endl;
        return menu();
    }
    switch (choice)
    {
    case 1:
        cout << "\n--- ����� ���� ---" << endl;
        ViewSpis2(0, *p);
        break;
    case 2:
        system("cls");
        return menu();
    default:
        cout << endl << "������!" << endl;
        return menu();
    }
}
