#include <iostream>
#include <map>

using namespace std;

int main() {
  map<char, int> mymap;
  map<char, int>::iterator it;

  mymap['a'] = 100;
  mymap['b'] = 200;
  mymap['c'] = 345;
  mymap['d'] = 321;

  it = mymap.find('e');
  if (it != mymap.end()) {
    cout << (*it).first << endl;
    cout << (*it).second << endl;
  }

  return 0;
}
