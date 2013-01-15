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

void Matrix::rotate_clock() {
  vector<long> new_data;
  for (int c = 0; c < col; c++)
    for (int r = row - 1; r >= 0; r--) {
      size_t idx = r * col + c;
      new_data.push_back(data[idx]);
    }
  size_t replace = row;
  row = col;
  col = replace;
  data = new_data;
}

int main() {
  Matrix matrix(9, 9);
  cout << matrix;
  matrix.rotate_clock();
  cout << "Rotate clockwise" << endl;
  cout << matrix;

  //<< endl;
  return 0;
}
