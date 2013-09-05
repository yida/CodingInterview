#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "rb");
  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);
  printf("%d\n", size);
  fclose(fp); 
  return 0;
}
