#include <iostream>
using namespace std;

void rotate_by_one(int &a, unsigned size)
{
    cout << &a << endl;
    cout << *(&a + 3) << endl;
    int last;
    for (int i = 0; i < size; i++)
    {
        int address = i - 1;
        address = address >= 0 ? address : address + size;
        if (i == 0)
            last = *(&a + size - 1);
        *(&a + address) = *(&a + i);
        if (i == size - 1)
            *(&a + size - 2) = last;
    }
    return;
}

void rotate(int &a, unsigned size, int shift)
{
    cout << &a << endl;
    int real_shift = shift % size;
    if (real_shift == 0)
        return;
    for (int i = 0; i < real_shift; i++)
        rotate_by_one(a, size);
    return;
}

int main()
{
    const int size = 5, shift = 3;
    int a[size] = {1, 2, 3, 4, 5};
    cout << &a << endl;
    rotate(*a, size, shift);
    for (int i = 0; i < size; i++)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
