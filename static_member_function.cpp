#include <iostream>

class sample {
  private:
    static int value;
  public:
    static int GetValue() { return value++; }
};

int sample::value = 1434;

int main() {
  for (int cnt = 0; cnt < 5; cnt++) {
    std::cout << sample::GetValue() << std::endl;
  }
  return 0;
}
