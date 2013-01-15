#include <iostream>

using namespace std;

class Delegatee {
  public:
    void foo() { bar(); }
    void bar() { cout << "Delegatee::bar" << endl; }
  private:
};


class Delegator {
  public:
    void foo() { fDelegatee->foo(); }
    void bar() { cout << "Delegator::bar" << endl; }
  private:
    Delegatee* fDelegatee;
};

int main() {
  Delegator de;
  de.foo();
  de.bar();
  return 0;
}
