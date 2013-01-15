// aabcccccaaa -> a2b1c5a3

#include <iostream>
#include <sstream>
#include <string>
#include <deque>

using namespace std;

string compression(string str) {
  size_t len = str.length();
  deque<size_t> acc;
  deque<char> c;
  c.push_back(str[0]);
  acc.push_back(1);
  size_t idx = 0;
  for (size_t cnt = 1; cnt < len; cnt ++) {
    if (c[idx] == str[cnt]) {
      acc[idx]++;
    }
    else {
      idx++;
      c.push_back(str[cnt]);
      acc.push_back(1);
    }
  }
  string new_str("");
  while (!c.empty()) {
    new_str += c.front();
    stringstream ss;
    ss << acc.front();
    new_str += ss.str();
    c.pop_front();
    acc.pop_front();
  }
  return new_str;
}

int main() {
  string str("aabcccccaa");
  cout << str << endl;
  cout << compression(str) << endl;
  return 0;
}
