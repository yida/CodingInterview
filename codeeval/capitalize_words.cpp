#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

char capitalize(char letter) {
  if (letter <= 'z' && letter >= 'a')
    return letter - 32;
  else
    return letter;
}

void capitalize_words(const string& input) {
  string str = input;
  str[0] = capitalize(str[0]);
  size_t pos = 0;
  string delimiter = " "; 
  while ((pos = str.find(delimiter, pos)) != string::npos) {
    str[pos + 1] = capitalize(str[pos + 1]); 
    pos ++;
  }
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
      capitalize_words(line);
    }
  }
  return 0;
}
