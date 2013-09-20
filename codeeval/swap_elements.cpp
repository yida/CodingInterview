#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
  string delimiter(" ");
  split(line, delimiter, num_array);
  for (size_t index = 0; index < num_array.size(); index ++) {
    int number = 0;
    istringstream ss(num_array[index]);
    ss >> number;
    array.push_back(number);
  }
}

void parse_swap(string& line, size_t& left_index, size_t& right_index) {
  vector<string> num_array;
  string delimiter("-");
  split(line, delimiter, num_array);
  istringstream left_ss(num_array[0]);
  left_ss >> left_index;
  istringstream right_ss(num_array[1]);
  right_ss >> right_index;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      string delimiter(":");
      vector<string> part_set;
      split(line, delimiter, part_set);
      vector<int> num_array;
      parse_array(part_set[0], num_array);
      delimiter = ",";
      vector<string> swap_set;
      split(part_set[1], delimiter, swap_set);
      size_t left_index = 0, right_index = 0;
      int temp = 0;
      for (size_t swap_index = 0; swap_index < swap_set.size(); swap_index ++) {
        parse_swap(swap_set[swap_index], left_index, right_index); 
        temp = num_array[left_index];
        num_array[left_index] = num_array[right_index]; 
        num_array[right_index] = temp;
      }
      for (size_t index = 0; index < num_array.size(); index ++) {
        cout << num_array[index] << ' ';
      }
      cout << endl;
    }
  }
  return 0;
}
