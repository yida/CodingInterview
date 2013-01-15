#include <iostream>
#include <string>
#include <set>

using namespace std;

// O(N)
bool check_anagram(string str1, string str2) {
  int len1 = str1.length();
  int len2 = str2.length();
  if (len1 != len2)
    return false;

  int char_stat[128];
  for (int cnt = 0; cnt < 128; cnt++)
    char_stat[cnt] = 0;

  for (int cnt = 0; cnt < len1; cnt++)
    char_stat[str1[cnt]]++;

  for (int cnt = 0; cnt < len2; cnt++)
    char_stat[str2[cnt]]--;

  for (int cnt = 0; cnt < 128; cnt++)
    if (char_stat[cnt] != 0)
      return false;

  return true;
}

// O(logN)
bool check_anagram_faster(string str1, string str2) {
  int len1 = str1.length();
  int len2 = str2.length();
  if (len1 != len2) return false;

  multiset<char> anagram;
  multiset<char>::iterator it;

  // construct bst
  for (int cnt = 0; cnt < len1; cnt++) {
    anagram.insert(str1[cnt]);
  }

  // destroy bst
  for (int cnt = 0; cnt < len2; cnt++) {
    it = anagram.find(str2[cnt]);
    if (it != anagram.end())
      anagram.erase(it);
    else
      return false;
  }
  if (anagram.empty())
    return true;
  else
    return false;
}

int main() {
  string str1("abc");
  string str2("bca");
//  string str1("abcd");
//  string str2("bca");
//  string str1("orchestra");
//  string str2("carthorse");
  cout << check_anagram(str1, str2) << endl;
  cout << check_anagram_faster(str1, str2) << endl;
  return 0;
}
