%parse-param {YYSTYPE *calc_result}
%{
  #define YYSTYPE double
  int yyerror (YYSTYPE *calc_result, char const *s);
  extern int yylex (void);
  int yy_scan_string(char const *s);
  void yylex_destroy(void);
%}
%token  PLS MNS
%token  MUL DIV
%token  NWL EQL
%token  NUM
%token  LFT RIT
%left   PLS MNS
%left   MUL DIV

%%
Seq:    /* empty */
|       Seq Line
Exp:    NUM             { $$ = $1; };
Exp:    Exp PLS Exp     { $$ = $1 + $3; };
Exp:    Exp MNS Exp     { $$ = $1 - $3; };
Exp:    Exp MUL Exp     { $$ = $1 * $3; };
Exp:    Exp DIV Exp     { $$ = $1 / $3; };
Exp:    LFT Exp RIT     { $$ = $2; };
Line:   EQL
Line:   Exp EQL         { *calc_result = $1; };
//Line:   Exp EQL         { printf("%f\n", $1); };
;
%%

int yyerror(YYSTYPE* calc_result,  char const *s) {
  *calc_result = -1.0;
  return 0;
}

int calc_parse(char const *s, YYSTYPE *result) {
    yy_scan_string(s);
    int ret = yyparse(result);
    yylex_destroy();
    return ret;
}
