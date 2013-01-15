#include <iostream>

using namespace std;

class Node {
  public:
    int data;
    Node* left;
    Node* right;
    Node(int input): data(input), left(NULL), right(NULL) {}
    Node(): data(0), left(NULL), right(NULL) {}
    ~Node() {}
    friend ostream& operator<< (ostream& out, Node& node);
};

ostream& operator<< (ostream& out, Node& node) {
  out << node.data;
  return out;
}

class BTree {
  private:
    Node* root;
  public:
    BTree(): root(NULL) {}
    ~BTree() {}
    void insert(int in);
    Node* get_root() { return root; }
    void traverse_in(Node* rt);
    void traverse_pre(Node* rt);
    void traverse_post(Node* rt);
};

void BTree::traverse_in(Node* rt) {
  if (rt == NULL) { 
    cout << "Empty Tree" << endl;
    return;
  }
  if (rt->left != NULL) {
    traverse_in(rt->left);
  }
  cout << rt->data << ' ';
  if (rt->right != NULL) {
    traverse_in(rt->right);
  }
}

void BTree::traverse_pre(Node* rt) {
  cout << rt->data << ' ';
  if (rt->left != NULL)
    traverse_pre(rt->left);
  if (rt->right != NULL) 
    traverse_pre(rt->right);
}

void BTree::traverse_post(Node* rt) {
  if (rt->left != NULL)
    traverse_post(rt->left);
  if (rt->right != NULL)
    traverse_post(rt->right);
  cout << rt->data << ' ';
}

void BTree::insert(int in) {
  if (root == NULL) {
    root = new Node(in);
  } else {
    Node* ptr = root;
    Node* parent = root;
    int left_or_right = 0;
    while (ptr != NULL) {
      if (in < ptr->data) {
        parent = ptr;
        ptr = ptr->left;
        left_or_right = -1;
      } else {
        parent = ptr;
        ptr = ptr->right;
        left_or_right = 1;
      }
    }
    if (left_or_right < 0)
      parent->left = new Node(in);
    else
      parent->right = new Node(in);
  }
}

int main() {
  BTree tree;
  tree.insert(15);
  tree.insert(1);
  tree.insert(100);
  tree.traverse_in(tree.get_root());
  cout << endl;
  tree.traverse_pre(tree.get_root());
  cout << endl;
  tree.traverse_post(tree.get_root());
  cout << endl;
  return 0;
}
