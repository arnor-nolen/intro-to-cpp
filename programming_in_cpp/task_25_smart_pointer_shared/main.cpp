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

struct SharedPtr {
  explicit SharedPtr(Expression *ptr = 0) : ptr_(ptr), count_(0) {
    if (ptr_)
      count_ = new size_t(1);
  }
  ~SharedPtr() {
    if (count_ && !--*count_) {
      delete ptr_;
      delete count_;
    }
  }
  Expression *get() const { return ptr_; }
  size_t getCount() const { return *count_; }
  void reset(Expression *ptr = 0) {
    if (count_ && !--*count_) {
      delete ptr_;
      delete count_;
    }
    ptr_ = ptr;
    if (ptr_)
      count_ = new size_t(1);
    else
      count_ = 0;
  }

  // Overloading operators so we can use our class as a pointer
  Expression &operator*() const { return *ptr_; }
  Expression *operator->() const { return ptr_; }

  // Overloading assignment operators
  SharedPtr(const SharedPtr &shPtr) : ptr_(shPtr.ptr_), count_(shPtr.count_) {
    if (count_)
      ++*count_;
  }
  SharedPtr &operator=(const SharedPtr &shPtr) {
    if (shPtr.get() == ptr_) {
      return *this;
    }
    if (count_ && !--*count_) {
      delete ptr_;
      delete count_;
    }
    ptr_ = shPtr.get();
    if (ptr_) {
      count_ = shPtr.count_;
      ++*count_;
    } else
      count_ = 0;
    return *this;
  }

private:
  size_t *count_;
  Expression *ptr_;
};

int main() {
  SharedPtr scPtr(new BinaryOperation(new Number(4.5), '*', new Number(5)));
  std::cout << scPtr->evaluate() << " " << scPtr.getCount() << std::endl;

  SharedPtr scPtr2(scPtr);
  std::cout << scPtr->evaluate() << " " << scPtr.getCount() << std::endl;
  std::cout << scPtr2->evaluate() << " " << scPtr2.getCount() << std::endl;
  scPtr.reset(new BinaryOperation(new Number(4), '+', new Number(2)));
  std::cout << scPtr->evaluate() << " " << scPtr.getCount() << std::endl;
  std::cout << scPtr2->evaluate() << " " << scPtr2.getCount() << std::endl;

  scPtr = scPtr2;
  std::cout << scPtr->evaluate() << " " << scPtr.getCount() << std::endl;
  std::cout << scPtr2->evaluate() << " " << scPtr2.getCount() << std::endl;

  return 0;
}
