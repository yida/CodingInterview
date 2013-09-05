#include <stdio.h>
#include <math.h>

int main() {
  int test_number = 1000;
  int counter = test_number;
  char number_string[5];
  int string_index = 0;
  int is_palidrome = 0, is_prime = 0;
  int p = 0, r = 0;
  for (; counter > 0; counter --) {
    string_index = 0; 
    test_number = counter;
    while (test_number) {
      number_string[string_index ++] = test_number % 10 + 48;
      test_number /= 10;
    }
    number_string[string_index] = 0;
    is_palidrome = 1; 
    p = 0;
    r = string_index - 1; 
    while (p < r) {
      if (number_string[p] != number_string[r]) {
        is_palidrome = 0;
        break;
      }
      p ++;
      r --;
    }
    is_prime = 1;
    for (p = 2; p < floor(sqrt(counter)); p ++)
      if (counter % p == 0) {
        is_prime = 0;
        break;
      }
    if (is_palidrome && is_prime) {
      printf("%d\n", counter);
      break;
    }
  }
  return 0;
}
