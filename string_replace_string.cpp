#include <iostream>
#include <string>
#include <regex>

using namespace std;

void replace_space(string &str) {
  size_t len = str.length();
  // remove space in the front
  while ((*str.begin()) == ' ')
    str.erase(str.begin());
  // remove space in the end
  while ((*(str.end()-1)) == ' ')
    str.erase(str.end()-1);
  string::iterator it = str.begin();
  while (it != str.end()) {
    if ((*it) == ' ') {
      string::iterator it_next = it + 1;
      while ((it_next != str.end()) && ((*it_next) == ' '))
        it_next++;
      str.replace(it, it_next, "%20");
    }
    it++;
  }
}

void replace_space_regex(string &str) {
  regex s("\\b(\\s)\\b([ ]*)");
  string str1 = regex_replace(str, s, "%20$2");
//  cout << str1 << 'D' << endl;
  regex s1("(\\s)\\b([ ]*)");
  string str2 = regex_replace(str1, s1, "$2");
//  cout << str2 << 'D' << endl;
  regex s2("\\b(\\s)([ ]*)");
  string str3 = regex_replace(str2, s2, "$3");
//  cout << str3 << 'D' << endl;
  str = str3;
}

int main() {
  string str1("Mr John Smith    ");
  string str2("Mr John Smith       ");
  replace_space(str1);
  replace_space_regex(str2);
  cout << str1 << endl;
  cout << str2 << endl;
  return 0;
}
