#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  int line_len = 0;
  int counter = 0;
  int sum = 0;
  while (fgets(line, 1024, fp)) {
    line_len = strlen(line); 
    sum = 0;
    for (counter = 0; counter < line_len - 1; counter ++) {
      sum += line[counter] - 48;
    } 
    printf("%d\n", sum);
  }
  fclose(fp);
  return 0;
}
