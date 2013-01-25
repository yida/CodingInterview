#include <iostream>
#include <cmath>

using namespace std;

void prime(int n) {
  if (n > 2) { cout << 1 << ' ' << 2 << ' '; }
  else { cout << n << endl;}
  for (int i = 3; i <= n; i++) {
    bool isprime = true;
    for (int j = 2; j <= floor(sqrt(i)); j++) {
      if (i % j == 0) { isprime = false; break;}
    }
    if (isprime) cout << i << ' ';
  }
  cout << endl;
}

void prime2(int n) {
  int* num = new int[n];
  for (int i = 0; i < n; i++) num[i] = 0;
  int ptr = 1;
  while (++ptr <= n) {
    if (!num[ptr - 1]) {
      int multiplier = 2;
      while ( ptr * multiplier <= n ) {
        num[ptr * multiplier - 1] = 1;
        multiplier ++;
      }
    }
  }
  for (int i = 1; i <= n; i++)
    if (!num[i - 1]) cout << i << ' ';
  cout << endl;
  delete [] num;
}

int main(void) {
  prime2(100);
  return 0;
}
