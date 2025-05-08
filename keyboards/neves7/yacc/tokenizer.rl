%%{

machine tokeniser;

main := |*

('-'?[0-9]+('.'[0-9]+)?) { std::cout << "LITERAL(" << std::atof(ts) << ")" << std::endl; };
'+'                      { std::cout << "ADD" << std::endl; };
'-'                      { std::cout << "SUB" << std::endl; };
'*'                      { std::cout << "MUL" << std::endl; };
'/'                      { std::cout << "DIV" << std::endl; };
'('                      { std::cout << "LPARENS" << std::endl; };
")"                      { std::cout << "RPARENS" << std::endl; };
space                    { /* ignore whitespace */ };
any                      { throw std::runtime_error("Unexpected character"); };

*|;

}%%
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
    %% write data;
    %% write init;
    %% write exec;

    return 0;
}
