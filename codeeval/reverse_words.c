#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  FILE *fp = fopen(argv[1], "r");
  char line[1024];
  char word_list[1024][1024];
  int word_counter = 0;
  char *word;
  int line_len = 0;
  int counter = 0;
  while (fgets(line, 1024, fp)) {
    word = strtok(line, " ");
    word_counter = 0;
    while (word) {
      strcpy(word_list[word_counter], word);
      line_len = strlen(word_list[word_counter]);
      if (word_list[word_counter][line_len - 1] == '\n') 
        word_list[word_counter][line_len - 1] = '\0';
      word_counter ++; 
      word = strtok(NULL, " ");
    } 
    for (counter = word_counter - 1; counter >= 0; counter --)
      printf("%s ", word_list[counter]);
    printf("\n");
  }
  fclose(fp);
  return 0;
}
