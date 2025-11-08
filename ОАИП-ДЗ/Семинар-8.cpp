#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;





void swapPointers(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

void task1() {
    int x = 10, y = 20;
    int* p1 = &x;
    int* p2 = &y;

    cout << "Before swap:\n";
    cout << "p1 -> " << p1 << " value: " << *p1 << endl;
    cout << "p2 -> " << p2 << " value: " << *p2 << endl;

    swapPointers(&p1, &p2);

    cout << "\nAfter swap:\n";
    cout << "p1 -> " << p1 << " value: " << *p1 << endl;
    cout << "p2 -> " << p2 << " value: " << *p2 << endl;
}





int** create2DArray(int n, int m) {
    int** arr = new int*[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
    }
    return arr;
}

void fillRandom(int** arr, int n, int m) {
    srand(time(nullptr));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            arr[i][j] = rand() % 100; 
        }
    }
}

void print2DArray(int** arr, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void task2() {
    int n, m;
    cout << "Enter n and m: ";
    cin >> n >> m;

    int** arr = create2DArray(n, m);
    fillRandom(arr, n, m);
    print2DArray(arr, n, m);

    
    
    
}





void free2D(int** arr, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}

void task3() {
    int n = 3, m = 4;
    int** arr = create2DArray(n, m);
    fillRandom(arr, n, m);
    cout << "Created array:\n";
    print2DArray(arr, n, m);

    free2D(arr, n);
    cout << "Memory freed." << endl;
}





int** transpose(int** matrix, int n, int m) {
    int** result = new int*[m];
    for (int i = 0; i < m; ++i) {
        result[i] = new int[n];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

void task4() {
    int n = 3, m = 4;
    int** mat = create2DArray(n, m);
    fillRandom(mat, n, m);
    cout << "Original matrix:\n";
    print2DArray(mat, n, m);

    int** transposed = transpose(mat, n, m);
    cout << "\nTransposed matrix:\n";
    print2DArray(transposed, m, n);

    free2D(mat, n);
    free2D(transposed, m);
}





void sortRowsBySum(int** arr, int n, int m) {
    
    int** rowPtrs = new int*[n];
    for (int i = 0; i < n; ++i) {
        rowPtrs[i] = arr[i];
    }

    
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            int sumJ = 0, sumJ1 = 0;
            for (int k = 0; k < m; ++k) {
                sumJ += rowPtrs[j][k];
                sumJ1 += rowPtrs[j+1][k];
            }
            if (sumJ > sumJ1) {
                int* temp = rowPtrs[j];
                rowPtrs[j] = rowPtrs[j+1];
                rowPtrs[j+1] = temp;
            }
        }
    }

    
    for (int i = 0; i < n; ++i) {
        arr[i] = rowPtrs[i];
    }

    delete[] rowPtrs;
}

void task5() {
    int n = 3, m = 4;
    int** arr = create2DArray(n, m);
    fillRandom(arr, n, m);
    cout << "Before sorting:\n";
    print2DArray(arr, n, m);

    sortRowsBySum(arr, n, m);
    cout << "\nAfter sorting by row sum:\n";
    print2DArray(arr, n, m);

    free2D(arr, n);
}





int sumElements(int** arr, int n, int m) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sum += *(*(arr + i) + j);
        }
    }
    return sum;
}

void task6() {
    int n = 3, m = 5;
    int** arr = create2DArray(n, m);
    
    int val = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            arr[i][j] = val++;
        }
    }

    cout << "Matrix:\n";
    print2DArray(arr, n, m);
    int total = sumElements(arr, n, m);
    cout << "Sum: " << total << endl;

    free2D(arr, n);
}





void sortWords(char** words, int count) {
    
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (strcmp(words[j], words[j+1]) > 0) {
                char* temp = words[j];
                words[j] = words[j+1];
                words[j+1] = temp;
            }
        }
    }
}

void task7() {
    const int COUNT = 7;
    char* words[COUNT] = {
        "banana",
        "apple",
        "cherry",
        "date",
        "elderberry",
        "fig",
        "grape"
    };

    cout << "Before sorting:\n";
    for (int i = 0; i < COUNT; ++i) {
        cout << words[i] << endl;
    }

    sortWords(words, COUNT);

    cout << "\nAfter sorting:\n";
    for (int i = 0; i < COUNT; ++i) {
        cout << words[i] << endl;
    }
}





double** allocatePlate(int n, int m) {
    double** plate = new double*[n];
    for (int i = 0; i < n; ++i) {
        plate[i] = new double[m];
    }
    return plate;
}

void freePlate(double** plate, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] plate[i];
    }
    delete[] plate;
}

void updateTemperature(double** plate, int n, int m) {
    double** newPlate = allocatePlate(n, m);

    
    for (int j = 0; j < m; ++j) {
        newPlate[0][j] = plate[0][j];
        newPlate[n-1][j] = plate[n-1][j];
    }
    for (int i = 0; i < n; ++i) {
        newPlate[i][0] = plate[i][0];
        newPlate[i][m-1] = plate[i][m-1];
    }

    
    for (int i = 1; i < n-1; ++i) {
        for (int j = 1; j < m-1; ++j) {
            double avg = (plate[i-1][j] + plate[i+1][j] + plate[i][j-1] + plate[i][j+1]) / 4.0;
            newPlate[i][j] = avg;
        }
    }

    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            plate[i][j] = newPlate[i][j];
        }
    }

    freePlate(newPlate, n);
}

void initializePlate(double** plate, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            plate[i][j] = 20.0;
        }
    }
    
    int centerI = n/2, centerJ = m/2;
    plate[centerI][centerJ] = 100.0;
}

void printPlate(double** plate, int n, int m) {
    cout << fixed << setprecision(1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << plate[i][j] << " ";
        }
        cout << endl;
    }
}

void task8() {
    int n = 5, m = 5;
    double** plate = allocatePlate(n, m);
    initializePlate(plate, n, m);

    cout << "Initial plate:\n";
    printPlate(plate, n, m);

    int iterations = 3;
    for (int k = 0; k < iterations; ++k) {
        updateTemperature(plate, n, m);
    }

    cout << "\nAfter " << iterations << " iterations:\n";
    printPlate(plate, n, m);

    freePlate(plate, n);
}





double* forward(double** weights, double* inputs, int n, int m) {
    double* outputs = new double[n];
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < m; ++j) {
            sum += weights[i][j] * inputs[j];
        }
        outputs[i] = sum;
    }
    return outputs;
}

void normalizeWeights(double** weights, int n, int m) {
    for (int i = 0; i < n; ++i) {
        double sum = 0.0;
        for (int j = 0; j < m; ++j) {
            sum += weights[i][j];
        }
        if (sum != 0.0) {
            for (int j = 0; j < m; ++j) {
                weights[i][j] /= sum;
            }
        }
    }
}

void task9() {
    int N = 3, M = 4;
    double** weights = new double*[N];
    for (int i = 0; i < N; ++i) {
        weights[i] = new double[M];
        for (int j = 0; j < M; ++j) {
            weights[i][j] = (rand() % 21 - 10) / 10.0; 
        }
    }

    double* inputs = new double[M];
    for (int j = 0; j < M; ++j) {
        inputs[j] = 1.0; 
    }

    cout << "Weights before normalization:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }

    normalizeWeights(weights, N, M);
    cout << "\nWeights after normalization:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << weights[i][j] << " ";
        }
        cout << endl;
    }

    double* outputs = forward(weights, inputs, N, M);
    cout << "\nOutputs:\n";
    for (int i = 0; i < N; ++i) {
        cout << outputs[i] << endl;
    }

    
    delete[] inputs;
    for (int i = 0; i < N; ++i) {
        delete[] weights[i];
    }
    delete[] weights;
    delete[] outputs;
}





double* averageLoadPerNode(int** load, int n, int t) {
    double* avg = new double[n];
    for (int i = 0; i < n; ++i) {
        long long total = 0;
        for (int j = 0; j < t; ++j) {
            total += load[i][j];
        }
        avg[i] = static_cast<double>(total) / t;
    }
    return avg;
}

void normalizeLoad(int** load, int n, int t) {
    double* avg = averageLoadPerNode(load, n, t);
    double threshold = 80.0;

    for (int i = 0; i < n; ++i) {
        if (avg[i] > threshold) {
            int over = static_cast<int>(avg[i] - threshold);
            int remaining = 0;
            for (int j = 0; j < n; ++j) {
                if (j != i) remaining += avg[j];
            }
            if (remaining > 0) {
                for (int j = 0; j < n; ++j) {
                    if (j != i) {
                        int transfer = static_cast<int>((over * avg[j]) / remaining);
                        for (int k = 0; k < t; ++k) {
                            load[j][k] += transfer;
                        }
                    }
                }
                for (int k = 0; k < t; ++k) {
                    load[i][k] -= over;
                }
            }
        }
    }

    delete[] avg;
}

int findCriticalInterval(int** load, int n, int t) {
    int maxSum = 0;
    int criticalIdx = 0;
    for (int j = 0; j < t; ++j) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += load[i][j];
        }
        if (sum > maxSum) {
            maxSum = sum;
            criticalIdx = j;
        }
    }
    return criticalIdx;
}

void task10() {
    int n, t;
    cout << "Enter number of nodes and time intervals: ";
    cin >> n >> t;

    int** load = new int*[n];
    for (int i = 0; i < n; ++i) {
        load[i] = new int[t];
    }

    cout << "Enter load for each node per interval:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i+1 << ": ";
        for (int j = 0; j < t; ++j) {
            cin >> load[i][j];
        }
    }

    cout << "\nOriginal load matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            cout << load[i][j] << " ";
        }
        cout << endl;
    }

    double* avg = averageLoadPerNode(load, n, t);
    cout << "\nAverage load per node:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i+1 << ": " << avg[i] << endl;
    }

    normalizeLoad(load, n, t);
    cout << "\nAfter normalization:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < t; ++j) {
            cout << load[i][j] << " ";
        }
        cout << endl;
    }

    int critical = findCriticalInterval(load, n, t);
    cout << "\nCritical interval: " << critical + 1 << " (sum = ";
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += load[i][critical];
    cout << sum << ")" << endl;

    
    delete[] avg;
    for (int i = 0; i < n; ++i) {
        delete[] load[i];
    }
    delete[] load;
}





int main() {
    int choice;
    cout << "Select task (1-10): ";
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
        default:
            cout << "Invalid task number." << endl;
            return 1;
    }

    return 0;
}