// Getting access to the Cls members, even though they are private

struct Cls {
  Cls(char c, double d, int i);
private:
  char c;
  double d;
  int i;
};

// Public version of a Cls class
struct ClsPubl
{
    ClsPubl(char c, double d, int i);
public: 
    char c;
    double d;
    int i;
};
 
char &get_c(Cls &cls) {
  // Trick is to cast to void *, then to required type
  void *void_ptr = (void *)(&cls);
  struct ClsPubl *fake_cls = (ClsPubl *)(void_ptr);
  return fake_cls->c;
}

double &get_d(Cls &cls) {
  void *void_ptr = (void *)(&cls);
  struct ClsPubl *fake_cls = (ClsPubl *)(void_ptr);
  return fake_cls->d;
}

int &get_i(Cls &cls) {
  void *void_ptr = (void *)(&cls);
  struct ClsPubl *fake_cls = (ClsPubl *)(void_ptr);
  return fake_cls->i;
}