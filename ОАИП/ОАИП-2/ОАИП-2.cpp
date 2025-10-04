#include <iostream>
#include <cstring>
#include <cctype>

#define _CRT_SECURE_NO_WARNINGS

const int MAX_LENGTH = 1000;
const int MAX_WORDS = 10;
const int MAX_WORD_LENGTH = 100;

int splitString(const char* str, char words[MAX_WORDS][MAX_WORD_LENGTH]) {
    int wordCount = 0;
    int charIndex = 0;
    bool inWord = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (std::isalpha(str[i])) {
            words[wordCount][charIndex++] = str[i];
            inWord = true;
        }
        else if (inWord) {
            words[wordCount][charIndex] = '\0';
            wordCount++;
            charIndex = 0;
            inWord = false;
        }
    }
    if (inWord && wordCount < MAX_WORDS) {
        words[wordCount][charIndex] = '\0';
        wordCount++;
    }

    return wordCount;
}


int countWordsEndingWithA(char words[MAX_WORDS][MAX_WORD_LENGTH], int wordCount) {
    int count = 0;
    for (int i = 0; i < wordCount; i++) {
        int len = std::strlen(words[i]);
        if (len > 0 && (words[i][len - 1] == 'a' || words[i][len - 1] == 'A')) {
            count++;
        }
    }
    return count;
}


int findShortestWordLength(char words[MAX_WORDS][MAX_WORD_LENGTH], int wordCount) {
    if (wordCount == 0) return 0;

    int minLength = std::strlen(words[0]);
    for (int i = 1; i < wordCount; i++) {
        int len = std::strlen(words[i]);
        if (len < minLength) {
            minLength = len;
        }
    }
    return minLength;
}


int countBInSecondWord(char words[MAX_WORDS][MAX_WORD_LENGTH], int wordCount) {
    if (wordCount < 2) return 0;

    int count = 0;
    char* word = words[1]; 
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == 'b' || word[i] == 'B') {
            count++;
        }
    }
    return count;
}


void toLowerCase(char words[MAX_WORDS][MAX_WORD_LENGTH], int wordCount) {
    for (int i = 0; i < wordCount; i++) {
        for (int j = 0; words[i][j] != '\0'; j++) {
            if (std::isupper(words[i][j])) {
                words[i][j] = std::tolower(words[i][j]);
            }
        }
    }
}


int countWordsWithSameEnds(char words[MAX_WORDS][MAX_WORD_LENGTH], int wordCount) {
    int count = 0;
    for (int i = 0; i < wordCount; i++) {
        int len = std::strlen(words[i]);
        if (len > 0 && words[i][0] == words[i][len - 1]) {
            count++;
        }
    }
    return count;
}


void findLongestCommonSubstring(char words[MAX_WORDS][MAX_WORD_LENGTH], int wordCount,
    char result[MAX_WORD_LENGTH]) {
    if (wordCount < 2) {
        result[0] = '\0';
        return;
    }

    int maxLength = 0;
    result[0] = '\0';

    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            char word1[MAX_WORD_LENGTH], word2[MAX_WORD_LENGTH];
            strcpy_s(word1, words[i]);
            strcpy_s(word2, words[j]);

            for (int start1 = 0; word1[start1] != '\0'; start1++) {
                for (int end1 = start1; word1[end1] != '\0'; end1++) {
                    int len = end1 - start1 + 1;

                    if (len <= maxLength) continue;


                    char substring[MAX_WORD_LENGTH];
                    strncpy_s(substring, &word1[start1], len);
                    substring[len] = '\0';

                    if (std::strstr(word2, substring) != nullptr) {
                        if (len > maxLength || (len == maxLength && std::strcmp(substring, result) < 0)) {
                            maxLength = len;
                            strcpy_s(result,sizeof result,substring);
                        }
                    }
                }
            }
        }
    }

    if (maxLength == 0) {
        result[0] = '\0';
    }
}

int main() {

    setlocale(LC_CTYPE, "Russian");
    char input[MAX_LENGTH];
    char words[MAX_WORDS][MAX_WORD_LENGTH];

    std::cout << "Введите строку из 10 слов на латинице: ";
    std::cin.getline(input, MAX_LENGTH);

    int wordCount = splitString(input, words);

    if (wordCount < 10) {
        std::cout << "Ошибка: в строке должно быть 10 слов!" << std::endl;
        return 1;
    }

    std::cout << "\nРезультаты анализа:\n";
    std::cout << "===================\n";


    std::cout << "1. Слов, оканчивающих на 'a': "
        << countWordsEndingWithA(words, wordCount) << std::endl;


    std::cout << "2. Длина самого короткого слова: "
        << findShortestWordLength(words, wordCount) << std::endl;


    std::cout << "3. Букв 'b' во втором слове: "
        << countBInSecondWord(words, wordCount) << std::endl;


    char wordsCopy[MAX_WORDS][MAX_WORD_LENGTH];
    for (int i = 0; i < wordCount; i++) {
        strcpy_s(wordsCopy[i], words[i]);
    }
    toLowerCase(wordsCopy, wordCount);
    std::cout << "4. Строка в нижнем регистре: ";
    for (int i = 0; i < wordCount; i++) {
        std::cout << wordsCopy[i];
        if (i < wordCount - 1) std::cout << " ";
    }
    std::cout << std::endl;

    std::cout << "5. Слов с одинаковыми первым и последним символами: "
        << countWordsWithSameEnds(words, wordCount) << std::endl;

    char commonSubstring[MAX_WORD_LENGTH];
    findLongestCommonSubstring(words, wordCount, commonSubstring);
    if (commonSubstring[0] != '\0') {
        std::cout << "6. Самая длинная общая подстрока: \""
            << commonSubstring << "\"" << std::endl;
    }
    else {
        std::cout << "6. Общих подстрок не найдено" << std::endl;
    }

    return 0;
}