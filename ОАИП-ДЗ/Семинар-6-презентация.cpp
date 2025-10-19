#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

const int MAX_LEN = 1000;


void task1() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    char longestWord[MAX_LEN] = "";
    char currentWord[MAX_LEN];
    int maxLen = 0;

    int i = 0;
    while (s[i] != '\0') {
        
        while (s[i] != '\0' && !isalpha(s[i])) i++;

        if (s[i] == '\0') break;

        
        int j = 0;
        while (s[i] != '\0' && isalpha(s[i])) {
            currentWord[j++] = s[i++];
        }
        currentWord[j] = '\0';

        int len = strlen(currentWord);
        if (len > maxLen) {
            maxLen = len;
            strcpy(longestWord, currentWord);
        }
    }

    if (maxLen > 0) {
        cout << longestWord << endl;
    } else {
        cout << "" << endl;
    }
}


void task2() {
    char s[MAX_LEN];
    char ch;
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);
    cout << "Enter a character to remove: ";
    cin >> ch;
    cin.ignore(); 

    int writeIndex = 0;
    for (int readIndex = 0; s[readIndex] != '\0'; ++readIndex) {
        if (s[readIndex] != ch) {
            s[writeIndex++] = s[readIndex];
        }
    }
    s[writeIndex] = '\0';

    cout << s << endl;
}


void task3() {
    char s[MAX_LEN];
    char oldSub[MAX_LEN], newSub[MAX_LEN];

    cout << "Enter the original string: ";
    cin.getline(s, MAX_LEN);
    cout << "Enter substring to replace: ";
    cin.getline(oldSub, MAX_LEN);
    cout << "Enter replacement string: ";
    cin.getline(newSub, MAX_LEN);

    if (strlen(oldSub) == 0) {
        cout << s << endl;
        return;
    }

    char result[MAX_LEN * 2] = ""; 
    int sLen = strlen(s);
    int oldLen = strlen(oldSub);
    int newLen = strlen(newSub);

    int i = 0, resIndex = 0;
    while (i < sLen) {
        
        bool match = true;
        if (i + oldLen <= sLen) {
            for (int j = 0; j < oldLen; ++j) {
                if (s[i + j] != oldSub[j]) {
                    match = false;
                    break;
                }
            }
        } else {
            match = false;
        }

        if (match) {
            
            for (int k = 0; k < newLen; ++k) {
                result[resIndex++] = newSub[k];
            }
            i += oldLen;
        } else {
            result[resIndex++] = s[i];
            i++;
        }
    }
    result[resIndex] = '\0';

    cout << result << endl;
}


void task4() {
    char s1[MAX_LEN], s2[MAX_LEN];
    cout << "Enter first string: ";
    cin.getline(s1, MAX_LEN);
    cout << "Enter second string: ";
    cin.getline(s2, MAX_LEN);

    
    int freq[26] = {0};

    
    for (int i = 0; s1[i] != '\0'; ++i) {
        if (isalpha(s1[i])) {
            char c = tolower(s1[i]);
            freq[c - 'a']++;
        }
    }

    
    for (int i = 0; s2[i] != '\0'; ++i) {
        if (isalpha(s2[i])) {
            char c = tolower(s2[i]);
            freq[c - 'a']--;
        }
    }

    bool isAnagram = true;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] != 0) {
            isAnagram = false;
            break;
        }
    }

    if (isAnagram) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}


void task5() {
    char s[MAX_LEN];
    cout << "Enter a string: ";
    cin.getline(s, MAX_LEN);

    int i = 0;
    while (s[i] != '\0') {
        
        while (s[i] != '\0' && !isalpha(s[i])) i++;
        if (s[i] == '\0') break;

        
        while (s[i] != '\0' && isalpha(s[i])) {
            cout << s[i];
            i++;
        }
        cout << endl;
    }
}


int main() {
    int choice;
    cout << "Select task (1-5):\n";
    cout << "1. Longest word\n";
    cout << "2. Remove character\n";
    cout << "3. Replace substring\n";
    cout << "4. Check anagrams\n";
    cout << "5. Extract words\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore(); 

    switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        default:
            cout << "Invalid task number." << endl;
            return 1;
    }

    return 0;
}