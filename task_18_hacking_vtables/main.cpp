#include <iostream>

struct Expression {
  Expression() {}
  virtual double evaluate() const = 0;
  virtual ~Expression() {}
};

struct Number : Expression {
  Number(double value) : value(value) {}

  double evaluate() const { return value; }

 private:
  double value;
};

struct BinaryOperation : Expression {
  BinaryOperation(Expression const* left, char op, Expression const* right)
      : left(left), op(op), right(right) {}

  double evaluate() const {
    switch (op) {
      case '+':
        return left->evaluate() + right->evaluate();
        break;
      case '-':
        return left->evaluate() - right->evaluate();
        break;
      case '*':
        return left->evaluate() * right->evaluate();
        break;
      case '/':
        return left->evaluate() / right->evaluate();
        break;
      default:
        return 0;
    }
  }
  ~BinaryOperation() {
    delete left;
    delete right;
  }

 private:
  Expression const* left;
  Expression const* right;
  char op;
};

// Checking if objects are of the same class (All the hacking is here!)
bool check_equals(Expression const* left, Expression const* right) {
  // Virtual function pointers take 4 bytes in memory for x86
  // and 8 bytes for x86_64
  const size_t ptrSize = 8;  // Adjust for your system!!
  long** leftVtable = (long**)&left;
  long** rightVtable = (long**)&right;
  int sizeLeftVtable = sizeof(leftVtable) / ptrSize;
  int sizeRightVtable = sizeof(rightVtable) / ptrSize;
  if (sizeLeftVtable != sizeRightVtable) {
    return false;
  }

  for (int i = 0; i != sizeLeftVtable; ++i)
    if (leftVtable[0][i] != rightVtable[0][i]) return false;
  return true;
}

int main() {
  Number* n = new Number(5);
  Number* m = new Number(6);
  BinaryOperation* b = new BinaryOperation(new Number(6), '+', new Number(3));

  std::cout << check_equals(n, b) << std::endl;
  std::cout << check_equals(n, m) << std::endl;

  delete n;
  delete b;

  return 0;
}