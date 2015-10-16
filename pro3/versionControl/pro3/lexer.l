%option yylineno
%pointer

%{
    #define YYSTYPE char*
    #include <stdlib.h>
    void yyerror(const char *);
    #include "parser.hpp"
%}

/* WRITEME: Write any definitions here. You can find information on
            definitions here:
            http://flex.sourceforge.net/manual/Definitions-Section.html */

/*digit [0-9] */

/* WRITEME: If you are going to use start conditions, write them here.
            You can find more information on start conditions here:
            http://flex.sourceforge.net/manual/Start-Conditions.html
            You will probably want to use exclusive conditions rather
            than inclusive conditions (use the %x instead of the %s). */

%%

"or" {return OR;}
and {return AND;}
"<" {return LESS;}
"<=" {return LESSEQL;}
"==" {return IFEQL;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return DIVIDE;}
"." {return DOT;}

"not" {return NOT;}
bool {return BOOL;}
int  {return INT;}
none {return NONE;}
print {return PRINT;}
return {return RETURN;}
if {return IF;}
else {return ELSE;}
for {return FOR;}
new {return NEW;}
and {return AND;}
or {return OR;}
true {return TRUE;}
false {return FALSE;}

0   {return INTEGER;}
[1-9][0-9]*              {return INTEGER;}

[A-Za-z][0-9A-Za-z]*         { return IDENTIFIER;}

";" { return SIMICOLON;}
":" { return COLON; }
"," { return COMMA; }
"|" { return ABSOLUTEVALUE;}
"(" { return OPENPAREN; }
")" { return CLOSEPAREN; }
"{" { return OPENBRACE;}
"}" { return CLOSEBRACE; }
"=" { return EQL; }
[ \t\n] ; /* skip whitespace */

%%

int yywrap(void) {
  return 1;
}
