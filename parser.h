#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
  TokenData *tokens;
  TokenData *curr_tok;
} Parser;

typedef struct {
  float lhs;
  float rhs;
} BindPwr;

int parse(Parser *parser);

BindPwr op_bind_power(Token tok);

#endif // !PARSER_H
