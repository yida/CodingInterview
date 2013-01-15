#include <iostream>

const maxN = 100;
long fibnum[maxN] = {0};

long fib(int n) {
  if (n <= 2) 
    return 1;
  return fib(n - 1) + fib(n - 2);
}

int main() {
  int n = 10;
  std::cout << fib(n) << std::endl;
}
