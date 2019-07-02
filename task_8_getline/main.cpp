#include <iostream>

char *resize(const char *str, unsigned size, unsigned new_size)
{
    char *array = new char[new_size];
    char *moving_str = (char *)str;
    char *moving_new = array;
    for (int i = 0; (i < size) && (i < new_size); i++)
    {
        *moving_new = *moving_str;
        moving_new++;
        moving_str++;
    }
    delete[] str;
    return array;
}

char *read_input()
{
    int init_buffer = 10;
    int buffer = init_buffer;
    char c;
    char *array = new char[buffer];
    char *moving_array = array;
    while (std::cin.get(c) && c != '\n')
    {
        if ((moving_array - array) == buffer)
        {
            // Need more space
            int curr_size = moving_array - array;
            array = resize(array, buffer, buffer + init_buffer);
            buffer += init_buffer;
            moving_array = array + curr_size;
        }
        *moving_array = c;
        moving_array++;
    }
    *moving_array = '\0';
    return array;
}

int main()
{
    char *input = read_input();
    std::cout << input << std::endl;
    delete[] input;
    input = 0;
    return 0;
}