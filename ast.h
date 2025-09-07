#ifndef AST_H
#define AST_H

#include "lexer.h"
typedef struct stmt Stmt;
typedef struct expr Expr;

typedef enum { STMT_VAR_DECL, STMT_FUN_DECL, STMT_EXPR } StmtType;

typedef enum {
  EXPR_INT_LITERAL,
  EXPR_STRING_LITERAL,
  EXPR_BINARY,
  EXPR_ID
} ExprType;

typedef struct {
  char *type; // TODO: Enum?
  char *id;
  Expr *value;
} VarDeclStmt;

// Better way to model list of params?
// TODO: Allow >1 params
// TODO: Allow multiple statements.
typedef struct {
  char *id;
  char *param_type;
  char *param_id;
  Expr *value;
} FunDeclStmt;

typedef struct {
  Expr *value;
} ExprStmt;

struct stmt {
  StmtType type;
  union {
    VarDeclStmt var_decl;
    FunDeclStmt fun_decl;
    ExprStmt expr;
  };
};

//

typedef struct {
  char *val;
} IntLiteralExpr;

typedef struct {
  char *val;
} StringLiteralExpr;

typedef struct {
  Token op;
  Expr *left;
  Expr *right;
} BinaryExpr;

typedef struct {
  char *id;
} IdExpr;

struct expr {
  ExprType type;
  union {
    IntLiteralExpr int_lit;
    StringLiteralExpr str_lit;
    BinaryExpr binary;
    IdExpr id;
  };
};

void print_expr(Expr *expr);

#endif // !AST_H
