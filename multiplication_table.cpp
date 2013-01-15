#include <iostream>

using namespace std;

int multiplication_table(int Max) {
    for (int row = 1; row <= Max; row++) {
        for (int col = 1; col <= Max; col++) {
            std::cout << col * row << " ";
        }
        std::cout << std::endl;
    }
  return 0;
}

int main() {
  int Max = 12;
  multiplication_table(Max);
  return 0;
}
