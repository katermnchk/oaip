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
        std::cout << "Введите число: ";
        std::cin >> input;

        // Проверяем каждый символ в строке
        bool hasLetter = false;
        for (char c : input)
        {
            if (std::isalpha(c)) // Если символ является буквой
            {
                hasLetter = true;
                break;
            }
        }

        if (!hasLetter) // Если во вводе нет букв
        {
            // Преобразуем строку в число
            try
            {
                number = std::stod(input);
                validInput = true; // Устанавливаем флаг в true, если удалось преобразовать строку в число
            }
            catch (const std::invalid_argument&) // Обработка исключения при некорректном вводе
            {
                std::cout << "Ошибка: введено не число. Попробуйте снова." << std::endl;
            }
        }
        else
        {
            std::cout << "Ошибка: ввод содержит буквы. Попробуйте снова." << std::endl;
        }

        // Очищаем буфер ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return number;
}

int main()
{
    double value = readNumber();
    std::cout << "Введено число: " << value << std::endl;

    return 0;
}
