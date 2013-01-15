#include <iostream>

class base {
  public:
    base() {}
    ~base() {}
    virtual const char* GetName() = 0;
};

class Derive: public base {
  public:
    Derive() {}
    ~Derive() {}
    const char* GetName() {
      return "Derive";
    }
};

int main() {
  Derive dd;
  std::cout << dd.GetName() << std::endl;
  return 0;
}
