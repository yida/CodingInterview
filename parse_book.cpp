#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void parse(string line) {
  int firstValid = 0;
  for (; firstValid < line.length(); firstValid++)
    if (line[firstValid] > 32) break;
  int p = firstValid;
  int k = p + 1;  
  while (k < line.length()) {  
  }

}

int main(int argc, char** argv) {
  if (argc < 2)
    cout << "Please give file name" << endl;

  ifstream file(argv[1]);
  if (file.is_open()) {
    string line;
    while (file.good()) {
      getline(file, line);
      if (line.length() < 1) continue;
      parse(line);
    }
    file.close();
  } else 
    cout << "Unable to open file" << endl;
  return 0;
}
