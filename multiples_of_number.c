#include <stdio.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024]; 
  char *number_token;
  int x = 0, n = 0;
  while (fgets(line, 1024, fp)) {
    x = strtol(line, &number_token, 10);
    n = strtol(number_token + 1, &number_token, 0); 
    int multiplier = 2;
    while (n * (multiplier ++) < x);
    printf("%d\n", n * (multiplier - 1));
  }
  return 0;
}
