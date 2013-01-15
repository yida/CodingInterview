#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <ctime>
#include <queue>

using namespace std;

class Node {
  public:
    int data;
    Node *next;
    Node(int input): data(input), next(NULL) {}
    Node(): data(0), next(NULL) {}
    ~Node() {}
    friend ostream& operator<< (ostream& out, Node& node);
};

ostream& operator<< (ostream& out, Node& node) {
  out << node.data;
  return out;
}

ostream& operator<< (ostream& out, Node* head) {
  Node *ptr = head;
  while (ptr != NULL) {
    out << ptr->data << ' ';
    ptr = ptr->next;
  }
  out << endl;
  return out;
}

Node* random_linked_list(size_t length) {
  srand(time(0));
  Node *head = new Node(rand()%SHRT_MAX);
  Node* head_ptr = head;
  while ((--length) > 0) {
    Node *node = new Node(rand()%SHRT_MAX);
    head_ptr->next = node;
    head_ptr = head_ptr->next;
  }
  return head;
}

Node* all_same_linked_list(size_t length) {
  srand(time(0));
  int num = rand()%SHRT_MAX;
  Node *head = new Node(num);
  Node* head_ptr = head;
  while ((--length) > 0) {
    Node *node = new Node(num);
    head_ptr->next = node;
    head_ptr = head_ptr->next;
  }
  return head;
}

void destroy_linked_list(Node *head) {
  if (head->next == NULL)
    delete head;
  else
    destroy_linked_list(head->next);
}

Node* add_front(Node *head, int data) {
  Node *new_head = new Node(data);
  new_head->next = head;
  return new_head;
}

Node* list_partition(Node* head, int mid) {
  queue<int> less;
  queue<int> more;
  Node* ptr = head;
  while (ptr != NULL) {
    if (ptr->data < mid)
      less.push(ptr->data);
    else
      more.push(ptr->data);
    ptr = ptr->next;
  }
  ptr = head;
  while (!less.empty()) {
    ptr->data = less.front();
    less.pop();
    ptr = ptr->next;
  }
  while (!more.empty()) {
    ptr->data = more.front();
    more.pop();
    ptr = ptr->next;
  }
  return head;
}

int main() {
  Node* head = random_linked_list(10);
  cout << head << endl;
  head = list_partition(head, 20000);
  cout << head << endl;

  return 0;
}
