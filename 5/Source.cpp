#include <iostream>
#include <string>
#include <cctype>

double readNumber()
{
    double number;
    std::string input;
    bool validInput = false;

    while (!validInput)
    {
        std::cout << "������� �����: ";
        std::cin >> input;

        // ��������� ������ ������ � ������
        bool hasLetter = false;
        for (char c : input)
        {
            if (std::isalpha(c)) // ���� ������ �������� ������
            {
                hasLetter = true;
                break;
            }
        }

        if (!hasLetter) // ���� �� ����� ��� ����
        {
            // ����������� ������ � �����
            try
            {
                number = std::stod(input);
                validInput = true; // ������������� ���� � true, ���� ������� ������������� ������ � �����
            }
            catch (const std::invalid_argument&) // ��������� ���������� ��� ������������ �����
            {
                std::cout << "������: ������� �� �����. ���������� �����." << std::endl;
            }
        }
        else
        {
            std::cout << "������: ���� �������� �����. ���������� �����." << std::endl;
        }

        // ������� ����� �����
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return number;
}

int main()
{
    double value = readNumber();
    std::cout << "������� �����: " << value << std::endl;

    return 0;
}
