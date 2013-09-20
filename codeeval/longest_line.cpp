#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

using namespace std;

struct compare_string {
  const bool operator() (const string& s1, const string& s2) {
    return s1.length() > s2.length();
  }
};

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  
  getline(file, line);
  istringstream ss(line); 
  int output_number = 0;
  ss >> output_number;
  vector<string> string_array;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      string_array.push_back(line);
    }
  }
  sort(string_array.begin(), string_array.end(), compare_string());
  for (size_t index = 0; index < output_number; index ++) {
    cout << string_array[index] << endl;
  } 
  return 0;
}
