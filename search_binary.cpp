// Standard binary search on a sorted array
#include <iostream>
#include <cmath>

int search(int array[], int x, int p, int r, int k) {
//  std::cout << p << ' ' << r << ' ' << k << std::endl;
  if (p > r) return -1;
  if ((r-p) == 1 && array[k+1] == x)
    return k + 1;
  if (x <= array[k])
    return search(array, x, p, k, floor((p+k)/2));
  else
    return search(array, x, k, r, floor((k+r)/2));
}

int main() {
  int array[20] = {1,2,3,4,6,7,8,9,12,15,16,19,23,45,67,68,78,79,84,85};
  std::cout << search(array, 85, 0, 20, 10) << std::endl;
  return 0;
}

