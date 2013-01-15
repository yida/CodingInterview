#include <iostream>

using namespace std;

class Node {
  int data;
  Node* left;
  Node* right;

  public:
    Node(int in): data(in), left(NULL), right(NULL) {}
    ~Node() {}
    friend class Tree;
};

class Tree {
  private:
    Node* root;
  public:
    Tree(): root(NULL) {}
    ~Tree() {}
    Node* get_root() { return root; }
    void insert(int value);
    void print_in_order(Node* rt) const;
    void print_pre_order(Node* rt) const;
    void print_post_order(Node* rt) const;
};

void Tree::print_in_order(Node* rt) const {
  if (rt != NULL) {
    print_in_order(rt->left);
    cout << rt->data << ' ';
    print_in_order(rt->right);
  }
}

void Tree::print_pre_order(Node* rt) const {
  if (rt != NULL) {
    cout << rt->data << ' ';
    print_pre_order(rt->left);
    print_pre_order(rt->right);
  }
}

void Tree::print_post_order(Node* rt) const {
  if (rt != NULL) {
    print_post_order(rt->left);
    print_post_order(rt->right);
    cout << rt->data << ' ';
  }
}

void Tree::insert(int value) {
  if (root == NULL) {
    root = new Node(value);
  } else {
    Node* ptr = root;
    Node* parent = root;
    char flag = 0;
    while (ptr != NULL) {
      if (value < ptr->data) {
        parent = ptr;
        ptr = ptr->left;
        flag = -1;
      } else {
        parent = ptr;
        ptr = ptr->right;
        flag = 1;
      }
    }
    if (flag < 0)
      parent->left = new Node(value);
    else
      parent->right = new Node(value);
  }
}

int main() {
  Tree tree;
  tree.insert(46);
  tree.insert(67);
  tree.insert(7);
  tree.print_in_order(tree.get_root());
  cout << endl;
  tree.print_pre_order(tree.get_root());
  cout << endl;
  tree.print_post_order(tree.get_root());
  cout << endl;
  return 0;
}
