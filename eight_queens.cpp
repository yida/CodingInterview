#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

bool checkvalid(int columns[], int col, int row) {
  for (int c = 0; c < col; c++) {
    if (columns[c] == row)
      return false;
    int coldis = abs(c - col);
    int rowdis = abs(columns[c] - row);
    if (coldis == rowdis)
      return false;
  }
  return true;
}

void print_queue(int columns[], int nqueens) {
  cout << "============================" << endl;
  for (int i = 0; i < nqueens; i++) { // row
    for (int j = 0; j < nqueens; j++) {// col
      if (columns[j] == i) 
        cout << '|' << '@';
      else
        cout << "| ";
    }
    cout << '|' << endl;
  }
  cout << "============================" << endl;
}

void queens(int columns[], int col, int nqueens) {
  if (col == nqueens) {
    print_queue(columns, nqueens);
  } else {
    for (int row = 0; row < nqueens; row++)
      if (checkvalid(columns, col, row)) {
        columns[col] = row;
        queens(columns, col + 1, nqueens);
      }
  }
}

int main(void) {
  int nqueens = 10;
  int* columns = new int[nqueens];
  for (int i = 0; i < nqueens; i++)
    columns[nqueens] = -1;
  queens(columns, 0, nqueens); 
  return 0;
}
