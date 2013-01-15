#include <iostream>
#include <cstdlib>

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
    int max_depth;
  public:
    Tree(): root(NULL), max_depth(0) {}
    ~Tree() {}
    Node* get_root() { return root; }
    void insert(int value);
    void print_in_order(Node* rt) const;
    void print_pre_order(Node* rt) const;
    void print_post_order(Node* rt) const;
    bool check_balance(Node* rt, int depth);
};

bool Tree::check_balance(Node* rt, int depth) {
  if (rt == NULL) return true;
  if (rt->left == NULL && rt->right == NULL) {
    if (abs(depth - max_depth) > 1 && max_depth > 0)
      return false;
    else {
      max_depth = (max_depth > depth)? max_depth : depth;
    }
    return true;
  } else {
    bool subflag = true;
    if (rt->left != NULL)
      subflag = check_balance(rt->left, depth + 1);
    if (rt->right != NULL)
      subflag = check_balance(rt->right, depth + 1);
    return subflag;
  }
}

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
  Tree tree1;
  tree1.insert(100);
  tree1.insert(110);
  tree1.insert(90);
  tree1.insert(95);
  tree1.insert(80);
  tree1.insert(70);
  tree1.print_in_order(tree1.get_root());
  cout << endl;
  tree1.print_pre_order(tree1.get_root());
  cout << endl;
  tree1.print_post_order(tree1.get_root());
  cout << endl;
  cout << tree1.check_balance(tree1.get_root(), 0) << endl;

  Tree tree2;
  tree2.insert(50);
  tree2.insert(57);
  tree2.insert(55);
  tree2.insert(40);
  tree2.insert(35);
  tree2.insert(45);
  tree2.print_in_order(tree2.get_root());
  cout << endl;
  tree2.print_pre_order(tree2.get_root());
  cout << endl;
  tree2.print_post_order(tree2.get_root());
  cout << endl;
  cout << tree2.check_balance(tree2.get_root(), 0) << endl;
  return 0;
}
