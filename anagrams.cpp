#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <ctime>

using namespace std;

class Wordslist {
  vector<string> words;
  vector<string> sorted_words;
  public:
    Wordslist() {}
    ~Wordslist() {}
    void find_anagrams();
    void insert(string str) { words.push_back(str); }
    long size() { return words.size(); }
    void lexi_sort();
};

void Wordslist::lexi_sort() {
// 65 A 
// 97 a
  size_t ascii[128] = {0};
  for (int i = 0; i < words.size(); i++) {
    for (int j = 0; j < words[i].length(); j++)
      ascii[words[i][j]] ++;
    string str;
    for (char k = 'A'; k <= 'Z'; k++) {
      str.append(ascii[k], k);
      ascii[k] = 0;
    }
    for (char k = 'a'; k <= 'z'; k++) {
      str.append(ascii[k], k);
      ascii[k] = 0;
    }
    sorted_words.push_back(str);
  }

}

void Wordslist::find_anagrams() {
  unordered_set<string> hashtable;  
  long anagrams_count = 0;

  unordered_set<string>::const_iterator got;
  for (long i = 0; i < words.size(); i++) {
    got = hashtable.find(sorted_words[i]);
    if (got == hashtable.end())
      hashtable.insert(sorted_words[i]);
    else
      anagrams_count++;
  }

  cout << anagrams_count << endl;
}

int main() {
  Wordslist wordslist;
  ifstream file("/usr/share/dict/words");
  string word;
  long count = 0;
  if (file.is_open()) {
    cout << "Generating Word List" << endl;
    while (file.good()) {
      getline(file, word);
      wordslist.insert(word);
    }
    file.close();
  } else 
    cout << "Unable to open file" << endl;
  cout << wordslist.size() << endl;
//  cout << "Sort with length" << endl;
//  wordslist.sort();
  clock_t t1, t2;
  t1 = clock();
  cout << "Search Anagrams" << endl;
  wordslist.lexi_sort();
  cout << "Lexi Sort" << endl;
  wordslist.find_anagrams();
  t2 = clock();
  cout << ((float)t2 - (float)t1) / 1000000.0F << endl;
  return 0;
}
