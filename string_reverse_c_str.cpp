#include <iostream>
#include <cstring>

using namespace std;

void reverse(char str[]) {
  int len = strlen(str);
  char temp_c = ' ';
  for (int cnt = 0; cnt < len / 2; cnt ++) {
    temp_c = str[cnt];
    str[cnt] = str[len - cnt - 1];
    str[len - cnt - 1] = temp_c;
  }
}

int main() {
  char str[] = "This is a string";
  reverse(str);
  cout << str << endl;
  return 0;
}
