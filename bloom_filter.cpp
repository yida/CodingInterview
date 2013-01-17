#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Hashtable {
  long size;
  long* table;
public:
  Hashtable(long SIZE);
  ~Hashtable() { delete [] table; }
  long HashFunction(const string& str);
  void insert(const string& str);
  bool search(const string& str);
};

Hashtable::Hashtable(long SIZE): size(SIZE) {
  table = new long[size];
  for (int i = 0; i < size; i++) table[0];
}

long Hashtable::HashFunction(const string& str) {
  long hashkey = 0;
  for (int i = 0; i < str.length(); i++)
    hashkey += str[i];
  return hashkey % size;
}

void Hashtable::insert(const string& str) {
  long hashkey = HashFunction(str);
  if (!table[hashkey]) table[hashkey] = 1;
}

bool Hashtable::search(const string& str) {
  long hashkey = HashFunction(str);
  return (table[hashkey])? true : false;
}

int main(int argc, char** argv) {
  Hashtable hashtable(1000000);
  string filename("/usr/share/dict/words");

  ifstream file(filename.c_str());
  cout << "Generate Spell Checker" << endl;
  string words;
  if (file.is_open()) {
    while (file.good()) {
      getline(file, words);
      hashtable.insert(words);
    }
    file.close();
  } else 
    cout << "Unable to open file" << endl;

  cout << hashtable.search("wqdfadfwerweoioiewo23jfkldsjflkerq") << endl;
  return 0;
}
