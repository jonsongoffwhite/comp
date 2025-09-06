#include "lexer.h"
#include "read.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *data = read_file("test.luk");
  printf("begin\n");
  if (!data) {
    perror("Error reading data");
    free(data);
    return 1;
  }

  Lexer lexer = {
      .cur_tok = data, .start_tok = data, .tokens = NULL, .token_count = 0};

  lex(&lexer);

  free(data);
  return 0;
}
