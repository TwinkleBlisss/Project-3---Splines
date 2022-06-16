#include <iostream>
#include <cmath>
using namespace std;

double splain(double x, double spln1_x[], double spln1_y[], double gamma[])
{
    int i = 0;

    while (x > (spln1_x[i]))
    {
        i++;
    }
    i--;
    //cout << spln1_x[i];
    double h = spln1_x[i+1] - spln1_x[i];
    double y;
    //cout << spln1_y[i] << " " << spln1_x[i+1] << " " << spln1_y[i+1] << " " << spln1_x[i] << " " << h << gamma[i] << " " << gamma[i+1];
    y = spln1_y[i]*(spln1_x[i+1] - x)/h + spln1_y[i+1]*(x - spln1_x[i])/h + gamma[i]*(pow(spln1_x[i+1] - x, 3) - pow(h, 2)*(spln1_x[i+1] - x))/(6*h)+ gamma[i +1]*(pow(x - spln1_x[i], 3) - pow(h, 2)*(x - spln1_x[i]))/(6*h);
    return y;
}

int main() {
    const int n = 10;
    double spln1_x[10] = {0.0, 0.33, 0.6,0.99, 1.32, 1.65, 1.98, 2.31, 2.64, 2.97};
    double spln1_y[10] = {0.0, 0.32, 0.61, 0.84, 0.97, 1.0, 0.92, 0.74, 0.48, 0.17};
    double spln2_x[10] = {0.0, 0.33, 0.66,0.99, 1.32, 1.65, 1.98, 2.31, 2.64, 2.97};
    double spln2_y[10] = {0.0, 0.32, 0.61, 0.84, 0.97, 1.0, 0.92, 0.74, 0.48, 0.17};
    // для нахождения гаммы
    double a[n-1] = {0};
    double b[n-1] = {0};
    double A[n-1] = {0};
    double B[n-1] = {0};
    double C[n-1] = {0};
    double F[n-1] = {0};
    double h_i, h_i1;
    double gamma[n] = {0};
    for (int i = 1; i < n - 1; i++)
    {
        h_i = spln1_x[i] - spln1_x[i - 1];
        h_i1 = spln1_x[i + 1] - spln1_x[i];
        A[i] = h_i/6;
        B[i] = (h_i + h_i1)/3;
        C[i] = h_i1/6;
        F[i] = ((spln1_y[i+1] - spln1_y[i])/h_i1 - (spln1_y[i] - spln1_y[i - 1])/h_i);
        a[i] = (-C[i])/(A[i]*a[i-1] + B[i]);
        b[i] = (F[i] - A[i]*b[i - 1])/(A[i]*a[i-1] + B[i]);
        //cout << b[i] << " ";
    }
    gamma[n-1] = (F[n-2] - A[n -2]*b[n - 2])/(B[n-2] + A[n - 2]*a[n - 2]);
    //cout << gamma[n-1];
    for (int i = n - 2; i > 0; i--)
    {
        gamma[i] = a[i]*gamma[i + 1] + b[i];
    }

    // находим точку пересечения

    cout << splain(1, spln1_x, spln1_y, gamma);
    double left = max(spln1_x[0], spln2_x[0]);
    double right = min(spln1_x[n-1], spln2_x[n-1]);
    double eps = 0.0001;
    return 0;
}
