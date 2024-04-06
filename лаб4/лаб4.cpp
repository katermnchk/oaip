#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <utility>
#include <stdexcept>
#include <windows.h>

using namespace std;

struct node//������� �����
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
    stack() : top(nullptr) {}//�����������
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
            cout << "���� ����!";
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
            cout << "���� ����!";
        }
        return top->data;
    }
    bool empty() const
    {
        return top == nullptr;
    }
};

static int priority(char symbol)//��������� ��������
{
    if (symbol == '+' || symbol == '-') return 1;
    if (symbol == '*' || symbol == '/') return 2;
    return 0; // ���� ������
}

static string translate(const string& simple)
{
    stack operators;
    string polska = "";
    for (char token : simple)
    {
        if (isalpha(token))
        {
            polska += token; // + ������ � ������
        }
        else if (isdigit(token))
        {
            polska += token; // + ������ � ������
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
                operators.pop(); // ������� '('
            }
        }
        else if (token == ' ')
        {
            continue;
        }
        else 
        { // ��������� +, -, *, /
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
            if (it == variables.end()) // ���������, ���� �� ��� ������� ����������
            {
                double variable;
                cout << "������� �������� ��� ���������� " << token << ": ";
                cin >> variable;
                variables.push_back(make_pair(token, variable)); // ��������� ���������� � ������ ���
                operands.push(variable);
            }
            else
            {
                operands.push(it->second); // ����� �������� ��� ��������� ���������� �� ������� ���
            }
        }
        else if (isdigit(token))
        {
            operands.push(token - '0'); // ����������� ������ � ����� � ��������� � ����
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
                    cout << "������: ������� �� ����!";
                }
                operands.push(operand1 / operand2);
                break;
            }
        }
    }
    return operands.pop();
}

int entry() // ���� � ���������
{
    int choice;
    cout << "������������ ������ 4" << endl << "1 - ���� � ���������" << endl;
    cout << "2 - ����� �� ���������" << endl;
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) // �������� �� ������������ �����
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

int answer();

int task()
{
    string simple;
    cout << "������� �������������� ��������� � ���������� ����������� (������ ��������� �������): ";
    getline(cin, simple);
    vector<pair<char, double>> variables; // ������ ��� �������� ��������� ����������
    for (char ch : simple)
    {
        if ((ch >= '�' && ch <= '�') || (ch >= '�' && ch <= '�'))// �������� �� ��� �����
        {
            cout << "������! ������� ������ ��������� �����." << endl;
            return 1;
        }
    }
    string postfix = translate(simple);
    cout << "�������� �������� ������: " << postfix << endl;
    try
    {
        double result = evaluatePostfix(postfix, variables);
        cout << "��������� ����������: " << result << endl;
    }
    catch (const exception& e) 
    {
        cerr << "������: " << e.what() << endl;
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
    cout << "������� ����������?\n1 - ��\n2 - ���\n��� �����: ";
    do
    {
        cin >> choice;
        if (cin.fail() || (choice != 1 && choice != 2)) // �������� �� ������������ �����
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
