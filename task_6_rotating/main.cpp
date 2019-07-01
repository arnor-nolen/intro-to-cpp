#include <iostream>
using namespace std;

void rotate(int a[], unsigned size, int shift)
{
    int real_shift = shift % size;
    if (real_shift == 0)
        return;

    int last;
    for (int i = 0; i < size; i++)
    {
        int address = i - real_shift;
        address = address >= 0 ? address : address + size;
        if (i == 0)
            last = a[size - real_shift];
        a[address] = a[i];
        if (i == size - 1)
            a[size - real_shift - 1] = last;
    }
    return;
}

int main()
{
    const int size = 4, shift = 2;
    int a[size] = {1, 2, 3, 4};
    rotate(a, size, shift);
    for (int i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}