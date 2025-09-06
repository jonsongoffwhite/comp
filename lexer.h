#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

typedef enum {
  TOK_TYPE,
  TOK_ID,
  TOK_EQ,
  TOK_NUMBER,
  TOK_STRING,
  TOK_FUN,
  TOK_LBRAC,
  TOK_RBRAC,
  TOK_PLUS,
  TOK_MINUS,
  TOK_ASTERISK,
  TOK_FSLASH,
  TOK_SEMICOL,
  TOK_EOF
} Token;

typedef struct {
  Token type;
  char *val;
} TokenData;

typedef struct {
  char *start_tok;
  char *cur_tok;
  TokenData *tokens;
  size_t token_count;
  size_t token_cap;
} Lexer;

int lex(Lexer *lexer);

char *token_to_string(Token token);

#endif
