#include <iostream>
#include <map>

using namespace std;

int main() {
  map<char, int> foo;
  map<char, int> bar;
  map<char, int>::iterator it;

  foo['x'] = 100;
  foo['y'] = 200;

  bar['a'] = 11;
  bar['b'] = 20;
  bar['c'] = 33;

  foo.swap(bar);

  cout << "foo contains:" << endl;
  for (it = foo.begin(); it != foo.end(); it++) 
    cout << (*it).first << " => " << (*it).second << endl;

  cout << "bar contains:" << endl;
  for (it = bar.begin(); it != bar.end(); it++)
    cout << (*it).first << " => " << (*it).second << endl;

  return 0;
}
