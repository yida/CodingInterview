#include <fstream>
#include <iostream>

using namespace std;

int main() {
  ifstream inFile;
  inFile.open("test.txt");
  if (!inFile) {
    cerr << "Unable to open file" << endl;
    exit(1);
  }
  int sum = 0, x = 0;
  try {
    while (inFile >> x) {
     sum = sum + x;
    }
  } catch (...) {
    cout << "Error Reading the File" << endl;
  }
  inFile.close();
  cout << sum << endl;
  return 0;   
}
