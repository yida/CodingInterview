#include <iostream>
#include <climits>
#include "Node.hh"

using namespace std;

class Stack {
  Node* head;
public:
  void push(int val);
  void pop();
  int peak();
  Stack(): head(NULL) {}
  ~Stack() {}
};

void Stack::push(int val) {
  Node *new_node = new Node(val);
  new_node->set_next(head);
  head = new_node;
}

void Stack::pop() {
  if (head != NULL) 
    head = head->get_next();
}

int Stack::peak() {
  return (head == NULL)? INT_MIN : head->get_value();
}

int main() {
  Stack ss;
  ss.push(456);
  ss.push(44211);
  cout << ss.peak() << endl;
  ss.pop();
  ss.pop();
  cout << ss.peak() << endl;
  return 0;
}
