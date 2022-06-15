#include <iostream>

int main() {
    const int n = 10;
    double spln1_x[10] = { 0.0, 0.33, 0.66,0.99, 1.32, 1.65, 1.98, 2.31, 2.64, 2.97 };
    double spln1_y[10] = { 0.0, 0.32, 0.61, 0.84, 0.97, 1.0, 0.92, 0.74, 0.48, 0.17 };
    // для нахождения гаммы
    double a[n] = { 0 };
    double b[n] = { 0 };
    double A[n] = { 0 };
    double B[n] = { 0 };
    double C[n] = { 0 };
    double F[n] = { 0 };
    double h[n] = { 0 };
    double gamma[n] = { 0 };
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            h[i] = 0;
            a[i] = 0;
            b[n] = 0;
            continue;
        }
        h[i] = spln1_x[i] - spln1_x[i - 1];
    }
    for (int i = 1; i < n; i++)
    {
        A[i] = h[i] / 6;
        B[i] = (h[i] + h[i + 1]) / 3;
        C[i] = h[i + 1] / 6;
        F[i] = (spln1_y[i + 1] - spln1_y[i]) / h[i + 1] - (spln1_y[i] - spln1_y[i - 1]) / h[i];
        a[i] = (-C[i - 1]) / (A[i - 1] * a[i - 1] + B[i - 1]);
        b[i] = (F[i - 1] - A[i] * b[i - 1]) / (A[i - 1] * a[i - 1] + B[i - 1]);
    }
    gamma[n - 1] = (F[n - 1] - A[n - 1] * b[n - 1]) / (B[n - 1] + A[n - 1] * a[n - 1]);
    for (int i = n - 2; i >= 1; i--)
    {
        gamma[i] = a[i + 1] * gamma[i + 1] + b[i + 1];
    }

    return 0;
}
