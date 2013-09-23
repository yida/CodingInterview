#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <set>

using namespace std;

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  if (line.size())
    tokens.push_back(line);
}

void remove_char(string line, string char_line) {
  set<char> char_set;
  for (size_t index = 0; index < char_line.size(); index ++) {
    char_set.insert(char_line[index]);
  }
  string new_line("");
  for (size_t index = 0; index < line.size(); index ++) {
    if (char_set.find(line[index]) == char_set.end()) 
      new_line.append(line.substr(index, 1));
  }
  cout << new_line << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      vector<string> array;
      string delimiter(", ");
      split(line, delimiter, array);
      remove_char(array[0], array[1]);
    }
  }
  return 0;
}
