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

int main() {
  SinglyLinked slist;
  slist.add("array");
  slist.add("test");
  slist.add("word");
  Node* finding = slist.find("array");
  if (finding != NULL)
    cout << finding->get_str() << endl;
  vector<string> out = slist.to_array();
  for (vector<string>::iterator it = out.begin(); it != out.end(); it++)
    cout << *it << ' ';
  cout << endl;
//  slist.remove("word");
//  slist.remove("array");
  slist.remove("test");
  out = slist.to_array();
  for (vector<string>::iterator it = out.begin(); it != out.end(); it++)
    cout << *it << ' ';
  cout << endl;
  return 0;
}
