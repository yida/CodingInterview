// given sorted string array and figure out comparison between characters
// 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Node {
  public:
    int value;
    Node* nexts[128];
    Node* prevs[128];
    std::vector<int> next;
    std::vector<int> prev;
    Node(): value(0) { for (int i = 0; i < 128; i++) { nexts[i] = NULL; prevs[i] = NULL;}}
    Node(int v): value(v) { for (int i = 0; i < 128; i++) { nexts[i] = NULL; prevs[i] = NULL;}}
    ~Node() {}
}; 

void print(const std::vector<int> & tries) {
  for (int i = 0; i < tries.size() - 1; i ++)
    std::cout << (char)tries[i] << " > ";
  std::cout << (char)tries[tries.size()-1] << std::endl;
}
 
void traverse_tries(Node* head, std::vector<int>& tries) {
  if (head->next.size() == 0) {
    tries.push_back(head->value);
    print(tries);
    tries.pop_back();
  }
  tries.push_back(head->value);
  for (int i = 0; i < head->next.size(); i++)
    traverse_tries(head->nexts[head->next[i]], tries);
  tries.pop_back();
}

void comparestring(std::string str[], int strlen, Node* nodelist[]) {
  for (int i = 0; i < strlen - 1; i++) {
    std::string strA = str[i];
    std::string strB = str[i+1]; // strB > strA;
    int comparelen = std::min(strA.length(), strB.length());
    for (int j = 0; j < comparelen; j++) {
      if (strA[j] != strB[j]) { // strB[j] > strA[j]
//      std::cout << strA[j] << ' ' << strB[j] << std::endl;
        if (nodelist[strA[j]] == NULL) // create a new node if not exist
          nodelist[strA[j]] = new Node(strA[j]);
        if (nodelist[strB[j]] == NULL)
          nodelist[strB[j]] = new Node(strB[j]);
        if (nodelist[strB[j]]->nexts[strA[j]] != NULL) break; // if strB > strA ever saw before
        if (nodelist[strA[j]]->prevs[strB[j]] != NULL) break; // if strA < strB ever saw before
        nodelist[strB[j]]->nexts[strA[j]] = nodelist[strA[j]]; // link B -> A
        nodelist[strB[j]]->next.push_back(strA[j]);
        nodelist[strA[j]]->prevs[strB[j]] = nodelist[strB[j]]; // link A <- B
        nodelist[strA[j]]->prev.push_back(strB[j]);
        break;
      }
    }
  }

  std::vector<int> tries;
  for (int i = 0; i < 128; i++)
    if (nodelist[i] != NULL) {
      if (nodelist[i]->prev.size() == 0) {
//        std::cout << (char)nodelist[i]->value << std::endl;
        traverse_tries(nodelist[i], tries);
      }
    }
}

int main() {
  std::string str[11];
  str[0] = "aZb";
  str[1] = "c35g";
  str[2] = "AbZ";
  str[3] = "BEDa";
  str[4] = "BDd";
  str[5] = "xyz";
  str[6] = "fBbx";
  str[7] = "fbt";
  str[8] = "fbr";
  str[9] = "FGr";
  str[10] = "FAr";

  Node* nodelist[128] = {NULL};
  comparestring(str, 11, nodelist);


  return 0;
}
