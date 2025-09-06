#ifndef AST_H
#define AST_H

typedef struct Stmt stmt;
typedef struct Expr expr;

typedef enum { STMT_VAR_DECL, STMT_FUN_DECL, STMT_EXPR } StmtType;

typedef enum {
  EXPR_INT_LITERAL,
  EXPR_STRING_LITERAL,
  EXPR_BINARY,
  EXPR_ID
} ExprType;

#endif // !AST_H
