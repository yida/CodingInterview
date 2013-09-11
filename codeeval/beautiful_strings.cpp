#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void beautiful_strings(const string& str) {
  vector<int> char_array(128, 0); 
  for (size_t index = 0; index < str.length(); index ++) {
    char current_char = str[index];
    if (current_char <= 'z' && current_char >= 'a') 
      current_char -= 32;
    if (current_char >= 'A' && current_char <= 'Z')
      char_array[current_char] ++;
  }
  sort(char_array.begin(), char_array.end());
  int sum = 0;
  int gain = 26;
  for (int index = char_array.size() - 1; index >= 0; index --) {
    if (!char_array[index]) break;
    sum += char_array[index] * (gain --);
  }
  cout << sum << endl;
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
      beautiful_strings(line);
    }
  }
  return 0;
}
