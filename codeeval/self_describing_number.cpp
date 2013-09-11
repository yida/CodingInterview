#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

void test_self_describing(const string& line) {
  map<int, int> number_map;
  // use map to store appearance
  for (size_t index = 0; index < line.length(); index ++) {
    number_map[index] = line[index] - 48; 
  } 
  map<int, int>::iterator it_map = number_map.begin();
  for (size_t index = 0; index < line.length(); index ++) {
    if ((it_map = number_map.find(line[index] - 48)) == number_map.end()) {
      cout << 0 << endl;
      return;
    } else {
      number_map[line[index] - 48] --;
    }
  }  
  for (it_map = number_map.begin(); it_map != number_map.end(); it_map ++)
    if ((*it_map).second > 0) {
      cout << 0 << endl;
      return;
    }
  cout << 1 << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  string line;
  file.open(argv[1]);
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      test_self_describing(line);
    }
  } 
  
  return 0;
}
