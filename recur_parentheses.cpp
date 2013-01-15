#include <iostream>
#include <string>
#include <queue>

using namespace std;

void addParen(queue<string> &list, int leftram, int rightram, 
                  char str[], int count) {
  if (leftram < 0 || rightram < leftram) return;
  if (leftram == 0 && rightram == 0) {
    string s(str);
    list.push(s);
  } else {
    if (leftram > 0) {
      str[count] = '(';
      addParen(list, leftram-1, rightram, str, count + 1);
    }

    if (rightram > leftram) {
      str[count] = ')';
      addParen(list, leftram, rightram - 1, str, count + 1);
    }
  }
}

int main() {
  int count = 3;
  char* str = new char[2 * 3];
  queue<string> list;
  addParen(list, count, count, str, 0);
  while (!list.empty()) {
    string par = list.front();
    cout << par << endl;
    list.pop();
  }
  return 1;
}
