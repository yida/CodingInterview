#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> array_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      int last_digits = line[line.size() - 1] - 48;
      if (last_digits % 2 == 0)
        cout << 1 << endl;
      else
        cout << 0 << endl;
    }
  }
  return 0;
}
