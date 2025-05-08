# lexer.rl
%%{

  machine test_lexer;

  integer = ('+'|'-')?[0-9]+;
   main := |*
     integer;
   *|;  
}%%

%% write data;
