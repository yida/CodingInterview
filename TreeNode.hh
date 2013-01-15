
class Node {
  int value;
  Node* left;
  Node* right;
public:
  Node(): value(0), right(NULL), left(NULL) {}
  Node(int val): value(val), left(NULL), right(NULL) {}
  ~Node() {}
  int get_value() { return value; }
  void set_value(int val) { value = val; }
  Node* get_left() { return left; }
  void set_left(Node* node) { left = node; }
  Node* get_right() { return right; }
  void set_right(Node* node) { right = node; }
};



