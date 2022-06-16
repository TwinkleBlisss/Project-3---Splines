#include <iostream>
#include <cmath>
using namespace std;

double splain(double x, double spln1_x[], double spln1_y[], double gamma[])
{
    int i = 0;
    if (x <= spln1_x[0])
    {
        i = 0;
    }
    else
    {
        while (x > (spln1_x[i]))
        {
            i++;
        }
        i--;
    }
    //cout << spln1_x[i];
    double h = spln1_x[i+1] - spln1_x[i];
    double y;
    //cout << spln1_y[i] << " " << spln1_x[i+1] << " " << spln1_y[i+1] << " " << spln1_x[i] << " " << h << gamma[i] << " " << gamma[i+1];
    y = spln1_y[i]*(spln1_x[i+1] - x)/h + spln1_y[i+1]*(x - spln1_x[i])/h + gamma[i]*(pow(spln1_x[i+1] - x, 3) - pow(h, 2)*(spln1_x[i+1] - x))/(6*h)+ gamma[i +1]*(pow(x - spln1_x[i], 3) - pow(h, 2)*(x - spln1_x[i]))/(6*h);
    return y;
}

int main() {
    const int n = 10;
    double spln1_x[10] = {0.0, 0.33, 0.66,0.99, 1.32, 1.65, 1.98, 2.31, 2.64, 2.97};
    double spln1_y[10] = {0.0, 0.32404, 0.61311,0.83602, 0.968715, 0.99687, 0.91743, 0.739005, 0.480823, 0.170752};
    double spln2_x[10] = {0.0, 0.33, 0.66,0.99, 1.32, 1.65, 1.98, 2.31, 2.64, 2.97};
    double spln2_y[10] = {1.0, 0.946042, 0.789992, 0.54869, 0.248175, -0.0791209, -0.397879, -0.6737, -0.876818, -0.985314};
    // для нахождения гаммы
    double a[n-1] = {0};
    double b[n-1] = {0};
    double A[n-1] = {0};
    double B[n-1] = {0};
    double C[n-1] = {0};
    double F[n-1] = {0};
    double h_i, h_i1;
    double gamma1[n] = {0};
    double gamma2[n] = {0};
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
    gamma1[n-1] = (F[n-2] - A[n -2]*b[n - 2])/(B[n-2] + A[n - 2]*a[n - 2]);
    //cout << gamma[n-1];
    for (int i = n - 2; i > 0; i--)
    {
        gamma1[i] = a[i]*gamma1[i + 1] + b[i];
    }
    a[n-1] = {0};
    b[n-1] = {0};

    for (int i = 1; i < n - 1; i++)
    {
        h_i = spln2_x[i] - spln2_x[i - 1];
        h_i1 = spln2_x[i + 1] - spln2_x[i];
        A[i] = h_i/6;
        B[i] = (h_i + h_i1)/3;
        C[i] = h_i1/6;
        F[i] = ((spln2_y[i+1] - spln2_y[i])/h_i1 - (spln2_y[i] - spln2_y[i - 1])/h_i);
        a[i] = (-C[i])/(A[i]*a[i-1] + B[i]);
        b[i] = (F[i] - A[i]*b[i - 1])/(A[i]*a[i-1] + B[i]);
        //cout << b[i] << " ";
    }
    gamma2[n-1] = (F[n-2] - A[n -2]*b[n - 2])/(B[n-2] + A[n - 2]*a[n - 2]);
    //cout << gamma[n-1];
    for (int i = n - 2; i > 0; i--)
    {
        gamma2[i] = a[i]*gamma2[i + 1] + b[i];
    }
    //cout << splain(1.59, spln2_x, spln2_y, gamma2);
    cout << "\n";
    // находим точку пересечения с помощью метода золотого сечения

   // cout << splain(0.00001, spln1_x, spln1_y, gamma1);
    double left = max(spln1_x[0], spln2_x[0]);
    double right = min(spln1_x[n-1], spln2_x[n-1]);
    double eps = 0.000001;
    double FIB = (1 + sqrt(5))/2;
   // cout << sqrt(5)<< " ";
   // cout << FIB << "\n";
    double x1, x2, y1, y2;
    while (abs(right - left) >= eps)
    {
        x1 = right - (right - left)/FIB;
        x2 = left + (right - left)/FIB;
        y1 = abs(splain(x1, spln1_x, spln1_y, gamma1) - splain(x1, spln2_x, spln2_y, gamma2));
        y2 = abs(splain(x2, spln1_x, spln1_y, gamma1) - splain(x2, spln2_x, spln2_y, gamma2));
        if (y1 >= y2)
            left = x1;
        else
            right = x2;
    }
    double per = (left + right)/2;
    cout << per;
    return 0;
}
