#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef struct {
  TokenData *tokens;
  TokenData *curr_tok;
} Parser;

int parse(Parser *parser);

#endif // !PARSER_H
