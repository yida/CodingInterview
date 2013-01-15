#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <ctime>
#include <vector>

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

bool check_palindrome(Node* head) {
  size_t length = 0;
  Node* ptr = head;
  if (ptr == NULL) return false;
  while (ptr != NULL) {
    length++;
    ptr = ptr->next;
  }
  size_t half_len = length / 2;
  vector<int> stack;
  ptr = head;
  // push first half elements to stack
  while (half_len > 0) {
    stack.push_back(ptr->data);
    ptr = ptr->next;
    half_len--;
  }
  // move one step forward to avoid mid elemennt
  if ((length % 2) == 1) ptr = ptr->next;
  while (ptr != NULL) {
    if (ptr->data != stack.back())
      return false;
    ptr = ptr->next;
    stack.pop_back();
  }
  return true;
}

int main() {
  Node* node1 = new Node(1);
  Node* node2 = new Node(2);
  Node* node3 = new Node(3);
  Node* node4 = new Node(2);
  Node* node5 = new Node(1);
  node1->next = node2;
  node2->next = node3;
  node3->next = node4;
  node4->next = node5;


  cout << node1 << endl;
  cout << check_palindrome(node1) << endl;

  return 0;
}
