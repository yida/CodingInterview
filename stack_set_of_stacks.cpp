#include <iostream>

using namespace std;

class Node {
  public:
    int data;
    Node* next_item;
    Node* next_stack; 
    Node(int value):data(value), next_item(NULL),
                    next_stack(NULL) {} 
    ~Node() {}
};

class SetOfStacks {
  private:
    Node* top;
    size_t stack_size;
    size_t stack_num;
    size_t item_num;
  public:
    SetOfStacks(size_t size): top(NULL), item_num(0),
                    stack_size(size), stack_num(0) {}
    SetOfStacks(): top(NULL), item_num(0), 
                    stack_size(5), stack_num(0) {}
    ~SetOfStacks() {}
    void push(int input);
    int pop();
    int popAt(int index);
};

void SetOfStacks::push(int input) {
  // first item
  if (top == NULL) {
    top = new Node(input);
    stack_num ++;
    item_num ++;
    return;
  }
  Node* new_node = new Node(input);
  if (item_num % stack_size == 0) {
    new_node->next_stack = top;
  } else {
    new_node->next_item = top;
    new_node->next_stack = top->next_stack;
    top->next_stack = NULL;
  }
  top = new_node;
  item_num ++;  
}

int SetOfStacks::pop() {
  if (top != NULL) {
    int data = top->data;
    if (top->next_item != NULL) {
      top->next_item->next_stack = top->next_stack;
      top = top->next_item;
    } else {
      top = top->next_stack;
    }
    return data;
  }
  return 0;
}

int SetOfStacks::popAt(int index) {
  Node* ptr = top;  
  if (index == 1) {
    int data = ptr->data;
    if (ptr->next_item == NULL)
      ptr = ptr->next_stack;
    else {
      ptr->next_item->next_stack = ptr->next_stack;
      ptr = ptr->next_item;
    }
    return data;
  } else {
    while ((ptr->next_stack != NULL) && (index > 2)) {
      index --;
      ptr = ptr->next_stack;
    }
    if (index > 2) return 0;
    int data = ptr->next_stack->data;
    ptr->next_stack->next_item->next_stack = ptr->next_stack->next_stack;
    ptr->next_stack = ptr->next_stack->next_item;
    return data;
  }
  return 0;
}

int main() {
  SetOfStacks stack;
  stack.push(10);
  stack.push(810);
  stack.push(435);
  stack.push(213);
  stack.push(13);
  stack.push(1246);
  stack.push(9843);
  stack.push(843);
  
  cout << stack.popAt(2) << endl;
  cout << stack.popAt(2) << endl;
  return 0;
}
