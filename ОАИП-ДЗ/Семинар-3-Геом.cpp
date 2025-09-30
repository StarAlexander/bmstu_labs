#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


void task1() {
    double coords[3][2];
    cout << "Enter coordinates of 3 triangle vertices (x, y):\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> coords[i][0] >> coords[i][1];
    }

    double x1 = coords[0][0], y1 = coords[0][1];
    double x2 = coords[1][0], y2 = coords[1][1];
    double x3 = coords[2][0], y3 = coords[2][1];

    double area = 0.5 * abs(x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
    cout << fixed << setprecision(4);
    cout << "Triangle area: " << area << endl;
}


void task2() {
    int n;
    cout << "Enter number of polygon vertices (n >= 3): ";
    cin >> n;

    if (n < 3) {
        cout << "Polygon must have at least 3 vertices." << endl;
        return;
    }

    double coords[100][2];
    cout << "Enter coordinates of " << n << " vertices (x, y):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> coords[i][0] >> coords[i][1];
    }

    double perimeter = 0.0;
    for (int i = 0; i < n; ++i) {
        int next = (i + 1) % n;
        double dx = coords[next][0] - coords[i][0];
        double dy = coords[next][1] - coords[i][1];
        perimeter += sqrt(dx*dx + dy*dy);
    }

    cout << fixed << setprecision(4);
    cout << "Polygon perimeter: " << perimeter << endl;
}


void task3() {
    double coords[3][2];
    cout << "Enter coordinates of 3 triangle vertices (x, y):\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> coords[i][0] >> coords[i][1];
    }

    double cx = (coords[0][0] + coords[1][0] + coords[2][0]) / 3.0;
    double cy = (coords[0][1] + coords[1][1] + coords[2][1]) / 3.0;

    cout << fixed << setprecision(4);
    cout << "Center of mass: C(" << cx << ", " << cy << ")" << endl;
}


void task4() {
    double coords[4][2];
    cout << "Enter coordinates of 4 rectangle vertices (x, y):\n";
    for (int i = 0; i < 4; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> coords[i][0] >> coords[i][1];
    }

    double maxDist = 0.0;
    int diag1 = 0, diag2 = 1;

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            double dx = coords[j][0] - coords[i][0];
            double dy = coords[j][1] - coords[i][1];
            double dist = sqrt(dx*dx + dy*dy);
            if (dist > maxDist) {
                maxDist = dist;
                diag1 = i;
                diag2 = j;
            }
        }
    }

    cout << fixed << setprecision(4);
    cout << "Diagonal connects Vertex " << diag1+1 << " and Vertex " << diag2+1 << endl;
    cout << "Diagonal length: " << maxDist << endl;
}


void task5() {
    double p[3][2];
    cout << "Enter coordinates of 3 points (x, y):\n";
    for (int i = 0; i < 3; ++i) {
        cout << "Point " << i+1 << " (x, y): ";
        cin >> p[i][0] >> p[i][1];
    }

    double abx = p[1][0] - p[0][0];
    double aby = p[1][1] - p[0][1];
    double acx = p[2][0] - p[0][0];
    double acy = p[2][1] - p[0][1];

    double cross = abx * acy - aby * acx;

    cout << fixed << setprecision(6);
    cout << "Cross product: " << cross << endl;

    if (abs(cross) < 1e-9) {
        cout << "Points lie on the same straight line." << endl;
    } else {
        cout << "Points do not lie on the same straight line." << endl;
    }
}


void task6() {
    double A[2], B[2], C[2], D[2]; 

    cout << "Enter coordinates of segment AB:\n";
    cout << "A (x1, y1): "; cin >> A[0] >> A[1];
    cout << "B (x2, y2): "; cin >> B[0] >> B[1];

    cout << "Enter coordinates of segment CD:\n";
    cout << "C (x3, y3): "; cin >> C[0] >> C[1];
    cout << "D (x4, y4): "; cin >> D[0] >> D[1];

    
    auto orient = [](double ax, double ay, double bx, double by, double cx, double cy) -> double {
        return (by - ay) * (cx - bx) - (bx - ax) * (cy - by);
    };

    double o1 = orient(A[0], A[1], B[0], B[1], C[0], C[1]);
    double o2 = orient(A[0], A[1], B[0], B[1], D[0], D[1]);
    double o3 = orient(C[0], C[1], D[0], D[1], A[0], A[1]);
    double o4 = orient(C[0], C[1], D[0], D[1], B[0], B[1]);

    bool intersect = false;

    
    if (((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
        ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0))) {
        intersect = true;
    }

    
    if (o1 == 0 && (A[0] <= C[0] && C[0] <= B[0] || B[0] <= C[0] && C[0] <= A[0]) &&
        (A[1] <= C[1] && C[1] <= B[1] || B[1] <= C[1] && C[1] <= A[1])) {
        intersect = true;
    }
    if (o2 == 0 && (A[0] <= D[0] && D[0] <= B[0] || B[0] <= D[0] && D[0] <= A[0]) &&
        (A[1] <= D[1] && D[1] <= B[1] || B[1] <= D[1] && D[1] <= A[1])) {
        intersect = true;
    }
    if (o3 == 0 && (C[0] <= A[0] && A[0] <= D[0] || D[0] <= A[0] && A[0] <= C[0]) &&
        (C[1] <= A[1] && A[1] <= D[1] || D[1] <= A[1] && A[1] <= C[1])) {
        intersect = true;
    }
    if (o4 == 0 && (C[0] <= B[0] && B[0] <= D[0] || D[0] <= B[0] && B[0] <= C[0]) &&
        (C[1] <= B[1] && B[1] <= D[1] || D[1] <= B[1] && B[1] <= C[1])) {
        intersect = true;
    }

    if (intersect) {
        cout << "Segments AB and CD intersect." << endl;
    } else {
        cout << "Segments AB and CD do not intersect." << endl;
    }
}


void task7() {
    int n;
    cout << "Enter number of polygon vertices (n >= 3): ";
    cin >> n;

    if (n < 3) {
        cout << "Polygon must have at least 3 vertices." << endl;
        return;
    }

    int poly[100][2]; 
    cout << "Enter coordinates of " << n << " polygon vertices (x, y):\n";
    for (int i = 0; i < n; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> poly[i][0] >> poly[i][1];
    }

    int point[2];
    cout << "Enter point to check (x, y): ";
    cin >> point[0] >> point[1];

    int intersections = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;

        
        if ((poly[i][1] > point[1]) != (poly[j][1] > point[1])) {
            double x_intersect = (double)(poly[j][0] - poly[i][0]) * (point[1] - poly[i][1]) /
                                 (poly[j][1] - poly[i][1]) + poly[i][0];
            if (point[0] < x_intersect) {
                intersections++;
            }
        }
    }

    if (intersections % 2 == 1) {
        cout << "Point is inside the polygon." << endl;
    } else {
        cout << "Point is outside the polygon." << endl;
    }
}


void task8() {
    double p1[2], p2[2];
    cout << "Enter first point (x1, y1): ";
    cin >> p1[0] >> p1[1];
    cout << "Enter second point (x2, y2): ";
    cin >> p2[0] >> p2[1];

    double dx = p2[0] - p1[0];
    double dy = p2[1] - p1[1];
    double length = sqrt(dx*dx + dy*dy);

    cout << fixed << setprecision(4);
    cout << "Segment length: " << length << endl;
}


void task9() {
    int n1, n2;
    cout << "Enter number of vertices for polygon 1 (n1 >= 3): ";
    cin >> n1;
    cout << "Enter number of vertices for polygon 2 (n2 >= 3): ";
    cin >> n2;

    if (n1 < 3 || n2 < 3) {
        cout << "Both polygons must have at least 3 vertices." << endl;
        return;
    }

    double poly1[100][2], poly2[100][2];

    cout << "Enter coordinates of polygon 1 vertices:\n";
    for (int i = 0; i < n1; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> poly1[i][0] >> poly1[i][1];
    }

    cout << "Enter coordinates of polygon 2 vertices:\n";
    for (int i = 0; i < n2; ++i) {
        cout << "Vertex " << i+1 << " (x, y): ";
        cin >> poly2[i][0] >> poly2[i][1];
    }

    
    auto orient = [](double ax, double ay, double bx, double by, double cx, double cy) -> double {
        return (by - ay) * (cx - bx) - (bx - ax) * (cy - by);
    };

    
    auto segmentsIntersect = [&](double p1x, double p1y, double q1x, double q1y,
                                 double p2x, double p2y, double q2x, double q2y) -> bool {
        double o1 = orient(p1x, p1y, q1x, q1y, p2x, p2y);
        double o2 = orient(p1x, p1y, q1x, q1y, q2x, q2y);
        double o3 = orient(p2x, p2y, q2x, q2y, p1x, p1y);
        double o4 = orient(p2x, p2y, q2x, q2y, q1x, q1y);

        if (((o1 > 0 && o2 < 0) || (o1 < 0 && o2 > 0)) &&
            ((o3 > 0 && o4 < 0) || (o3 < 0 && o4 > 0))) {
            return true;
        }

        
        return false;
    };

    bool intersect = false;
    for (int i = 0; i < n1; ++i) {
        int next1 = (i + 1) % n1;
        for (int j = 0; j < n2; ++j) {
            int next2 = (j + 1) % n2;
            if (segmentsIntersect(poly1[i][0], poly1[i][1], poly1[next1][0], poly1[next1][1],
                                  poly2[j][0], poly2[j][1], poly2[next2][0], poly2[next2][1])) {
                intersect = true;
                break;
            }
        }
        if (intersect) break;
    }

    if (intersect) {
        cout << "Polygons intersect." << endl;
    } else {
        cout << "Polygons do not intersect." << endl;
    }
}


int main() {
    int choice;
    cout << "Select a geometry task (1-9):\n";
    cout << "1. Triangle area by coordinates\n";
    cout << "2. Polygon perimeter\n";
    cout << "3. Triangle center of mass\n";
    cout << "4. Rectangle diagonal length\n";
    cout << "5. Check if 3 points are collinear\n";
    cout << "6. Check if two segments intersect\n";
    cout << "7. Point in convex polygon (ray casting)\n";
    cout << "8. Segment length between two points\n";
    cout << "9. Check if two polygons intersect\n";
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
        case 9: task9(); break;
        default:
            cout << "Invalid task number." << endl;
            return 1;
    }

    return 0;
}