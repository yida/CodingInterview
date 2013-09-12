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

void find_a_writer(string& str, string& number_string) {
  string delimiter(" ");
  vector<string> number_array_str;
  split(number_string, delimiter, number_array_str);
  int num_index = 0;
  for (size_t index = 0; index < number_array_str.size(); index ++) {
    istringstream ss(number_array_str[index]);
    ss >> num_index; 
    cout << str[num_index - 1];
  }
  cout << endl;
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
      string delimiter("| ");
      split(line, delimiter, array_string);
      find_a_writer(array_string[0], array_string[1]);
    }
  }
  return 0;
}
