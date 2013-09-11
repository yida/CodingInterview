#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void happy_number(const string& number_string) {
  string snumber = number_string;
  int sum = 0;
  set<int> number_set;
  set<int>::iterator it_set = number_set.begin();
  while (sum != 1) {
    sum = 0;
    for (int index = 0; index < snumber.size(); index ++) {
      sum += (snumber[index] - 48) * (snumber[index] - 48);
    }
    if ((it_set = number_set.find(sum)) == number_set.end()) {
      number_set.insert(sum);
    } else {
      cout << 0 << endl;
      return;
    }
    ostringstream ss;
    ss << sum;
    snumber = ss.str(); 
  }
  cout << 1 << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> array_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      happy_number(line);
    }
  }
  return 0;
}
