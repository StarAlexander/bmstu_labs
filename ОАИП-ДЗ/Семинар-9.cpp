#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cstring>
using namespace std;





void task1() {
    unique_ptr<int> ptr = make_unique<int>(10);
    cout << "Initial value: " << *ptr << endl;
    *ptr = 25;
    cout << "After change: " << *ptr << endl;
}





void task2() {
    int n;
    cout << "Enter array size N: ";
    cin >> n;

    auto arr = make_unique<int[]>(n);

    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    cout << "Array content: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}





void fillArray(unique_ptr<int[]>& arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i] = i * i; 
    }
}

void task3() {
    int n = 5;
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    fillArray(arr, n);

    cout << "Filled array: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}





void task4() {
    unique_ptr<int> ptr1 = make_unique<int>(42);
    unique_ptr<int> ptr2 = move(ptr1); 

    if (ptr1 == nullptr) {
        cout << "ptr1 is now nullptr." << endl;
    } else {
        cout << "ptr1 still holds value: " << *ptr1 << endl;
    }

    if (ptr2 != nullptr) {
        cout << "ptr2 holds value: " << *ptr2 << endl;
    }
}





void task5() {
    int N, M;
    cout << "Enter N and M: ";
    cin >> N >> M;

    unique_ptr<int[]> matrix = make_unique<int[]>(N * M);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix[i * M + j] = i * j;
        }
    }

    cout << "Matrix:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cout << matrix[i * M + j] << " ";
        }
        cout << endl;
    }
}





void task6() {
    shared_ptr<int> ptr = make_shared<int>(100);
    shared_ptr<int> ptr2 = ptr;
    shared_ptr<int> ptr3 = ptr;

    cout << "use_count after creation: " << ptr.use_count() << endl;

    ptr3.reset(); 
    cout << "use_count after reset ptr3: " << ptr.use_count() << endl;

    cout << "Final value: " << *ptr << endl;
}





void task7() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    unique_ptr<char[]> arr = make_unique<char[]>(input.length() + 1);
    strcpy(arr.get(), input.c_str());

    int vowelCount = 0;
    const char vowels[] = "aeiouAEIOU";
    for (char* p = arr.get(); *p != '\0'; ++p) {
        for (int i = 0; vowels[i] != '\0'; ++i) {
            if (*p == vowels[i]) {
                vowelCount++;
                break;
            }
        }
    }

    
    unique_ptr<char[]> vowelsOnly = make_unique<char[]>(vowelCount + 1);
    char* writePtr = vowelsOnly.get();
    for (char* p = arr.get(); *p != '\0'; ++p) {
        for (int i = 0; vowels[i] != '\0'; ++i) {
            if (*p == vowels[i]) {
                *writePtr = *p;
                writePtr++;
                break;
            }
        }
    }
    *writePtr = '\0';

    cout << "Original string: " << arr.get() << endl;
    cout << "Vowels count: " << vowelCount << endl;
    cout << "Vowels only: " << vowelsOnly.get() << endl;
    
}





void task8() {
    unique_ptr<double[]> temp = make_unique<double[]>(5);
    unique_ptr<double[]> press = make_unique<double[]>(5);
    unique_ptr<double[]> hum = make_unique<double[]>(5);

    
    double t[] = {20.5, 21.0, 22.3, 19.8, 20.1};
    double p[] = {101.3, 100.8, 101.5, 102.0, 100.5};
    double h[] = {55.0, 52.3, 60.1, 48.9, 57.2};

    for (int i = 0; i < 5; ++i) {
        temp[i] = t[i];
        press[i] = p[i];
        hum[i] = h[i];
    }

    cout << "Parameter     Average Value\n";
    cout << "Temperature   " << accumulate(temp.get(), temp.get() + 5, 0.0) / 5.0 << endl;
    cout << "Pressure      " << accumulate(press.get(), press.get() + 5, 0.0) / 5.0 << endl;
    cout << "Humidity      " << accumulate(hum.get(), hum.get() + 5, 0.0) / 5.0 << endl;
}





void processA(shared_ptr<vector<int>> buf) {
    for (int& x : *buf) {
        x += 1;
    }
}

void processB(shared_ptr<vector<int>> buf) {
    for (int& x : *buf) {
        x *= 2;
    }
}

void task9() {
    shared_ptr<vector<int>> buffer = make_shared<vector<int>>();
    for (int i = 1; i <= 10; ++i) {
        buffer->push_back(i);
    }

    cout << "Initial: ";
    for (int x : *buffer) cout << x << " ";
    cout << endl;

    processA(buffer);
    cout << "After A: ";
    for (int x : *buffer) cout << x << " ";
    cout << endl;

    processB(buffer);
    cout << "After B: ";
    for (int x : *buffer) cout << x << " ";
    cout << endl;
}





unique_ptr<int[]> createArray(int n) {
    unique_ptr<int[]> arr = make_unique<int[]>(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}

void task10() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    unique_ptr<int[]> arr = createArray(n);

    cout << "Array elements: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}





double mean(const vector<double>& signals) {
    return accumulate(signals.begin(), signals.end(), 0.0) / signals.size();
}

void normalize(vector<double>& signals) {
    double avg = mean(signals);
    double maxVal = *max_element(signals.begin(), signals.end());
    for (double& s : signals) {
        s = (s - avg) / (maxVal - avg);
    }
}

void copyBack(const vector<double>& normalized, vector<double>& original) {
    copy(normalized.begin(), normalized.end(), original.begin());
}

void task11() {
    int N;
    cout << "Enter number of measurements: ";
    cin >> N;

    vector<double> signals(N);
    cout << "Enter " << N << " signals: ";
    for (int i = 0; i < N; ++i) {
        cin >> signals[i];
    }

    cout << "Original signals: ";
    for (double s : signals) cout << s << " ";
    cout << endl;

    double avg = mean(signals);
    cout << "Mean: " << avg << endl;

    
    unique_ptr<double[]> normSignals = make_unique<double[]>(N);
    vector<double> tempNorm = signals;
    normalize(tempNorm);

    for (int i = 0; i < N; ++i) {
        normSignals[i] = tempNorm[i];
    }

    cout << "Normalized signals: ";
    for (int i = 0; i < N; ++i) {
        cout << normSignals[i] << " ";
    }
    cout << endl;

    copyBack(tempNorm, signals);
    cout << "Restored original: ";
    for (double s : signals) cout << s << " ";
    cout << endl;
}





void task12() {
    vector<string> logs = {
        "INFO: Start",
        "ERROR: Disk failure",
        "WARNING: Low memory",
        "ERROR: Disk failure",
        "INFO: Stop"
    };

    shared_ptr<vector<string>> pLogs = make_shared<vector<string>>(logs);
    shared_ptr<vector<string>> errors = make_shared<vector<string>>();

    
    for (const string& log : *pLogs) {
        if (log.find("ERROR") != string::npos) {
            errors->push_back(log);
        }
    }

    cout << "Original journal:\n";
    for (const string& log : *pLogs) {
        cout << log << endl;
    }

    cout << "\nErrors:\n";
    for (const string& err : *errors) {
        cout << err << endl;
    }

    
    sort(errors->begin(), errors->end());
    auto last = unique(errors->begin(), errors->end());
    errors->erase(last, errors->end());

    cout << "\nDeduplicated errors:\n";
    for (const string& err : *errors) {
        cout << err << endl;
    }
}





void task13() {
    unique_ptr<string> part1 = make_unique<string>("Sensor data:");
    unique_ptr<string> part2 = make_unique<string>("Voltage stable.");
    unique_ptr<string> part3 = make_unique<string>("System nominal.");

    vector<unique_ptr<string>> reportParts;
    reportParts.push_back(move(part1));
    reportParts.push_back(move(part2));
    reportParts.push_back(move(part3));

    
    string fullReport;
    for (auto& part : reportParts) {
        fullReport += *part + "\n";
    }

    cout << "Full report:\n" << fullReport << endl;

    
    int count = 0;
    auto countWord = [](const string& text, const string& word) -> int {
        int c = 0;
        size_t pos = 0;
        while ((pos = text.find(word, pos)) != string::npos) {
            c++;
            pos += word.length();
        }
        return c;
    };

    int dataCount = countWord(fullReport, "data");
    cout << "Word 'data' appears " << dataCount << " time(s)" << endl;
}





void task14() {
    int N, M;
    cout << "Enter N and M: ";
    cin >> N >> M;

    unique_ptr<double[]> matrix = make_unique<double[]>(N * M);

    cout << "Enter matrix elements row by row:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> matrix[i * M + j];
        }
    }

    
    vector<double> colSums(M, 0.0);
    for (int j = 0; j < M; ++j) {
        for (int i = 0; i < N; ++i) {
            colSums[j] += matrix[i * M + j];
        }
    }

    
    int maxIndex = 0;
    double maxSum = colSums[0];
    for (int j = 1; j < M; ++j) {
        if (colSums[j] > maxSum) {
            maxSum = colSums[j];
            maxIndex = j;
        }
    }

    cout << "Column sums: [";
    for (int j = 0; j < M; ++j) {
        cout << colSums[j];
        if (j < M - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Column with maximum sum: " << maxIndex + 1 << " (sum: " << maxSum << ")" << endl;
}





void task15() {
    vector<string> routes = {
        "Moscow-Berlin",
        "Berlin-Paris",
        "Paris-Rome",
        "Rome-Moscow"
    };

    shared_ptr<vector<string>> ptrRoutes = make_shared<vector<string>>(routes);

    
    auto countCity = [](const shared_ptr<vector<string>>& routes, const string& city) -> int {
        int count = 0;
        for (const string& route : *routes) {
            if (route.find(city) != string::npos) {
                count++;
            }
        }
        return count;
    };

    auto sortByLength = [](const shared_ptr<vector<string>>& routes) {
        sort(routes->begin(), routes->end(),
             [](const string& a, const string& b) {
                 return a.length() < b.length();
             });
    };

    auto concatRoutes = [](const shared_ptr<vector<string>>& routes) -> string {
        string result;
        for (const string& route : *routes) {
            if (!result.empty()) result += " -> ";
            result += route;
        }
        return result;
    };

    
    int parisCount = countCity(ptrRoutes, "Paris");
    cout << "Number of routes containing 'Paris': " << parisCount << endl;

    sortByLength(ptrRoutes);
    cout << "Sorted routes by length:\n";
    for (const string& route : *ptrRoutes) {
        cout << route << endl;
    }

    string allRoutes = concatRoutes(ptrRoutes);
    cout << "All routes combined: " << allRoutes << endl;
}





int main() {
    int choice;
    cout << "Select smart pointer task (1-15): ";
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
        case 12: task12(); break;
        case 13: task13(); break;
        case 14: task14(); break;
        case 15: task15(); break;
        default:
            cout << "Invalid task number." << endl;
            return 1;
    }

    return 0;
}