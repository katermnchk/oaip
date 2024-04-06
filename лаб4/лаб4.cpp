#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <utility>
#include <stdexcept>
#include <windows.h>

using namespace std;

struct node//элемент стека
{
    char data;
    node* next;
    node(char data) : data(data), next(nullptr) {}
};

class stack
{
private:
    node* top;
public:
    stack() : top(nullptr) {}//конструктор
    void push(char data)
    {
        node* newnode = new node(data);
        newnode->next = top;
        top = newnode;
    }
    char pop()
    {
        if (empty())
        {
            cout << "Стек пуст!";
        }
        char data = top->data;
        node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }
    char topData() const
    {
        if (empty())
        {
            cout << "Стек пуст!";
        }
        return top->data;
    }
    bool empty() const
    {
        return top == nullptr;
    }
};

static int priority(char symbol)//приоритет символов
{
    if (symbol == '+' || symbol == '-') return 1;
    if (symbol == '*' || symbol == '/') return 2;
    return 0; // если скобки
}

static string translate(const string& simple)
{
    stack operators;
    string polska = "";
    for (char token : simple)
    {
        if (isalpha(token))
        {
            polska += token; // + символ к строке
        }
        else if (isdigit(token))
        {
            polska += token; // + символ к строке
        }
        else if (token == '(')
        {
            operators.push(token);
        }
        else if (token == ')')
        {
            while (!operators.empty() && operators.topData() != '(')
            {
                polska += operators.pop();
            }
            if (!operators.empty() && operators.topData() == '(') 
            {
                operators.pop(); // удаляем '('
            }
        }
        else if (token == ' ')
        {
            continue;
        }
        else 
        { // операторы +, -, *, /
            while (!operators.empty() && priority(operators.topData()) >= priority(token)) 
            {
                polska += operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty())
    {
        polska += operators.pop();
    }

    return polska;
}

double evaluatePostfix(const string& polska, vector<pair<char, double>>& variables)
{
    stack operands;
    for (char token : polska)
    {
        if (isalpha(token))
        {
            auto it = find_if(variables.begin(), variables.end(), [&](const pair<char, double>& p) { return p.first == token; });
            if (it == variables.end()) // Проверяем, была ли уже введена переменная
            {
                double variable;
                cout << "Введите значение для переменной " << token << ": ";
                cin >> variable;
                variables.push_back(make_pair(token, variable)); // Добавляем переменную в вектор пар
                operands.push(variable);
            }
            else
            {
                operands.push(it->second); // Берем значение уже введенной переменной из вектора пар
            }
        }
        else if (isdigit(token))
        {
            operands.push(token - '0'); // Преобразуем символ в цифру и добавляем в стек
        }
        else if (token != ' ') 
        {
            double operand2 = operands.pop();
            double operand1 = operands.pop();
            switch (token) {
            case '+':
                operands.push(operand1 + operand2);
                break;
            case '-':
                operands.push(operand1 - operand2);
                break;
            case '*':
                operands.push(operand1 * operand2);
                break;
            case '/':
                if (operand2 == 0) 
                {
                    cout << "Ошибка: деление на ноль!";
                }
                operands.push(operand1 / operand2);
                break;
            }
        }
    }
    return operands.pop();
}

int entry() // вход в программу
{
    int choice;
    cout << "Лабораторная работа 4" << endl << "1 - Вход в программу" << endl;
    cout << "2 - Выход из программы" << endl;
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) // проверка на корректность ввода
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

int answer();

int task()
{
    string simple;
    cout << "Введите математическое выражение с буквенными переменными (только латинские символы): ";
    getline(cin, simple);
    vector<pair<char, double>> variables; // вектор для хранения введенных переменных
    for (char ch : simple)
    {
        if ((ch >= 'а' && ch <= 'я') || (ch >= 'А' && ch <= 'Я'))// проверка на рус буквы
        {
            cout << "Ошибка! Введите только латинские буквы." << endl;
            return 1;
        }
    }
    string postfix = translate(simple);
    cout << "Обратная польская запись: " << postfix << endl;
    try
    {
        double result = evaluatePostfix(postfix, variables);
        cout << "Результат вычислений: " << result << endl;
    }
    catch (const exception& e) 
    {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    if (entry())
    {
        do {
            task();
        } while (answer());
    }
    return 0;
}

int answer()
{
    int choice;
    cout << "Желаете продолжить?\n1 - Да\n2 - Нет\nВаш выбор: ";
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) // проверка на корректность ввода
        {
            cout << endl << "Ошибка! Введите 1 или 2" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
    } while (choice != 1 && choice != 2);
    cin.ignore();
    if (choice == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
