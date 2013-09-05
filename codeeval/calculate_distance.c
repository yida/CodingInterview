#include <stdio.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
  while (fgets(line, 1024, fp)) {
    sscanf(line, "(%d, %d) (%d, %d)\n", &x1, &y1, &x2, &y2);
    printf("%.0f\n", sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
  }
  return 0;
}
