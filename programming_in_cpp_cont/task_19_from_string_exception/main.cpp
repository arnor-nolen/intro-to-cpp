#include <exception>
#include <iostream>
#include <sstream>
#include <string>

struct bad_from_string : std::exception {
  bad_from_string(const std::string &s) {}

  const char *what() const noexcept {
    return "Incorrect string for conversion.";
  }
};

template <class T> T from_string(std::string const &s) {
  T data;
  std::istringstream stream(s);
  stream >> std::noskipws >> data;
  if (stream.fail() || stream.peek() != EOF)
    throw bad_from_string(s);
  return data;
}

int main() {
  try {
    std::string s1("123");
    int a1 = from_string<int>(s1);                 // a1 = 123
    double b1 = from_string<double>(s1);           // b1 = 123.0
    std::string c1 = from_string<std::string>(s1); // c1 = "123"

    std::string s2("12.3");
    // int a2 = from_string<int>(s2); // exception
    double b2 = from_string<double>(s2);           // b2 = 12.3
    std::string c2 = from_string<std::string>(s2); // c2 = "12.3"

    std::string s3("abc");
    // int a3 = from_string<int>(s3); // exception
    // double b3 = from_string<double>(s3);           // exception
    std::string c3 = from_string<std::string>(s3); // c3 = "abc"

    // Tests from forum
    from_string<char>(" "); // space
    // from_string<std::string>(" "); // exception
    // from_string<std::string>(""); // exception
    // from_string<std::string>("a "); // exception
    // from_string<std::string>(" a"); // exception
    // from_string<std::string>("a b"); // exception

    std::cout << "Everything converted successfully!" << std::endl;
  } catch (const std::exception &e) {
    std::cout << "An error has occured." << std::endl << e.what() << std::endl;
  }

  return 0;
}