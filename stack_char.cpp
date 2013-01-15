#include <iostream>

using namespace std;

class Node {
  public:
    char data;
    Node* next;
    Node(char c): data(c), next(NULL) {}
    ~Node();
    friend ostream& operator<< (ostream& out, Node* node);
};

ostream& operator<< (ostream& out, Node& node) {
  out << node.data;
  return out;
}

class Stack {
  public:
    Node* top;
    size_t size;
    Stack(): size(0), top(NULL) {}
    ~Stack() {}
    void push(char c) {
      Node* new_node = new Node(c);
      size++;
      new_node->next = top;
      top = new_node;
    }
    char pop() {
      char data = top->data;
      size--;
      top = top->next;
      return data;
    }
    bool empty() {
      return (size > 0)? true : false;
    }
};

int main() {
  Stack char_int;
  char_int.push('c');
  cout << char_int.pop() << endl;
  return 0;
}
