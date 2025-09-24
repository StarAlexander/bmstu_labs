#include <iostream>
#include <string>
using namespace std;

// Task 1
void task1() {
    int cm;
    cout << "Enter length in centimeters: ";
    cin >> cm;

    int meters = cm / 100;
    int remaining_cm = cm % 100;

    cout << "Full meters: " << meters << ", remaining centimeters: " << remaining_cm << endl;
}

// Task 2
void task2() {
    double length, width;
    cout << "Enter rectangle length and width: ";
    cin >> length >> width;

    double area = length * width;
    cout << "Rectangle area: " << area << endl;
}

// Task 3
void task3() {
    double celsius;
    cout << "Enter temperature in Celsius: ";
    cin >> celsius;

    double fahrenheit = celsius * 9.0 / 5.0 + 32;
    cout << "Temperature in Fahrenheit: " << fahrenheit << endl;
}

// Task 4
void task4() {
    int number;
    cout << "Enter an integer: ";
    cin >> number;

    if (number % 2 == 0)
        cout << "The number is even." << endl;
    else
        cout << "The number is odd." << endl;
}

// Task 5
void task5() {
    int number;
    cout << "Enter a number: ";
    cin >> number;

    bool div3 = (number % 3 == 0);
    bool div5 = (number % 5 == 0);

    if (div3 && div5)
        cout << "The number is divisible by both 3 and 5." << endl;
    else if (div3)
        cout << "The number is divisible by 3." << endl;
    else if (div5)
        cout << "The number is divisible by 5." << endl;
    else
        cout << "The number is not divisible by 3 or 5." << endl;
}

// Task 6
void task6() {
    int age;
    cout << "Enter your age: ";
    cin >> age;

    if (age < 18)
        cout << "Age is under 18." << endl;
    else if (age >= 18 && age <= 60)
        cout << "Age is between 18 and 60." << endl;
    else
        cout << "Age is over 60." << endl;
}

// Task 7
void task7() {
    int n;
    cout << "Enter a number n: ";
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cout << "Square of " << i << " = " << i * i << endl;
    }
}

// Task 8
void task8() {
    string s;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, s);

    string vowels = "aeiouAEIOU";
    int count = 0;

    for (char c : s) {
        if (vowels.find(c) != string::npos) {
            count++;
        }
    }

    cout << "Number of vowels: " << count << endl;
}

// Task 9
void task9() {
    int n;
    cout << "Enter a number n: ";
    cin >> n;

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i % 2 == 0 || i % 5 == 0) {
            sum += i;
        }
    }

    cout << "Sum of numbers from 1 to " << n << " divisible by 2 or 5: " << sum << endl;
}

// Task 10
void task10() {
    double number;
    cout << "Enter a number: ";
    cin >> number;

    if (number > 0)
        cout << "The number is positive." << endl;
    else if (number < 0)
        cout << "The number is negative." << endl;
    else
        cout << "The number is zero." << endl;
}

// Task 11
void task11() {
    cout << "Code\tCharacter\n";
    cout << "----------------\n";
    for (int i = 32; i <= 126; ++i) {
        cout << i << "\t" << static_cast<char>(i) << endl;
    }
}

// Main menu
int main() {
    int choice;
    cout << "Select a task (1-11): ";
    cin >> choice;

    switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 6: task6(); break;
        case 7: task7(); break;
        case 8: task8(); break;
        case 9: task9(); break;
        case 10: task10(); break;
        case 11: task11(); break;
        default:
            cout << "Invalid task number." << endl;
            return 1;
    }

    return 0;
}