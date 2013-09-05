#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<char> prime;
  prime.resize(4294967295);
  for (size_t cnt = 0; cnt < prime.size(); cnt ++);
  cout << prime.max_size() << endl;
}
