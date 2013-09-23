#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class Node {
  public:
    Node(int data) : data(data), left(NULL), right(NULL) {}
    ~Node() {}
    Node* left;
    Node* right;
    int data;
};

class Tree {
  public:
    Tree() : root(NULL) {}
    ~Tree() {}
    void insert(int data);
    void search(int left, int right);
    bool check_side(int left, int right, int base, int& left_or_right);
  private:
    Node* root;
};

void Tree::insert(int data) {
  if (!root) {
    root = new Node(data);
  } else {
    Node * head = root;
    Node * parent = root;
    while (head) {
      parent = head;
      if (data < head->data) 
        head = head->left;
      else
        head = head->right;
    }
    if (data < parent->data)
      parent->left = new Node(data);
    else
      parent->right = new Node(data);
  } 
}

bool Tree::check_side(int left, int right, int base, int& left_or_right) {
  bool same_side = false;
  if (left <= base && right <= base) { 
    same_side = true;
    left_or_right = 1;
  }
  if (left >= base && right >= base) {
    same_side = true;
    left_or_right = -1;
  }
  return same_side;
}

void Tree::search(int left, int right) {
  Node* head = root;
  int left_or_right = 0;
  while (head && check_side(left, right, head->data, left_or_right)) {
    if (left_or_right > 0)
      head = head->left;
    else
      head = head->right;
  }
  cout << head->data << endl;
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
  Tree tree;
  tree.insert(30);
  tree.insert(8);
  tree.insert(52);
  tree.insert(3);
  tree.insert(20);
  tree.insert(10);
  tree.insert(29);

  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      vector<int> num_array;
      parse_array(line, num_array);
      tree.search(num_array[0], num_array[1]); 
    }
  }
  return 0;
}
