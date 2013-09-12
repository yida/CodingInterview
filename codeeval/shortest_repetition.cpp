#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void shortest_repetition(const string& line) {
//  cout << line << endl;
  for (int size_p = 1; size_p <= line.size() / 2; size_p ++) {
    bool repeat = true;
    if (line.size() % size_p != 0) {
      repeat = false;
      continue;
    }
    string base = line.substr(0, size_p);
//    cout << "base " << base << endl;
    // compare  
    for (int index_search = size_p; index_search < (line.size() - size_p + 1);
        index_search += size_p) {
//      cout << line.substr(index_search, size_p);
      if (line.compare(index_search, size_p, base) != 0) {
        repeat = false;
      }
    }
//    cout << endl;
    if (repeat) {
      cout << size_p << endl;
      return; 
    }
  } 
  cout << line.size() << endl;
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
//      cout << line << ' ' << line.size() << endl;
      shortest_repetition(line);
    }
  }
  return 0;
}
