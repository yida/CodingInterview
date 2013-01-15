#include <iostream>
#include <map>
//#include <utility>

using namespace std;

int main() {
  map<char, int> mymap;
  map<char, int>::iterator it;
  pair<map<char, int>::iterator, bool> ret;

  mymap.insert( pair<char, int>('a', 100) );
  mymap.insert( pair<char, int>('z', 200) );
  ret = mymap.insert( pair<char, int>('z', 500) );

  if (ret.second == false) {
    cout << "element 'z' already existed";
    cout << " with a value of " << ret.first->second << endl;
  }
  
  it = mymap.begin();
  mymap.insert(it, pair<char, int>('b', 300));
  mymap.insert(it, pair<char, int>('c', 400));

  map<char, int> anothermap;
  anothermap.insert(mymap.begin(), mymap.find('c'));

  cout << "mymap contains:\n";
  for (it = mymap.begin(); it != mymap.end(); it++)
  {
    cout << (*it).first << " => " << (*it).second << endl;
    cout << (*it).first << " => " << mymap[(*it).first] << endl;
  }

  cout << "anothermap contains:\n";
  for (it = anothermap.begin(); it != anothermap.end(); it++)
  {
    cout << (*it).first << " => " << (*it).second << endl;
    cout << (*it).first << " => " << anothermap[(*it).first] << endl;
  }

  cout << "The size of mymap is " << mymap.size() << endl;

  while (!mymap.empty()) {
    cout << mymap[mymap.begin()->first] << endl;
    mymap.erase(mymap.begin());
  }

  cout << mymap['v'] << endl;

  return 0;
}
