#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

void check_pangram(string& line) {
  int letters[26] = {0};
  char letter = 0;
  for (size_t index = 0; index < line.length(); index ++) {
    letter = line[index]; 
    if (letter >= 'A' && letter <= 'Z') {
      letter += 32;
    } else if (letter < 'a' || letter > 'z') continue;
    letters[letter - 'a'] ++; 
  }
  bool missing = false;
  for (size_t index = 0; index < 26; index ++) {
    if (!letters[index]) {
      cout << static_cast<char>(index + 97);
      missing = true;
    }
  }
  if (!missing) cout << "NULL" << endl;
  else
    cout << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      check_pangram(line);
    }
  }
  return 0;
}
