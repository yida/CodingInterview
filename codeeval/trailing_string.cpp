#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

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

void trailing_string(const string& line, const string& word) {
  int line_index = line.length() - 1;
  int word_index = word.length() - 1;
  for (; line_index >= 0 && word_index >= 0; line_index --, word_index --) {
    if (line[line_index] != word[word_index]) break;
  }
  if (word_index < 0)
    cout << 1 << endl;
  else
    cout << 0 << endl;  
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      string delimiter(",");
      vector<string> string_set;
      split(line, delimiter, string_set);
      trailing_string(string_set[0], string_set[1]);
    }
  }
  return 0;
}
