#include <stdio.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024]; 
  char *number_token;
  int n = 0, m = 0;
  int divisor = 0;
  while (fgets(line, 1024, fp)) {
    n = strtol(line, &number_token, 10);
    m = strtol(number_token + 1, &number_token, 10); 
    divisor = 1; 
    while (n >= (m * divisor)) {
      divisor ++;
    }
    printf("%d\n", n - (divisor - 1) * m);
  }
  return 0;
}
