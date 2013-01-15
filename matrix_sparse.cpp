#include <iostream>
#include <map>

using namespace std;

class sMatrix {
  private:
    unsigned int row;
    unsigned int col;
    map<unsigned int, double> data;

  public:
    sMatrix(unsigned int r, unsigned int c)
      :row(r), col(c) {}
    ~sMatrix() {}
    double& operator() (unsigned int r, unsigned int c) {
      unsigned int idx = r * row + c;
      return data[idx];
    }
    friend ostream& operator << (ostream &out, sMatrix &matrix) {
      unsigned int idx = 0;
      for (unsigned int i = 0; i < matrix.row; i++) {
        for (unsigned int j = 0; j < matrix.col; j++) {
          idx = i * matrix.row + j;
          out << matrix.data[idx] << ' ';
        }
        out << endl;
      }
      return out;
    }
};

int main() {
  sMatrix mat(5,6);
  mat(0,0) = 3.45;
  mat(1,2) = 1.453;
  mat(4,5) = 0.456;

  cout << mat << endl;
  return 0;
}
