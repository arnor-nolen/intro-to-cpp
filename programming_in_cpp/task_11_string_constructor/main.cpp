#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
#include <iostream>
using namespace std;

struct String
{

    String(const char *str = "")
    {
        size_t size = strlen(str);
        this->size = size;
        this->str = new char[size + 1];
        strcpy(this->str, str);
    }

    size_t size;
    char *str;
};

int main()
{
    const char cs[] = "omegalul";
    String s = String(cs);
    cout << s.str << endl;
    cout << s.size << endl;
    return 0;
}