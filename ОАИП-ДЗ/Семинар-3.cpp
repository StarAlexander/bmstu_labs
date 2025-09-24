#include <iostream>
#include <climits>
using namespace std;

// Task 1
void task1() {
    int n;
    cout << "Enter the number of elements (n): ";
    cin >> n;

    if (n <= 0 || n > 1000) {
        cout << "n must be a positive integer (max 1000)." << endl;
        return;
    }

    int A[1000];
    cout << "Enter " << n << " natural numbers: "<< endl;
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    int count = 0;
    for (int k = 0; k < n; ++k) {
        if (A[k] > 2 * (k + 1)) {
            count++;
        }
    }

    cout << "Number of elements satisfying A[k] > 2*k: " << count << endl;
}

// Task 2
void task2() {
    int n;
    cout << "Enter the number of elements (n): ";
    cin >> n;

    if (n <= 0 || n > 1000) {
        cout << "n must be a positive integer (max 1000)." << endl;
        return;
    }

    int A[1000];
    cout << "Enter " << n << " integers: " << endl;
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    int maxOdd = INT_MIN;
    int evenCount = 0;
    bool hasOdd = false;

    for (int i = 0; i < n; ++i) {
        if (A[i] % 2 == 0) {
            evenCount++;
        } else {
            if (!hasOdd || A[i] > maxOdd) {
                maxOdd = A[i];
                hasOdd = true;
            }
        }
    }

    if (hasOdd) {
        cout << "Maximum odd number: " << maxOdd << endl;
    } else {
        cout << "No odd numbers found." << endl;
    }
    cout << "Count of even numbers: " << evenCount << endl;
}

// Task 3
void task3() {
    const int N = 15;
    double A[N];
    cout << "Enter 15 real numbers: " << endl;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (A[i] < A[minIndex]) minIndex = i;
        if (A[i] > A[maxIndex]) maxIndex = i;
    }

    // Swap min with first
    double temp = A[0];
    A[0] = A[minIndex];
    A[minIndex] = temp;

    // Swap max with last
    temp = A[N - 1];
    A[N - 1] = A[maxIndex];
    A[maxIndex] = temp;

    cout << "Array after swapping:" << endl;
    for (int i = 0; i < N; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// Task 4
void task4() {
    const int N = 15;
    double A[N];
    cout << "Enter 15 real numbers: " << endl;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (A[i] < A[minIndex]) minIndex = i;
        if (A[i] > A[maxIndex]) maxIndex = i;
    }

    if (maxIndex < minIndex) {
        double product = A[maxIndex] * A[minIndex];
        cout << "Max precedes min. Product = " << product << endl;
    } else {
        cout << "Max does not precede min." << endl;
    }
}

// Task 5
void task5() {
    const int N = 10;
    int A[N];
    cout << "Enter 10 integers: " << endl;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (A[i] < A[minIndex]) minIndex = i;
        if (A[i] > A[maxIndex]) maxIndex = i;
    }

    if (minIndex == 4 && maxIndex == 9) {
        double avg = (A[minIndex] + A[maxIndex]) / 2.0;
        cout << "Min at position 5 and max at position 10. Average = " << avg << endl;
    } else {
        cout << "Condition not met." << endl;
    }
}

// Task 6
void task6() {
    const int N = 15;
    double A[N];
    cout << "Enter 15 real numbers: " << endl;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (A[i] < A[minIndex]) minIndex = i;
        if (A[i] > A[maxIndex]) maxIndex = i;
    }

    if (minIndex == 1 && maxIndex == 0) {
        for (int i = 0; i < N; ++i) {
            A[i] /= 2.0;
        }
        cout << "All elements halved:" << endl;
        for (int i = 0; i < N; ++i) {
            cout << A[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Condition not met." << endl;
    }
}

// Task 7
void task7() {
    const int N = 15;
    int A[N];
    cout << "Enter 15 integers: " << endl;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (A[i] < A[minIndex]) minIndex = i;
        if (A[i] > A[maxIndex]) maxIndex = i;
    }

    if (A[minIndex] == 0 || A[maxIndex] == 0) {
        for (int i = 0; i < minIndex; ++i) {
            A[i] = 0;
        }
        cout << "Elements before min set to zero:" << endl;
        for (int i = 0; i < N; ++i) {
            cout << A[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Neither min nor max is zero." << endl;
    }
}

// Task 8
void task8() {
    const int N = 10;
    int A[N];
    cout << "Enter 10 integers: " << endl;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < N; ++i) {
        if (A[i] < A[minIndex]) minIndex = i;
        if (A[i] > A[maxIndex]) maxIndex = i;
    }

    if (maxIndex == 1 && minIndex == 4) {
        int maxValue = A[maxIndex];
        for (int i = minIndex; i < N; ++i) {
            A[i] = maxValue;
        }
        cout << "Elements from min to end set to max value:" << endl;
        for (int i = 0; i < N; ++i) {
            cout << A[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Condition not met." << endl;
    }
}

// Main menu
int main() {
    int choice;
    cout << "Select a task (1-8): ";
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
        default:
            cout << "Invalid task number." << endl;
            return 1;
    }

    return 0;
}