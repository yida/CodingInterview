#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void rightmost_char(const string& line, const char letter) {
  int index = line.length() - 1;
  for (; index >= 0; index --) {
    if (line[index] == letter) break;
  }
  cout << index << endl;
}

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  tokens.push_back(line);
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
      array_string.clear();
      string delimiter(",");
      split(line, delimiter, array_string);
      rightmost_char(array_string[0], array_string[1][0]);
    }
  }
  return 0;
}
