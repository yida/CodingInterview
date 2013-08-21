#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

int main(int argc, char ** argv) {
  int N = 0;
  cin >> N; 

  vector<int64_t> num_array; 
  int64_t input;
  int64_t product = 1;

  for (int counter = 0; counter < N; counter ++) {
    cin >> input;
    num_array.push_back(input);
  }
  
  for (int counter = 0; counter < N; counter ++) {
    product = 1;
    for (int num = 0; num < N; num ++) {
      if (num != counter)
        product *= num_array[num];
    }
    cout << product << endl;
  }
 
  return 0;
}

