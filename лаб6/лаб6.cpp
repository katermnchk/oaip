#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Tree
{
    int key;
    string data;
    Tree* left, * right;
    int height;
};

Tree* CreateNode(int key, const string& data)
{
    Tree* newNode = new Tree;
    newNode->key = key;
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

int Height(Tree* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

void UpdateHeight(Tree* node)
{
    node->height = 1 + max(Height(node->left), Height(node->right));
}

Tree* RightRotate(Tree* y)
{
    Tree* x = y->left;
    Tree* T2 = x->right;

    x->right = y;
    y->left = T2;

    UpdateHeight(y);
    UpdateHeight(x);

    return x;
}

Tree* LeftRotate(Tree* x)
{
    Tree* y = x->right;
    Tree* T2 = y->left;

    y->left = x;
    x->right = T2;

    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

int BalanceFactor(Tree* node)
{
    if (node == nullptr)
        return 0;
    return Height(node->left) - Height(node->right);
}

Tree* BalanceTree(Tree* root)
{
    if (root == nullptr)
        return root;

    int balance = BalanceFactor(root);

    if (balance > 1)
    {
        if (BalanceFactor(root->left) < 0)
            root->left = LeftRotate(root->left);
        return RightRotate(root);
    }
    else if (balance < -1)
    {
        if (BalanceFactor(root->right) > 0)
            root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

Tree* InsertNode(Tree* root, int key, const string& data)
{
    if (root == nullptr)
    {
        return CreateNode(key, data);
    }

    if (key < root->key)
        root->left = InsertNode(root->left, key, data);
    else if (key > root->key)
        root->right = InsertNode(root->right, key, data);
    else
        cout << "����� ���� ��� ����!" << endl;

    UpdateHeight(root);

    return root;
}

Tree* FindMinNode(Tree* root)
{
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Tree* DeleteNode(Tree* root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = DeleteNode(root->left, key);
    else if (key > root->key)
        root->right = DeleteNode(root->right, key);
    else
    {
        if (root->left == nullptr || root->right == nullptr)
        {
            Tree* temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else
        {
            Tree* temp = FindMinNode(root->right);
            root->key = temp->key;
            root->data = temp->data;
            root->right = DeleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    UpdateHeight(root);

    return root;
}

Tree* Search(Tree* root, int key)
{
    if (root == nullptr || root->key == key)
        return root;

    if (root->key < key)
        return Search(root->right, key);

    return Search(root->left, key);
}

void PrintTree(Tree* root, int space = 0, int count = 5)
{
    if (root == nullptr)
        return;

    space += count;

    PrintTree(root->right, space, count);

    cout << endl;
    for (int i = count; i < space; i++)
        cout << " ";
    cout << root->key << ":" << root->data << endl;

    PrintTree(root->left, space, count);
}


void InOrderAscending(Tree* node)
{
    if (node == nullptr)
        return;

    InOrderAscending(node->left);
    cout << node->key << ":" << node->data << endl;
    InOrderAscending(node->right);
}

void PreOrderTraversal(Tree* node, int space = 0, int count = 5)
{
    if (node == nullptr)
        return;

    space += count;

    cout << endl;
    for (int i = count; i < space; i++)
        cout << " ";
    cout << node->key << ":" << node->data << endl;

    PreOrderTraversal(node->left, space, count);
    PreOrderTraversal(node->right, space, count);
}

void PostOrderTraversal(Tree* node, int space = 0, int count = 5)
{
    if (node == nullptr)
        return;

    space += count;

    PostOrderTraversal(node->left, space, count);
    PostOrderTraversal(node->right, space, count);

    cout << endl;
    for (int i = count; i < space; i++)
        cout << " ";
    cout << node->key << ":" << node->data << endl;
}


int NodeCountOnLevel(Tree* root, int level, int currentLevel = 1)
{
    if (root == nullptr)
        return 0;

    if (level == currentLevel)
        return 1;

    int leftCount = NodeCountOnLevel(root->left, level, currentLevel + 1);
    int rightCount = NodeCountOnLevel(root->right, level, currentLevel + 1);

    return leftCount + rightCount;
}

static int menu() {
    int choice;

        cout << "----------------------------------------------------\n";
        cout << "|                      ����                        |\n";
        cout << "| 1 - �������� ����                                |\n";
        cout << "| 2 - ����������� ������                           |\n";
        cout << "| 3 - �������������� ������                        |\n";
        cout << "| 4 - ����� ���� �� �����                          |\n";
        cout << "| 5 - ������� ���� �� �����                        |\n";
        cout << "| 6 - ������ �����                                 |\n";
        cout << "| 7 - �������� �����                               |\n";
        cout << "| 8 - ������� � ������� ����������� �����          |\n";
        cout << "| 9 - ���������� ����� ����� �� ������ ������      |\n";
        cout << "| 0 - �����                                        |\n";
        cout << "----------------------------------------------------\n";
        cout << "������� ��� �����: ";
        do
        {
            cin >> choice;
            if (cin.fail() || (choice < 0 && choice > 9))
            {
                cout << endl << "������! ������� �� 0 �� 9" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
        } while (choice < 0 && choice > 9);
        cin.ignore(INT_MAX, '\n');
    return choice;
}


int entry()//���� � ���������
{
    int choice;
    cout << "������������ ������ 6" << endl << "1 - ���� � ���������" << endl;
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

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Tree* root = nullptr;
    int choice2, key;
    string data;
    if (entry())
    {
        choice2 = menu();
        if (choice2 == 0) return 0;
        while ((choice2 = menu()) != 0)
        {
            switch (choice2)
            {
            case 1:
                do
                {
                    cout << "������� ���� (��� ���������� ����� ������� 0): ";
                    while (!(cin >> key) || cin.peek() != '\n')
                    {
                        cout << "������������ ����! ������� ���� ������: ";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                    }

                    if (key == 0)
                        break;

                    cout << "������� ���: ";
                    cin.ignore(); // ������� ������ ����� ����������� ������
                    getline(cin, data);
                    root = InsertNode(root, key, data);
                } while (key != 0);

            case 2:
                
                if (root == nullptr) 
                {
                    cout << "������ ������.\n";
                }
                else 
                {
                    cout << "������:\n";
                    PrintTree(root);
                }
                break;
            case 3:
                if (root == nullptr)
                {
                    cout << "������ ������.\n";
                }
                else
                {
                    root = BalanceTree(root);
                    cout << "������ ��������������\n";
                    PrintTree(root);
                }
                break;
            case 4:
                cout << "������� ���� ��� ������: ";
                cin >> key;
                {
                    Tree* result = Search(root, key);
                    if (result != nullptr)
                        cout << "������: " << result->data << endl;
                    else
                        cout << "���� �� ������!" << endl;
                }
                break;
            case 5:
                if (root == nullptr)
                {
                    cout << "������ ������.\n";
                }
                else
                {
                    cout << "������� ���� ��� ��������: ";
                    cin >> key;
                    root = DeleteNode(root, key);
                    cout << "\n���� ������� ������.";
                }
                break;
            case 6:
                if (root == nullptr)
                {
                    cout << "������ ������.\n";
                }
                else
                {
                    cout << "������ �����:\n";
                    PreOrderTraversal(root);
                }
                break;
            case 7:
                if (root == nullptr)
                {
                    cout << "������ ������.\n";
                }
                else
                {
                    cout << "�������� �����:\n";
                    PostOrderTraversal(root);
                }
                break;
            case 8:
                if (root == nullptr)
                {
                    cout << "������ ������.\n";
                }
                else
                {
                    cout << "� ������� ����������� �����:\n";
                    InOrderAscending(root);
                }
                break;
            case 9:
                cout << "������� �������: ";
                cin >> key;
                if (NodeCountOnLevel(root, key) == 0)
                    cout << "�� ���� ������ ����� ���\n";
                else cout << "���������� ����� �� ������ " << key << ": " << NodeCountOnLevel(root, key) << endl;
                break;
            case 0:
                return 0;
                break;
            default:
                cout << "�������� �����. ����������, ���������� �����.\n";
            }
        }
    }

    return 0;
}
