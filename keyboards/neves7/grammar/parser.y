%include {
#include "parser.h"
#include <math.h>
struct Context {
    double result;
    char error;
};
}
%left ADD SUB.
%left MUL DIV.
%left POW.
%token_type { double }
%extra_argument { struct Context * context }

formula ::= expr(A).
    { context->result = A; }

expr(A) ::= SUB expr(B).
    { A = -B; }

expr(A) ::= expr(B) ADD expr(C).
    { A = B + C; }

expr(A) ::= expr(B) SUB expr(C).
    { A = B - C; }

expr(A) ::= expr(B) MUL expr(C).
    { A = B * C; }

expr(A) ::= expr(B) POW expr(C).
    { A = pow(B,C); }

expr(A) ::= expr(B) DIV expr(C).
    { A = B / C; }

expr(A) ::= LPAREN expr(B) RPAREN.
    { A = B; }

expr(A) ::= LITERAL(B).
    { A = B; }

%parse_failure
    { context->error = 1; }
