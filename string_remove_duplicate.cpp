#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

void remove_duplicate_char(string &str) {
  string::iterator it = str.begin();
  queue<int> duplicate;
  for (int cnt = 0; cnt < str.length(); cnt++) {
    for (int next = cnt + 1; next < str.length(); next++) 
      if (str[next] == str[cnt])
        duplicate.push(next);

    int offset = 0;
    while (!duplicate.empty()) {
      int idx = duplicate.front();
      str.erase(it + idx - offset);
      offset++;
      duplicate.pop();
    }
  }
}

//void remove_duplicate_char(string &str) {
//  queue<string::iterator> duplicate;
//  for (string::iterator it = str.begin(); it != str.end() - 1; it++) {
//    for (string::iterator it_next = it + 1; it_next != str.end(); it_next++) {
//      cout << (*it) << ' ' << (*it_next) << ' ';
//      if ((*it) == (*it_next)) {
//        cout << "push" << ' ';
//        duplicate.push(it_next);
//      }
//    }
//    cout << endl;
//
//    int offset = 0;
//    while (!duplicate.empty()) {
//      str.erase(duplicate.front() - offset);
//      offset ++;
//      duplicate.pop();
//    }
//  }
//}

int main() {
  string str1("this is an sample string!\n");
  string str2("ttttttttttttt");
  string str3("abcdef");
  remove_duplicate_char(str1);
  remove_duplicate_char(str2);
  remove_duplicate_char(str3);
  cout << str1 << endl;
  cout << str2 << endl;
  cout << str3 << endl;
  return 0;

}
