#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  char *token;
  int sum = 0;
  while (fgets(line, 1024, fp)) {
    sum += atoi(line);
  }
  printf("%d\n", sum);
  fclose(fp);
}
