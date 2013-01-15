#include <iostream>
#include <map>

using namespace std;

int main() {
  map<char, int> mymap;
  char c;

  mymap['a'] = 101;
  mymap['c'] = 202;
  mymap['f'] = 304;

  for (c = 'a'; c < 'h'; c++) {
    cout << c;
    if (mymap.count(c) > 0)
      cout << " is an element of mymap." << endl;
    else
      cout << " is not am element of mymap." << endl;
  }

  return 0;
}
