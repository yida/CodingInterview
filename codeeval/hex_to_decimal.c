#include <stdio.h>
#include <string.h>
#include <math.h>

int hex_mapping(char hex_char) {
  if (hex_char >= '0' && hex_char <= '9') return hex_char - 48;
  else if (hex_char <= 'f' && hex_char >= 'a') {
    switch (hex_char) {
      case 'a':
        return 10;
      case 'b':
        return 11;
      case 'c':
        return 12;
      case 'd':
        return 13;
      case 'e':
        return 14;
      case 'f':
        return 15;
      default:
        return 0;
    }
  } else
    return 0;
}

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  int line_len = 0;
  int counter = 0;
  int sum = 0;
  int digit_order = 0;
  int decimal = 0;
  while (fgets(line, 1024, fp)) {
    line_len = strlen(line); 
    decimal = 0;
    for (counter = 0; counter < line_len - 1; counter ++) {
      digit_order = line_len - counter - 2;
      decimal += hex_mapping(line[counter]) * (int)pow(16, digit_order);
    }
    printf("%d\n", decimal);
  }
  fclose(fp);
  return 0;
}
