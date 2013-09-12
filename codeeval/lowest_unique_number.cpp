#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  tokens.push_back(line);
}

void lowest_unique_number(string& number_string) {
  vector<string> number_array_string;
  string delimitor(" ");
  split(number_string, delimitor, number_array_string);
  unsigned char number[10] = {0};
  unsigned char char_number = 0;
  for (int index = 0; index < number_array_string.size(); index ++) {
    char char_number = number_array_string[index][0];
    number[char_number - 48] ++;
  }
  for (int index = 0; index < 10; index ++) {
    if (number[index] == 1) {
      for (int order = 0; order < number_array_string.size(); order ++) {
        if (number_array_string[order][0] == (index + 48)) {
          cout << order + 1 << endl; 
          return;
        }
      }
      break;
    }
  }
  cout << 0 << endl;
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
      lowest_unique_number(line);
    }
  }
  return 0;
}
