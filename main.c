#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  FILE *input_file_ptr = NULL;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  char *keyword = NULL;
  bool case_sensitive = true;
  FILE *output_file_ptr = stdout;
  bool has_output_file = false;
  int c;
  char *output_path = NULL;

  while ((c = getopt(argc, argv, "io:")) != -1) {
    switch (c) {
    case 'i':
      case_sensitive = false;
      break;
    case 'o':
      has_output_file = true;
      output_path = optarg;
      break;
    case '?':
      printf("Wrong argument");
      exit(EXIT_FAILURE);
    }
  }

  if (has_output_file == true) {
    output_file_ptr = fopen(output_path, "a");
  }

  if (argc - optind < 2) {
    printf("Not enough arguments");
    exit(EXIT_FAILURE);
  }

  keyword = argv[optind];

  for (int i = 1; argc - optind - i > 0; i++) {
    FILE *input_file_ptr = fopen(argv[optind + i], "r");
    if (input_file_ptr == NULL) {
      exit(EXIT_FAILURE);
    }

    bool contains = false;
    while ((nread = getline(&line, &len, input_file_ptr)) != -1) {
      contains = false;
      if (case_sensitive == false && strcasestr(line, keyword) != NULL) {
        contains = true;
      }
      if (case_sensitive == true && strstr(line, keyword) != NULL) {
        contains = true;
      }

      if (contains == true) {
        fprintf(output_file_ptr, line);
      }

      line = NULL;
      free(line);
    }

    fclose(input_file_ptr);
    input_file_ptr = NULL;
  }
  fclose(output_file_ptr);
  exit(EXIT_SUCCESS);
}
