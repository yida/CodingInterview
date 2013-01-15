#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

bool all_unique(const char* str) {
  int len = strlen(str);
  bool char_appear[128];
  for (int cnt = 0; cnt < 128; cnt++)
    char_appear[cnt] = false;
  for (int cnt = 0; cnt < len; cnt++)
    if (!char_appear[str[cnt]]) 
      char_appear[str[cnt]] = true;
    else
      return false;
  return true;
}

bool all_unique_no_cache(const char* str) {
  int len = strlen(str);
  for (int cnt = 0; cnt < len - 2; cnt++) {
    for (int next = cnt + 1; next < len - 1; next++) {
      if (str[cnt] == str[next])
        return false;
    }
  }
  return true;
}

int main() {
  string str("this is a sample string!\n");
  cout << all_unique(str.c_str()) << endl;
  cout << all_unique_no_cache(str.c_str()) << endl;
  return 0;
}
