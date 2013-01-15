#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <ctime>

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

Node* add_front(Node *head) {
  Node *new_head = new Node(head->data);
  new_head->next = head;
  return new_head;
}

void delete_middle_node(Node *head) {
  Node* ptr = head;
  if (ptr == NULL) return;
  while (ptr->next != NULL) {
    ptr->data = ptr->next->data;
    if (ptr->next->next == NULL)
      ptr->next = NULL;
    else
      ptr = ptr->next;
  }
}

int main() {
  Node* Link1 = random_linked_list(5);
//  Node* Link1 = all_same_linked_list(5);
  cout << SHRT_MAX << endl;
  cout << Link1 << endl;

  delete_middle_node(Link1->next);
  cout << Link1 << endl;
  destroy_linked_list(Link1);
//  cout << node << endl;
  return 0;
}
