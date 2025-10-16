#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX_LEN = 1000;


void task1() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    int left = 0, right = strlen(s) - 1;
    bool isPalindrome = true;

    while (left < right) {
        
        while (left < right && !isalnum(s[left])) left++;
        
        while (left < right && !isalnum(s[right])) right--;

        if (tolower(s[left]) != tolower(s[right])) {
            isPalindrome = false;
            break;
        }
        left++;
        right--;
    }

    if (isPalindrome) {
        cout << "Palindrome" << endl;
    } else {
        cout << "Not a palindrome" << endl;
    }
}


void task2() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    int len = strlen(s);
    int uniqueCount = 0;

    for (int i = 0; i < len; ++i) {
        bool foundEarlier = false;
        for (int j = 0; j < i; ++j) {
            if (s[j] == s[i]) {
                foundEarlier = true;
                break;
            }
        }
        if (!foundEarlier) {
            uniqueCount++;
        }
    }

    cout << uniqueCount << endl;
}


void task3() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    int writeIndex = 0;
    for (int readIndex = 0; s[readIndex] != '\0'; ++readIndex) {
        if (!isdigit(s[readIndex])) {
            s[writeIndex++] = s[readIndex];
        }
    }
    s[writeIndex] = '\0';

    cout << s << endl;
}


void task4() {
    char A[MAX_LEN], B[MAX_LEN];
    cout << "Enter string A: ";
    cin.getline(A, MAX_LEN);
    cout << "Enter string B: ";
    cin.getline(B, MAX_LEN);

    bool allFound = true;
    int lenB = strlen(B);

    for (int i = 0; i < lenB; ++i) {
        char c = B[i];
        bool found = false;
        for (int j = 0; A[j] != '\0'; ++j) {
            if (A[j] == c) {
                found = true;
                break;
            }
        }
        if (!found) {
            allFound = false;
            break;
        }
    }

    if (allFound) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}


void task5() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    const char vowels[] = "aeiou";
    int vowelCount = 0, consonantCount = 0;

    for (int i = 0; s[i] != '\0'; ++i) {
        if (isalpha(s[i])) {
            char ch = tolower(s[i]);
            bool isVowel = false;
            for (int j = 0; vowels[j] != '\0'; ++j) {
                if (ch == vowels[j]) {
                    isVowel = true;
                    break;
                }
            }
            if (isVowel) {
                vowelCount++;
            } else {
                consonantCount++;
            }
        }
    }

    cout << "Vowels: " << vowelCount << endl;
    cout << "Consonants: " << consonantCount << endl;
}


void task6() {
    char text[MAX_LEN];
    int shift;
    cout << "Enter text: ";
    cin.getline(text, MAX_LEN);
    cout << "Enter shift: ";
    cin >> shift;
    cin.ignore(); 

    shift = shift % 26;
    if (shift < 0) shift += 26;

    for (int i = 0; text[i] != '\0'; ++i) {
        char c = text[i];
        if (c >= 'A' && c <= 'Z') {
            text[i] = (c - 'A' + shift) % 26 + 'A';
        } else if (c >= 'a' && c <= 'z') {
            text[i] = (c - 'a' + shift) % 26 + 'a';
        }
    }

    cout << text << endl;
}


void task7() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    if (s[0] == '\0') {
        cout << "" << endl;
        return;
    }

    char result[MAX_LEN * 2];
    int resIndex = 0;
    int i = 0;

    while (s[i] != '\0') {
        char current = s[i];
        int count = 0;
        int j = i;
        while (s[j] == current) {
            count++;
            j++;
        }

        result[resIndex++] = current;

        
        char countStr[10];
        int num = count;
        int idx = 0;
        if (num == 0) {
            countStr[idx++] = '0';
        } else {
            while (num > 0) {
                countStr[idx++] = '0' + (num % 10);
                num /= 10;
            }
        }
        
        for (int k = idx - 1; k >= 0; --k) {
            result[resIndex++] = countStr[k];
        }

        i = j;
    }
    result[resIndex] = '\0';

    cout << result << endl;
}


void task8() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    bool newSentence = true;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == '.' || s[i] == '!' || s[i] == '?') {
            newSentence = true;
        } else if (newSentence && isalpha(s[i])) {
            s[i] = toupper(s[i]);
            newSentence = false;
        } else if (isalpha(s[i])) {
            s[i] = tolower(s[i]);
        }
    }

    cout << s << endl;
}


void task9() {
    char str1[MAX_LEN], str2[MAX_LEN];
    cout << "Enter string 1: ";
    cin.getline(str1, MAX_LEN);
    cout << "Enter string 2: ";
    cin.getline(str2, MAX_LEN);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    const int N = 500;
    if (len1 >= N || len2 >= N) {
        cout << "String too long." << endl;
        return;
    }

    int dp[N+1][N+1] = {0};
    int maxLength = 0;
    int endingPos = 0; 

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endingPos = i;
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    if (maxLength == 0) {
        cout << "" << endl;
    } else {
        for (int i = endingPos - maxLength; i < endingPos; ++i) {
            cout << str1[i];
        }
        cout << endl;
    }
}


void task10() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    int start = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == ' ') {
            reverse(s + start, s + i);
            start = i + 1;
        }
    }
    reverse(s + start, s + strlen(s));

    cout << s << endl;
}


void task11() {
    char s[MAX_LEN];
    int k;
    cout << "Enter string: ";
    cin.getline(s, MAX_LEN);
    cout << "Enter k: ";
    cin >> k;
    cin.ignore();

    int len = strlen(s);
    if (k <= 0 || k > len) {
        return;
    }

    for (int i = 0; i <= len - k; ++i) {
        bool unique = true;
        
        for (int j = i; j < i + k; ++j) {
            for (int m = j + 1; m < i + k; ++m) {
                if (s[j] == s[m]) {
                    unique = false;
                    break;
                }
            }
            if (!unique) break;
        }
        if (unique) {
            for (int j = 0; j < k; ++j) {
                cout << s[i + j];
            }
            cout << endl;
        }
    }
}


int main() {
    int choice;
    cout << "Select string task (1-11): ";
    cin >> choice;
    cin.ignore(); 

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