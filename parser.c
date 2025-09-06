#include "parser.h"
#include "lexer.h"
#include <stdio.h>

int parse(Parser *parser) {
  while (parser->curr_tok->type != TOK_EOF) {

    switch (parser->curr_tok->type) {
    case TOK_TYPE:
      // parse variable declaration
      printf("variable declaration\n");
      while (parser->curr_tok->type != TOK_SEMICOL) {
        parser->curr_tok++;
      }
      parser->curr_tok++;
      break;
    case TOK_FUN:
      // parse function declaration
      printf("function declaration\n");
      while (parser->curr_tok->type != TOK_SEMICOL)
        parser->curr_tok++;
      parser->curr_tok++;
      break;
    case TOK_ID:
      // parse expression statement (call)
      printf("expression statement\n");
      while (parser->curr_tok->type != TOK_SEMICOL)
        parser->curr_tok++;
      parser->curr_tok++;
      break;
    default:
      // invalid start of statement
      printf("invalid start of statement\n");
      return 1;
    }
  }
  return 0;
}
