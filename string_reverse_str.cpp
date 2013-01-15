#include <iostream>
#include <cstring>

using namespace std;

std::string reverse(std::string str) {
    int len = str.length();
    std::string str_new = str;
    for (int cnt = 0; cnt < len; cnt ++) {
          str_new[len - cnt - 1] = str[cnt];
    }
    return str_new;
}

int main() {
  string name("My name is Yida Zhang");
  cout << name.length() << " " <<  reverse(name) << endl;
  return 0;
}
