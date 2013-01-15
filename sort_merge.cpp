#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

void merge_sort(int array[], int p, int r);
void merge(int array[], int p, int r, int k);

int main() {
  int size = 10;
  int array[size];
  for (int i = 0; i < size; i++) array[i] = rand()%100 + 1;
  for (int i = 0; i < size; i++) std::cout << array[i] << ' ';
  std::cout << std::endl;

  merge_sort(array, 0, size - 1);
  for (int i = 0; i < size; i++) std::cout << array[i] << ' ';
  std::cout << std::endl;
  return 0;
}

void merge_sort(int array[], int p, int r) {
  if (r > p) {
    int k = (r + p) / 2;
    merge_sort(array, p, k);
    merge_sort(array, k + 1, r);
    merge(array, p, r, k);
  }
}

void merge(int array[], int p, int r, int k) {
  std::vector<int> temp;
  std::vector<bool> flag;
  int frontB = p, frontE = k;
  int rareB = k + 1, rareE = r;
  while (frontB <= frontE && rareB <= rareE) {
    if (array[frontB] < array[rareB]) {
      temp.push_back(array[frontB]);
      frontB ++;
    } else {
      temp.push_back(array[rareB]);
      rareB ++;
    }
  }
  while (frontB <= frontE)
    temp.push_back(array[frontB++]);

  while (rareB <= rareE)
    temp.push_back(array[rareB++]);
  
  for (int i = p; i <= r; i++)
    array[i] = temp[i - p];
}
