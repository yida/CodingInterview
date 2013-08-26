#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

bool ispalidrome(string numstr) {
  long long startp = 0;
  long long endp = numstr.length() - 1;
  while (startp <= endp) {
    if (numstr[startp] != numstr[endp]) return false;
    startp ++;
    endp--;
  }
  return true;
}

long long fair_square(double si, double ei) {
  double sqei = sqrt(ei);
  double sqsi = sqrt(si);
  long long minrt = static_cast<int>(ceil(sqsi));
  long long maxrt = static_cast<int>(floor(sqei));
  // check all square numbers in the interval
  long long nfairsquare = 0;
  for (long long sqrnum = minrt; sqrnum <= maxrt; sqrnum++) {
    double sqnum = sqrnum * sqrnum;
    ostringstream convert, convertorigin;
    convert << sqnum;
    convertorigin << sqrnum;
    if (ispalidrome(convert.str()) && ispalidrome(convertorigin.str()))
      nfairsquare ++;
  }
  return nfairsquare;
}

int main(int argc, char** argv) {
  int T = 0;
  cin >> T;
  double si = 0, ei = 0; // start interval and end interval
  for (int i = 0; i < T; i++) {
    cin >> si >> ei;
    long long ret = fair_square(si, ei);
    cout << "Case #" << i + 1 << ": " << ret << endl;
  }
  return 0;
}
