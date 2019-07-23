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

struct ScopedPtr {
  explicit ScopedPtr(Expression *ptr = 0) { ptr_ = ptr; }
  ~ScopedPtr() { delete ptr_; }
  Expression *get() const { return ptr_; }
  Expression *release() {
    Expression *tmp = ptr_;
    ptr_ = 0;
    return tmp;
  }
  void reset(Expression *ptr = 0) {
    delete ptr_;
    ptr_ = ptr;
  }
  // Overloading operators so we can use our class as a pointer
  Expression &operator*() const { return *ptr_; }
  Expression *operator->() const { return ptr_; }

private:
  // Forbid assignment of ScopedPtr to prevent memory leaks
  ScopedPtr(const ScopedPtr &);
  ScopedPtr &operator=(const ScopedPtr &);

  Expression *ptr_;
};

int main() {
  ScopedPtr scPtr(new BinaryOperation(new Number(4.5), '*', new Number(5)));

  std::cout << scPtr->evaluate() << std::endl;
  std::cout << scPtr.release()->evaluate() << std::endl;
  scPtr.reset(new BinaryOperation(new Number(3), '+', new Number(2)));
  std::cout << scPtr->evaluate() << std::endl;
  scPtr.reset(new BinaryOperation(new Number(4), '+', new Number(2)));
  std::cout << scPtr->evaluate() << std::endl;

  return 0;
}
