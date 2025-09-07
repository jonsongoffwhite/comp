#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

// TODO: Write expr_to_string using snprinf and dynamic allocation
void print_expr(Expr *expr) {

  switch (expr->type) {
  case EXPR_STRING_LITERAL:
    printf("\"%s\"", expr->str_lit.val);
    break;
  case EXPR_INT_LITERAL:
    printf("%s", expr->int_lit.val);
    break;
  case EXPR_BINARY:
    printf("(%s ", token_to_string(expr->binary.op));
    print_expr(expr->binary.left);
    printf(" ");
    print_expr(expr->binary.right);
    printf(")");
    break;
  case EXPR_ID:
    printf("%s", expr->id.id);
    break;
  case EXPR_FUN_CALL:
    printf("%s(", expr->call.fun_id);
    print_expr(expr->call.arg);
    printf(")");
    break;
  }
}

void add_stmt(Prog *prog, Stmt *stmt) {
  if (prog->stmt_count == prog->stmt_cap) {
    size_t new_cap = (prog->stmt_cap == 0) ? 4 : prog->stmt_cap * 2;
    Stmt **new_stmts = realloc(prog->stmts, new_cap * sizeof(Stmt *));
    if (!new_stmts) {
      perror("realloc failed");
      exit(1);
    }
    prog->stmts = new_stmts;
    prog->stmt_cap = new_cap;
  }
  prog->stmts[prog->stmt_count++] = stmt;
};
