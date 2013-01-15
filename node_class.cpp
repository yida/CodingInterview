#include <iostream>
#include <cstddef>

using namespace std;

class Node {
  private:
    int data;
    Node *next;
  public:
    Node(int input): data(input), next(NULL) {}
    Node(): data(0), next(NULL) {}
    ~Node() {}
    friend ostream& operator<< (ostream& out, Node& node);
};

ostream& operator<< (ostream& out, Node& node) {
  out << node.data;
  return out;
}

int main() {
  Node node(435);
  cout << node << endl;
  return 0;
}
