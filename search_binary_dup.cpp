// array[] = {1, 2, 3, 4, 4, 4, 5, 6, 6, 11, 11, 12, 12, 12, 15, 16, 17, 18, 19, 20};
// find index of first x

#include <iostream>
#include <cmath>

int search_x(int array[], int x, int p, int r, int k) {
  if (p > r) return -1;
  if ((r-p) == 1) return k + 1;
  if (x <= array[k]) // 11 11 12 12 12 
    return search_x(array, x, p, k, floor((p+k)/2));
  else if (x > array[k])
    return search_x(array, x, k, r, floor((r+k)/2));
}

int main() {
  int array[] = {1, 2, 3, 4, 4, 4, 5, 6, 6, 11, 11, 12, 12, 12, 15, 16, 17, 18, 19, 20};
  std::cout << search_x(array, 12, 0, 20, floor(20/2)) << std::endl;
  return 0;
}

