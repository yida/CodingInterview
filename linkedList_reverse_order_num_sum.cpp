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

Node* sum_reverse_linkedList_num(Node* num1, Node* num2) {
  if (num1 == NULL || num2 == NULL) return NULL;
  queue<int> n1;
  queue<int> n2;
  Node* ptr1 = num1;
  while (ptr1 != NULL) {
    n1.push(ptr1->data);
    ptr1 = ptr1->next;
  }
  Node* ptr2 = num2;
  while (ptr2 != NULL) {
    n2.push(ptr2->data);
    ptr2 = ptr2->next;
  }

  Node* sum = NULL;
  int acc = 0, carry = 0;
  while (!n1.empty() || !n2.empty()) {
    acc = 0;
    if (!n1.empty()) {
      acc += n1.front();
      n1.pop();
    }
    if (!n2.empty()) {
      acc += n2.front();
      n2.pop();
    }
    Node* node = new Node((acc + carry) % 10);
    carry = (acc + carry) / 10;
    node->next = sum;
    sum = node;
  }
  return sum;
}

int main() {
  Node* Link1 = random_linked_list(5);
//  Node* Link1 = all_same_linked_list(5);
  cout << SHRT_MAX << endl;

  Node* num1 = new Node(5);
  Node* num2 = new Node(2);
  num1 = add_front(num1, 1);
  num1 = add_front(num1, 3);
  num2 = add_front(num2, 9);
  num2 = add_front(num2, 5);
  cout << num1 << endl;
  cout << num2 << endl;
  Node* sum = sum_reverse_linkedList_num(num1, num2);
  cout << sum << endl;
  destroy_linked_list(Link1);
  destroy_linked_list(num1);
  destroy_linked_list(num2);
//  cout << node << endl;
  return 0;
}
