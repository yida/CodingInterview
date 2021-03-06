#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

class Node {
  int data;
  Node* left;
  Node* right;
  int state;
  int depth;
  public:
    Node(int in): data(in), left(NULL), 
                  state(0), depth(0), right(NULL) {}
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
    void check_depth(Node* rt, int depth);
    void BFS(Node* rt);
};

void Tree::BFS(Node* rt) {
  if (rt == NULL) return;

  queue<Node*> NodeList;
  NodeList.push(rt);
  while (!NodeList.empty()) {
    Node* node = NodeList.front();
    if (node->state == 0) { // unvisited
      cout << node->data << ' ' << node->depth << endl;
      node->state = 1; // set to visited
      if (node->left != NULL) {
        node->left->depth = node->depth + 1;
        NodeList.push(node->left);
      }
      if (node->right != NULL) {
        node->right->depth = node->depth + 1;
        NodeList.push(node->right);
      }
    }
    NodeList.pop();
  }
}

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

void Tree::check_depth(Node* rt, int depth) {
  if (rt != NULL) {
    check_depth(rt->left, depth+1);
    cout << "Depth " << depth << ' ';
    check_depth(rt->right, depth+1);
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

void construct_tree(vector<int>& array, int first, 
                                        int last, Tree& tree) {
  if (first > last) 
    return;
  if (first == last) {
    tree.insert(array[first]);
  } else {
    size_t mid = first + (last - first) / 2;
    tree.insert(array[mid]);
    construct_tree(array, first, mid - 1, tree);
    construct_tree(array, mid + 1, last, tree);
  }
}

int main() {
  vector<int> sample;
  for (size_t cnt = 0; cnt < 100; cnt ++)
    sample.push_back(rand()%1000);
  sort(sample.begin(), sample.end());

  Tree balanced_tree;
  construct_tree(sample, 0, sample.size() - 1, balanced_tree);
  cout <<  balanced_tree.check_balance(balanced_tree.get_root(), 0) << endl;
  balanced_tree.print_in_order(balanced_tree.get_root());
  cout << endl;
  balanced_tree.check_depth(balanced_tree.get_root(), 0);
  cout << endl;
  balanced_tree.BFS(balanced_tree.get_root());

  for (size_t cnt = 0; cnt < 100; cnt ++)
    cout << sample[cnt] << ' ';
  cout << endl;
  return 0;
}
