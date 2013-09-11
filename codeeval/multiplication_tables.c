#include <stdio.h>

int main() {
  int num_x = 0, num_y = 0;
  for (num_x = 1; num_x <= 12; num_x ++) {
    for (num_y = 1; num_y <= 12; num_y ++) {
      printf("%4d", num_x * num_y); 
    }
    printf("\n");
  } 
  return 0;
}
