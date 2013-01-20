#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
  string value;
  Node* next;
  Node* prev;
public:
  Node(string STR): value(STR), next(NULL), prev(NULL) {}
  ~Node() {}
  void set_str(string STR) { value = STR; }
  string get_str() { return value; } 
  void set_next(Node* node) { next = node; }
  Node* get_next() { return next; }
  void set_prev(Node* node) { prev = node; }
  Node* get_prev() { return prev; }
};

class SinglyLinked {
  Node* head;
public:
  SinglyLinked(): head(NULL) {}
  ~SinglyLinked() {}
  void add(string str);
  Node* find(string str);
  void remove(string str);
  vector<string> to_array();
};

void SinglyLinked::add(string str) {
  if (head == NULL) head = new Node(str);
  else {
    Node* ptr = head;
    while (ptr->get_next() != NULL) 
      ptr = ptr->get_next();
    ptr->set_next(new Node(str));
  }
}

Node* SinglyLinked::find(string str) {
  Node* ptr = head;
  while (ptr != NULL) {
    if (ptr->get_str().compare(str) == 0)
      return ptr;
    ptr = ptr->get_next();
  }
  return NULL;
}

void SinglyLinked::remove(string str) {
  if (head == NULL) return;
  else if (head->get_str().compare(str) == 0) {
    Node* ptr = head;
    head = head->get_next();
    delete ptr;
    return;
  }

  Node* parent = head;
  Node* ptr = head->get_next();
  while (ptr != NULL) {
    if (ptr->get_str().compare(str) == 0) {
      cout << "remove" << endl;
      parent->set_next(ptr->get_next());
      delete ptr;
      return;
    }
    parent = ptr;
    ptr = ptr->get_next();
  }
}

vector<string> SinglyLinked::to_array() {    
  vector<string> list;
  int count = 0;
  Node* ptr = head;
  while (ptr != NULL) {
    list.push_back(ptr->get_str());
    ptr = ptr->get_next();
  }
  return list;
}

class DoublyLinked {
  Node* head;
  Node* tail;
public:
  DoublyLinked():head(NULL), tail(NULL) {}
  ~DoublyLinked() {}
  void add(string str);
  Node* find(string str);
  void remove(string str);
  vector<string> to_array();
};

void DoublyLinked::add(string str) {
  if (head == NULL) {
    head = new Node(str);
    tail = head;
  } else {
    Node* ptr = new Node(str);
    tail->set_next(ptr);
    ptr->set_prev(tail);
    tail = tail->get_next();
  }
}

Node* DoublyLinked::find(string str) {
  Node* ptr = head;
  while (ptr != NULL) {
    if (ptr->get_str().compare(str) == 0)
      return ptr;
    ptr = ptr->get_next();
  }
}

void DoublyLinked::remove(string str) {
  if (head == NULL) return;
  if (head->get_str().compare(str) == 0) {
    Node* ptr = head;
    head = ptr->get_next();
    head->set_prev(NULL);
    delete ptr;
    return; 
  }
  if (tail->get_str().compare(str) == 0) {
    Node* ptr = tail;
    tail = tail->get_prev();
    tail->set_next(NULL);
    delete ptr;
    return;
  }
  Node* parent = head;
  Node* ptr = head->get_next();
  while (ptr != NULL) {
    if (ptr->get_str().compare(str) == 0) {
      parent->set_next(ptr->get_next());  
      parent->get_next()->set_prev(parent);
      delete ptr;
      return;
    }
    parent = ptr;
    ptr = ptr->get_next();
  }
}

vector<string> DoublyLinked::to_array() {
  vector<string> list;
  Node* ptr = head;
  while (ptr != NULL) {
    list.push_back(ptr->get_str());
    ptr = ptr->get_next();
  }
  return list;
}

int main() {
  DoublyLinked slist;
  slist.add("array");
  slist.add("test");
  slist.add("computer");
  slist.add("word");
  Node* finding = slist.find("rray");
  if (finding != NULL)
    cout << finding->get_str() << endl;
  vector<string> out = slist.to_array();
  for (vector<string>::iterator it = out.begin(); it != out.end(); it++)
    cout << *it << ' ';
  cout << endl;
  slist.remove("word");
//  slist.remove("array");
//  slist.remove("test");
  out = slist.to_array();
  for (vector<string>::iterator it = out.begin(); it != out.end(); it++)
    cout << *it << ' ';
  cout << endl;
  return 0;
}
