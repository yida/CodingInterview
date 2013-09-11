#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void split(string& line, string& delimiter, vector<string>& tokens) {
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  tokens.push_back(line);
}

void fizz_buzz(int A, int B, int number) {
  for (int index = 1; index <= number; index ++) {
    int mod_A = index % A;
    int mod_B = index % B;
    if (mod_A == 0 && mod_B == 0) 
      cout << "FB ";
    else if (mod_A == 0) 
      cout << "F ";
    else if (mod_B == 0)
      cout << "B ";
    else
      cout << index << ' ';
  }
  cout << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> number_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      number_string.clear();
      string delimiter(" ");
      split(line, delimiter, number_string);
      stringstream A_string(number_string[0]); 
      stringstream B_string(number_string[1]); 
      stringstream N_string(number_string[2]); 
      int A = 0, B = 0, N = 0;
      A_string >> A;
      B_string >> B;
      N_string >> N; 
      fizz_buzz(A, B, N); 
    }
  }
  return 0;
}
