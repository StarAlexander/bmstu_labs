#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;

// Task 1: Mirror reflections of matrix
void task1() {
    int N;
    cout << "Enter matrix size N (1 <= N <= 100): ";
    cin >> N;

    if (N < 1 || N > 100) {
        cout << "Invalid N. Must be between 1 and 100." << endl;
        return;
    }

    int A[100][100];
    cout << "Enter matrix " << N << "x" << N << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    int M1[100][100]; // main diagonal
    int M2[100][100]; // anti-diagonal
    int M3[100][100]; // vertical mirror
    int M4[100][100]; // horizontal mirror

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            M1[i][j] = A[j][i];
            M2[i][j] = A[N-1-j][N-1-i];
            M3[i][j] = A[i][N-1-j];
            M4[i][j] = A[N-1-i][j];
        }
    }

    cout << "\nMatrix 1 (main diagonal reflection):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << M1[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix 2 (anti-diagonal reflection):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << M2[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix 3 (vertical mirror):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << M3[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix 4 (horizontal mirror):\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << M4[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nMatching matrices:\n";
    bool foundMatch = false;
    for (int i = 1; i <= 4; ++i) {
        for (int j = i + 1; j <= 4; ++j) {
            bool match = true;
            int (*m1)[100], (*m2)[100];
            if (i == 1) m1 = M1;
            else if (i == 2) m1 = M2;
            else if (i == 3) m1 = M3;
            else m1 = M4;

            if (j == 1) m2 = M1;
            else if (j == 2) m2 = M2;
            else if (j == 3) m2 = M3;
            else m2 = M4;

            for (int r = 0; r < N && match; ++r) {
                for (int c = 0; c < N; ++c) {
                    if (m1[r][c] != m2[r][c]) {
                        match = false;
                        break;
                    }
                }
            }

            if (match) {
                cout << "(" << i << ", " << j << ") ";
                foundMatch = true;
            }
        }
    }

    if (!foundMatch) {
        cout << "NONE";
    }
    cout << endl;
}

// Task 2: Magic square check
void task2() {
    int N;
    cout << "Enter matrix size N (1 <= N <= 50): ";
    cin >> N;

    if (N < 1 || N > 50) {
        cout << "Invalid N. Must be between 1 and 50." << endl;
        return;
    }

    int A[50][50];
    cout << "Enter matrix " << N << "x" << N << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }

    int targetSum = 0;
    for (int j = 0; j < N; ++j) targetSum += A[0][j];

    for (int i = 1; i < N; ++i) {
        int rowSum = 0;
        for (int j = 0; j < N; ++j) rowSum += A[i][j];
        if (rowSum != targetSum) { cout << "NO" << endl; return; }
    }

    for (int j = 0; j < N; ++j) {
        int colSum = 0;
        for (int i = 0; i < N; ++i) colSum += A[i][j];
        if (colSum != targetSum) { cout << "NO" << endl; return; }
    }

    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < N; ++i) {
        diag1 += A[i][i];
        diag2 += A[i][N-1-i];
    }
    if (diag1 != targetSum || diag2 != targetSum) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES " << targetSum << endl;
}

// Task 3: Saddle points
void task3() {
    int N, M;
    cout << "Enter matrix dimensions N M (1 <= N,M <= 100): ";
    cin >> N >> M;

    if (N < 1 || N > 100 || M < 1 || M > 100) {
        cout << "Invalid dimensions." << endl;
        return;
    }

    int A[100][100];
    cout << "Enter matrix " << N << "x" << M << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j];
        }
    }

    int rowMin[100], rowMax[100];
    int colMin[100], colMax[100];

    for (int i = 0; i < N; ++i) {
        rowMin[i] = rowMax[i] = A[i][0];
        for (int j = 1; j < M; ++j) {
            if (A[i][j] < rowMin[i]) rowMin[i] = A[i][j];
            if (A[i][j] > rowMax[i]) rowMax[i] = A[i][j];
        }
    }

    for (int j = 0; j < M; ++j) {
        colMin[j] = colMax[j] = A[0][j];
        for (int i = 1; i < N; ++i) {
            if (A[i][j] < colMin[j]) colMin[j] = A[i][j];
            if (A[i][j] > colMax[j]) colMax[j] = A[i][j];
        }
    }

    bool found = false;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i][j] == rowMin[i] && A[i][j] == colMax[j]) {
                cout << "A " << A[i][j] << " " << i << " " << j << endl;
                found = true;
            }
            if (A[i][j] == rowMax[i] && A[i][j] == colMin[j]) {
                cout << "B " << A[i][j] << " " << i << " " << j << endl;
                found = true;
            }
        }
    }

    if (!found) cout << "NONE" << endl;
}

// Task 4: Spiral fill matrix
void task4() {
    int N;
    cout << "Enter matrix size N (1 <= N <= 100): ";
    cin >> N;

    if (N < 1 || N > 100) {
        cout << "Invalid N." << endl;
        return;
    }

    int A[100][100];
    int num = 1;
    int top = 0, bottom = N-1, left = 0, right = N-1;

    while (num <= N*N) {
        for (int j = left; j <= right; ++j) A[top][j] = num++;
        top++;
        for (int i = top; i <= bottom; ++i) A[i][right] = num++;
        right--;
        if (top <= bottom)
            for (int j = right; j >= left; --j) A[bottom][j] = num++;
        bottom--;
        if (left <= right)
            for (int i = bottom; i >= top; --i) A[i][left] = num++;
        left++;
    }

    cout << "Spiral matrix:\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}

// Task 5: Spiral traversal
void task5() {
    int N, M;
    cout << "Enter matrix dimensions N M: ";
    cin >> N >> M;

    if (N < 1 || M < 1) {
        cout << "Invalid dimensions." << endl;
        return;
    }

    int A[100][100];
    cout << "Enter matrix " << N << "x" << M << ":\n";
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j];
        }
    }

    int top = 0, bottom = N-1, left = 0, right = M-1;
    vector<int> result;

    while (top <= bottom && left <= right) {
        for (int j = left; j <= right; ++j) result.push_back(A[top][j]); top++;
        for (int i = top; i <= bottom; ++i) result.push_back(A[i][right]); right--;
        if (top <= bottom) for (int j = right; j >= left; --j) result.push_back(A[bottom][j]); bottom--;
        if (left <= right) for (int i = bottom; i >= top; --i) result.push_back(A[i][left]); left++;
    }

    cout << "Spiral traversal: ";
    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
}

// --- NEW: Parameterized solvers for systems ---

// Task 6: Solve 2x2 system: a1*x + b1*y = c1; a2*x + b2*y = c2
void solveSystem2x2(double a1, double b1, double c1,
                    double a2, double b2, double c2) {
    double det = a1 * b2 - a2 * b1;
    if (abs(det) < 1e-9) {
        cout << "System has no unique solution." << endl;
        return;
    }
    double x = (c1 * b2 - c2 * b1) / det;
    double y = (a1 * c2 - a2 * c1) / det;
    cout << fixed << setprecision(4);
    cout << "Solution: x = " << x << ", y = " << y << endl;
}

// Task 7 & 8: Solve 3x3 system using Cramer's rule
void solveSystem3x3(double a11, double a12, double a13, double b1,
                    double a21, double a22, double a23, double b2,
                    double a31, double a32, double a33, double b3) {
    // Main determinant
    double det = a11*(a22*a33 - a23*a32)
               - a12*(a21*a33 - a23*a31)
               + a13*(a21*a32 - a22*a31);

    if (abs(det) < 1e-9) {
        cout << "System has no unique solution." << endl;
        return;
    }

    // Dx: replace first column with constants
    double Dx = b1*(a22*a33 - a23*a32)
              - a12*(b2*a33 - a23*b3)
              + a13*(b2*a32 - a22*b3);

    // Dy: replace second column
    double Dy = a11*(b2*a33 - a23*b3)
              - b1*(a21*a33 - a23*a31)
              + a13*(a21*b3 - b2*a31);

    // Dz: replace third column
    double Dz = a11*(a22*b3 - b2*a32)
              - a12*(a21*b3 - b2*a31)
              + b1*(a21*a32 - a22*a31);

    double x = Dx / det;
    double y = Dy / det;
    double z = Dz / det;

    cout << fixed << setprecision(4);
    cout << "Solution: x = " << x << ", y = " << y << ", z = " << z << endl;
}

// Task 6: Wrapper for specific system
void task6() {
    // System: 2x + 3y = 13; 5x - y = 9
    solveSystem2x2(2, 3, 13,
                   5, -1, 9);
}

// Task 7: Wrapper for specific system
void task7() {
    // x + y + z = 6
    // 2x - y + 3z = 14
    // -x + 4y - z = 2
    solveSystem3x3(1, 1, 1, 6,
                   2, -1, 3, 14,
                   -1, 4, -1, 2);
}

// Task 8: Wrapper for specific system
void task8() {
    // 3x - y + 2z = 5
    // 2x + 4y - z = 6
    // x - 3y + z = 4
    solveSystem3x3(3, -1, 2, 5,
                   2, 4, -1, 6,
                   1, -3, 1, 4);
}

// Main menu
int main() {
    int choice;
    cout << "Select a matrix/task (1-8):\n";
    cout << "1. Matrix mirror reflections\n";
    cout << "2. Magic square check\n";
    cout << "3. Saddle points\n";
    cout << "4. Spiral fill matrix\n";
    cout << "5. Spiral matrix traversal\n";
    cout << "6. Solve 2x2 system (Task 6)\n";
    cout << "7. Solve 3x3 system (Task 7)\n";
    cout << "8. Solve 3x3 system (Task 8)\n";
    cout << "Enter choice: ";
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