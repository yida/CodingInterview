#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

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

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      string delimiter(" ");
      vector<string> number_array;
      split(line, delimiter, number_array);
      map<string, size_t> pos_map;
      map<string, size_t>::iterator it = pos_map.begin();
      for (size_t index = 0; index < number_array.size(); index ++) {
//        cout << number_array[index] << endl;
        if ((it = pos_map.find(number_array[index])) == pos_map.end()) {
          pos_map[number_array[index]] = index;
        } else {
          for (size_t out_index = (*it).second; 
              out_index < index; out_index ++) {
            cout << number_array[out_index] << ' ';
          }
          cout << endl;
          break;
        }
      }
    }
  }
  return 0;
}
