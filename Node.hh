
class Node {
  int value;
  Node* next;
  Node* prev;
public:
  Node(): value(0), next(NULL), prev(NULL) {}
  Node(int val): value(val), next(NULL), prev(NULL) {}
  ~Node() {}
  int get_value() { return value; }
  void set_value(int val) { value = val; }
  Node* get_next() { return next; }
  void set_next(Node* node) { next = node; }
  Node* get_prev() { return prev; }
  void set_prev(Node* node) { prev = node; }
};



