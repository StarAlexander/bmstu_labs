#include <iostream>
#include <exception>


int main()
{
    setlocale(LC_CTYPE, "Russian");
    double temp;
    std::cout << "Введите температуру (дробное число): ";
    std::cin.exceptions(std::ios::failbit);
    try {
        std::cin >> temp;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
        std::cout << "Температура должна быть числом.\n";
        return 1;
    }
    std::cout << std::endl;

    if (temp < 0.0) {
        std::cout << "Наденьте зимнюю одежду.\n";
    }
    else if (temp <= 10.0) {
        std::cout << "Наденьте теплую одежду.\n";
        ;
    }

    else if (temp <= 20.0) {
        std::cout << "Наденьте легкую одежду.\n";
    }
    else {
        std::cout << "Наденьте летнюю одежду.\n";
    }


    int stops;
    std::cout << "Введите кол-во остановок (целочисленное): ";
    try {
        std::cin >> stops;
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Ошибка ввода: " << e.what() << std::endl;
        std::cout << "Кол-во должно быть числом.\n";
        return 1;
    }
    std::cout << std::endl;
    if (stops <= 0) {
        std::cout << "Кол-во должно быть положительным.";
        return 1;
    }
    int cost = 0;
    for (int i = 0; i < stops; i++) {
        cost += 5;
    }


    std::cout << "Цена проезда: " << cost << std::endl;

    return 0;
}