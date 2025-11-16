#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
using namespace std;

const string INPUT_FILE = "input.txt";
const string OUTPUT_FILE = "output.txt";
const string SOURCE_FILE = "source.txt";
const string COPY_FILE = "copy.txt";
const string DATA_FILE = "data.txt";
const string NUMBERS_FILE = "numbers.txt";
const string TEXT_FILE = "text.txt";
const string FILE1_FILE = "file1.txt";
const string FILE2_FILE = "file2.txt";
const string TEMP_DATA_FILE = "temperature_data.txt";
const string POWER_LOG_FILE = "power_log.txt";
const string VIBRATION_LOG_FILE = "vibration_log.txt";





void task1() {
    ifstream inFile(INPUT_FILE);
    if (!inFile) {
        cout << "Error: File '" << INPUT_FILE << "' not found." << endl;
        return;
    }

    cout << "File content:\n";
    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}





void task2() {
    ifstream inFile(DATA_FILE);
    if (!inFile) {
        cout << "Error: File '" << DATA_FILE << "' not found." << endl;
        return;
    }

    int count = 0;
    string line;
    while (getline(inFile, line)) {
        count++;
    }
    inFile.close();

    cout << "Number of lines in file: " << count << endl;
}





void task3() {
    ifstream inFile(TEXT_FILE);
    if (!inFile) {
        cout << "Error: File '" << TEXT_FILE << "' not found." << endl;
        return;
    }

    int wordCount = 0;
    string word;
    while (inFile >> word) {
        wordCount++;
    }
    inFile.close();

    cout << "Number of words in file: " << wordCount << endl;
}





void task4() {
    
    ofstream src(SOURCE_FILE);
    src << "Line 1\nLine 2\nLine 3\nLine 4\nLine 5\n";
    src.close();

    ifstream inFile(SOURCE_FILE);
    ofstream outFile(COPY_FILE);

    if (!inFile || !outFile) {
        cout << "Error: Cannot open files." << endl;
        return;
    }

    string line;
    int copiedLines = 0;
    while (getline(inFile, line)) {
        outFile << line << endl;
        copiedLines++;
    }

    inFile.close();
    outFile.close();

    cout << "File successfully copied." << endl;
    cout << "Number of copied lines: " << copiedLines << endl;
}





void task5() {
    ifstream inFile(INPUT_FILE);
    if (!inFile) {
        cout << "Error: File '" << INPUT_FILE << "' not found." << endl;
        return;
    }

    char ch;
    int charCount = 0;
    while (inFile.get(ch)) {
        charCount++;
    }
    inFile.close();

    cout << "Number of characters in file: " << charCount << endl;
}





void task6() {
    ofstream outFile(OUTPUT_FILE);
    if (!outFile) {
        cout << "Error: Cannot create file '" << OUTPUT_FILE << "'." << endl;
        return;
    }

    cout << "Enter lines (empty line to stop):\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line.empty()) break;
        outFile << line << endl;
    }
    outFile.close();

    cout << "Data saved to file '" << OUTPUT_FILE << "'." << endl;
}





void task7() {
    ifstream inFile(NUMBERS_FILE);
    if (!inFile) {
        cout << "Error: File '" << NUMBERS_FILE << "' not found." << endl;
        return;
    }

    int count = 0;
    double sum = 0.0;
    int num;
    while (inFile >> num) {
        count++;
        sum += num;
    }
    inFile.close();

    double avg = count > 0 ? sum / count : 0.0;

    cout << "Number of numbers: " << count << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
}





void task8() {
    ofstream f1(FILE1_FILE);
    f1 << "Line 1\nLine 2\nLine 3\n";
    f1.close();

    ofstream f2(FILE2_FILE);
    f2 << "Line 1\nLine 2\nLine 3\n";
    f2.close();

    ifstream inFile1(FILE1_FILE);
    ifstream inFile2(FILE2_FILE);

    if (!inFile1 || !inFile2) {
        cout << "Error: Cannot open files." << endl;
        return;
    }

    string line1, line2;
    bool identical = true;
    int lineNumber = 1;

    while (getline(inFile1, line1) && getline(inFile2, line2)) {
        if (line1 != line2) {
            identical = false;
            break;
        }
        lineNumber++;
    }

    
    if (inFile1.good() || inFile2.good()) {
        identical = false;
    }

    inFile1.close();
    inFile2.close();

    if (identical) {
        cout << "Files are identical." << endl;
    } else {
        cout << "Files differ." << endl;
    }
}





void task9() {
    ifstream inFile(TEMP_DATA_FILE);
    if (!inFile) {
        cout << "Error: File '" << TEMP_DATA_FILE << "' not found." << endl;
        return;
    }

    map<string, vector<double>> sensorData;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string sensorName;
        double temp;
        if (ss >> sensorName >> temp) {
            sensorData[sensorName].push_back(temp);
        }
    }
    inFile.close();

    ofstream outFile("report.txt");
    if (!outFile) {
        cout << "Error: Cannot create report.txt." << endl;
        return;
    }

    for (const auto& pair : sensorData) {
        const string& name = pair.first;
        const vector<double>& temps = pair.second;
        double minTemp = *min_element(temps.begin(), temps.end());
        double maxTemp = *max_element(temps.begin(), temps.end());
        double avgTemp = accumulate(temps.begin(), temps.end(), 0.0) / temps.size();

        outFile << name << ": min = " << minTemp << ", max = " << maxTemp << ", avg = " << avgTemp << endl;
    }
    outFile.close();

    cout << "Temperature analysis saved to report.txt" << endl;
}





void task10() {
    ifstream inFile(POWER_LOG_FILE);
    if (!inFile) {
        cout << "Error: File '" << POWER_LOG_FILE << "' not found." << endl;
        return;
    }

    map<string, vector<double>> deviceData;

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string timestamp, deviceName;
        double power;
        if (ss >> timestamp >> deviceName >> power) {
            deviceData[deviceName].push_back(power);
        }
    }
    inFile.close();

    ofstream outFile("energy_report.txt");
    if (!outFile) {
        cout << "Error: Cannot create energy_report.txt." << endl;
        return;
    }

    for (const auto& pair : deviceData) {
        const string& name = pair.first;
        const vector<double>& powers = pair.second;
        double total = accumulate(powers.begin(), powers.end(), 0.0);
        double avg = total / powers.size();
        int count = powers.size();

        outFile << fixed << setprecision(2);
        outFile << name << ": measurements = " << count << ", total = " << total << " kWh, average = " << avg << " kW" << endl;
    }
    outFile.close();

    cout << "Energy consumption analysis saved to energy_report.txt" << endl;
}





void task11() {
    ifstream inFile(VIBRATION_LOG_FILE);
    if (!inFile) {
        cout << "Error: File '" << VIBRATION_LOG_FILE << "' not found." << endl;
        return;
    }

    vector<double> amplitudes;
    double val;
    while (inFile >> val) {
        amplitudes.push_back(val);
    }
    inFile.close();

    
    vector<double> filtered;
    for (double a : amplitudes) {
        if (a > 0.05) {
            filtered.push_back(a);
        }
    }

    double avg = 0.0;
    double minVal = 0.0;
    double maxVal = 0.0;
    if (!filtered.empty()) {
        avg = accumulate(filtered.begin(), filtered.end(), 0.0) / filtered.size();
        minVal = *min_element(filtered.begin(), filtered.end());
        maxVal = *max_element(filtered.begin(), filtered.end());
    }

    ofstream outFile("vibration_report.txt");
    if (!outFile) {
        cout << "Error: Cannot create vibration_report.txt." << endl;
        return;
    }

    outFile << "Number of measurements: " << amplitudes.size() << endl;
    outFile << "Filtered values (>0.05): ";
    for (size_t i = 0; i < filtered.size(); ++i) {
        if (i > 0) outFile << " ";
        outFile << filtered[i];
    }
    outFile << endl;
    outFile << "Average: " << avg << endl;
    outFile << "Minimum: " << minVal << endl;
    outFile << "Maximum: " << maxVal << endl;
    outFile.close();

    cout << "Vibration data analysis finished. Report saved to vibration_report.txt" << endl;
}





int main() {
    int choice;
    cout << "Select file task (1-11): ";
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