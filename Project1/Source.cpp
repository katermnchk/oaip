#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <vector>
#include <utility>
#include <stdexcept>
#include <windows.h>
#include <cstdlib>

using namespace std;

struct node
{
    double data; // �������� ��� ������ � ����� � char �� double
    node* next;
    node(double data) : data(data), next(nullptr) {} // �������� ��� ������ � ������������
};

class stack
{
private:
    node* top;
public:
    stack() : top(nullptr) {}
    void push(double data) // �������� ��� ������ � ������ push
    {
        node* newnode = new node(data);
        newnode->next = top;
        top = newnode;
    }
    double pop() // �������� ��� ������ � ������ pop
    {
        if (empty())
        {
            cout << "���� ����!";
            return 0; // ���������� 0 � ������ ������� �����
        }
        double data = top->data;
        node* temp = top;
        top = top->next;
        delete temp;
        return data;
    }
    double topData() const // �������� ��� ������ � ������ topData
    {
        if (empty())
        {
            cout << "���� ����!";
            return 0; // ���������� 0 � ������ ������� �����
        }
        return top->data;
    }
    bool empty() const
    {
        return top == nullptr;
    }
};

static int priority(char symbol)
{
    if (symbol == '+' || symbol == '-') return 1;
    if (symbol == '*' || symbol == '/') return 2;
    return 0;
}

static string translate(const string& simple)
{
    stack operators;
    string polska = "";
    string number = "";
    bool hasDecimal = false;
    for (char token : simple)
    {
        if (isalpha(token))
        {
            polska += token;
        }
        else if (isdigit(token) || token == '.')
        {
            number += token;
            if (token == '.')
            {
                hasDecimal = true;
            }
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
                operators.pop();
            }
        }
        else if (token == ' ')
        {
            if (!number.empty())
            {
                polska += number + " ";
                number = "";
                hasDecimal = false;
            }
            continue;
        }
        else
        {
            if (!number.empty())
            {
                polska += number + " ";
                number = "";
                hasDecimal = false;
            }
            while (!operators.empty() && priority(operators.topData()) >= priority(token))
            {
                polska += operators.pop();
            }
            operators.push(token);
        }
    }

    if (!number.empty())
    {
        polska += number + " ";
    }

    while (!operators.empty())
    {
        polska += operators.pop();
    }

    return polska;
}

int answer();

double readNumber()
{
    double number;
    cin >> number;
    return number;
}


double evaluatePostfix(const string& polska, vector<pair<string, double>>& variables)
{
    stack operands;
    string number = "";
    for (int i = 0; i < polska.size(); ++i)
    {
        char token = polska[i];
        if (isalpha(token))
        {
            string variable = "";
            while (isalpha(token)) {
                variable += token;
                ++i;
                token = polska[i];
            }
            --i; // ������������ �� ���� ��� �����, ����� ��������� ��������� ������
            auto it = find_if(variables.begin(), variables.end(), [&](const pair<string, double>& p) { return p.first == variable; });
            if (it == variables.end())
            {
                double value;
                cout << "������� �������� ��� ���������� " << variable << ": ";
                value = readNumber();
                variables.push_back(make_pair(variable, value));

                operands.push(value);
            }
            else
            {
                operands.push(it->second);
            }
        }
        else if (isdigit(token) || token == '.')
        {
            number += token;
        }
        else if (token == ' ' && !number.empty())
        {
            double num = stod(number);
            operands.push(num);
            number = "";
        }
        else if (token != ' ')
        {
            double operand2 = operands.pop();
            double operand1 = operands.pop();
            switch (token)
            {
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
                    cout << "�� ���� ������ ������!" << endl;
                    return 0;
                }
                operands.push(operand1 / operand2);
                break;
            }
        }
    }
    if (!number.empty())
    {
        double num = stod(number);
        operands.push(num);
    }
    double result = operands.pop();
    cout << "��������� ����������: " << fixed << setprecision(2) << result << endl;
    return result;
}


int entry()
{
    int choice;
    cout << "������������ ������ 4" << endl << "1 - ���� � ���������" << endl;
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

int task()
{
    string simple;
    cout << "������� �������������� ��������� � ���������� ����������� (������ ��������): ";
    getline(cin, simple);
    vector<pair<string, double>> variables;
    for (char ch : simple)
    {
        if ((ch >= '�' && ch <= '�') || (ch >= '�' && ch <= '�'))
        {
            cout << "������! ������� ������ ��������� �����." << endl;
            return 1;
        }
    }
    string postfix = translate(simple);
    cout << "�������� �������� ������: " << postfix << endl;
    double result = evaluatePostfix(postfix, variables);
    return 1;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    if (entry())
    {
        do
        {
            task();
        } while (answer());
    }
    return 0;
}

int answer()
{
    int choice;
    cout << "������� ����������?\n1 - ��\n2 - ���\n��� �����: ";
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