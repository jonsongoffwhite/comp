#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"

typedef struct {
  TokenData *tokens;
  TokenData *curr_tok;
} Parser;

typedef struct {
  float lhs;
  float rhs;
} BindPwr;

Prog *parse(Parser *parser);

BindPwr op_bind_power(Token tok);

#endif // !PARSER_H
