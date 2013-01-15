#include <iostream>

using namespace std;

class Node {
  public:
    char data;
    Node* next;
    Node():data(0), next(NULL) {}
    Node(char input): data(input), next(NULL) {}
    ~Node() {}
};

class Queue {
  private:
    Node* first;
    Node* last;
    size_t size;
  public:
    Queue():first(NULL), last(NULL), size(0) {}
    ~Queue() {}
    void enqueue(char data) {
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
    char dequeue() {
      if (first != NULL) {
        char data = first->data;
        first = first->next;
        return data;
      } else
        return 0;
    }
    bool empty() {
      return (size > 0)? true : false;
    }
};

int main() {
  Queue char_queue;
  char_queue.enqueue('D');
  char_queue.enqueue('f');
  cout << char_queue.dequeue() << endl;
  cout << char_queue.dequeue() << endl;
  return 0;
}
