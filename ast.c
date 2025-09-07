#include "ast.h"
#include "lexer.h"
#include <stdio.h>

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
  }
}
