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

Stack tower[3];

size_t getBuffer(size_t srcTower, size_t desTower) {
  switch (srcTower+desTower) {
    case 1:
      return 2;
    case 2:
      return 1;
    case 3:
      return 0;
    default:
      cout << "Select wrong tower" << endl;
      return 0;
  }
}

void hanoi(size_t n, size_t srcTower, size_t desTower) {
  size_t bufTower = getBuffer(srcTower, desTower);
  cout << n << ' ' << srcTower << ' ' << desTower << endl;
  if (n == 1) {
    int item = tower[srcTower].pop();
    if (item < tower[desTower].peek() || tower[desTower].empty()) {
      tower[desTower].push(item);
    } else {
      cerr << "Wrong Step" << endl;
    }
  }
  else {
    hanoi(n-1, srcTower, bufTower);
    hanoi(n, srcTower, desTower);
    hanoi(n-1, bufTower, desTower);
  }
}

int main() {
  tower[0].push(5);
  tower[0].push(4);
  tower[1].push(3);
  tower[1].push(2);
  tower[2].push(1);
  hanoi(5, 0, 2);
//  cout << "Tower 1" << endl;
//  while (!tower[0].empty())
//    cout << tower[0].pop() << endl;
//  cout << "Tower 2" << endl;
//  while (!tower[1].empty())
//    cout << tower[1].pop() << endl;
//  cout << "Tower 3" << endl;
//  while (!tower[2].empty())
//    cout << tower[2].pop() << endl;  
  return 0;
}
