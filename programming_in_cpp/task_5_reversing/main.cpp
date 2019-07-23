#include <iostream>
using namespace std;

void reversing()
{
    int number;
    cin >> number;
    if (number == 0)
        return;
    reversing();
    cout << number << " ";
    return;
}

int main()
{
    reversing();
    cout << endl;
    return 0;
}