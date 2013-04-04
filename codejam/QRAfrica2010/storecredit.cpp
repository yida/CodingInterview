#include <iostream>
#include <map>

using namespace std;

int main() {
    map<int, int> numbers;
    int N = 0;
    int C = 0, I = 0, P = 0;
    cin >> N;
    for (int i = 0; i < N; i++) {
      numbers.clear();
      cin >> C;
      cin >> I;
      for (int j = 0; j < I; j++) {
        cin >> P;
        int complement = C - P;
        if (numbers.find(complement) == numbers.end()) {
          numbers.insert(make_pair<int, int>(P, j));
        } else {
          cout << "Case #" << i + 1 << ": ";
          cout << numbers[complement] + 1 << ' ' << j + 1 << endl;
        }
      }
    }
    return 1;
}
