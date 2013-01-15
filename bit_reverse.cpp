#include <iostream>
#include <bitset>
#include <string>

using namespace std;

unsigned long reversebit(unsigned long num) {
  bitset<8> num_bit(num);
  string num_str = num_bit.to_string();
  cout << num_str << endl;
  string rev_str = num_str;
  for (int i = 0; i < rev_str.length(); i++)
    rev_str[i] = num_str[rev_str.length() - i - 1];
  cout << rev_str << endl;
  bitset<8> new_bit(rev_str);
  return new_bit.to_ulong();
}

int main() {
  unsigned long rev = reversebit(235ul);
  cout << rev << endl; 
  return 0;
}
