#include <iostream>

using namespace std;

const int table_size = 128;

class Node {
public:
  int key;
  int value;
  Node* next;
  Node(): key(-1), value(0), next(NULL) {}
  ~Node() {}
  Node(int Key, int Value): key(Key), value(Value), next(NULL) {}
};

class Hashtable {
  Node* table[table_size];
public:
  Hashtable();
  ~Hashtable() {}
  void put(int key, int value);
  int get(int key);
  bool search(int key, int value);
};

Hashtable::Hashtable() {
  for (int i = 0; i < table_size; i++)
    table[i] = NULL;
}

void Hashtable::put(int key, int value) {
  int idx = key % 128;
  if (table[idx] == NULL) {
    table[idx] = new Node(key, value);
  } else {
    Node *ptr = table[idx];
    while (ptr->next != NULL) ptr = ptr->next;
    ptr = new Node(key, value);
  }
}

bool Hashtable::search(int key, int value) {
  int idx = key % 128;
  if (table[idx] == NULL) return false;
  else {
    Node* ptr = table[idx];
    while (ptr != NULL) {
      if (ptr->value == value) return true;
      ptr = ptr->next;
    }
    return false;
  }
}

int Hashtable::get(int key) {
  int idx = key % 128;
  if (table[idx] == NULL) {
    return -1;
  } else {
    Node* ptr = table[idx];
    table[idx] = ptr->next;
    return ptr->value;
  }
}

int main() {
  Hashtable htable;
  htable.put(4325, 4443);
  htable.put(50, 456);
  cout << htable.search(34, 345) << ' ' << htable.search(50, 456) << endl;
  cout << htable.get(34) << ' ' << htable.get(4325) << endl;
  return 0;
}
