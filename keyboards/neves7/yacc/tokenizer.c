
#line 1 "tokenizer.rl"

#line 19 "tokenizer.rl"

#include <string.h>
int main() {
    const char* input ="(1.2 + 1) * 2.5";

    // Setup constants used in generated code
    const char * p = input;
    const char * pe = input + strlen(input);
    const char * eof = pe;

    int cs;
    const char * ts;
    const char * te;
    int act;

    // Directives to embed tokeniser
    
#line 23 "tokenizer.c"
static const char _tokeniser_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 12
};

static const char _tokeniser_key_offsets[] = {
	0, 2, 13, 15, 18
};

static const char _tokeniser_trans_keys[] = {
	48, 57, 32, 40, 41, 42, 43, 45, 
	47, 9, 13, 48, 57, 48, 57, 46, 
	48, 57, 48, 57, 0
};

static const char _tokeniser_single_lengths[] = {
	0, 7, 0, 1, 0
};

static const char _tokeniser_range_lengths[] = {
	1, 2, 1, 1, 1
};

static const char _tokeniser_index_offsets[] = {
	0, 2, 12, 14, 17
};

static const char _tokeniser_trans_targs[] = {
	4, 1, 1, 1, 1, 1, 1, 2, 
	1, 1, 3, 1, 3, 1, 0, 3, 
	1, 4, 1, 1, 1, 1, 1, 0
};

static const char _tokeniser_trans_actions[] = {
	0, 25, 17, 13, 15, 9, 7, 0, 
	11, 17, 5, 19, 5, 23, 0, 5, 
	21, 0, 21, 25, 23, 21, 21, 0
};

static const char _tokeniser_to_state_actions[] = {
	0, 1, 0, 0, 0
};

static const char _tokeniser_from_state_actions[] = {
	0, 3, 0, 0, 0
};

static const char _tokeniser_eof_trans[] = {
	20, 0, 21, 23, 23
};

static const int tokeniser_start = 1;
static const int tokeniser_first_final = 1;
static const int tokeniser_error = -1;

static const int tokeniser_en_main = 1;


#line 36 "tokenizer.rl"
    
#line 86 "tokenizer.c"
	{
	cs = tokeniser_start;
	ts = 0;
	te = 0;
	act = 0;
	}

#line 37 "tokenizer.rl"
    
#line 96 "tokenizer.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
_resume:
	_acts = _tokeniser_actions + _tokeniser_from_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 1:
#line 1 "NONE"
	{ts = p;}
	break;
#line 115 "tokenizer.c"
		}
	}

	_keys = _tokeniser_trans_keys + _tokeniser_key_offsets[cs];
	_trans = _tokeniser_index_offsets[cs];

	_klen = _tokeniser_single_lengths[cs];
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

	_klen = _tokeniser_range_lengths[cs];
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
	cs = _tokeniser_trans_targs[_trans];

	if ( _tokeniser_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _tokeniser_actions + _tokeniser_trans_actions[_trans];
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
#line 8 "tokenizer.rl"
	{te = p+1;{ std::cout << "ADD" << std::endl; }}
	break;
	case 4:
#line 10 "tokenizer.rl"
	{te = p+1;{ std::cout << "MUL" << std::endl; }}
	break;
	case 5:
#line 11 "tokenizer.rl"
	{te = p+1;{ std::cout << "DIV" << std::endl; }}
	break;
	case 6:
#line 12 "tokenizer.rl"
	{te = p+1;{ std::cout << "LPARENS" << std::endl; }}
	break;
	case 7:
#line 13 "tokenizer.rl"
	{te = p+1;{ std::cout << "RPARENS" << std::endl; }}
	break;
	case 8:
#line 14 "tokenizer.rl"
	{te = p+1;{ /* ignore whitespace */ }}
	break;
	case 9:
#line 15 "tokenizer.rl"
	{te = p+1;{ throw std::runtime_error("Unexpected character"); }}
	break;
	case 10:
#line 7 "tokenizer.rl"
	{te = p;p--;{ std::cout << "LITERAL(" << std::atof(ts) << ")" << std::endl; }}
	break;
	case 11:
#line 9 "tokenizer.rl"
	{te = p;p--;{ std::cout << "SUB" << std::endl; }}
	break;
	case 12:
#line 7 "tokenizer.rl"
	{{p = ((te))-1;}{ std::cout << "LITERAL(" << std::atof(ts) << ")" << std::endl; }}
	break;
#line 224 "tokenizer.c"
		}
	}

_again:
	_acts = _tokeniser_actions + _tokeniser_to_state_actions[cs];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 ) {
		switch ( *_acts++ ) {
	case 0:
#line 1 "NONE"
	{ts = 0;}
	break;
#line 237 "tokenizer.c"
		}
	}

	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	if ( _tokeniser_eof_trans[cs] > 0 ) {
		_trans = _tokeniser_eof_trans[cs] - 1;
		goto _eof_trans;
	}
	}

	}

#line 38 "tokenizer.rl"

    return 0;
}
