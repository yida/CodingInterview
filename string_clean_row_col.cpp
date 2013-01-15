#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <climits>
#include <iomanip>
#include <queue>

using namespace std;

class Matrix {
  private:
    size_t row;
    size_t col;
    vector<long> data;
  public:
    Matrix(size_t r, size_t c):row(r), col(c) {
      for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++) {
          size_t idx = i * col + j;
          data.push_back(rand()%LONG_MAX);
        }
    }
    ~Matrix() {}
    long& operator()(size_t r, size_t c) {
      size_t idx = r * col + c;
      return data[idx];
    }
    friend ostream& operator << (ostream &out, Matrix &mat);
    void rotate_clock();
    void clean_row_col();
};
    
ostream& operator << (ostream &out, Matrix &mat) {
  out << "The Matrix:" << endl;
  for (size_t i = 0; i < mat.row; i++) {
    for (size_t j = 0; j < mat.col; j++) {
      out << setw(10) << mat(i, j) << ' ';
    }
    out << endl;
  }
}

void Matrix::clean_row_col() {
  queue<size_t> zeros_row;
  queue<size_t> zeros_col;
  for (size_t i = 0; i < row; i++) {
    for (size_t j = 0; j < col; j++) {
      size_t idx = i * col + j;
      if (data[idx] == 0) {
        zeros_row.push(i);
        zeros_col.push(j);
      }
    }
  }
  while (!zeros_row.empty()) {
    size_t r = zeros_row.front();
    size_t c = zeros_col.front();
    for (size_t cnt = 0; cnt < row; cnt++) {
      size_t id = cnt * col + c;
      data[id] = 0;
    }
    for (size_t cnt = 0; cnt < col; cnt++) {
      size_t id = r * col + cnt;
      data[id] = 0;
    }

    zeros_row.pop();
    zeros_col.pop();
  }
}


int main() {
  Matrix matrix(9, 9);
  cout << matrix;

  matrix(3, 4) = 0;
  matrix(1, 1) = 0;
  matrix.clean_row_col();
  cout << matrix;
  //<< endl;
  return 0;
}
