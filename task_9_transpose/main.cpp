#include <cstdlib>

int **create_array2d(size_t a, size_t b)
{
    int **m = new int *[a];
    m[0] = new int[a * b];
    for (size_t i = 1; i < a; i++)
        m[i] = m[i - 1] + b;
    return m;
}

void free_array2d(int **m, size_t a)
{
    delete[] m[0];
    delete[] m;
}

int **transpose(const int *const *m, unsigned rows, unsigned cols)
{
    int **temp = create_array2d(cols, rows);
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            temp[i][j] = m[j][i];
        }
    }
    return temp;
}

int main()
{
    const int a = 3;
    const int b = 4;
    int **m = create_array2d(a, b);
    m = transpose(m, a, b);
    free_array2d(m, a);
    return 0;
}