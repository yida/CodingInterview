#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

void armstring_numbers(const string& number_string) {
  istringstream ss(number_string);
  int number = 0;
  ss >> number; 
  int order = number_string.size();
  int sum = 0;
  for (size_t index = 0; index < number_string.size(); index ++) {
    sum += pow(number_string[index] - 48, order * 1.0);
  }
  if (sum == number)
    cout << "True" << endl;
  else
    cout << "False" << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> array_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      armstring_numbers(line);
    }
  }
  return 0;
}
