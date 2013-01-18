#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "Please input file name" << endl;
    return 0;
  }
  ifstream file(argv[1]);
  if (file.is_open()) {
    string line;
    int count = 0;
    while (file.good()) {
      getline(file, line);
      char cc = 0;
      char c = 0;
      for (int i = 0; i < line.size()-1; i++)
        if (line[i] > 33) { c = line[i]; break; }
      if (c == '/' || c == '*') { cout << "- ";}
      else { count++; cout << count << ' '; }
      cout << line << endl;
    }
    file.close();
  } else 
    cout << "Unable to read file" << endl;
  return 0;
}
