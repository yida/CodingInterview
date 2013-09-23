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

void parse_array(string& line, vector<int>& array) {
  vector<string> num_array;
  string delimiter(",");
  split(line, delimiter, num_array);
  for (size_t index = 0; index < num_array.size(); index ++) {
    int number = 0;
    istringstream ss(num_array[index]);
    ss >> number;
    array.push_back(number);
  }
}

void max_subarray(vector<int> array) {
  int max_so_far = array[0];
  int max_ending_here = array[0];
  for (size_t index = 1; index < array.size(); index ++) {
    if (max_ending_here < 0) 
      max_ending_here = array[index];
    else
      max_ending_here += array[index];
    if (max_ending_here >= max_so_far)
      max_so_far = max_ending_here;
  }
  cout << max_so_far << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      vector<int> num_array;
      parse_array(line, num_array);
      max_subarray(num_array);
    }
  }
  return 0;
}
