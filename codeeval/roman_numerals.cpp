#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

string less_than_ten(int digit) {
  string part;
  if (digit == 4) 
    part = "IV";
  else if (digit == 9)
    part = "IX";
  else if (digit >= 5) {
    part.append("V");
    digit -= 5;
    for (int index = 0; index < digit; index ++)
      part.append("I");
  } else {
    for (int index = 0; index < digit; index ++)
      part.append("I");
  }
  return part;
}

string less_than_hundred(int digit) {
  string part;
  if (digit == 4) 
    part = "XL";
  else if (digit == 9)
    part = "XC";
  else if (digit >= 5) {
    part.append("L");
    digit -= 5;
    for (int index = 0; index < digit; index ++)
      part.append("X");
  } else {
    for (int index = 0; index < digit; index ++)
      part.append("X");
  }
  return part;
}

string less_than_thousand(int digit) {
  string part;
  if (digit == 4) 
    part = "CD";
  else if (digit == 9)
    part = "CM";
  else if (digit >= 5) {
    part.append("D");
    digit -= 5;
    for (int index = 0; index < digit; index ++)
      part.append("C");
  } else {
    for (int index = 0; index < digit; index ++)
      part.append("C");
  }
  return part;
}

string less_than_max(int digit) {
  string part;
  for (int index = 0; index < digit; index ++)
    part.append("M");
  return part;
}

void cardinal_to_roman(const string& cardinal) {
  string part;
  for (int order = 0; order < cardinal.size(); order ++) {
    switch (cardinal.size() - order) {
      case 1:
        part = less_than_ten(cardinal[order] - 48);
        break;
      case 2:
        part = less_than_hundred(cardinal[order] - 48);
        break;
      case 3:
        part = less_than_thousand(cardinal[order] - 48);
        break;
      case 4:
        part = less_than_max(cardinal[order] - 48);
        break;
      default:
        break;
    }
    cout << part;
  }
  cout << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> array_string;
  vector<string> number_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      cardinal_to_roman(line);
    }
  }
  return 0;
}
