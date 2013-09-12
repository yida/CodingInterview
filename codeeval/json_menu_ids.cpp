#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

bool match_parenthesis(const char left, const char right) {
  if (left == '{' && right == '}') return true;
  if (left == '[' && right == ']') return true;
  return false;
}

bool is_parenthesis(const char c) {
  if (c == '{' || c == '}' || c == '[' || c == ']') return true;
  else return false;
}

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  tokens.push_back(line);
}

int parse_content(string& content) {
  vector<string> elements_array;
  string delimitor(",");
  split(content, delimitor, elements_array);  
  bool has_label = false;
  int id = 0;
  for (size_t element_index = 0; element_index < elements_array.size();
      element_index ++) { 
    if (elements_array[element_index].find("id") != string::npos) {
      delimitor = ':';
      vector<string> key_value;
      split(elements_array[element_index], delimitor, key_value);
      istringstream ss(key_value[1]);
      ss >> id;
    }
    if (elements_array[element_index].find("label") != string::npos) {
      has_label = true;    
    }
  }
  if (has_label) return id;
  else return 0;
}

void parenthesis_search(const string& line) {
  vector<char> parenthesis_stack;
  vector<int> pos_stack;
  
  parenthesis_stack.push_back(line[0]);
  pos_stack.push_back(0);
  int sum = 0;
  for (int index = 1; index < line.size(); index ++) {
    if (is_parenthesis(line[index])) {
      if (match_parenthesis(parenthesis_stack.back(), line[index])) {
        string content = line.substr(pos_stack.back() + 1, index - pos_stack.back() - 1);
        if (content.find("{") == string::npos) {
          sum += parse_content(content);
        }
        parenthesis_stack.pop_back();
        pos_stack.pop_back();
      } else {
        parenthesis_stack.push_back(line[index]);
        pos_stack.push_back(index);
      }
    }  
  } 
  cout << sum << endl;
}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      parenthesis_search(line);
    }
  }
  return 0;
}
