#include <iostream>
#include <stdint.h>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <cmath>

using namespace std;

void double_square(long number) {
  long sqrt_number = (long)sqrt(number);
  long count = 0;
  for (long left = 0; left < sqrt_number + 1; left ++) {
    double right = sqrt((long)number - left * left); 
    if (right == (long)right)
      if (left * left == right)
        count += 2;
      else
        count += 1; 
  } 
  cout << count / 2 << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;

  getline(file, line);
  istringstream ss(line); 
  int number = 0;
  ss >> number;

  for (int count = 0; count < number; count ++) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      istringstream ss_number(line); 
      long current_number = 0;
      ss_number >> current_number;

//      cout << "test " << current_number << endl;
      double_square(current_number);
    }
  }
  file.close();
  return 0;
}
