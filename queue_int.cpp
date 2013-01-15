#include <iostream>

using namespace std;

class Node {
  public:
    int data;
    Node* next;
    Node(int input): data(input), next(NULL) {}
    Node(): data(0), next(NULL) {}
    ~Node() {}
};

class Queue {
  private:
    Node* first;
    Node* last;
    size_t size;
  public:
    Queue(): first(NULL), last(NULL), size(0) {}
    ~Queue() {}
    bool empty() {
      return (size > 0)? true : false;
    }
    void enqueue(int data) {
      Node* new_node = new Node(data);
      if (first == NULL) {
        first = new Node(data); 
        last = first;
        size ++;
      } else {
        last->next = new Node(data);
        last = last->next;
        size ++;
      }
    }
    int dequeue() {
      if (first != NULL) {
        int data = first->data;
        first = first->next;
        size--;
        return data;
      }
      return 0;
    } 
};

int main() {
  Queue int_queue;
  int_queue.enqueue(56);
  int_queue.enqueue(24);
  cout << int_queue.dequeue() << endl;
  cout << int_queue.dequeue() << endl;
  return 0;
}
