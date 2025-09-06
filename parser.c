#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include <stdio.h>

Expr *parse_exp(TokenData *start);

int parse(Parser *parser) {
  while (parser->curr_tok->type != TOK_EOF) {

    switch (parser->curr_tok->type) {
    case TOK_TYPE:
      // parse variable declaration
      printf("variable declaration\n");
      char *type = parser->curr_tok->val;
      char *id = (++parser->curr_tok)->val;

      if ((++parser->curr_tok)->type != TOK_EQ) {
        printf("no equals '=' in variable declaration");
        return 1;
      }

      // Rest goes to exp parser
      parse_exp(++parser->curr_tok);

      // TODO: evaluate rest as expression

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

Expr *parse_exp(TokenData *start) {
  while (start->type != TOK_SEMICOL) {
    printf("parse exp tok: %s: %s\n", token_to_string(start->type), start->val);
    start++;
  }
  return NULL;
}
