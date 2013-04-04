#include <string>
#include <iostream>
#include <map>

using namespace std;

int main() {
  map<char, string> keymap; 
  keymap.insert(pair<char, string>('a', "2"));
  keymap.insert(pair<char, string>('b', "22"));
  keymap.insert(pair<char, string>('c', "222"));
  keymap.insert(pair<char, string>('d', "3"));
  keymap.insert(pair<char, string>('e', "33"));
  keymap.insert(pair<char, string>('f', "333"));
  keymap.insert(pair<char, string>('g', "4"));
  keymap.insert(pair<char, string>('h', "44"));
  keymap.insert(pair<char, string>('i', "444"));
  keymap.insert(pair<char, string>('j', "5"));
  keymap.insert(pair<char, string>('k', "55"));
  keymap.insert(pair<char, string>('l', "555"));
  keymap.insert(pair<char, string>('m', "6"));
  keymap.insert(pair<char, string>('n', "66"));
  keymap.insert(pair<char, string>('o', "666"));
  keymap.insert(pair<char, string>('p', "7"));
  keymap.insert(pair<char, string>('q', "77"));
  keymap.insert(pair<char, string>('r', "777"));
  keymap.insert(pair<char, string>('s', "7777"));
  keymap.insert(pair<char, string>('t', "8"));
  keymap.insert(pair<char, string>('u', "88"));
  keymap.insert(pair<char, string>('v', "888"));
  keymap.insert(pair<char, string>('w', "9"));
  keymap.insert(pair<char, string>('x', "99"));
  keymap.insert(pair<char, string>('y', "999"));
  keymap.insert(pair<char, string>('z', "999"));
  keymap.insert(pair<char, string>(' ', "0"));

  int N;
  string str;
  cin >> N;
  getline(cin, str);
  for (int i = 0; i < N; i++) {
    cout << "Case #" << i+1 << ": ";
    getline(cin, str);
    cout << keymap[str[0]];
    string lastStr = keymap[str[0]];
    for (int i = 1; i < str.length(); i++) {
      if (lastStr[lastStr.length()-1] == keymap[str[i]][0]) 
        cout << ' ';
      cout << keymap[str[i]];
      lastStr = keymap[str[i]];
    }
    cout << endl;
  }
  return 1;
}
