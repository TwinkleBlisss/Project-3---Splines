#include <fstream>
#include <iostream>
#include <cmath>
#define size 20
using namespace std;

void file_reading(int n, double spln_x[], double spln_y[], ifstream &func){
    if (!func.is_open()) {
        cout << "File didn't open.\n\n";
        exit(-1);
    }
    while (!func.eof()) {
        for (int i = 0; i < n; i++) {
            func >> spln_x[i];
        }
        for (int i = 0; i < n; i++) {
            func >> spln_y[i];
        }

    }
    func.close();
}

double splain(double x, double spln_x[], double spln_y[], double gamma[])
{
    int i = 0;
    if (x <= spln_x[0]) {
        i = 0;
    }
    else {
        while (x > (spln_x[i])) {
            i++;
        }
        i--;
    }
    double h = spln_x[i + 1] - spln_x[i];
    double y;
    y = spln_y[i] * (spln_x[i + 1] - x) / h + spln_y[i + 1] * (x - spln_x[i]) / h + gamma[i] * (pow(spln_x[i + 1] - x, 3) - pow(h, 2) * (spln_x[i + 1] - x)) / (6 * h) + gamma[i + 1] * (pow(x - spln_x[i], 3) - pow(h, 2) * (x - spln_x[i])) / (6 * h);
    return y;
}

void print(double spl[], int n) {
    for (int i = 0; i < n; i++) {
        cout << spl[i] << " ";
    }
    cout << "\n\n";
}

void counting_arrays(int n, double h_i, double h_i1, double a[], double b[], double A[], double B[], double C[], double F[], double spln_x[], double spln_y[], double gamma[]){
    for (int i = 1; i < n - 1; i++)
    {
        h_i = spln_x[i] - spln_x[i - 1];
        h_i1 = spln_x[i + 1] - spln_x[i];
        A[i] = h_i / 6;
        B[i] = (h_i + h_i1) / 3;
        C[i] = h_i1 / 6;
        F[i] = ((spln_y[i + 1] - spln_y[i]) / h_i1 - (spln_y[i] - spln_y[i - 1]) / h_i);
        a[i] = (-C[i]) / (A[i] * a[i - 1] + B[i]);
        b[i] = (F[i] - A[i] * b[i - 1]) / (A[i] * a[i - 1] + B[i]);
    }
    gamma[n - 1] = (F[n - 2] - A[n - 2] * b[n - 2]) / (B[n - 2] + A[n - 2] * a[n - 2]);
    for (int i = n - 2; i > 0; i--)
    {
        gamma[i] = a[i] * gamma[i + 1] + b[i];
    }
}

void file_writing(int n, double spln_x[], double spln_y[], double gamma[], ofstream &spline, double step){
    if (!spline.is_open()) {
        cout << "File didn't open.\n\n";
        exit(-2);
    }
    for (double i = 0; i < spln_x[n-1]; i += step) {
        spline << i << endl;
    }
    for (double i = 0; i < spln_x[n-1]; i += step) {
        spline << splain(i, spln_x, spln_y, gamma) << endl;
    }
}

void intersection_point(int n, double spln1_x[], double spln2_x[], double spln1_y[], double spln2_y[], double gamma1[], double gamma2[], double result[]){
    double left = max(spln1_x[0], spln2_x[0]);
    double right = min(spln1_x[n - 1], spln2_x[n - 1]);
    double eps = 0.000001;
    double FIB = (1 + sqrt(5)) / 2;
    double x1, x2, y1, y2;
    while (abs(right - left) >= eps)
    {
        x1 = right - (right - left) / FIB;
        x2 = left + (right - left) / FIB;
        y1 = abs(splain(x1, spln1_x, spln1_y, gamma1) - splain(x1, spln2_x, spln2_y, gamma2));
        y2 = abs(splain(x2, spln1_x, spln1_y, gamma1) - splain(x2, spln2_x, spln2_y, gamma2));
        if (y1 >= y2)
            left = x1;
        else
            right = x2;
    }
    double per = (left + right) / 2;
    y1 = splain(per, spln1_x, spln1_y, gamma1);
    y2 = splain(per, spln2_x, spln2_y, gamma2);
    if (abs(y1 - y2) <= eps){
        result[0] = per;
        result[1] = y1;
        cout << "Intersection point: x = " << per << ", y = " << y1;
    }
    else
    {
        cout << "Intersection point not found";
    }
}

int main() {
    const int n = 10;

    // First function
    double* spln1_x = new double[size];
    double* spln1_y = new double[size];
    ifstream func1;
    func1.open(R"(C:\Users\honor\Desktop\func1.txt)");
    file_reading(n, spln1_x, spln1_y, func1);
    func1.close();

    // Second function
    double* spln2_x = new double[size];
    double* spln2_y = new double[size];
    ifstream func2;
    func2.open(R"(C:\Users\honor\Desktop\func2.txt)");
    file_reading(n, spln2_x, spln2_y, func2);
    func2.close();

    // для нахождения гаммы
    double a[n - 1] = { 0 };
    double b[n - 1] = { 0 };
    double A[n - 1] = { 0 };
    double B[n - 1] = { 0 };
    double C[n - 1] = { 0 };
    double F[n - 1] = { 0 };
    double h_i, h_i1;
    double gamma1[n] = { 0 };
    double gamma2[n] = { 0 };
    counting_arrays(n, h_i, h_i1, a, b, A, B, C, F, spln1_x, spln1_y, gamma1);
    a[n - 1] = { 0 }; b[n - 1] = { 0 };
    counting_arrays(n, h_i, h_i1, a, b, A, B, C, F, spln2_x, spln2_y, gamma2);

    // Записываем сплайны в файлы
    double step = 0.01;
    //First
    ofstream spline1;
    spline1.open(R"(C:\Users\honor\Desktop\spline1.txt)");
    file_writing(n, spln1_x, spln1_y, gamma1, spline1, step);
    spline1.close();
    //Second
    ofstream spline2;
    spline2.open(R"(C:\Users\honor\Desktop\spline2.txt)");
    file_writing(n, spln2_x, spln2_y, gamma2, spline2, step);
    spline2.close();

    cout << "\n";

    // находим точку пересечения с помощью метода золотого сечения
    double result[2] = {0};
    intersection_point(n, spln1_x, spln2_x, spln1_y, spln2_y, gamma1, gamma2, result);

    // записываем в файл точку пересечения
    ofstream intersection_point;
    intersection_point.open(R"(C:\Users\honor\Desktop\intersection_point.txt)");
    intersection_point << result[0] << "\n" << result[1];
    intersection_point.close();


    cout << "\n";

    delete[] spln1_x; delete[] spln1_y; delete[] spln2_x; delete[] spln2_y;
    return 0;
}
