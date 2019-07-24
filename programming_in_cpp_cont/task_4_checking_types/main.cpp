#include <typeinfo>

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
  BinaryOperation(Expression const *left, char op, Expression const *right)
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
  Expression const *left;
  Expression const *right;
  char op;
};

// Checking if objects are of the same class
bool check_equals(Expression const *left, Expression const *right) {
  if (typeid(*left) == typeid(*right))
    return true;
  return false;
}

int main() {
  Number *n = new Number(5);
  Number *m = new Number(6);
  BinaryOperation *b = new BinaryOperation(new Number(6), '+', new Number(3));

  std::cout << check_equals(n, b) << std::endl;
  std::cout << check_equals(n, m) << std::endl;

  delete n;
  delete b;

  return 0;
}
