#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_first_digit(char *buffer, size_t size);
int find_last_digit(char *buffer, size_t size);
void printline(char *line, size_t size);

int main(int argc, char **argv) {
  int sum    = 0;
  int nlines = 0;
  FILE *fd;
  char *line  = NULL;
  size_t size = 0;
  ssize_t read;

  fd = fopen("./input.txt", "r");
  if (fd == NULL)
    exit(EXIT_FAILURE);

  while ((read = getline(&line, &size, fd)) != -1) {
    nlines++;
    char code[3]    = {0};
    int index_first = find_first_digit(line, size);
    int index_last  = find_last_digit(line, size);
    code[0]         = line[index_first];
    code[1]         = line[index_last];

    printline(line, size);
    printf("%s\n", code);
    sum += atoi(code);
    memset(line, 0, size);
  }

  printf("sum: %d, from lines: %d\n", sum, nlines);

  fclose(fd);
  if (line)
    free(line);

  return 0;
}

int find_first_digit(char *buffer, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (isdigit(buffer[i])) {
      return i;
    }
  }
  return -1;
}

int find_last_digit(char *buffer, size_t size) {
  for (size_t i = size - 1; i >= 0; i--) {
    if (isdigit(buffer[i])) {
      return i;
    }
  }
  return -1;
}

void printline(char *line, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%c", line[i]);
  }
}
