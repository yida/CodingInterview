#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>
#include <ctime>

using namespace std;

class Node {
  public:
    string name;
    string prev;
    long value;
    bool visited;
    Node(string str):name(str), prev(str), value(10000000), visited(false) {};
};

void dijkstra(string bstr, string estr, 
    unordered_map<string, Node*>& wordmap, vector<string> lists[]) {
  queue<string> nexts;
  nexts.push(bstr);
  string curstr;
  char lastchar;
  bool found = false;
  while (nexts.size() > 0) {
    curstr = nexts.front();
    nexts.pop();
    lastchar = curstr[curstr.length()-1] - 97;
    if (wordmap[curstr]->visited) continue;
    else wordmap[curstr]->visited = true;

    for (long i = 0; i < lists[lastchar].size(); i++) {
      if ((wordmap[curstr]->value+1) < wordmap[lists[lastchar][i]]->value) {
        wordmap[lists[lastchar][i]]->value = wordmap[curstr]->value + 1;
        wordmap[lists[lastchar][i]]->prev = curstr;
      }

      if (lists[lastchar][i].compare(estr) == 0) { // found
        cout << "Found " << wordmap[lists[lastchar][i]]->value << endl;
        found = true;
        Node* ptr = wordmap[lists[lastchar][i]];
        vector<string> result; 
        while (ptr->value != 0) {
          result.push_back(ptr->name);
          ptr = wordmap[ptr->prev];
        }
        result.push_back(bstr);
        while (result.size() > 0) {
          cout << result.back() << ' ';
          result.pop_back();
        }
        cout << endl;
        break;
      }

      nexts.push(lists[lastchar][i]);
    }

    if (found) break;
  }
}

int main(int argc, char** argv) {
  vector<string> lists[26];
  unordered_map<string, Node*> wordmap;
  ifstream file("/usr/share/dict/words");
  if (file.is_open()) {
    string line;
    while (file.good()) {
      getline(file, line);
      line[0] = (line[0] < 97)? line[0] + 32 : line[0];
      Node* new_node = new Node(line);
      wordmap.insert(make_pair(line, new_node));
      lists[line[0] - 97].push_back(line);
    }
    file.close();
  } else 
    cout << "Unable to read word list " << endl;

  clock_t t1 = clock();
  wordmap["run"]->value = 0;
  dijkstra("run", "time", wordmap, lists);
  clock_t t2 = clock();
  cout << ((float)t2 - (float)t1) / CLOCKS_PER_SEC << endl; 

//  cout << "Map size " << wordmap.size() << endl;
//  for (char i = 'a'; i < 'z'; i++)
//    cout << i << ' ' << lists[i - 97].size() << endl;
  return 0;
}
