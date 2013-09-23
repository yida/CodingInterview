#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

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
      int sum = 0;
      int mask = 0x1;
      for (int count = 1; count < size; count ++) {
        sum += number & mask;
        number = number >> 1;
      }
      cout << sum << endl;
    }
  }
  return 0;
}
