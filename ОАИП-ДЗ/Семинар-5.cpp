#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>
using namespace std;


void task1() {
    vector<int> v(10);
    iota(v.begin(), v.end(), 1);
    cout << "Vector: ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;
}


void task2() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for_each(v.begin(), v.end(), [](int& x) { x *= 2; });
    cout << "Doubled vector: ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;
}


void task3() {
    vector<int> v(20);
    iota(v.begin(), v.end(), 1);
    random_device rd;
    mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;
    auto m = max_element(v.begin(),v.end(),[](const int& a, const int& b) {
        return a<b;
    });
    if (m != v.end())
    cout << "Max element: " << *m << endl;
}


void task4() {
    vector<int> v(10);
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<> dis(-50,50);
    for (int& s: v) s = dis(mt);
    cout << "Original: ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;
    v.erase(remove_if(v.begin(), v.end(), [](int x) { return x < 0; }), v.end());
    cout << "After removing negatives: ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;
}


void task5() {
    vector<int> v(20);
    iota(v.begin(), v.end(), 1);
    random_device rd;
    mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);

    auto mm = minmax_element(v.begin(), v.end());
    double mean = accumulate(v.begin(), v.end(), 0.0) / v.size();

    vector<int> sorted = v;
    sort(sorted.begin(), sorted.end());
    double median = (sorted.size() % 2 == 0)
        ? (sorted[sorted.size()/2 - 1] + sorted[sorted.size()/2]) / 2.0
        : sorted[sorted.size()/2];

    cout << fixed << setprecision(2);
    cout << "Min: " << *(mm.first) << ", Max: " << *(mm.second)
         << ", Mean: " << mean << ", Median: " << median << endl;
}


void task6() {
    vector<int> v = {1, 7, 3, 7, 2, 5, 7, 9, 2, 4, 6, 8, 10, 1, 3, 5, 7, 9, 2, 4};
    if (find(v.begin(), v.end(), 7) != v.end()) {
        cout << "Number 7 is present." << endl;
    } else {
        cout << "Number 7 is NOT present." << endl;
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    cout << "After removing duplicates: ";
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
    cout << endl;
}


void task7() {
    vector<double> temps = {-60, -45, -10, 0, 15, 25, 30, 55, 40, -5, 10, -51, 49, 50, -50};
    temps.erase(remove_if(temps.begin(), temps.end(), [](double t) { return t < -50 || t > 50; }), temps.end());
    if (temps.empty()) {
        cout << "No valid temperatures." << endl;
        return;
    }
    auto mm = minmax_element(temps.begin(), temps.end());
    double mean = accumulate(temps.begin(), temps.end(), 0.0) / temps.size();
    bool allAboveMinus10 = all_of(temps.begin(), temps.end(), [](double t) { return t > -10; });
    cout << fixed << setprecision(2);
    cout << "Min: " << *(mm.first) << ", Max: " << *(mm.second) << ", Mean: " << mean << endl;
    cout << "All > -10? " << (allAboveMinus10 ? "Yes" : "No") << endl;
}


void task8() {
    vector<int> speeds(50);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 180);
    for (auto& s : speeds) s = dis(gen);
    for (int s : speeds) cout << s << " ";
    double avgSpeed = accumulate(speeds.begin(), speeds.end(), 0.0) / speeds.size();
    bool alwaysMoving = all_of(speeds.begin(), speeds.end(), [](int s) { return s > 0; });

    vector<int> topSpeeds = speeds;
    sort(topSpeeds.rbegin(), topSpeeds.rend());
    topSpeeds.resize(10);

    cout << fixed << setprecision(2);
    cout << "Average speed: " << avgSpeed << endl;
    cout << "Always moving? " << (alwaysMoving ? "Yes" : "No") << endl;
    cout << "Top 10 speeds: ";
    for (int s : topSpeeds) cout << s << " ";
    cout << endl;
}


void task9() {
    vector<double> power = { -2, 5, 12, 88, 95, 0, 10, 45, 70, 90, 91, 5, 15, 80, 85, 92, 3, 50, 60, 75 };
    power.erase(remove_if(power.begin(), power.end(), [](double p) { return p < 0; }), power.end());
    if (power.empty()) {
        cout << "No valid power measurements." << endl;
        return;
    }
    auto mm = minmax_element(power.begin(), power.end());
    double mean = accumulate(power.begin(), power.end(), 0.0) / power.size();
    bool withinRange = all_of(power.begin(), power.end(), [](double p) { return p >= 10 && p <= 90; });

    vector<double> sorted = power;
    sort(sorted.begin(), sorted.end());
    double median = (sorted.size() % 2 == 0)
        ? (sorted[sorted.size()/2 - 1] + sorted[sorted.size()/2]) / 2.0
        : sorted[sorted.size()/2];

    cout << fixed << setprecision(2);
    cout << "Min: " << *(mm.first) << ", Max: " << *(mm.second) << ", Mean: " << mean << ", Median: " << median << endl;
    cout << "All in [10,90]? " << (withinRange ? "Yes" : "No") << endl;
}


void task10() {
    vector<double> energy(30);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(10.0, 100.0);
    for (auto& e : energy) e = dis(gen);
    cout << fixed << setprecision(2);
    for (auto& e: energy) cout << e << " ";
    cout << endl;
    double total = accumulate(energy.begin(), energy.end(), 0.0);
    double avg = total / 30.0;

    auto mm = minmax_element(energy.begin(), energy.end());
    int minDay = mm.first - energy.begin() + 1;
    int maxDay = mm.second - energy.begin() + 1;

    vector<double> peakDays;
    copy_if(energy.begin(), energy.end(), back_inserter(peakDays),
            [avg](double e) { return e > avg * 1.2; });

    cout << "Total consumption: " << total << " kWh" << endl;
    cout << "Average per day: " << avg << " kWh" << endl;
    cout << "Min on day " << minDay << " (" << *(mm.first) << "), Max on day " << maxDay << " (" << *(mm.second) << ")" << endl;
    cout << "Peak days (>20% above avg): " << peakDays.size() << endl;
}


void task11() {
    vector<double> vib(50);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.5);
    for (auto& v : vib) v = dis(gen);
    cout << fixed << setprecision(3);
    for (auto& v: vib) cout << v << " ";
    cout << endl;
    vib.erase(remove_if(vib.begin(), vib.end(), [](double a) { return a < 0.1; }), vib.end());
    if (vib.empty()) {
        cout << "No significant vibrations." << endl;
        return;
    }

    double mean = accumulate(vib.begin(), vib.end(), 0.0) / vib.size();
    auto maxIt = max_element(vib.begin(), vib.end());
    bool allAbove05 = all_of(vib.begin(), vib.end(), [](double a) { return a > 0.5; });

    vector<double> top10 = vib;
    sort(top10.rbegin(), top10.rend());
    if (top10.size() > 10) top10.resize(10);

    
    cout << "Mean amplitude: " << mean << ", Max: " << *maxIt << endl;
    cout << "All > 0.5? " << (allAbove05 ? "Yes" : "No") << endl;
    cout << "Top 10 amplitudes: ";
    for (double a : top10) cout << a << " ";
    cout << endl;
}


void task12() {
    vector<double> fuel(50);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(5.0, 100.0);
    for (auto& f : fuel) f = dis(gen);
    cout << fixed << setprecision(2);
    for (auto& f: fuel) cout << f << " ";
    cout << endl;
    auto minIt = min_element(fuel.begin(), fuel.end());
    double minLevel = *minIt;
    double maxLevel = *max_element(fuel.begin(), fuel.end());
    bool below5Percent = (minLevel < 0.05 * maxLevel);
    double totalConsumption = 0;
    for (int i=1; i<fuel.size()-1;i++) {
        if (fuel[i] < fuel[i-1]) totalConsumption += fuel[i-1]-fuel[i];
    }
    vector<double> sorted = fuel;
    sort(sorted.begin(), sorted.end());
    double median = sorted[sorted.size()/2];

    
    cout << "Min fuel level: " << minLevel << endl;
    cout << "Below 5% of max? " << (below5Percent ? "Yes" : "No") << endl;
    cout << "Total consumption (start - end): " << totalConsumption << endl;
    cout << "Median level: " << median << endl;
}


void task13() {
    vector<double> pressure(50);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 13.0);
    for (auto& p : pressure) p = dis(gen);
    cout << fixed << setprecision(2);
    for (auto& p : pressure) cout << p << " ";
    cout << endl;
    pressure.erase(remove_if(pressure.begin(), pressure.end(),
        [](double p) { return p < 0 || p > 12; }), pressure.end());

    if (pressure.empty()) {
        cout << "No valid pressure readings." << endl;
        return;
    }

    double avg = accumulate(pressure.begin(), pressure.end(), 0.0) / pressure.size();
    auto mm = minmax_element(pressure.begin(), pressure.end());

    
    cout << "Average pressure: " << avg << " bar" << endl;
    cout << "Min: " << *(mm.first) << ", Max: " << *(mm.second) << " bar" << endl;
    cout << "Pressures > 8 bar: ";
    for_each(pressure.begin(), pressure.end(), [](double p) {
        if (p > 8) cout << p << " ";
    });
    cout << endl;
}


void task14() {
    vector<double> consumption(24);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(100.0, 500.0);
    for (auto& c : consumption) c = dis(gen);
    cout << fixed << setprecision(2);
    for (auto& c : consumption) cout << c << " ";
    cout << endl;
    double total = accumulate(consumption.begin(), consumption.end(), 0.0);
    double avg = total / 24.0;

    auto maxIt = max_element(consumption.begin(), consumption.end());
    int peakHour = maxIt - consumption.begin() + 1;

    vector<double> deviations(24);
    transform(consumption.begin(), consumption.end(), deviations.begin(),
              [avg](double c) { return c - avg; });
    cout << "deviations: ";
    for (auto& d: deviations) cout << d << " ";
    cout << endl;
    vector<double> sorted = consumption;
    sort(sorted.begin(), sorted.end());
    cout << "Top 5 lowest consumption hours: ";
    for (int i = 0; i < 5; ++i) cout << sorted[i] << " ";
    cout << endl;
    cout << "Total: " << total << " kWh, Average: " << avg << " kWh" << endl;
    cout << "Peak hour: " << peakHour << " (" << *maxIt << " kWh)" << endl;
}


void task15() {
    const int N_TEMP = 30, N_PRESS = 100, CHANNELS = 5;
    vector<vector<double>> temp(CHANNELS, vector<double>(N_TEMP));
    vector<vector<double>> pressure(CHANNELS, vector<double>(N_PRESS));

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> tempDist(20.0, 120.0);
    uniform_real_distribution<> pressDist(1.0, 10.0);

    for (int ch = 0; ch < CHANNELS; ++ch) {
        for (int i = 0; i < N_TEMP; ++i) temp[ch][i] = tempDist(gen);
        for (int i = 0; i < N_PRESS; ++i) pressure[ch][i] = pressDist(gen);
    }

    
    vector<double> avgTemp(CHANNELS);
    transform(temp.begin(), temp.end(), avgTemp.begin(),
              [](const vector<double>& t) {
                  return accumulate(t.begin(), t.end(), 0.0) / t.size();
              });

    
    vector<pair<double, double>> pressRange(CHANNELS);
    for (int ch = 0; ch < CHANNELS; ++ch) {
        auto mm = minmax_element(pressure[ch].begin(), pressure[ch].end());
        pressRange[ch] = make_pair(*(mm.first), *(mm.second));
    }

    
    vector<double> tempVar(CHANNELS);
    for (int ch = 0; ch < CHANNELS; ++ch) {
        auto mm = minmax_element(temp[ch].begin(), temp[ch].end());
        tempVar[ch] = *(mm.second) - *(mm.first);
    }

    int maxVarChannel = max_element(tempVar.begin(), tempVar.end()) - tempVar.begin();


    vector<vector<double>> normPressure = pressure;
    for (int ch = 0; ch < CHANNELS; ++ch) {
        double minP = pressRange[ch].first;
        double maxP = pressRange[ch].second;
        double range = maxP - minP;
        if (range == 0) range = 1;
        transform(normPressure[ch].begin(), normPressure[ch].end(), normPressure[ch].begin(),
                  [minP, range](double p) { return (p - minP) / range; });
    }

    cout << "Normalized pressure values > 0.9:\n";
    for (int ch = 0; ch < CHANNELS; ++ch) {
        for (double p : normPressure[ch]) {
            if (p > 0.9) {
                cout << "Ch" << ch+1 << ": " << fixed << setprecision(3) << p << " ";
            }
        }
    }
    cout << endl;


    vector<pair<double, int>> tempWithIndex;
    for (int i = 0; i < CHANNELS; ++i) {
        tempWithIndex.push_back(make_pair(avgTemp[i], i));
    }
    sort(tempWithIndex.begin(), tempWithIndex.end(),
         [](const pair<double,int>& a, const pair<double,int>& b) {
             return a.first > b.first;
         });
    int hottestChannel = tempWithIndex[0].second;

    cout << "Channel with max temp variation: " << maxVarChannel + 1 << endl;
    cout << "Hottest channel (max avg temp): " << hottestChannel + 1 << endl;
}


int main() {
    int choice;
    cout << "Select vector task (1-15): ";
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