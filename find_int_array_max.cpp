#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

int array_max(int sample[], int size) {
    int max_num = INT_MIN;
      for (int cnt = 0; cnt < size; cnt ++) {
            if (sample[cnt] > max_num)
                    max_num = sample[cnt];
              }
        return max_num;
}

int main() {
  int array_size = 100;
  int array[array_size];
  for (int cnt = 0; cnt < array_size; cnt ++) {
    array[cnt] = (rand()%100) + 1;
  }

  cout << array_max(array, array_size) << endl;
  return 0;
}
