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

Node* add_front(Node *head, int data) {
  Node *new_head = new Node(data);
  new_head->next = head;
  return new_head;
}

Node* find_circular_head(Node* head) {
  Node* ptr_slow = head;
  Node* ptr_fast = head;
  while (true) {
    ptr_slow = ptr_slow->next;
    ptr_fast = ptr_fast->next->next;
    if (ptr_slow == NULL || ptr_fast == NULL) return NULL;
    if (ptr_slow == ptr_fast)
      break;
  }
  ptr_fast = head;
  while (ptr_slow != ptr_fast) {
    ptr_slow = ptr_slow->next;
    ptr_fast = ptr_fast->next;
  }
  cout << ptr_slow->data << endl;
  return NULL;
}

int main() {
  Node* nodeA = new Node(3462);
  Node* nodeB = new Node(462);
  Node* nodeC = new Node(948);
  Node* nodeD = new Node(1248);
  Node* nodeE = new Node(48);
  
  nodeA->next = nodeB;
  nodeB->next = nodeC;
  nodeC->next = nodeD;
  nodeD->next = nodeE;
  nodeE->next = nodeC;

  Node* head = nodeA;
  Node* cnode = find_circular_head(head);

//  cout << cnode->data << endl;

  return 0;
}
