#include <iostream>


using namespace std;

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


int main()
{
    setlocale(LC_CTYPE, "Russian");
    int arr[10];


    for (int i = 0; i < 10; i++) {
        cout << "Введите элемент массива:";
        cin >> arr[i];
    }

    int m = arr[0];

    for (int i = 1; i < 10; i++) {
        if (m > arr[i]) {
            m = arr[i];
        }
    }

    cout << "Минимальный элемент:" << m << endl;

    insertionSort(arr, 10);


    int sum = 0;

    for (auto& m : arr) {
        sum += m;
        cout << m << endl;
    }

    cout << "Сумма:" << sum << endl;


    return 0;
}
