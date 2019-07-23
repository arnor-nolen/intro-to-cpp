#include <iostream>
#include <cmath>
using namespace std;

double discriminant(double a, double b, double c)
{
    int d = b * b - 4 * a * c;
    return d;
}

int main()
{
    double a, b, c;
    cin >> a >> b >> c;

    int d = discriminant(a, b, c);
    double root1 = (-b + sqrt(d)) / (2 * a);
    double root2 = (-b - sqrt(d)) / (2 * a);

    if (d < 0)
        cout << "No real roots" << endl;
    else
        cout << root1 << " " <<  root2 << endl;

    return 0;
}
