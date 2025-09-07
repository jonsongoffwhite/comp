#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

Expr *parse_expr(TokenData **curr, float min_bp);
Expr *parse_atom(TokenData token);

Prog *parse(Parser *parser) {
  Prog *prog = malloc(sizeof(Prog));
  *prog = (Prog){.stmts = NULL, .stmt_count = 0, .stmt_cap = 0};

  while (parser->curr_tok->type != TOK_EOF) {

    switch (parser->curr_tok->type) {
    case TOK_TYPE: {
      // parse variable declaration
      char *type = parser->curr_tok->val;
      char *id = (++parser->curr_tok)->val;

      if ((++parser->curr_tok)->type != TOK_EQ) {
        printf("no equals '=' in variable declaration");
        return NULL;
      }

      // Rest goes to exp parser
      ++parser->curr_tok;
      TokenData **start_ptr = &parser->curr_tok;
      Expr *expr = parse_expr(start_ptr, 0.0f);
      print_expr(expr);
      printf("\n");
      // Advance past semi colon
      parser->curr_tok++;

      Stmt *stmt = malloc(sizeof(Stmt));
      *stmt = (Stmt){.type = STMT_VAR_DECL,
                     .var_decl =
                         (VarDeclStmt){.type = type, .id = id, .value = expr}};
      add_stmt(prog, stmt);
      break;
    }
    case TOK_FUN: {
      // parse function declaration
      printf("function declaration\n");
      parser->curr_tok++;
      char *id = (++parser->curr_tok->val);

      if ((++parser->curr_tok)->type != TOK_LBRAC) {
        printf("no '<' in function declaration\n");
        printf("got: %s\n", token_to_string(parser->curr_tok->type));
        return NULL;
      }

      char *param_type = ((++parser->curr_tok)->val);
      char *param_id = ((++parser->curr_tok)->val);

      if ((++parser->curr_tok)->type != TOK_RBRAC) {
        printf("no '>' in function declaration\n");
        printf("got: %s\n", token_to_string(parser->curr_tok->type));
        return NULL;
      }

      if ((++parser->curr_tok)->type != TOK_EQ) {
        printf("no '=' in function declaration\n");
        return NULL;
      }

      parser->curr_tok++;
      TokenData **start_ptr = &parser->curr_tok;
      Expr *expr = parse_expr(start_ptr, 0.0f);

      Stmt *stmt = malloc(sizeof(Stmt));
      *stmt = (Stmt){.type = STMT_FUN_DECL,
                     .fun_decl = (FunDeclStmt){.id = id,
                                               .param_type = param_type,
                                               .param_id = param_id,
                                               .value = expr}};
      add_stmt(prog, stmt);

      print_expr(expr);
      printf("\n");

      parser->curr_tok++;
      break;
    }
    case TOK_ID: {
      // TODO: Handle other expr stmts than raw fun call
      printf("expression statement\n");
      char *id = (parser->curr_tok)->val;
      printf("id: %s\n", id);
      parser->curr_tok++;
      TokenData **start_ptr = &parser->curr_tok;
      Expr *expr = parse_expr(start_ptr, 0.0f);

      Expr *fun_call = malloc(sizeof(Expr));
      *fun_call = (Expr){.type = EXPR_FUN_CALL,
                         .call = (FunCallExpr){.fun_id = id, .arg = expr}};
      printf("full fun expr\n");
      print_expr(fun_call);
      printf("\n");

      Stmt *stmt = malloc(sizeof(Stmt));
      *stmt = (Stmt){.type = STMT_EXPR, .expr = (ExprStmt){.value = fun_call}};

      add_stmt(prog, stmt);

      parser->curr_tok++;
      break;
    }
    default:
      // invalid start of statement
      printf("invalid start of statement\n");
      return NULL;
    }
  }
  return prog;
}

Expr *parse_expr(TokenData **curr, float min_bp) {
  Expr *lhs = parse_atom(**curr);
  (*curr)++;

  for (;;) {
    Token op = (*curr)->type;
    if (op == TOK_SEMICOL)
      break;
    BindPwr bp = op_bind_power(op);
    if (bp.lhs < min_bp) {
      break;
    }
    (*curr)++;
    Expr *rhs = parse_expr(curr, bp.rhs);

    // Create binary
    Expr *expr = malloc(sizeof(Expr));
    *expr = (Expr){.type = EXPR_BINARY,
                   .binary = (BinaryExpr){.op = op, .left = lhs, .right = rhs}};
    lhs = expr;
  }

  print_expr(lhs);
  printf("\n");
  return lhs;
}

Expr *parse_atom(TokenData token) {
  // TODO: Handle error when atom is expected but none there
  // TODO: Make function call a valid atom? (can contain expressions within)
  Expr *expr = malloc(sizeof(Expr));
  switch (token.type) {
  case TOK_STRING:
    *expr = (Expr){.type = EXPR_STRING_LITERAL,
                   .str_lit = (StringLiteralExpr){.val = token.val}};
    break;
  case TOK_NUMBER:
    *expr = (Expr){.type = EXPR_INT_LITERAL,
                   .int_lit = (IntLiteralExpr){.val = token.val}};
    break;
  case TOK_ID:
    *expr = (Expr){.type = EXPR_ID, .id = (IdExpr){.id = token.val}};
    break;
  default:
    // printf("unexpected atom: %s\n", token_to_string(token.type));
    free(expr);
    return NULL;
  }
  return expr;
}

BindPwr op_bind_power(Token tok) {
  float lhs, rhs;
  switch (tok) {
  case TOK_PLUS:
  case TOK_MINUS:
    lhs = 1.0;
    rhs = 1.1;
    break;
  case TOK_ASTERISK:
  case TOK_FSLASH:
    lhs = 2.0;
    rhs = 2.1;
    break;
  default:
    lhs = 0.0f;
    rhs = 0.0f;
    break;
  };
  return (BindPwr){.lhs = lhs, .rhs = rhs};
}
