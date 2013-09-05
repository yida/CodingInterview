#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge_sort(float* array, int p, int r) {
  float temp[1024];
  if (r > p) {
    merge_sort(array, p, (p + r) / 2);
    merge_sort(array, (p + r) / 2 + 1, r);
    int index = 0;
    int index_p = p;
    int index_r = (p + r) / 2 + 1;
    while ((index_p <= (p + r) / 2) && index_r <= r) {
      if (array[index_p] < array[index_r]) {
        temp[index ++] = array[index_p ++];
      } else {
        temp[index ++] = array[index_r ++];
      }
    }
    while (index_p <= (p + r) / 2)
      temp[index ++] = array[index_p ++]; 
    while (index_r <= r)
      temp[index ++] = array[index_r ++];
    int counter = 0;
    for (counter = 0; counter < index; counter ++) {
      array[p + counter] = temp[counter];
    }
  }
}

void sort(float *array, int size) {
  merge_sort(array, 0, size - 1); 
}

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  char *number_token;
  float array[1024];
  int array_size = 0, counter = 0;
  while (fgets(line, 1024, fp)) {
    if (line[0] == '\n') continue; 
    number_token = strtok(line, " ");
    array_size = 0;
    while (number_token) {
      array[array_size ++] = (float)atof(number_token); 
      number_token = strtok(NULL, " ");
    }
    sort(array, array_size);
    for (counter = 0; counter < array_size; counter ++)
      printf("%.3f ", array[counter]);
    printf("\n");
  }
  fclose(fp); 
}
