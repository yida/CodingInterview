#include <iostream>
using namespace std;

int print_odd() {
  for (int cnt = 1; cnt < 100; cnt += 2) {
    cout << cnt << " ";
  }
  cout << endl;
}

int main() {
  print_odd();
  return 0;
}
