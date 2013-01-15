#include <iostream>
#include <map>

using namespace std;

int main() {
  map<char, int> mymap;
  map<char, int>::key_compare mycomp;
  map<char, int>::iterator it;
  char highest;
  pair<char, int> high;

  mycomp = mymap.key_comp();

  mymap['a'] = 100;
  mymap['b'] = 200;
  mymap['c'] = 300;

  cout << "mymap contains:" << endl;

  highest = mymap.rbegin()->first;
  high = *mymap.rbegin();

  it = mymap.begin();
  do {
    cout << (*it).first << " => " << (*it).second << endl;
  } while ( mycomp((*it++).first, highest) );
  cout << endl;

  it = mymap.begin();
  do {
    cout << (*it).first << " => " << (*it).second << endl;
  } while ( mymap.value_comp()(*it++, high) );

  return 0;
}
