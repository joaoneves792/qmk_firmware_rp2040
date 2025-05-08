%option noyywrap
%{
  #define YYSTYPE double
  #include "yacc.tab.h"
%}
DIG         [0-9]

%%
{DIG}+      { yylval = atoi(yytext); return NUM; }
"+"                             { return PLS; }
"-"                             { return MNS; }
"*"                             { return MUL; }
"/"                             { return DIV; }
"\n"                                { return NWL; }
"="                                { return EQL; }
"("                             { return LFT; }
")"                             { return RIT; }
%%
