%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #define YYDEBUG 1

    int yylex(void);
    void yyerror(const char *);
%}

%error-verbose

/* WRITEME: List all your tokens here */
%token OR;
%token AND;
%token LESS;
%token LESSEQL;
%token IFEQL;
%token BOOL;
%token INT;
%token NONE;
%token PRINT;
%token RETURN;
%token IF;
%token ELSE;
%token FOR;
%token NEW;
%token TRUE;
%token FALSE;
%token INTEGER;
%token SIMICOLON;
%token COLON;
%token COMMA;
%token ABSOLUTEVALUE;
%token OPENPAREN;
%token CLOSEPAREN;
%token OPENBRACE;
%token CLOSEBRACE;
%token EQL;
%token DOT;
%token IDENTIFIER;
%token PLUS;
%token MINUS;
%token TIMES;
%token DIVIDE;
%token NOT;


/* WRITEME: Specify precedence here */
%left OR;
%left AND;
%left LESS LESSEQL IFEQL;
%left PLUS MINUS;
%left TIMES DIVIDE;
%right NOT;


%%

/* WRITEME: This rule is a placeholder, since Bison requires
            at least one rule to run successfully. Replace
            this with your appropriate start rules. */


Start : Class
      ;

Class : IDENTIFIER OPENBRACE ClassBody CLOSEBRACE Class | IDENTIFIER COLON IDENTIFIER OPENBRACE ClassBody CLOSEBRACE Class
	  |
	  ;

ClassBody : Members Methods
		  | Members
		  | Methods
		  ;

Members : Type IDENTIFIER Members
		|
		;

Methods : IDENTIFIER OPENPAREN Arguments CLOSEPAREN COLON Type OPENBRACE Body CLOSEBRACE Methods
		|
		;

Arguments : Type IDENTIFIER ArgumentsPrime
		  |
		  ;

ArgumentsPrime : COMMA Arguments
			   |
			   ;

Body : Declarations Body 
	| Statements Body 
	| returnStatement
	|
	;

Declarations : Type IDENTIFIER DeclarationsPrime
			 ;

DeclarationsPrime : COMMA IDENTIFIER DeclarationsPrime
				  |
				  ;

Statements : Assignment Statements
		   | MethodCall Statements
		   | ifElse Statements
		   | forLoop Statements
		   | Print Statements
		   |
		   ;

Assignment : IDENTIFIER EQL Expression
		;

ifElse : IF Expression OPENBRACE Statements CLOSEBRACE
	   | IF Expression OPENBRACE Statements CLOSEBRACE ELSE OPENBRACE Statements CLOSEBRACE
	   ;

forLoop : FOR Assignment SIMICOLON Expression SIMICOLON Assignment OPENBRACE Statements CLOSEBRACE
		;

Print : PRINT Expression
	  ;

Type : INT
	 | BOOL
	 | NONE
	 | IDENTIFIER
	 ;

returnStatement : RETURN Expression
				;

Expression:		Expression PLUS Expression
		|	Expression MINUS Expression	
		|	Expression TIMES Expression
		|	Expression DIVIDE Expression
		|	Expression LESS Expression
		|	Expression LESSEQL Expression
		|	Expression IFEQL Expression
		|	Expression AND Expression
		|	Expression OR Expression
		|	NOT Expression					%prec NOT
		|	MINUS Expression				%prec NOT
		|	IDENTIFIER
		|	IDENTIFIER DOT IDENTIFIER
		|	MethodCall
		|	OPENPAREN Expression CLOSEPAREN
		|	INTEGER
		|	TRUE
		|	FALSE
		|   NEW IDENTIFIER
		|	NEW IDENTIFIER OPENPAREN Parameters CLOSEPAREN
		;

MethodCall:		IDENTIFIER OPENPAREN Parameters CLOSEPAREN
		|	IDENTIFIER DOT IDENTIFIER OPENPAREN Parameters CLOSEPAREN
		;

Parameters:	ParametersPrime
		|		
		;

ParametersPrime:	ParametersPrime COMMA Expression
		|	Expression
		;


%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
