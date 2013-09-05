#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  char *token;
  int array[1024]; 
  int array_size = 0, counter = 0;
  int num = 0;
  while (fgets(line, 1024, fp)) {
    array_size = 0;
    token = strtok(line, ",");
    while (token) {
      array[array_size ++] = atoi(token); 
      token = strtok(NULL, ",");
    }
    num = array[0];
    printf("%d", array[0]);
    for (counter = 1; counter < array_size; counter ++) {
      if (array[counter] != num) {
        printf(",%d", array[counter]);
        num = array[counter];
      }
    }
    printf("\n");
  }
  fclose(fp);
}
