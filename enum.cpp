#include <iostream>

using namespace std;

int main() {
  enum state {unvisited, visited, visiting };
  state s = visiting;
  cout << s << endl;
  return 0;
}

