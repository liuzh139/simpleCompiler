%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    void yyerror(const char *);
%}

/* WRITEME: Copy any definitions and start conditions from Project 3 here */


/* WRITEME: Copy your Flex rules from Project 3 here */

%x comment
%%

"/*"         BEGIN(comment);

<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n
<comment>"*"+"/"        BEGIN(INITIAL);

else                         { return ELSE;    }
if                           { return IF;      }
for                          { return FOR;     }
none                         { return NONE; }
print                        { return PRINT;}
return                       { return RETURN;  }
new                          { return NEW;	}
bool                         { return BOOL;    }
int                          { return INT;     }
true                         { return TRUE; }
false                        { return FALSE; }
or                       	 { return OR;    }
and                       	 { return AND;  }
not                          { return NOT;     }
"<"                          { return LT;      }
"<="                         { return LTE;     }
"=="                         { return EQLTO;    }
"+"                          { return PLUS;    }
"-"                          { return MINUS;   }
"*"                          { return TIMES;   }
"/"                          { return DIVIDE;  }
";"                          { return SEMICOLON;}
":"                          { return COLON; }
","                          { return COMMA; }
"{"                          { return LEFTBRACE;}
"}"                          { return RIGHTBRACE; }
"("                          { return LEFTPAREN; }
")"                          { return RIGHTPAREN; }
"="                          { return ASSIGNMENT; }
"."                          { return DOT; }

[a-zA-Z][a-zA-Z0-9]*         { yylval.identifier_ptr = new IdentifierNode(std::string(strdup(yytext))); return MNAME;}
[1-9][0-9]*|0          		 { yylval.integer_ptr = new IntegerNode(atoi(yytext)); return INT;} //atoi !!

[ \t\n]                      ; /* skip whitespace */

.                 { yyerror("invalid character"); }

%%

int yywrap(void) {
  return 1;
}
