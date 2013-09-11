#include <stdio.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024]; 
  char *number_token;
  int n = 0, p1 = 0, p2 = 0;
  int counter = 0;
  int bits[32];
  while (fgets(line, 1024, fp)) {
    n = strtol(line, &number_token, 10);
    p1 = strtol(number_token + 1, &number_token, 10); 
    p2 = strtol(number_token + 1, &number_token, 10); 
    counter = sizeof(int) * 8;
    while (counter > 0) {
      bits[sizeof(int) * 8 - counter] = n & 0x01;
      n = n >> 1;
      counter --;
    }         
    if (bits[p1 - 1] == bits[p2 - 1])
      printf("true\n");
    else
      printf("false\n");
  }
  return 0;
}
