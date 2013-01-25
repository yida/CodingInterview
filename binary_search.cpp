#include <iostream>
#include <cmath>

using namespace std;

int search(int array[], int x, int p, int r) {
  if ((r-p) == 1) return (array[p] == x)? p : -1;
  int k = floor((r+p)/2);
  if (array[k] > x) 
    return search(array, x, p, k);
  else
    return search(array, x, k, r);
}

int main(void) {
  int array[10] = {0, 1, 24, 45, 67, 89, 193, 300, 500};
  cout << search(array, 0, 0, 10) << endl;
  return 0;
}
