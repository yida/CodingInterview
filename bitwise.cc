#include <iostream>

using namespace std;

int getMaxInt() {
  return ~(1 << 31);
}

int getMinInt() {
  return 1 << 31;
}

bool isOddNumber(int n) {
  return (n & 1) == 1;
}

void swap(int *a, int *b) {
  (*a) ^= (*b) ^= (*a) ^= (*b);
}

bool isSameSign(int x, int y) {
  return (x ^ y) >= 0;
}

int main() {
  cout << getMaxInt() << endl;
  cout << getMinInt() << endl;
  cout << isOddNumber(4562) << endl;
  int a = 4536, b = 1234;
  cout << a << ' ' << b << endl;
  swap(a, b);
  cout << a << ' ' << b << endl;
  return 0;
}
