#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  tokens.push_back(line);
}

int translate(const string& token) {
  if (token.find("zero") != string::npos)
    return 0;
  else if (token.find("one") != string::npos)
    return 1;
  else if (token.find("two") != string::npos)
    return 2;
  else if (token.find("three") != string::npos)
    return 3;
  else if (token.find("four") != string::npos)
    return 4;
  else if (token.find("five") != string::npos)
    return 5;
  else if (token.find("six") != string::npos)
    return 6;
  else if (token.find("seven") != string::npos)
    return 7;
  else if (token.find("eight") != string::npos)
    return 8;
  else if (token.find("nine") != string::npos)
    return 9;
  else 
    return 0;
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
      string delimitor(";");
      split(line, delimitor, number_string);
      for (int index = 0; index < number_string.size(); index ++) {
        cout << translate(number_string[index]);
      }
      cout << endl;
    }
  }
  return 0;
}
