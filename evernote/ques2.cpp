#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Word {
  public:
    string key;
    size_t number;
};

class compare_word {
  public:
    const bool operator() (const Word& w1, const Word& w2) {
      size_t w1_index = 0;
      size_t w2_index = 0; 
      if (w1.number > w2.number) {
        return true;
      } else if (w1.number == w2.number) {
        vector<char> w1_vec(w1.key.begin(), w1.key.end());
        vector<char> w2_vec(w2.key.begin(), w2.key.end());
        return lexicographical_compare(w1_vec.begin(), w1_vec.end(),
                                       w2_vec.begin(), w2_vec.end());
      } else {
        return false;
      }
    }
};

int main() {
  size_t N = 0;
  cin >> N;
  
  string input_str;
  unordered_map<string, size_t> dictionary;
  unordered_map<string, size_t>::iterator dic_it;
  for (int counter = 0; counter < N; counter ++) {
    cin >> input_str;
    if ((dic_it = dictionary.find(input_str)) == dictionary.end()) {
      dictionary[input_str] = 1;
    } else {
      dictionary[input_str] ++;
    }
  }

  size_t K = 0;
  cin >> K;

  vector<Word> words_list;
  Word word_sample;
  for (dic_it = dictionary.begin(); dic_it != dictionary.end(); dic_it ++) {
    word_sample.key = dic_it->first;
    word_sample.number = dic_it->second;
    words_list.push_back(word_sample);
  }
  
  sort(words_list.begin(), words_list.end(), compare_word());
  for (size_t index = 0; index < K; index ++) {
    cout << words_list[index].key << endl;
  }
 
  return 0;
}
