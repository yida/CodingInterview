// Binary search n in array

#include <iostream>
#include <cmath>

int search_head(int array[], int p, int r, int k) {
  if ((r-p) == 2) return k;
  if (array[p] > array[k-1])
    return search_head(array, p, k, floor((p+k)/2));
  if (array[k] > array[r-1])
    return search_head(array, k, r, floor((k+r)/2));
}

int search_n(int array[], int x, int p, int r, int k) { // 0 ~ 100 , p = 0; r = 100; k = (0+100)/2 = 50
  if (p > r) return 0;
  if (array[k] == x) return k;
  if (array[k] > x)
    return search_n(array, x, p, k, floor((p+k)/2));
  else 
    return search_n(array, x, k, r, floor((k+r)/2));
}

void search(int array[], int x, int p, int r) {
  int head = search_head(array, p, r, floor((p+r)/2));
  int idx = 0;
  if (x < array[p])
    idx = search_n(array, x, head, r, floor((head+r)/2));
  else if (x > array[p])
    idx = search_n(array, x, p, head, floor((head+p)/2));
  else
    idx = head;
  std::cout << idx << std::endl;
}

int main() {
  int array[] = {6, 7, 9, 12, 23, 1, 2, 4, 5};
  search(array, 12, 0, 9);
}
