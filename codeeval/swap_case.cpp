#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

char swap(char letter) {
  if (letter <= 'z' && letter >= 'a')
    return letter - 32;
  else if (letter <= 'Z' && letter >= 'A')
    return letter + 32;
  else
    return letter;
}

void swap_case(const string& input) {
  string str = input;
  for (size_t index = 0; index < str.size(); index ++)
    str[index] = swap(str[index]);
  cout << str << endl;
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
      swap_case(line);
    }
  }
  return 0;
}
