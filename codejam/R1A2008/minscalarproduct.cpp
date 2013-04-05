// rearrangement inequality

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  int N = 0, I = 0;
  long long sum = 0, P = 0;
  vector<long long> set1, set2;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> I;
    set1.clear();
    set2.clear();
    for (int j = 0; j < I; j++) {
      cin >> P;
      set1.push_back(P);
    }
    for (int j = 0; j < I; j++) {
      cin >> P;
      set2.push_back(P);
    }
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());
    sum = 0; 
    for (int j = 0; j < I; j++) {
      sum += set1[j] * set2[I - j - 1];
    }
    cout << "Case #" << i + 1 << ": " << sum << endl;
  }
  return 1;
}
