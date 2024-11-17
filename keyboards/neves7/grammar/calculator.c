
#line 1 "calculator.rl"

#line 20 "calculator.rl"



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

    
#line 36 "calculator.c"
static const char _formula_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	5, 1, 6, 1, 7, 1, 8, 1, 
	9, 1, 10, 1, 11, 1, 12, 1, 
	13, 1, 14, 1, 15, 2, 2, 3, 
	2, 2, 4
};

static const char _formula_key_offsets[] = {
	0, 2, 14, 16, 19
};

static const char _formula_trans_keys[] = {
	48, 57, 32, 40, 41, 42, 43, 45, 
	46, 47, 9, 13, 48, 57, 48, 57, 
	46, 48, 57, 48, 57, 0
};

static const char _formula_single_lengths[] = {
	0, 8, 0, 1, 0
};

static const char _formula_range_lengths[] = {
	1, 2, 1, 1, 1
};

static const char _formula_index_offsets[] = {
	0, 2, 13, 15, 18
};

static const char _formula_trans_targs[] = {
	4, 1, 1, 1, 1, 1, 1, 1, 
	2, 1, 1, 3, 1, 2, 1, 0, 
	3, 1, 4, 1, 1, 1, 1, 1, 
	0
};

static const char _formula_trans_actions[] = {
	0, 25, 19, 15, 17, 11, 7, 9, 
	32, 13, 19, 5, 21, 29, 27, 0, 
	5, 23, 0, 23, 25, 27, 23, 23, 
	0
};

static const char _formula_to_state_actions[] = {
	0, 1, 0, 0, 0
};

static const char _formula_from_state_actions[] = {
	0, 3, 0, 0, 0
};

static const char _formula_eof_trans[] = {
	21, 0, 22, 24, 24
};

static const int formula_start = 1;
static const int formula_first_final = 1;
static const int formula_error = -1;

static const int formula_en_main = 1;


#line 50 "calculator.rl"
    
#line 102 "calculator.c"
	{
	cs = formula_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 51 "calculator.rl"
    
#line 112 "calculator.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _formula_actions + _formula_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 131 "calculator.c"
		}
	}

	_keys = _formula_trans_keys + _formula_key_offsets[cs];
	_trans = _formula_index_offsets[cs];

	_klen = _formula_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _formula_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
_eof_trans:
	cs = _formula_trans_targs[_trans];

	if ( _formula_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _formula_actions + _formula_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 2:
#line 1 "NONE"
	{te = p+1;}
	break;
	case 3:
#line 8 "calculator.rl"
	{act = 2;}
	break;
	case 4:
#line 16 "calculator.rl"
	{act = 10;}
	break;
	case 5:
#line 9 "calculator.rl"
	{te = p+1;{ Parse(parser, ADD, 0, context); }}
	break;
	case 6:
#line 10 "calculator.rl"
	{te = p+1;{ Parse(parser, SUB, 0, context); }}
	break;
	case 7:
#line 11 "calculator.rl"
	{te = p+1;{ Parse(parser, MUL, 0, context); }}
	break;
	case 8:
#line 12 "calculator.rl"
	{te = p+1;{ Parse(parser, DIV, 0, context); }}
	break;
	case 9:
#line 13 "calculator.rl"
	{te = p+1;{ Parse(parser, LPAREN, 0, context); }}
	break;
	case 10:
#line 14 "calculator.rl"
	{te = p+1;{ Parse(parser, RPAREN, 0, context); }}
	break;
	case 11:
#line 15 "calculator.rl"
	{te = p+1;{ /* ignore whitespace */ }}
	break;
	case 12:
#line 16 "calculator.rl"
	{te = p+1;{ return 0; }}
	break;
	case 13:
#line 7 "calculator.rl"
	{te = p;p--;{ Parse(parser, LITERAL, atof(ts), context); }}
	break;
	case 14:
#line 7 "calculator.rl"
	{{p = ((te))-1;}{ Parse(parser, LITERAL, atof(ts), context); }}
	break;
	case 15:
#line 1 "NONE"
	{	switch( act ) {
	case 2:
	{{p = ((te))-1;} Parse(parser, LITERAL, atof(ts), context); }
	break;
	case 10:
	{{p = ((te))-1;} return 0; }
	break;
	}
	}
	break;
#line 260 "calculator.c"
		}
	}

_again:
	_acts = _formula_actions + _formula_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 273 "calculator.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _formula_eof_trans[cs] > 0 ) {
		_trans = _formula_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 52 "calculator.rl"

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
