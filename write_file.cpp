#include <iostream>
#include <fstream>

using namespace std;

int main() {
  ofstream outFile;
  outFile.open("result.txt");
  if (!outFile) {
    cerr << "Unable to open file" << endl;
    exit(1);
  }
  try {
    outFile << 456543433452 << endl;
  } catch (...) {
    cout << "Error Write File" << endl;
  }
  outFile.close();
  return 0;
}
