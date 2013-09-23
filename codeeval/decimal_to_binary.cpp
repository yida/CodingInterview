#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void dec_to_bin(int number) {
  vector<int> bits;
  int mod = 0;
  while (number > 0) {
    mod = number % 2;
    number /= 2;
    bits.push_back(mod); 
  }
  while (!bits.empty()) {
    cout << bits.back();
    bits.pop_back();
  }
  cout << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      istringstream ss(line); 
      int number = 0;
      int size = sizeof(int) * 8;
      ss >> number;
      dec_to_bin(number);
    }
  }
  return 0;
}
