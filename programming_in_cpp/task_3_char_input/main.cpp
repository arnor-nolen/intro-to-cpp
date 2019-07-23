#include <iostream>
using namespace std;

int main()
{
    bool hadSpace = false;

    char c = '\0';
    while (cin.get(c))
    {
        if (c == '\0')
            break;
        else if (c == ' ')
            if (hadSpace)
                continue;
            else
            {
                hadSpace = true;
                cout << c;
            }
        else
        {
            cout << c;
            hadSpace = false;
        }
    }

    return 0;
}