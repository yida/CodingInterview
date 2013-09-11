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

void set_intersection(vector<int>& array_1, vector<int>& array_2) {
  set<int> number_set;
  vector<int> intersection;
  for (size_t index = 0; index < array_1.size(); index ++) {
    number_set.insert(array_1[index]);
  }
  set<int>::iterator it_set = number_set.begin();
  for (size_t index = 0; index < array_2.size(); index ++) {
    if ((it_set = number_set.find(array_2[index])) != number_set.end()) {
      intersection.push_back(array_2[index]); 
    }
  }
  if (intersection.size() > 0) {
    cout << intersection[0];
    for (size_t index = 1; index < intersection.size(); index ++)
      cout << ',' << intersection[index];
  }
  cout << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> array_string;
  vector<string> number_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      array_string.clear();
      string delimiter(";");
      split(line, delimiter, array_string);
      delimiter = ",";
      split(array_string[0], delimiter, number_string);
      vector<int> array_1;
      vector<int> array_2;
      int number = 0;
      for (size_t index = 0; index < number_string.size(); index ++) {
        stringstream num_str(number_string[index]); 
        num_str >> number; 
        array_1.push_back(number);
      }
      split(array_string[1], delimiter, number_string);
      for (size_t index = 0; index < number_string.size(); index ++) {
        stringstream num_str(number_string[index]); 
        num_str >> number; 
        array_2.push_back(number);
      }
      set_intersection(array_1, array_2);
    }
  }
  return 0;
}
