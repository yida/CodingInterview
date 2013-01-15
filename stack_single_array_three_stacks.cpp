#include <iostream>

using namespace std;

class TriStack {
  private:
    size_t length;
    size_t head1;
    size_t head2;
    size_t head3;
    size_t size1;
    size_t size2;
    size_t size3;
    int* data;
  public:
    TriStack(size_t len)
      :length(len), size1(0), size2(0), size3(0),
        head1(0), head2(length - 1), head3(length / 2) {
        data = new int[length];
        for (size_t cnt = 0; cnt < length; cnt++)
          data[cnt] = 0;
     }
    TriStack() { delete [] data; }
    friend ostream& operator<< (ostream& out, TriStack& stack);

    void shift_stack3(int dir) {
      if (dir < 0) {
        cout << "shift left" << endl;
        for (size_t cnt = head3; cnt < (head3 + size3); cnt++)
          data[cnt - 1] = data[cnt];
        head3 --;
      } else if (dir > 0) {
        cout << "shift right" << endl;
        for (size_t cnt = (head3 + size3); cnt > head3; cnt--)
          data[cnt] = data[cnt - 1];
        head3 ++;
      }
    }
    void push(size_t nth, int input) {
      if ((size1 + size2 + size3 + 1) > length) {
        cout << "Stack Full" << endl;
        return;
      }
      switch (nth) {
        case 1:
          cout << "push stack 1" << endl;
          if (size1 == head3) {
            shift_stack3(1);
            data[size1++] = input;
            // move stack 3 right
          } else {
            data[size1++] = input;
          }
          break;
        case 2:
          cout << "push stack 2" << endl;
          if ((head3 + size3 - 1) == (head2 - size2)) {
            // move stack 3 left
            shift_stack3(-1);
            data[head2 - size2] = input;
          } else {
            data[head2 - size2] = input;
            size2 ++;
          }
          break;
        case 3:
          cout << "push stack 3" << endl;
          if ((head3 + size3) == (head2 - size2 + 1)) {
            // move stack 3 left
            shift_stack3(-1);
            data[head3 + size3] = input;
          } else {
            data[head3 + size3] = input;
            size3 ++;
          }
          break;
        default:
          cout << "must be 1 2 or 3" << endl;
          break;
      }
    }
    int pop(size_t nth) {
      switch (nth) {
        case 1:
          if (size1 > 0) {
            int out = data[size1 - 1];
            size1 --;
            return out;
          }
          break;
        case 2:
          if (size2 > 0) {
            int out = data[head2 - size2 + 1];
            size2 --;
            return out;
          }
          break;
        case 3:
          if (size3 > 0) {
            int out = data[head3 + size3 - 1];
            size3 --;
            return out;
          }
          break;
        default:
          break;
      }
    }
};

ostream& operator<< (ostream& out, TriStack& stack) {
  for (size_t cnt = 0; cnt < stack.length; cnt++) 
    out << stack.data[cnt] << ' ';
  out << endl;
  return out;
}

int main() {
  TriStack stack(6);
  cout << stack << endl;
  stack.push(1, 457);
  cout << stack << endl;
  stack.push(2, 123);
  cout << stack << endl;
  stack.push(3, 984);
  cout << stack << endl;
  stack.push(1, 84);
  cout << stack << endl;
  stack.push(1, 4);
  cout << stack << endl;
  stack.push(1, 109);
  cout << stack << endl;


  return 0;
}
