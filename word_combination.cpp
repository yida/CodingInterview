#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int main() {
  vector<string> wordslist;
  ifstream file("/usr/share/dict/words");
  string word;
  unordered_set<string> less6words; 
  long count = 0;
  if (file.is_open()) {
    cout << "Generating Word List" << endl;
    while (file.good()) {
      getline(file, word);
      if (word.length() == 6)
        wordslist.push_back(word);
      else if (word.length() < 6)
        less6words.insert(word);
    }
    file.close();
  } else 
    cout << "Unable to open file" << endl;
  cout << wordslist.size() << endl;
  
  long combination = 0;
  unordered_set<string>::const_iterator got;
  for (int i = 0; i < wordslist.size(); i++) {
    for (int j = 1; j < 6; j++) {
      // abcdef
      string str1 = wordslist[i].substr(0, j);
      string str2 = wordslist[i].substr(j, 6-j);
      got = less6words.find(str1);
      if (got == less6words.end())
        continue;
      got = less6words.find(str2);
      if (got == less6words.end())
        continue;
      combination++;
      cout << str1 << " + " << str2 << " = " << wordslist[i] << endl;
    }
  }
  cout << combination << endl;

  return 0;
}

