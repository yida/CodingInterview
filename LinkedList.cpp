#include <iostream>
#include <climits>
#include "Node.hh"

using namespace std;

class LinkedList {
  Node* head;
public:
  void insertHead(int val);
  void insertTail(int val);
  int remove(int val);
  void removeHead();
  void removeTail();
  void print();
  LinkedList(): head(NULL) {}
  ~LinkedList() {}
};

void LinkedList::insertHead(int val) {
  if (head == NULL) head = new Node(val);
  else {
    Node* ptr = new Node(val);
    ptr->set_next(head);
    head = ptr;
  }
}

void LinkedList::insertTail(int val) {
  if (head == NULL) head = new Node(val);
  else {
    Node* ptr = head;
    while (ptr->get_next() != NULL) ptr = ptr->get_next();
    ptr->set_next(new Node(val));
  }
}

int LinkedList::remove(int val) {
  if (head == NULL) return -1;
  if (head->get_value() == val) {
    head = head->get_next();
    return 1;
  } else {
    Node * ptr = head;
    while (ptr->get_next() != NULL) {
      Node * next_ptr = ptr->get_next(); 
      if (next_ptr->get_value() == val) {
        ptr->set_next(next_ptr->get_next());
        return 1;
      }
      ptr = next_ptr;
    }
    return -1;
  }
}


void LinkedList::removeTail() {
  if (head != NULL) {
    if (head->get_next() == NULL) head = NULL;
    else {
      Node *ptr = head;
      Node *next_ptr = ptr->get_next();
      while (next_ptr->get_next() != NULL) {
        ptr = next_ptr;
        next_ptr = next_ptr->get_next();
      }
      ptr->set_next(NULL);
    }
  }
}

void LinkedList::removeHead() {
  if (head != NULL) {
    head = head->get_next();
  }
}

void LinkedList::print() {
  Node *ptr = head;
  while (ptr != NULL) {
    cout << ptr->get_value() << ' ';
    ptr = ptr->get_next();
  }
  cout << endl;
}


class DoubleList {
  Node* head;
  Node* tail;
  int size;
public:
  void push_back(int val);
  void push_front(int val);
  int pop_back();
  int pop_front();
  int front();
  int back();
  void print();
  DoubleList(): head(NULL), tail(NULL), size(0) {}
  ~DoubleList() {}
};

void DoubleList::push_back(int val) {
  if (head == NULL) {
    head = new Node(val);
    tail = head;
    head->set_next(tail);
    tail->set_prev(head);
    size++;
  } else {
    Node *new_node = new Node(val);
    Node *prev = tail->get_prev();
    prev->set_next(new_node);
    new_node->set_prev(prev);
    tail = new_node;
    size++;
  }
}

void DoubleList::push_front(int val) {
  if (head == NULL) {
    head = new Node(val);
    tail = head;
    head->set_next(tail);
    tail->set_prev(head);
    size++;
  } else {
    Node* new_node = new Node(val);
    new_node->set_next(head);
    head->set_prev(new_node);
    head = new_node;
    size++;
  }
}

int DoubleList::pop_back() {
  tail = tail->get_prev();
  tail->set_next(NULL);
  size--;
  return 0;
}

int DoubleList::pop_front() {
  head = head->get_next();
  head->set_prev(NULL);
  size--;
  return 0;
}

int DoubleList::front() {
  if (head != NULL) return head->get_value();
  else return INT_MIN;
}

int DoubleList::back() {
  if (tail != NULL) return tail->get_value();
  else return INT_MIN;
}

void DoubleList::print() {
  Node* ptr = head;
  int count = 0;
  while (count++ < size) {
    cout << ptr->get_value() << ' ';
    ptr = ptr->get_next(); 
  }
  cout << endl;
}

int main() {
  LinkedList list;
  list.insertHead(45);
  list.insertHead(23);
  list.print();
  list.insertTail(456);
  list.insertTail(234);
  list.insertTail(34);
  list.print();
  cout << list.remove(456) << endl;
  list.print();
  list.removeHead();
  list.removeTail();
  list.print();
  cout << endl;

  DoubleList dlist;
  dlist.push_back(45);
  dlist.push_back(3456);
  dlist.push_front(12);
  dlist.push_front(2);
  cout << dlist.front() << ' ' << dlist.back() << endl;
  dlist.print();
  dlist.pop_back();
  dlist.pop_front();
  dlist.print();
  return 0;
}
