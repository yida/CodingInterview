#include <iostream>
#include <deque>

using namespace std;

class Node {
  int data;
  deque<Node*> siblings;

  public:
    Node(int value): data(value) {}
    ~Node() {}
    friend class TriTree;
};

class TriTree {
  Node* root;
  public:
    TriTree(): root(NULL) {}
    ~TriTree() {}
    void insert(int data);
};
