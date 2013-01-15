#include <iostream>

using namespace std;

class Node {
  public:
    int data;
    Node* next;
    Node(int input): data(input) {}
    ~Node() {}
    friend ostream& operator<< (ostream& out, Node &node);
};

ostream& operator<< (ostream& out, Node &node) {
  out << node.data;
  return out;
}

class Stack {
  public:
    Node* top;
    int pop() {
      int data = top->data;
      top = top->next;
      return data;
    }
    void push(int data) {
      Node* new_node = new Node(data);
      new_node->next = top;
      top = new_node;
    }
    size_t size; 
    Stack(): size(0), top(NULL) {}
    ~Stack() {}
    bool empty() {
      return (size > 0)? true : false;
    }
};

int main() {
  Stack int_stack;
  int_stack.push(456);
  cout << int_stack.empty() << endl;
  cout << int_stack.pop() << endl;
  return 0;
}
