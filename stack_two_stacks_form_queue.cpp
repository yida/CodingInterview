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
      size --;
      return data;
    }
    void push(int data) {
      Node* new_node = new Node(data);
      new_node->next = top;
      top = new_node;
      size ++;
    }
    size_t size; 
    Stack(): size(0), top(NULL) {}
    ~Stack() {}
    bool empty() {
      return (size > 0)? false : true;
    }
};

class MyQueue {
  private:
    Stack forward;
    Stack backward;
  public:
    MyQueue() {}
    ~MyQueue() {}
    void push(int input);
    int pop();
};

void MyQueue::push(int input) {
  forward.push(input);
}

int MyQueue::pop() {
  int item = 0;
  while (!forward.empty()) {
    item = forward.pop();
    backward.push(item);
  }
  int data = backward.pop();
  while (!backward.empty()) {
    item = backward.pop();
    forward.push(item);
  }
  return data;
}

int main() {
  MyQueue myqueue;
  myqueue.push(456);
  myqueue.push(56);
  myqueue.push(1256);
  cout << myqueue.pop() << endl;
  cout << myqueue.pop() << endl;
  cout << myqueue.pop() << endl;
  return 0;
}
