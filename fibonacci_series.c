#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int fibonacci(int n, int* array) {
  if (n < 2)
    return array[n];   
  else {
    if (array[n - 1] < 0)
      array[n - 1] = fibonacci(n - 1, array);
    if (array[n - 2] < 0)
      array[n - 2] = fibonacci(n - 2, array);
    return array[n - 1] + array[n - 2];
  }
}

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  char *token;
  int n = 0, counter = 0;
  int array[1024];
  for (counter = 0; counter < 1024; counter ++) {
    array[counter] = -1;
  }
  array[0] = 0;
  array[1] = 1;
  while (fgets(line, 1024, fp)) {
    n = atoi(line);
    printf("%d\n", fibonacci(n, array));
  }
  fclose(fp);
}
