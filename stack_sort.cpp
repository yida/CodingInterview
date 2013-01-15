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
      if (top != NULL) {
        int data = top->data;
        top = top->next;
        size --;
        return data;
      }
      return 0;
    }
    void push(int data) {
      Node* new_node = new Node(data);
      new_node->next = top;
      top = new_node;
      size ++;
    }
    int peek() {
      return (top == NULL)? 0 : top->data;
    }
    size_t size; 
    Stack(): size(0), top(NULL) {}
    ~Stack() {}
    bool empty() {
      return (size > 0)? false : true;
    }
};

void sort_stack(Stack& stack) {
  Stack sorted_stack;
  int temp = 0;
  while (!stack.empty()) {
    temp = stack.pop();
    if (sorted_stack.empty()) {
      sorted_stack.push(temp);
    }
    else {
      while ((sorted_stack.peek() < temp) && (!sorted_stack.empty())) {
        int item = sorted_stack.pop();
        stack.push(item);
      } 
      sorted_stack.push(temp);
    }
  }
  stack = sorted_stack;
}

int main() {
  Stack mystack;
  mystack.push(456);
  mystack.push(56);
  mystack.push(1256);
  mystack.push(6);
  mystack.push(35);
  sort_stack(mystack);
  while (!mystack.empty()) {
    cout << mystack.pop() << endl;
  }
  return 0;
}
