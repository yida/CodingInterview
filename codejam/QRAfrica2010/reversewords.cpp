#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int N = 0;
  string str;
  cin >> N;
  getline(cin, str);
  for (int i = 0; i < N; i++) {
    getline(cin, str);
    istringstream iss(str);
    vector<string> tokens;
    copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter<vector<string> >(tokens));
    cout << "Case #" << i+1 << ": ";
    for (vector<string>::reverse_iterator it = tokens.rbegin(); 
        it != tokens.rend(); it++) {
      cout << *it << ' ';
    }
    cout << endl;
  }
  return 1;
}
