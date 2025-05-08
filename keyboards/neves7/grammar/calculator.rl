%%{

machine formula;

action number { Parse(parser, LITERAL, atof(ts), context); }
number = (
    ('.'[0-9]+)|([0-9]+('.'[0-9]+)?)
) %number;

main := |*

number                   {};
'+'                      { Parse(parser, ADD, 0, context); };
'-'                      { Parse(parser, SUB, 0, context); };
'*'                      { Parse(parser, MUL, 0, context); };
'^'                      { Parse(parser, POW, 0, context); };
'/'                      { Parse(parser, DIV, 0, context); };
'('                      { Parse(parser, LPAREN, 0, context); };
")"                      { Parse(parser, RPAREN, 0, context); };
space                    { /* ignore whitespace */ };

*|;

}%%


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
typedef struct {
    double result;
    char error;
} Context;

void Parse( void * parser, int kind, double value, Context * context);

void *ParseAlloc( void * (*mallocProc)(size_t));

void ParseFree( void * pParser, void (*freeProc)(void*));

char calculate(void * parser, char* input, Context * context) {
    int cs;
    const char * ts;
    const char * te;
    int act;

    // Setup constants for lexical analyzer
    const char * p = input;
    const char * pe = input + strlen(input);
    const char * eof = pe;

    %% write data;
    %% write init;
    %% write exec;

    Parse(parser, 0, 0, context);

    return 0;
}

//int main() {
//   void * parser = ParseAlloc(&malloc);
//   Context context;
//   context.error = 0;
//   char* input = "1+1";
//   if (!calculate(parser, input, &context) && !context.error) {
//     printf("%f\n", context.result);
//   } else {
//     printf("Error: Invalid input.\n");
//   }
//   ParseFree(parser, &free);
//   return 0;
//}
