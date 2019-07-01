#include <iostream>
using namespace std;

int logarithm(double number)
{
    int log = 0, temp = 1;
    while (temp <= number)
    {
        temp *= 2;
        log++;
    }
    log--;
    return log;
}

int main()
{
    int n = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        long number = 0;
        cin >> number;
        cout << logarithm(number) << endl;
    }
}