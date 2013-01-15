#include <iostream>
#include <cstddef>

using namespace std;

struct Node {
  int data;
  Node* next;
};

int main() {
  struct Node node = {435, NULL};
  cout << node.data << endl;
  return 0;
}
