#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIGITS_NR 10
#define MAX_DIGIT_LEN

const char *g_digit_strings[DIGITS_NR] = {"zero",  "one",  "two", "three",
                                          "four",  "five", "six", "seven",
                                          "eight", "nine"};

int find_first_digit(char *buffer, size_t size);
int find_last_digit(char *buffer, size_t size);

bool contains(char *buffer, const char *substr);
bool contains_nr_string(char *buffer);

char map_str_int(const char *nr_string);

// void replace_string_w_digits(char *buffer, size_t size);
void replace_string_w_digits_start(char *buffer, size_t size);
void replace_string_w_digits_end(char *buffer, size_t size);

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
    char linecopy[size];
    strncpy(linecopy, line, size);

    printline(line, size);
    replace_string_w_digits_start(line, size);
    printline(line, size);
    printline(linecopy, size);
    replace_string_w_digits_end(linecopy, size);
    printline(linecopy, size);

    int index_first = find_first_digit(line, size);
    int index_last  = find_last_digit(linecopy, size);

    char code[3] = {0};
    code[0]      = line[index_first];
    code[1]      = linecopy[index_last];

    printline(line, size);

    // printf("%d\n", contains_nr_string(line, &i1));
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

int find_first_digitstr(char *buffer, size_t size) {
  bool contains_nr_str = false;
  for (int i = 0; i <= DIGITS_NR; i++) {
    if (contains(buffer, g_digit_strings[i])) {
      contains_nr_str = true;
      break;
    }
  }

  if (!contains_nr_str) {
    return -1;
  }
  return -1;
}

bool contains(char *buffer, const char *substr) {
  return (strstr(buffer, substr) != NULL);
}

bool contains_nr_string(char *buffer) {
  for (int i = 0; i < DIGITS_NR; i++) {
    if (contains(buffer, g_digit_strings[i]))
      return true;
  }
  return false;
}

char map_str_int(const char *nr_string) {
  for (int i = 0; i <= DIGITS_NR; i++) {
    if (strcmp(nr_string, g_digit_strings[i]) == 0) {
      return i + '0';
    }
  }
  return -1;
}

void replace_string_w_digits_start(char *buffer, size_t size) {
  bool done        = false;
  size_t substrlen = size;
  for (size_t i = 0; i < size && !done; i++) {
    char substr[size];
    strncpy(substr, &(buffer[i]), substrlen--);

    for (size_t index_digit = 0; index_digit < DIGITS_NR; index_digit++) {
      size_t d_len = strlen(g_digit_strings[index_digit]);
      if (strncmp(substr, g_digit_strings[index_digit], d_len) == 0) {
        printf("Start needs replacing: %s\n", g_digit_strings[index_digit]);

        char digit = map_str_int(g_digit_strings[index_digit]);
        for (size_t j = 0; j < d_len; j++) {
          buffer[i + j] = digit;
        }
        done = true;
        break;
      }
    }
  }
}

void replace_string_w_digits_end(char *buffer, size_t size) {
  bool done        = false;
  size_t substrlen = 2; // we can skip first few iterations, since no digit has
                        // only 1 or 2 letters

  // Same goes for the -3 here
  for (size_t i = size - 3; i > 0 && !done; i--) {
    char substr[size];
    strncpy(substr, &(buffer[i]), substrlen++);

    for (size_t index_digit = 0; index_digit < DIGITS_NR; index_digit++) {
      size_t d_len = strlen(g_digit_strings[index_digit]);
      if (strncmp(substr, g_digit_strings[index_digit], d_len) == 0) {
        printf("End needs replacing: %s\n", g_digit_strings[index_digit]);

        char digit = map_str_int(g_digit_strings[index_digit]);
        for (size_t j = 0; j < d_len; j++) {
          buffer[i + j] = digit;
        }
        done = true;
        break;
      }
    }
  }
}

void replace_string_w_digits2(char *buffer, size_t size) {
  while (contains_nr_string(buffer)) {
    for (int i = 0; i < DIGITS_NR; i++) {
      char *substr = strstr(buffer, g_digit_strings[i]);
      if (!(substr == NULL)) {
        char digit = map_str_int(g_digit_strings[i]);
        size_t len = strlen(g_digit_strings[i]);
        for (size_t j = 0; j < len; j++) {
          substr[j] = digit;
        }
      }
    }
  }
}

void printline(char *line, size_t size) {
  for (size_t i = 0; i < size; i++) {
    printf("%c", line[i]);
  }
}
