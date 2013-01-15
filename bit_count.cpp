#include <bitset>
#include <iostream>

int pop(unsigned x) {
// x = (x & 0x55555555) + (x >> 1) & 0x55555555
// x = (x & 0x33333333) + (x >> 2) & 0x33333333
// x = (x & 0x0F0F0F0F) + (x >> 4) & 0x0F0F0F0F
// x = (x & 0x00FF00FF) + (x >> 8) & 0x00FF00FF
// x = (x & 0x0000FFFF) + (x >> 16) & 0x0000FFFF
  x = x - ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  x = (x + (x >> 4)) & 0x0F0F0F0F;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x0000003F;
}

int main() {
  unsigned int b = 4535;
  unsigned int a = b;
  std::bitset<32> Bit(a);
  std::cout << Bit.to_string() << std::endl;
  int c = 0;
  for (int i = 0; i < 32; i ++) {
    c += a & 1;
    a = a >> 1;
  }
  std::cout << c << std::endl;
  std::cout << pop(b) << std::endl;
  return 0;
}
