#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  char string[1024];
  char letter = ' ';
  int line_len = 0, counter = 0;
  while (fgets(line, 1024, fp)) {
    line_len = strlen(line);
    while (line[counter ++] != ',') {}
    letter = line[counter];
    line[counter - 1] = '\0';
    counter = 0;
    while (line[counter ++] != letter) {}
    printf("%d\n", counter - 1);
  } 
  fclose(fp);
  return 0;
}
