#include "ast.hpp"
#include "parser.hpp"

extern int yydebug;
extern int yyparse();

ASTNode* astRoot;

int main(void) {
    yydebug = 0; // Set this to 1 if you want the parser to output debug information and parse process
    
    astRoot = NULL;
    
    yyparse();
    
    if (astRoot) {
        Print* printer = new Print();
        astRoot->accept(printer);
    }

    return 0;
}
