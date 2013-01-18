#include <set>
#include <iostream>

using namespace std;

int main() {
  multiset<char> ascii;
  ascii.insert('a');
  ascii.insert('v');
  ascii.insert('a');
  cout << ascii.count('a') << endl;
  return 0;
}
