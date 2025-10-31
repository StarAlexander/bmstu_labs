#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <string>
using namespace std;

const int MAX_LEN = 1000;






int myStrLen(const char* str) {
    const char* p = str;
    while (*p != '\0') p++;
    return p - str;
}


void myStrCpy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}


void myStrCat(char* dest, const char* src) {
    char* end = dest;
    while (*end != '\0') end++;
    while (*src != '\0') {
        *end = *src;
        end++;
        src++;
    }
    *end = '\0';
}


int countSymbol(const char* str, char symbol) {
    int count = 0;
    for (const char* p = str; *p != '\0'; ++p) {
        if (*p == symbol) count++;
    }
    return count;
}


void replaceSpaces(char* str) {
    for (char* p = str; *p != '\0'; ++p) {
        if (*p == ' ') *p = '_';
    }
}


void reverse(char* str) {
    if (str == nullptr) return;
    int len = myStrLen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}


bool isPalindrome(const char* str) {
    if (str == nullptr) return true;
    int len = myStrLen(str);
    for (int i = 0; i < len / 2; ++i) {
        if (str[i] != str[len - 1 - i]) return false;
    }
    return true;
}


const char* findSubstring(const char* text, const char* word) {
    if (text == nullptr || word == nullptr) return nullptr;
    int textLen = myStrLen(text);
    int wordLen = myStrLen(word);
    if (wordLen == 0) return text;

    for (int i = 0; i <= textLen - wordLen; ++i) {
        bool match = true;
        for (int j = 0; j < wordLen; ++j) {
            if (text[i + j] != word[j]) {
                match = false;
                break;
            }
        }
        if (match) return &text[i];
    }
    return nullptr;
}


void removeSpaces(char* str) {
    char* read = str;
    char* write = str;
    while (*read != '\0') {
        if (*read != ' ') {
            *write = *read;
            write++;
        }
        read++;
    }
    *write = '\0';
}


int myStrCmp(const char* s1, const char* s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

// task 14
int sumVector(vector<int>& vec) {
    if (vec.empty()) return 0;
    int* p = &vec[0];
    int sum = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        sum += *(p + i);
    }
    return sum;
}

// task 14
void increaseBy10(vector<int>& vec) {
    if (vec.empty()) return;
    int* p = vec.data();
    for (size_t i = 0; i < vec.size(); ++i) {
        *(p + i) += 10;
    }
}






void parseTelemetry(const char* data) {
    if (data == nullptr) return;

    const char* p = data;
    while (*p != '\0') {
        
        while (*p == ' ' || *p == '\t' || *p == '\n') p++;

        if (*p == '\0') break;

        
        char name[50] = "";
        int nameIdx = 0;
        while (*p != ':' && *p != '\0' && nameIdx < 49) {
            name[nameIdx++] = *p++;
        }
        name[nameIdx] = '\0';

        if (*p != ':') break; 
        p++; 

        
        char value[50] = "";
        int valIdx = 0;
        while (*p != ';' && *p != '\0' && valIdx < 49) {
            value[valIdx++] = *p++;
        }
        value[valIdx] = '\0';

        
        if (myStrCmp(name, "TEMP") == 0) {
            cout << "Temperature: " << value << endl;
        } else if (myStrCmp(name, "PRESS") == 0) {
            cout << "Pressure: " << value << endl;
        } else if (myStrCmp(name, "HUM") == 0) {
            cout << "Humidity: " << value << endl;
        }

        if (*p == ';') p++; 
    }
}


struct Command {
    string name;
    int value;
};

void parseCommand(const char* input, vector<Command>& buffer) {
    if (input == nullptr) return;

    
    char name[50] = "";
    int i = 0;
    while (input[i] != ' ' && input[i] != '\0' && i < 49) {
        name[i] = input[i];
        i++;
    }
    name[i] = '\0';

    int value = 0;
    if (input[i] == ' ') {
        
        i++;
        int sign = 1;
        if (input[i] == '-') {
            sign = -1;
            i++;
        }
        while (input[i] >= '0' && input[i] <= '9') {
            value = value * 10 + (input[i] - '0');
            i++;
        }
        value *= sign;
    }

    Command cmd;
    cmd.name = name;
    cmd.value = value;
    buffer.push_back(cmd);
}


void analyzePressure(const vector<double>& data, double& minVal, double& maxVal, double& avgVal) {
    if (data.empty()) {
        minVal = maxVal = avgVal = 0.0;
        return;
    }

    const double* p = data.data();
    minVal = maxVal = *p;
    double sum = *p;

    for (size_t i = 1; i < data.size(); ++i) {
        double val = *(p + i);
        if (val < minVal) minVal = val;
        if (val > maxVal) maxVal = val;
        sum += val;
    }

    avgVal = sum / data.size();
}





void testStringFunctions() {
    cout << "\n=== Testing String Functions ===\n";

    char s1[] = "Hello";
    cout << "Length of '" << s1 << "': " << myStrLen(s1) << endl;

    char s2[50];
    myStrCpy(s2, s1);
    cout << "Copied: " << s2 << endl;

    myStrCat(s2, " World");
    cout << "Concatenated: " << s2 << endl;

    cout << "Spaces in 'a b c': " << countSymbol("a b c", ' ') << endl;

    char s3[] = "Hello World";
    replaceSpaces(s3);
    cout << "Replaced spaces: " << s3 << endl;

    char s4[] = "hello";
    reverse(s4);
    cout << "Reversed: " << s4 << endl;

    cout << "Is 'madam' palindrome? " << (isPalindrome("madam") ? "Yes" : "No") << endl;

    const char* found = findSubstring("abcdef", "cde");
    cout << "Found 'cde'? " << (found ? "Yes at " : "No") << (found ? found : "") << endl;

    char s5[] = "  a b  c  ";
    removeSpaces(s5);
    cout << "Removed spaces: '" << s5 << "'" << endl;

    cout << "Compare 'abc' and 'abd': " << myStrCmp("abc", "abd") << endl;
}


// task 14
void testVectorFunctions() {
    cout << "\n=== Testing Vector Functions ===\n";

    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "Sum: " << sumVector(vec) << endl;

    increaseBy10(vec);
    cout << "After +10: ";
    for (int x : vec) cout << x << " ";
    cout << endl;
}

void testPracticalTasks() {
    cout << "\n=== Testing Practical Tasks ===\n";

    
    cout << "\nTask 13: Telemetry parsing\n";
    parseTelemetry("TEMP:24.5;PRESS:101.3;HUM:55.2");

    
    cout << "\nTask 15: Robot commands\n";
    vector<Command> buffer;
    parseCommand("FORWARD 10", buffer);
    parseCommand("TURN 90", buffer);
    parseCommand("STOP", buffer);
    for (const auto& cmd : buffer) {
        cout << "Command: " << cmd.name << ", Value: " << cmd.value << endl;
    }

    
    cout << "\nTask 16: Pressure analysis\n";
    vector<double> pressure = {101.3, 100.8, 101.9, 100.5, 102.0};
    double minP, maxP, avgP;
    analyzePressure(pressure, minP, maxP, avgP);
    cout << "Min pressure: " << minP << endl;
    cout << "Max pressure: " << maxP << endl;
    cout << "Average pressure: " << avgP << endl;
}





int main() {
    int choice;
    cout << "Select task group:\n";
    cout << "1. Basic string functions (1-12)\n";
    cout << "2. Practical tasks (13,15,16)\n";
    cout << "3. Run all tests\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            testStringFunctions();
            testVectorFunctions();
            break;
        case 2:
            testPracticalTasks();
            break;
        case 3:
            testStringFunctions();
            testVectorFunctions();
            testPracticalTasks();
            break;
        default:
            cout << "Invalid choice." << endl;
            return 1;
    }

    return 0;
}