#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
  char line[1024]; 
  int line_length = 0, counter = 0;
  FILE *fp = fopen(argv[1], "r"); 
  while (fgets(line, 1024, fp)) {
    if (line[0] == '\n') {
      continue;
    }
    line_length = strlen(line); 
    for (counter = 0; counter < line_length; counter ++) {
      if (line[counter] <= 'Z' && line[counter] >= 'A') 
        line[counter] += 32;
    } 
    printf("%s", line);
  }
  return 0;
}
