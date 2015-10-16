%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include "ast.hpp"

    #define YYDEBUG 1
    int yylex(void);
    void yyerror(const char *);
    extern ASTNode* astRoot;
%}

%error-verbose
/* WRITEME: Copy your token and precedence specifiers from Project 3 here */
%token ELSE
%token IF
%token FOR
%token NONE
%token PRINT
%token RETURN
%token NEW
%token BOOL
%token INT
%token TRUE
%token FALSE
%token MNAME
%token OR
%token AND
%token LT
%token LTE
%token EQLTO
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token NOT
%token SEMICOLON
%token COLON
%token COMMA
%token LEFTBRACE
%token RIGHTBRACE
%token LEFTPAREN
%token RIGHTPAREN
%token ASSIGNMENT
%token DOT

/*Type specification */
%type <expression_ptr> Expression 
%type <expression_list_ptr> Parameters
%type <identifier_ptr> MNAME
%type <integer_ptr> INT
%type <parameter_list_ptr>  Arguments ArgumentsPrime
%type <type_ptr> Type
%type <print_ptr> Print
%type <for_ptr> forLoop
%type <ifelse_ptr> ifElse
%type <methodcall_ptr> MethodCall
%type <assignment_ptr> Assignment
%type <statement_list_ptr> Statement StatementPrime
%type <statement_ptr> Statements
%type <identifier_list_ptr> Declarations 
%type <declaration_list_ptr> Declaration Members
%type <returnstatement_ptr> ReturnStatement
%type <methodbody_ptr> Body
%type <method_list_ptr> Methods 
%type <class_list_ptr> Class  
%type <program_ptr> Start

/* WRITEME: Specify precedence here */
%left OR;
%left AND;
%left LT LTE EQLTO;
%left PLUS MINUS;
%left TIMES DIVIDE;
%right NOT ;

/* WRITEME: Specify types for all nonterminals and necessary terminals here */

%%
Start: Class { $$ = new ProgramNode($1); astRoot = $$; } ; 

Class: MNAME LEFTBRACE Members Methods RIGHTBRACE Class { $$ = $6; $$ ->push_front(new ClassNode($1, NULL, $3,$4));} 
    | MNAME COLON MNAME LEFTBRACE Members Methods RIGHTBRACE Class { $$ = $8; $$ ->push_front(new ClassNode($1,$3,$5,$6));} 
    | { $$ = new std::list<ClassNode*>();}  ; 

Members: Members Type MNAME { 
        $$ = $1;
        std::list<IdentifierNode*>* temp = new std::list<IdentifierNode*>(); 
        temp->push_back($3); 
        $$ -> push_back(new DeclarationNode($2, temp)); }
    | { $$ = new std::list<DeclarationNode*>(); } ;

Methods: MNAME LEFTPAREN Arguments RIGHTPAREN COLON Type LEFTBRACE Body RIGHTBRACE Methods 
        { $$ = $10; $$ -> push_front( new MethodNode($1, $3, $6, $8)); } 
    | { $$ = new std::list<MethodNode*>(); } ;

Arguments: ArgumentsPrime { $$ = $1; }
    | { $$ = new std::list<ParameterNode*>(); } ;

ArgumentsPrime: ArgumentsPrime COMMA Type MNAME { $$ = $1; $$ -> push_back( new ParameterNode($3, $4));}
    | Type MNAME { $$ = new std::list<ParameterNode*>(); $$ -> push_back( new ParameterNode($1, $2));} ; 

Body: Declaration StatementPrime ReturnStatement { $$ = new MethodBodyNode($1, $2, $3); } ;

ReturnStatement: RETURN Expression { $$ = new ReturnStatementNode($2); }
    | { $$ = NULL; } ; 

Declaration: Declaration Type MNAME Declarations { $$ = $1; $4->push_front($3); $$ -> push_back( new DeclarationNode( $2, $4)); } 
   | { $$ = new std::list<DeclarationNode*>(); } ;

Declarations: COMMA MNAME Declarations { $$ = $3, $$->push_front($2); } 
    | { $$ = new std::list<IdentifierNode*>(); } ; 

StatementPrime : Statement { $$ = $1; }
               | { $$ = new std::list<StatementNode*>(); }

Statement: Statements Statement { $$ = $2; $$ -> push_front($1); }
    | Statements { $$ = new std::list<StatementNode*>(); $$-> push_front($1); } ;

Statements: Assignment { $$ = $1; }
    | MethodCall { $$ = new CallNode($1); }
    | ifElse { $$ = $1; }
    | forLoop { $$ = $1; }
    | Print { $$ = $1; } ; 

Assignment: MNAME ASSIGNMENT Expression { $$ = new AssignmentNode($1, $3); } ;

MethodCall: MNAME LEFTPAREN Parameters RIGHTPAREN { $$ = new MethodCallNode( $1, NULL, $3); } //no class prefix? 
    | MNAME DOT MNAME LEFTPAREN Parameters RIGHTPAREN { $$ = new MethodCallNode($1, $3, $5); };

ifElse: IF Expression LEFTBRACE Statement RIGHTBRACE { $$ = new IfElseNode($2, $4, new std::list<StatementNode*>()); }
    | IF Expression LEFTBRACE Statement RIGHTBRACE ELSE LEFTBRACE Statement RIGHTBRACE {$$ = new IfElseNode($2, $4, $8); };

forLoop: FOR Assignment SEMICOLON Expression SEMICOLON Assignment LEFTBRACE Statement RIGHTBRACE 
    { $$ = new ForNode($2, $4, $6, $8); }; 

Print: PRINT Expression { $$ = new PrintNode($2); } ;

Type: INT { $$ = new IntegerTypeNode(); } 
    | BOOL { $$ = new BooleanTypeNode(); }
    | MNAME { $$ = new ObjectTypeNode($1); } 
    | NONE { $$ = new NoneNode(); } ; 

Expression: Expression PLUS Expression { $$ = new PlusNode($1,$3); }
    | Expression MINUS Expression { $$ = new MinusNode($1,$3); }
    | Expression TIMES Expression { $$ = new TimesNode($1,$3); }
    | Expression DIVIDE Expression { $$ = new DivideNode($1,$3); }
    | Expression LT Expression { $$ = new LessNode($1,$3); }
    | Expression LTE Expression { $$ = new LessEqualNode($1,$3); }
    | Expression EQLTO Expression { $$ = new EqualNode($1,$3); }
    | Expression AND Expression { $$ = new AndNode($1,$3); }
    | Expression OR Expression { $$ = new OrNode($1,$3); }
    | NOT Expression          %prec NOT { $$ = new NotNode($2); }
    | MINUS Expression        %prec NOT { $$ = new NegationNode($2); }
    | MNAME { $$ = new VariableNode($1); }
    | MNAME DOT MNAME { $$ = new MemberAccessNode($1,$3); } 
    | MethodCall { $$ = $1; } 
    | LEFTPAREN Expression RIGHTPAREN { $$ = $2; } 
    | INT { $$ = new IntegerLiteralNode($1); } 
    | TRUE { $$ = new BooleanLiteralNode( new IntegerNode(1)); } 
    | FALSE { $$ = new BooleanLiteralNode( new IntegerNode(0)); }
    | NEW MNAME { $$ = new NewNode($2, new std::list<ExpressionNode*>()); } 
    | NEW MNAME LEFTPAREN Parameters RIGHTPAREN { $$ = new NewNode($2, $4); } ; 

Parameters: Parameters COMMA Expression { $$ = $1; $$ -> push_back($3); }
    | Expression { $$ = new std::list<ExpressionNode*>(); $$ -> push_back($1);}  //used parameter_list_ptr here?
    | { $$ = new std::list<ExpressionNode*>(); } ; 

/* Anything under this should not be changed! */
%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
