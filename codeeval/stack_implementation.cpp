#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class Node {
  public:
    Node(int data) : data(data) {}
    ~Node() {}
    Node* next;
    int data;
};

class Stack {
  public:
    Stack() : root(NULL) {}
    ~Stack() {}
    void push(int data);
    void pop();
    int top();

    Node* root;
};

void Stack::push(int data) {
  Node* new_head = new Node(data);  
  new_head->next = root;
  root = new_head;
}

void Stack::pop() {
  if (root)
    root = root->next;
}

int Stack::top() {
  if (root)
    return root->data;
  else
    return 0; 
}

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  if (line.size())
    tokens.push_back(line);
}

void parse_array(string& line, vector<int>& array) {
  vector<string> num_array;
  string delimiter(" ");
  split(line, delimiter, num_array);
  for (size_t index = 0; index < num_array.size(); index ++) {
    int number = 0;
    istringstream ss(num_array[index]);
    ss >> number;
    array.push_back(number);
  }
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      vector<int> num_array;
      parse_array(line, num_array);
      Stack my_stack;
      for (size_t index = 0; index < num_array.size(); index ++) {
        my_stack.push(num_array[index]); 
      }
      for (size_t index = 0; index < num_array.size(); index ++) {
        if (index % 2 == 0)
          cout << my_stack.top() << ' ';
        my_stack.pop(); 
      }
      cout << endl;
    }
  }
  return 0;
}
