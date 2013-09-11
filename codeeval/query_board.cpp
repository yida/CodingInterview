#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

const int SIZE = 256;
int board[SIZE][SIZE] = {0};

void split(string& line, string& delimiter, vector<string>& tokens) {
  tokens.clear();
  size_t pos = 0;
  while ((pos = line.find(delimiter)) != string::npos) {
    tokens.push_back(line.substr(0, pos));
    line.erase(0, pos + delimiter.length());
  }
  tokens.push_back(line);
}

void set_command(const string& command, int dim, int value) {
  if (command.find("Row") != string::npos) {
    for (size_t counter = 0; counter < 256; counter ++) {
      board[dim][counter] = value;
    }
  } else if (command.find("Col") != string::npos) {
    for (size_t counter = 0; counter < 256; counter ++) {
      board[counter][dim] = value;
    }
  } 
}

void query_command(const string& command, int dim) {
  int sum = 0;
  if (command.find("Row") != string::npos) {
    for (size_t counter = 0; counter < 256; counter ++)
      sum += board[dim][counter]; 
  } else if (command.find("Col") != string::npos) {
    for (size_t counter = 0; counter < 256; counter ++)
      sum += board[counter][dim];   
  } 
  cout << sum << endl;
}

void parse_line(string& line) {
  vector<string> command_tokens;
  string delimiter(" ");
  split(line, delimiter, command_tokens);
  string command = command_tokens[0];
  int dim = 0, index = 0;
  if (command.find("Set") != string::npos) {
    istringstream ss_dim(command_tokens[1]);
    istringstream ss_index(command_tokens[2]);
    ss_dim >> dim;
    ss_index >> index;
    set_command(command, dim, index);
  } else if (command.find("Query") != string::npos) {
    istringstream ss_dim(command_tokens[1]);
    ss_dim >> dim;
    query_command(command, dim);
  }

}

int main(int argc, char** argv) {
  ifstream file;
  file.open(argv[1]);
  string line;
  vector<string> array_string;
  for (; !file.eof();) {
    getline(file, line);
    if (!line.length()) continue;
    else {
      parse_line(line);
    }
  }
  return 0;
}
