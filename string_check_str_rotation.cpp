#include <iostream>
#include <string>

using namespace std;

bool isSubstring(string str, string substr) {
  if (str.find(substr) == string::npos)
    return false;
  else
    return true;
}

bool check_rotation(string str1, string str2) {
  size_t len1 = str1.length();
  size_t len2 = str2.length();
  if (len1 != len2) return false;

  string str = str1 + str1;
  if (isSubstring(str, str2))
    return true;
  else
    return false;
}

int main() {
  string str1("waterbottle");
  string str2("efbottlewat");
  cout << check_rotation(str1, str2) << endl;

  return 0;
}
