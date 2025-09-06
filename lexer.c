#include "lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_token(Lexer *lexer, Token type, char *val);
bool is_type_name(char *str);
char *read_alnum(char **ptr);

int lex(Lexer *lexer) {
  printf("lexing\n");
  while (*lexer->cur_tok) {
    switch (*lexer->cur_tok) {
    case ';':
      add_token(lexer, TOK_SEMICOL, NULL);
      lexer->cur_tok++;
      break;
    case '+':
      add_token(lexer, TOK_PLUS, NULL);
      lexer->cur_tok++;
      break;
    case '-':
      add_token(lexer, TOK_MINUS, NULL);
      lexer->cur_tok++;
      break;
    case '*':
      add_token(lexer, TOK_ASTERISK, NULL);
      lexer->cur_tok++;
      break;
    case '/':
      add_token(lexer, TOK_FSLASH, NULL);
      lexer->cur_tok++;
      break;
    case '=':
      add_token(lexer, TOK_EQ, NULL);
      lexer->cur_tok++;
      break;
    case '<':
      add_token(lexer, TOK_LBRAC, NULL);
      lexer->cur_tok++;
      break;
    case '>':
      add_token(lexer, TOK_RBRAC, NULL);
      lexer->cur_tok++;
      break;
    case '"':
      // start string
      lexer->cur_tok++;
      // non alphanumeric string values not allowed yet
      char *val = read_alnum(&lexer->cur_tok);
      add_token(lexer, TOK_STRING, val);
      lexer->cur_tok++; // skip last "
      break;
    default:
      if (isalpha(*lexer->cur_tok)) {
        char *val = read_alnum(&lexer->cur_tok);
        printf("VAL: %s\n", val);
        Token tok;
        if (is_type_name(val)) {
          tok = TOK_TYPE;
        } else {
          tok = TOK_ID;
        }
        add_token(lexer, tok, val);
      } else {
        lexer->cur_tok++;
      }
      break;
    }
  }

  printf("done lexing. token count: %zu\n", lexer->token_count);

  // Print tokens
  for (size_t i = 0; i < lexer->token_count; i++) {
    printf("%s: %s\n", token_to_string(lexer->tokens[i].type),
           lexer->tokens[i].val);
  }

  return 0;
}

// Reads a full alphanumeric string
// Advances input pointer to position after last char
char *read_alnum(char **ptr) {
  char *start = *ptr;
  while (isalnum(**ptr))
    (*ptr)++;
  size_t len = *ptr - start;
  char *val = malloc(len + 1); // extra for \0
  strncpy(val, start, len);
  val[len] = '\0';
  return val;
}

bool is_type_name(char *str) {
  return strcmp(str, "int") == 0 || strcmp(str, "str") == 0 ||
         strcmp(str, "fun") == 0;
}

char *token_to_string(Token token) {
  switch (token) {
  case TOK_SEMICOL:
    return "SEMICOL";
  case TOK_TYPE:
    return "TYPE";
  case TOK_ID:
    return "ID";
  case TOK_EQ:
    return "EQ";
  case TOK_NUMBER:
    return "NUMBER";
  case TOK_STRING:
    return "STRING";
  case TOK_FUN:
    return "FUN";
  case TOK_LBRAC:
    return "LBRAC";
  case TOK_RBRAC:
    return "RBRAC";
  case TOK_PLUS:
    return "PLUS";
  case TOK_MINUS:
    return "MINUS";
  case TOK_ASTERISK:
    return "ASTERISK";
  case TOK_FSLASH:
    return "FSLASH";
  case TOK_EOF:
    return "EOF";
  }
}

void add_token(Lexer *lexer, Token type, char *val) {

  if (lexer->token_count == lexer->token_cap) {
    size_t new_cap = (lexer->token_cap == 0) ? 4 : lexer->token_cap * 2;
    TokenData *new_toks = realloc(lexer->tokens, new_cap * sizeof(TokenData));
    if (!new_toks) {
      perror("realloc failed");
      exit(1);
    }
    lexer->tokens = new_toks;
    lexer->token_cap = new_cap;
  }

  TokenData new_token = {.type = type, .val = val};

  lexer->tokens[lexer->token_count++] = new_token;
}
