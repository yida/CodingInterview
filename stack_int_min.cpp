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
  protected:
    Node* top;
    size_t size; 
  public:
    int pop() {
      int data = top->data;
      top = top->next;
      size --;
      return data;
    }
    int back() {
      return top->data;
    }
    void push(int data) {
      Node* new_node = new Node(data);
      new_node->next = top;
      top = new_node;
      size ++;
    }
    Stack(): size(0), top(NULL) {}
    ~Stack() {}
    bool empty() {
      return (size > 0)? false : true;
    }
};

class StackMin: public Stack {
  private:
    Stack min;
  public:
    StackMin() {}
    ~StackMin() {}
    void push(int data) {
      Node* new_node = new Node(data);
      new_node->next = top;
      top = new_node;
      if (min.empty()) {
        min.push(data);
      }
      else {
        if (data < min.back()) min.push(data);
      }
    }
    int getMin() {
      return min.back();
    }
    int pop() {
      int out = top->data;
      top = top->next;
      if (out == min.back()) min.pop();
      return out;
    }
};

int main() {
  StackMin int_stack;
  int_stack.push(456);
  int_stack.push(56);
  int_stack.push(6);
  int_stack.push(136);
  cout << "min: " << int_stack.getMin() << endl;
  cout << int_stack.pop() << endl;
  cout << "min: " << int_stack.getMin() << endl;
  cout << int_stack.pop() << endl;
  cout << "min: " << int_stack.getMin() << endl;
  return 0;
}
