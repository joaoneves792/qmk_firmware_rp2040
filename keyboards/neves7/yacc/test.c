#include <stdio.h>
#include "yacc.tab.h"

#define YYSTYPE double

YYSTYPE calc_parse(char const *s, YYSTYPE *result);

int main(){
  YYSTYPE result = -1.0;
  calc_parse("1-1=", &result);
  printf("%f\n", result);
  return 0;
}
