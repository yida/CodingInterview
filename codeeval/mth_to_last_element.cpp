#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

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

void parse_char(string& line, vector<char>& array) {
  vector<string> num_array;
  string delimiter(" ");
  split(line, delimiter, num_array);
  for (size_t index = 0; index < num_array.size(); index ++) {
    char character = 0;
    istringstream ss(num_array[index]);
    ss >> character;
    array.push_back(character);
  }
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
      string delimiter(" ");
      split(line, delimiter, array);
      istringstream ss(array[array.size() - 1]);
      int mth = 0;
      ss >> mth; 
      if (mth <= (array.size() - 1)) {
        cout << array[array.size() - 1 - mth];
        cout << endl;
      }
    }
  }
  return 0;
}
