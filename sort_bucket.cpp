#include <iostream>
#include <string>

using namespace std;

int main() {
  string str("When not studying nuclear physics, Bambi likes to play beach volleyball."); 
  int ascii[128] = {0};
  for (int i = 0; i < str.length(); i++) {
    char c = str[i];
    if (c <= 'Z' && c >= 'A') c += 32;
    ascii[c]++;
  }
  string out("");
  for (char c = 'a'; c <= 'z'; c++)
    out.append(ascii[c], c); 

  cout << out << endl;
  return 0;
}
