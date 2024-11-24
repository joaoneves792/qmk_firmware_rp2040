/*
This is the modified version of [calculator by MWWorks](https://github.com/MWWorks/mw_calc_numpad/blob/master/calc.c). Below is the quote from [MWWorks](https://github.com/MWWorks).

   Calculator for QMK-based keyboard by MWWorks, https://mwworks.uk
   This is free, usual disclaimers, don't use it to calculate megaton yields, surgery plans, etc

   I did not plan to reinvent the wheel for this - I figured surely somebody somewhere has working calculator code?
   Found lots but none that actually work like you expect a calculator to, hence DIYing it

   As such, this is probably a bit janky, especially as I am a bit of a hack at C
   Seems to be working well, with occasional glitchs, solved by clearing it
   And some occasional doubleing-point issues - eg get a long decimal rather than the whole number you were expecting
   Feel free to fix it! I think it needs to detect the precision of the two operands and then figure out what the precision of the result should be

*/
#include "neves7.h"
#include <math.h>
#include <float.h>
#include "printf.h"

extern uint8_t calc_precision;
uint8_t calc_base = CALC_BASE_DEC;

#define CALC_MAX_BUFFER 20
char calc_buffer[CALC_MAX_BUFFER];
char calc_result_buffer[CALC_MAX_BUFFER];
uint8_t calc_buffer_size = 0;


void *ParseAlloc( void * (*mallocProc)(size_t));
void ParseFree( void * pParser, void (*freeProc)(void*));


typedef struct {
    double result;
    char error;
} Context;

char calculate(void * parser, char* input, Context * context);

void calcBegin(void){
  calc_buffer[0] = 0;
  calc_buffer_size = 0;
  calc_result_buffer[0] = '0';
  calc_result_buffer[1] = 0;
}

void calc_print(double val){
  if( !(val==val) ){
    // NaN
    // The supposedly portable way to check for NaN is to use the IEEE 754 property that NaN is not equal to itself: i.e. x == x will be false for x being NaN.
    calc_result_buffer[0] = 'N';
    calc_result_buffer[1] = 'a';
    calc_result_buffer[2] = 'N';
    calc_result_buffer[3] = '\0';

    // finish here
    return; 
  }  

  if(!(val <= DBL_MAX && val >= -DBL_MAX)){
    // inf
    calc_result_buffer[0] = 'i';
    calc_result_buffer[1] = 'n';
    calc_result_buffer[2] = 'f';
    calc_result_buffer[3] = '\0';

    // finish here
    return;
  }
  
  switch(calc_base){
    case CALC_BASE_HEX:
      snprintf(calc_result_buffer, CALC_MAX_BUFFER, "0x%0*lX", calc_precision-2, (unsigned long)val);
      break;
    case CALC_BASE_OCT:
      snprintf(calc_result_buffer, CALC_MAX_BUFFER, "%#0*lo", calc_precision, (unsigned long)val);
      break;
    case CALC_BASE_BIN:
      snprintf(calc_result_buffer, CALC_MAX_BUFFER, "%#0*lb", calc_precision, (unsigned long)val);
      break;
    default:
    case CALC_BASE_DEC:
      snprintf(calc_result_buffer, CALC_MAX_BUFFER, "%.*f", calc_precision, val);
      break;
  }
}

void calcUpdate(void){
   void * parser = ParseAlloc(&malloc);
   Context context;
   context.error = 0;
   context.result = 0.0;
   for(uint8_t i = 0; i < CALC_MAX_BUFFER; i++)
     calc_result_buffer[i] = ' ';
   calc_result_buffer[CALC_MAX_BUFFER-1] = 0;
   if (!calculate(parser, calc_buffer, &context) && !context.error) {
      calc_print(context.result);
   }else{
      calc_result_buffer[0] = 'i';
      calc_result_buffer[1] = 'n';
      calc_result_buffer[2] = 'v';
      calc_result_buffer[3] = '.';
   }
   ParseFree(parser, &free);
}

void calcInput(char input){
    
    if ( 'c' == input ){
      calc_buffer_size = 0;
      calc_buffer[0] = 0;
      calc_result_buffer[0] = 0;
      return;
    }


    if (calc_buffer_size > CALC_MAX_BUFFER) {
      return;
    }

    calc_buffer[calc_buffer_size] = input;
    calc_buffer[calc_buffer_size+1] = 0;
    calc_buffer_size++;
    
    calcUpdate();
}
