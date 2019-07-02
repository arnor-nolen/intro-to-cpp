#include <iostream>
using namespace std;

int find(const char *text, const char *pattern)
{
    if (!*(pattern))
        return 0;
    int position = 0;
    while (*text)
    {
        const char *moving_pattern = pattern;
        const char *moving_text = text;
        while (*moving_text && (*moving_text == *moving_pattern))
        {
            if (!*(++moving_pattern))
            {
                return position;
            }
            moving_text++;
        }
        position++;
        text++;
    }
    return -1;
}

// Not my tests, guy posted on forum
void test()
{
    (0 == find("", "")) ? cout << "OK : 1"
                               << " (" << 0 << " : " << (0 == find("", "")) << " )" << endl
                        : cout << "Failed : 1"
                               << " (" << 0 << " : " << (0 == find("", "")) << " )" << endl;
    (0 == find("a", "")) ? cout << "OK : 2"
                                << " (" << 0 << " : " << (0 == find("a", "")) << " )" << endl
                         : cout << "Failed : 2"
                                << " (" << 0 << " : " << (0 == find("a", "")) << " )" << endl;
    (0 == find("a", "a")) ? cout << "OK : 3"
                                 << " (" << 0 << " : " << (0 == find("a", "a")) << " )" << endl
                          : cout << "Failed : 3"
                                 << " (" << 0 << " : " << (0 == find("a", "a")) << " )" << endl;
    (-1 == find("a", "b")) ? cout << "OK : 4"
                                  << " (" << -1 << " : " << (-1 == find("a", "b")) << " )" << endl
                           : cout << "Failed : 4"
                                  << " (" << -1 << " : " << (-1 == find("a", "b")) << " )" << endl;

    (0 == find("aa", "")) ? cout << "OK : 5"
                                 << " (" << 0 << " : " << (0 == find("aa", "")) << " )" << endl
                          : cout << "Failed : 5"
                                 << " (" << 0 << " : " << (0 == find("aa", "")) << " )" << endl;
    (0 == find("aa", "a")) ? cout << "OK : 6"
                                  << " (" << 0 << " : " << (0 == find("aa", "a")) << " )" << endl
                           : cout << "Failed : 6"
                                  << " (" << 0 << " : " << (0 == find("aa", "a")) << " )" << endl;
    (0 == find("ab", "a")) ? cout << "OK : 7"
                                  << " (" << 0 << " : " << (0 == find("ab", "a")) << " )" << endl
                           : cout << "Failed : 7"
                                  << " (" << 0 << " : " << (0 == find("ab", "a")) << " )" << endl;
    (1 == find("ba", "a")) ? cout << "OK : 8"
                                  << " (" << 1 << " : " << (1 == find("ba", "a")) << " )" << endl
                           : cout << "Failed : 8"
                                  << " (" << 1 << " : " << (1 == find("ba", "a")) << " )" << endl;
    (-1 == find("bb", "a")) ? cout << "OK : 9"
                                   << " (" << -1 << " : " << (-1 == find("bb", "a")) << " )" << endl
                            : cout << "Failed : 9"
                                   << " (" << -1 << " : " << (-1 == find("bb", "a")) << " )" << endl;

    (0 == find("aaa", "")) ? cout << "OK : 10"
                                  << " (" << 0 << " : " << (0 == find("aaa", "")) << " )" << endl
                           : cout << "Failed : 10"
                                  << " (" << 0 << " : " << (0 == find("aaa", "")) << " )" << endl;
    (0 == find("aaa", "a")) ? cout << "OK : 11"
                                   << " (" << 0 << " : " << (0 == find("aaa", "a")) << " )" << endl
                            : cout << "Failed : 11"
                                   << " (" << 0 << " : " << (0 == find("aaa", "a")) << " )" << endl;
    (1 == find("abc", "b")) ? cout << "OK : 12"
                                   << " (" << 1 << " : " << (1 == find("abc", "b")) << " )" << endl
                            : cout << "Failed : 12"
                                   << " (" << 1 << " : " << (1 == find("abc", "b")) << " )" << endl;
    (2 == find("abc", "c")) ? cout << "OK : 13"
                                   << " (" << 2 << " : " << (2 == find("abc", "c")) << " )" << endl
                            : cout << "Failed : 13"
                                   << " (" << 2 << " : " << (2 == find("abc", "c")) << " )" << endl;
    (-1 == find("abc", "d")) ? cout << "OK : 14"
                                    << " (" << -1 << " : " << (-1 == find("abc", "d")) << " )" << endl
                             : cout << "Failed : 14"
                                    << " (" << -1 << " : " << (-1 == find("abc", "d")) << " )" << endl;

    (-1 == find("a", "aa")) ? cout << "OK : 15"
                                   << " (" << -1 << " : " << (-1 == find("a", "aa")) << " )" << endl
                            : cout << "Failed : 15"
                                   << " (" << -1 << " : " << (-1 == find("a", "aa")) << " )" << endl;
    (-1 == find("a", "ba")) ? cout << "OK : 16"
                                   << " (" << -1 << " : " << (-1 == find("a", "ba")) << " )" << endl
                            : cout << "Failed : 16"
                                   << " (" << -1 << " : " << (-1 == find("a", "ba")) << " )" << endl;
    (-1 == find("a", "ab")) ? cout << "OK : 17"
                                   << " (" << -1 << " : " << (-1 == find("a", "ab")) << " )" << endl
                            : cout << "Failed : 17"
                                   << " (" << -1 << " : " << (-1 == find("a", "ab")) << " )" << endl;
    (-1 == find("a", "bb")) ? cout << "OK : 18"
                                   << " (" << -1 << " : " << (-1 == find("a", "bb")) << " )" << endl
                            : cout << "Failed : 18"
                                   << " (" << -1 << " : " << (-1 == find("a", "bb")) << " )" << endl;

    (-1 == find("a", "aaa")) ? cout << "OK : 19"
                                    << " (" << -1 << " : " << (-1 == find("a", "aaa")) << " )" << endl
                             : cout << "Failed : 19"
                                    << " (" << -1 << " : " << (-1 == find("a", "aaa")) << " )" << endl;
    (-1 == find("aa", "aaa")) ? cout << "OK : 20"
                                     << " (" << -1 << " : " << (-1 == find("aa", "aaa")) << " )" << endl
                              : cout << "Failed : 20"
                                     << " (" << -1 << " : " << (-1 == find("aa", "aaa")) << " )" << endl;
    (0 == find("aaa", "aaa")) ? cout << "OK : 21"
                                     << " (" << 0 << " : " << (0 == find("aaa", "aaa")) << " )" << endl
                              : cout << "Failed : 21"
                                     << " (" << 0 << " : " << (0 == find("aaa", "aaa")) << " )" << endl;
    (0 == find("aaab", "aaa")) ? cout << "OK : 22"
                                      << " (" << 0 << " : " << (0 == find("aaab", "aaa")) << " )" << endl
                               : cout << "Failed : 22"
                                      << " (" << 0 << " : " << (0 == find("aaab", "aaa")) << " )" << endl;
    (1 == find("baaa", "aaa")) ? cout << "OK : 23"
                                      << " (" << 1 << " : " << (1 == find("baaa", "aaa")) << " )" << endl
                               : cout << "Failed : 23"
                                      << " (" << 1 << " : " << (1 == find("baaa", "aaa")) << " )" << endl;
    (1 == find("baaaa", "aaa")) ? cout << "OK : 24"
                                       << " (" << 1 << " : " << (1 == find("baaaa", "aaa")) << " )" << endl
                                : cout << "Failed : 24"
                                       << " (" << 1 << " : " << (1 == find("baaaa", "aaa")) << " )" << endl;
    (1 == find("baaab", "aaa")) ? cout << "OK : 25"
                                       << " (" << 1 << " : " << (1 == find("baaab", "aaa")) << " )" << endl
                                : cout << "Failed : 25"
                                       << " (" << 1 << " : " << (1 == find("baaab", "aaa")) << " )" << endl;
    (-1 == find("abd", "abc")) ? cout << "OK : 26"
                                      << " (" << -1 << " : " << (-1 == find("abd", "abc")) << " )" << endl
                               : cout << "Failed : 26"
                                      << " (" << -1 << " : " << (-1 == find("abd", "abc")) << " )" << endl;

    (2 == find("ababc", "abc")) ? cout << "OK : 27"
                                       << " (" << 2 << " : " << (2 == find("ababc", "abc")) << " )" << endl
                                : cout << "Failed : 27"
                                       << " (" << 2 << " : " << (2 == find("ababc", "abc")) << " )" << endl;
    (3 == find("abdabc", "abc")) ? cout << "OK : 28"
                                        << " (" << 3 << " : " << (3 == find("abdabc", "abc")) << " )" << endl
                                 : cout << "Failed : 28"
                                        << " (" << 3 << " : " << (3 == find("abdabc", "abc")) << " )" << endl;
}

int main()
{
    test();
    return 0;
}