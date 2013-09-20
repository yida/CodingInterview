#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      string delimiter(" ");
      vector<string> word_set;
      split(line, delimiter, word_set);
      string longest_word;
      size_t max_length = 0;
      for (size_t size = 0; size < word_set.size(); size ++) {
        if (word_set[size].length() > max_length) {
          max_length = word_set[size].length();
          longest_word = word_set[size];
        }
      }
      cout << longest_word << endl;
    }
  }
  return 0;
}
