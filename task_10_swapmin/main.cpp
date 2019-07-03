#include <cstdlib>
#include <iostream>
using namespace std;

int **create_array2d(size_t a, size_t b)
{
    int **m = new int *[a];
    m[0] = new int[a * b];
    for (size_t i = 1; i < a; ++i)
        m[i] = m[i - 1] + b;
    return m;
}

void free_array2d(int **m, size_t a)
{
    delete[] m[0];
    delete[] m;
}

void swap_min(int *m[], size_t rows, size_t cols)
{
    // Never do that in a real project!
    // Causes segfault during array deletion (free_array2d)
    int *first_p = m[0];
    int *lowest_p = first_p;
    int lowest_row = 0;
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            if (*lowest_p > m[i][j])
            {
                lowest_p = &m[i][j];
                lowest_row = i;
            }
    m[0] = m[lowest_row];
    m[lowest_row] = first_p;
}

int main()
{
    const int rows = 3;
    const int cols = 3;
    int f = 10;
    int **m = create_array2d(rows, cols);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            m[i][j] = f;
            cout << m[i][j] << " ";
            --f;
        }
        cout << endl;
    }
    swap_min(m, 3, 3);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
            cout << m[i][j] << " ";
        cout << endl;
    }
    // Do not free the memory, causes segfault!
    // Check swap_min for more info

    return 0;
}