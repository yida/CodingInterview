/*
Write a function that determines if a specific position on a board is 'winnable', meaning you are able to reach the value 0.  In order to explain what that means I will use the board [1, 1, 2, 3, 0, 6, 4], where a “board” is an array.  The value in each position represents the number of cells to the left and right which you may jump.  For example, if I start at position board[2] I may move to board[0] or board[4] because the value at board[2] is 2.  This would be a 'winnable' position because I am able to reach the value 0 (board[4]).  If I start at board[5] this would not be winnable because I am not able to reach the 0 cell.  
*/


#include <iostream>
#include <set>
#include <queue>

using namespace std;

// To execute C++, please define "int main()"

int main() {
  int i;
  int board[7] = {1, 1, 2, 3, 0, 6, 4};
  int board_size = sizeof(board) / sizeof(int);
  int start_index = 5;  // input
  set<int> number_set;
  set<int>::iterator it_set;
  queue<int> number_queue;
  number_queue.push(start_index);
  bool winnable = false;
  while (!number_queue.empty()) {
    if (board[number_queue.front()] == 0) {
      winnable = true;
      break;
    }
    // check if current one visited or not
    it_set = number_set.find(number_queue.front());
    if (it_set == number_set.end()) {
        number_set.insert(number_queue.front());
        // left extension
        if ((number_queue.front() - board[number_queue.front()]) >= 0)
           number_queue.push(number_queue.front() - board[number_queue.front()]);
        // right extension
        if ((number_queue.front() + board[number_queue.front()]) < board_size)
           number_queue.push(number_queue.front() + board[number_queue.front()]);         
    }
    number_queue.pop();
  }
  if (winnable)
     cout << "We are winnable" << endl;
  else
     cout << "We are not winnable" << endl;
  return 0;
}
