#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <memory>

using namespace std;

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      set<char> repeated;
      map<char, int> first_appear; 
      for (size_t index = 0; index < line.size(); index ++) {
        if (repeated.find(line[index]) != repeated.end()) continue;
        if (first_appear.find(line[index]) == first_appear.end()) {
          first_appear[line[index]] = index;
        } else {
          repeated.insert(line[index]);
          first_appear.erase(line[index]);
        }
      } 
      char first_char;
      int min_index = line.size();
      for (map<char, int>::iterator it = first_appear.begin();
          it != first_appear.end(); it ++) {
        if (it->second < min_index) {
          min_index = it->second;
          first_char = it->first;
        } 
      }
      cout << first_char << endl;
    }
  }
  return 0;
}
