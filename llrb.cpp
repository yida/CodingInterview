#include <iostream>
#include <cstdlib>
#include <climits>
#include <queue>

using namespace std;

const bool red = true;
const bool black = false;

class Node {
  public:
    char key;
    int val;
    bool color;
    Node* left;
    Node* right;
    Node():key(0), val(0), color(black), left(NULL), right(NULL) {}
    Node(char Key, int Val, bool Color):left(NULL), right(NULL), 
            key(Key), val(Val), color(Color) {}
    ~Node() {}
};

class LLRB {
  private:
    Node* root;
    Node* insert(Node* h, char key, int val);
    Node* colorFlip(Node* h);
    Node* rotateLeft(Node* h);
    Node* rotateRight(Node* h);
    bool isRed(Node* x);
    void inorder_traverse(Node* x);
    Node* deleteMax(Node* h);
    Node* deleteMin(Node* h);
    Node* deleteAny(Node* h, char key);
    Node* moveRedRight(Node* h);
    Node* moveRedLeft(Node* h);
    Node* fixUp(Node* h);
    Node* minNode(Node* h);
  public:
    LLRB(): root(NULL) {}
    ~LLRB(){}
    int get(Node* h, char key); // search method
    void insert(char key, int val); // insert method
    void print();
    void deleteMax();
    void deleteMin();
    void deleteAny(char key);
};

Node* LLRB::minNode(Node* h) {
  while (h->left != NULL) {
    h = h->left;
  }
  return h;
}

void LLRB::deleteAny(char key) {
  root = deleteAny(root, key);
}

Node* LLRB::deleteAny(Node* h, char key) {
  if (h->key < key) {
    if (!isRed(h->left) && !isRed(h->left->left))
      h = moveRedLeft(h);
    h->left = deleteAny(h->left, key);
  } else {
    if (isRed(h->left)) h = rotateRight(h);
    if ((h->key == key) && (h->right == NULL))
      return NULL;
    if (!isRed(h->right) && !isRed(h->right->left)) 
      h = moveRedRight(h);
    if (h->key == key) {
      Node* minNd = minNode(h->right);
      h->key = minNd->key;
      h->val = get(h->right, h->key);
      h->right = deleteMin(h->right);
    } else 
      h->right = deleteAny(h->right, key);
  }
  return fixUp(h);
}

void LLRB::deleteMin() {
  root = deleteMin(root);
  root->color = black;
}

Node* LLRB::deleteMin(Node* h) {
  if (h->left == NULL)
    return NULL;
  if (!isRed(h->left) && !isRed(h->left->left))
    h = moveRedLeft(h);
  h->left = deleteMin(h->left);
  return fixUp(h);
}

Node* LLRB::moveRedLeft(Node* h) {
  colorFlip(h);
  if (isRed(h->right->left)) {
    h->right = rotateRight(h->right);
    h = rotateLeft(h);
    colorFlip(h);
  }
  return h;
}

Node* LLRB::fixUp(Node* h) {
  if (isRed(h->right))
    h = rotateLeft(h);
  if (isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if (isRed(h->left) && isRed(h->right))
    colorFlip(h);
  return h;
}

Node* LLRB::moveRedRight(Node* h) {
  colorFlip(h);
  if (isRed(h->left->left)) {
    h = rotateRight(h);
    colorFlip(h);
  }
  return h;
}

void LLRB::deleteMax() {
  root = deleteMax(root);
  root->color = black;
}

Node* LLRB::deleteMax(Node* h) {
  if (isRed(h->left)) 
    h = rotateRight(h);
  if (h->right == NULL)
    return NULL;
  if (!isRed(h->right) && !isRed(h->right->left))
    h = moveRedRight(h);
  h->left = deleteMax(h->left);

  return fixUp(h);
}

void LLRB::inorder_traverse(Node* x) {
  if (x != NULL) {
//    cout << "left" << endl;
    inorder_traverse(x->left);
//    cout << "mid" << endl;
    cout << x->key << ' ' << x->val << endl;
//    cout << "right" << endl;
    inorder_traverse(x->right);
  }
}

bool LLRB::isRed(Node* x) {
  if (x == NULL) return false;
  return x->color == red;
}

void LLRB::print() {
  inorder_traverse(root);
}

Node* LLRB::rotateRight(Node* h) {
  Node* ptr = h->left;
  h->left = ptr->right;
  ptr->right = h;
  ptr->color = ptr->right->color;
  ptr->right->color = red;
  return ptr;
}

Node* LLRB::rotateLeft(Node* h) {
  Node* ptr = h->right;
  h->right = ptr->left;
  ptr->left = h;
  ptr->color = ptr->left->color;
  ptr->left->color = red;
  return ptr;
}

Node* LLRB::colorFlip(Node* h) {
  h->color = !h->color;
  h->left->color = !h->left->color;
  h->right->color = !h->right->color;
  return h;
}

Node* LLRB::insert(Node* h, char key, int val) {
  if (h == NULL)
    return new Node(key, val, red);

  if (h->key == key) h->val = val;
  else if (h->key < key) 
    h->left = insert(h->left, key, val);
  else if (h->key > key)
    h->right = insert(h->right, key, val);

  if (isRed(h->right)) 
    h = rotateLeft(h);
  if (isRed(h->left) && isRed(h->left->left))
    h = rotateRight(h);
  if (isRed(h->left) && isRed(h->right))
    colorFlip(h);

  return h;
}

int LLRB::get(Node* h, char key) {
  Node* ptr = h;
  while (ptr != NULL) {
    if (root->key == key) return root->val;
    else if (root->key > key) ptr = ptr->right;
    else if (root->key < key) ptr = ptr->left;
  }
  return INT_MIN;
}

void LLRB::insert(char Key, int Val) {
  root = insert(root, Key, Val); 
}


int main() {
  LLRB rb;   
  rb.insert('H', 456);
  rb.insert('D', 45);
  rb.insert('B', 56);
  rb.insert('A', 5);
  rb.deleteMax();
  rb.deleteMin();
  rb.deleteAny('A');
  rb.print();
  return 0;
}
