#include <iostream>
#include <map>

using namespace std;

class sMatrix {
  public:
    sMatrix(unsigned int row, unsigned int col) {
      r = row;
      c = col;
    }
    ~sMatrix() {}

    double& operator()(unsigned int row, unsigned int col) {
      unsigned int idx = row * r + col;
      return data[idx];
    }
    double& operator()(unsigned int idx) {
      return data[idx];
    }

    friend ostream& operator << (ostream &out, sMatrix &matrix) {
      for (unsigned int i = 0; i < matrix.r; i++) {
        for (unsigned int j = 0; j < matrix.c; j++) {
         unsigned int idx = i * matrix.r + j;
         out << matrix.data[idx] << ' ';
        }
        out << endl;
      }
      return out;
    }


  private:
    unsigned int r;
    unsigned int c;
    map<unsigned int, double> data;
};



int main() {
  sMatrix mat(6, 7);
  mat(1,3) = 4.3435;
  mat(0,0) = 3.456;
  mat(3,2) = 1.345;

  cout << mat << endl;
  return 0;
}
