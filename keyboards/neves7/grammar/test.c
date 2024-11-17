#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include <stdint.h>
#include <float.h>

char *my_dtostrf( double val,  int8_t char_num, uint8_t precision, char *chr_buffer)
{
  int       right_j;
  int       i, j ;
  double     r_val;
  long      i_val;
  char      c, c_sign;

  if( !(val==val) ){
    // NaN
    // The supposedly portable way to check for NaN is to use the IEEE 754 property that NaN is not equal to itself: i.e. x == x will be false for x being NaN.
    chr_buffer[0] = 'N';
    chr_buffer[1] = 'a';
    chr_buffer[2] = 'N';
    chr_buffer[3] = '\0';

    // finish here
    return chr_buffer;
  }  

  if(!(val <= DBL_MAX && val >= -DBL_MAX)){
    // inf
    chr_buffer[0] = 'i';
    chr_buffer[1] = 'n';
    chr_buffer[2] = 'f';
    chr_buffer[3] = '\0';

    // finish here
    return chr_buffer;
  }


  // check the sign
  if (val < 0.0) {
    // print the - sign
    c_sign = '-';

    // process the absolute value
    val = - val;
  } else {
    // put a space for positive numbers
    c_sign = ' ';
    
  }

  // check the left-right justification
  if (char_num < 0)
  {
    // set the flag
    right_j = 1;

    // make the number positive
    char_num = -char_num; 
    
  } else {
    right_j = 0;
  }


  // no native exponential function for int
  j=1;
  for(i=0; i < (char_num - precision - 3 );i++) j *= 10;
  
  // Hackish fail-fast behavior for larger-than-what-can-be-printed values, countig the precision + sign ('-') +'.' + '\0'
  if (val >= (double)(j))
  {
    // not enough space
    // strcpy(chr_buffer, "ovf"); - this is very byte consuming (388 bytes) , so we go for the cheap array
    chr_buffer[0] = 'o';
    chr_buffer[1] = 'v';
    chr_buffer[2] = 'f';
    chr_buffer[3] = '\0';

    // finish here
    return chr_buffer;
  }  



  // Simplistic rounding strategy so that e.g. print(1.999, 2)
  // prints as "2.00"
  r_val = 0.5;
  for ( i = 0; i < precision; i++) {
      // debug
      // Serial.println(r_val, 6);
      r_val /= 10.0;
  }
  val += r_val;

  // Extract the integer and decimal part of the number and print it
  i_val = (long) val;
  r_val = val - (double) i_val;


  // print the integral part ... but it is in reverse order ... so leaves the space for  '.' and the decimal part (and remember that array indexes start from 0
  i = char_num - precision - 2;
  do 
  {
      // debug
      // Serial.println(i_val);
      
      chr_buffer[i] = '0' + ( i_val % 10);
      i_val /= 10;
      i--;
      
  }   while ( i_val > 0) ;

  // add the sign char
  chr_buffer[i] = c_sign;

  // prepare for the decimal part
  j = char_num - precision - 1;

  // Print the decimal point, but only if there are digits beyond
  if (precision > 0) {
    chr_buffer[j] = '.';
    j++;

    // Extract digits from the remainder one at a time
    while (precision > 0) {
      // prepare the data
      r_val *= 10.0;
      i_val  = (int)    r_val;
      r_val -= (double)  i_val;
  
      // update the string
      chr_buffer[j] = '0' + ( i_val );
      j++;

      // use precision as the counter
      precision--;      
    }
  }

  // terminate the string
  chr_buffer[j] = '\0';

  // check the justification direction
  if (right_j)
  {
    // pad the string with leading ' '
    while (i > 0)
    {
      i--;

      chr_buffer[i] = ' ';       
    }
    
  } 
  
 // return the pointer to the first char of the prepared string
 return ( &chr_buffer[i]); 

}

typedef struct {
    double result;
    char error;
} Context;

void *ParseAlloc( void * (*mallocProc)(size_t));

void ParseFree( void * pParser, void (*freeProc)(void*));

char calculate(void * parser, char* input, Context * context);

int main() {
   void * parser = ParseAlloc(&malloc);
   Context context;
   context.error = 0;
   char inbuffer[20];
   fgets(inbuffer,20, stdin);
   char buffer[20];
   for(int i=0; i<20; i++){
    buffer[i] = ' ';
   }
   buffer[20-1] = 0;
   if (!calculate(parser, inbuffer, &context) && !context.error) {
      my_dtostrf(context.result, 20, 10, buffer);
      printf("%s", buffer);
   } else {
     printf("Error: Invalid input.\n");
   }
   ParseFree(parser, &free);
   return 0;
}
