#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>

using namespace std;

// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_POWER,
    T_DIVIDE,
    T_OPENPAREN,
    T_CLOSEPAREN,
    T_OPENBRACKET,
    T_CLOSEBRACKET,
    T_EQUALS,
    T_SEMICOLON,
    T_M,
    T_PRINT,
    T_NUMBER,
    T_EOF,
    T_newLine,
    T_SPACE
} token;

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_POWER:
            return std::string("**");
        case T_DIVIDE:
            return std::string("/");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_OPENBRACKET:
            return std::string("[");
        case T_CLOSEBRACKET:
            return std::string("]");
        case T_EQUALS:
            return std::string("=");
        case T_SEMICOLON:
            return std::string(";");
        case T_M:
            return std::string("M");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_EOF:
            return std::string("EOF");
        case T_newLine:
            return string("new_line");
        case T_SPACE:
            return string("blank");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the index for memory is out of bounds (less
// than 0 or greater than 99). ONLY THROW IF evaluate flag is true.
void indexError(int line, int index) {
    std::cerr << "Semantic error: index " << index << " out of bounds at line " << line << std::endl;
    exit(1);
}

// Throw this error when a division by zero occurs. ONLY THROW IF evaluate flag is true.
void divideError(int line) {
    std::cerr << "Semantic error: division by zero at line " << line << std::endl;
    exit(1);
}

class Scanner {
    
public:
    token nextToken();
    void eatToken(token);
    int lineNumber();
    int getNumberValue();
    static int line;
    
};

int Scanner::line = 1;

//peek the next word and put it back.
string nextString(){
    string strIn = "";
    cin >> strIn;
    for (int i= strIn.length(); i>0; --i) {
        cin.putback(strIn.at(i-1)); //put the chars back in reverse order.
    }
    return strIn;
}

token Scanner::nextToken() {
    char readIn = cin.peek();
    string print = "print";
    
    // WRITEME
    string strIn = nextString();
    if(isdigit(readIn)){return T_NUMBER;}
    else if(strIn == "**"){return T_POWER;}
    else if(strIn == "***"){
        return T_POWER;
    }
    else{
        switch (readIn) {
            case '+': return T_PLUS;
            case '-': return T_MINUS;
            case '*':return T_MULTIPLY;
            case '/': return T_DIVIDE;
            case '(': return T_OPENPAREN;
            case ')': return T_CLOSEPAREN;
            case '[': return T_OPENBRACKET;
            case ']': return T_CLOSEBRACKET;
            case '=': return T_EQUALS;
            case ';': return T_SEMICOLON;
            case 'm':
            case 'M':
                return T_M;
            case 'p':
            case 'P':
                if (strIn=="print") {
                    return T_PRINT;
                }else{
                    for (int i=0; i<strIn.length(); i++) {
                        if (strIn.at(i)!=print.at(i)) {
                            scanError(line, strIn.at(i));
                            break;
                        }
                    }
                }
            case '\t':
            case ' ' : return nextToken();
            case EOF: return T_EOF;
            case '\n':
                line++;
                return nextToken();
                break;
            default:
                char c = cin.peek();
                scanError(line, c);
                break;
        }
    }
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
    char readIn = cin.peek();
    // WRITEME
    
    if (toConsume != nextToken()) {
        mismatchError(lineNumber(), toConsume, nextToken());
    }else{
        string strIn = nextString();
        if (toConsume == T_PRINT) {cin.ignore(5);}
        else if(readIn == '\n'){
            line++;
        }
        else if(toConsume == T_POWER){cin.ignore(2);}
        else if(toConsume == T_NUMBER){
            while(isdigit(cin.peek())){
                cin.ignore();
            }
        }
        else {
            cin.ignore();
        }
    }
}

int Scanner::lineNumber() {
    //return the current line number (to be used for errors).
    return line;
}

int Scanner::getNumberValue() {
    //return the last number value that was scanned.
    //This will be used when evaluating expressions.
    
    // WRITEME
    int value;
    if (nextToken()==T_NUMBER) {
        cin >> value ;
        cin.putback(value);
    }
    return value;
}

class Parser {
    
private:
    Scanner scanner;
    
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate;
    
    
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    // WRITEME
    void Statements();
    void Statement();
    void States();
    void Exp();
    void Term();
    void Factor();
    void Bottom();
    
    
public:
    void parse();
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
    }
};






void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    Start();
}

void Parser::Bottom(){
    //cout << "state" <<endl;
    
    switch (scanner.nextToken()) {
        case T_M:
            scanner.eatToken(T_M);
            scanner.eatToken(T_OPENBRACKET);
            if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                Exp();
            else parseError(scanner.lineNumber(), scanner.nextToken());
            scanner.eatToken(T_CLOSEBRACKET);
            break;
            
        case T_NUMBER:
            scanner.eatToken(T_NUMBER);
            break;
            
        case T_OPENPAREN:
            scanner.eatToken(T_OPENPAREN);
            if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                Exp();
            else parseError(scanner.lineNumber(), scanner.nextToken());
            scanner.eatToken(T_CLOSEPAREN);
            break;
            
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
    
}

void Parser::Factor(){
    //cout << "state" <<endl;
    // cout << "1111111111111111111111: " << tokenToString(scanner.nextToken())<< endl;
    if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
    {
        Bottom();
        
        //cout << "state" <<endl;
        
        switch (scanner.nextToken()) {
            case T_POWER:
                scanner.eatToken(T_POWER);
                if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                    Factor();
                else parseError(scanner.lineNumber(), scanner.nextToken());
                break;
                // default:
                
                //     parseError(scanner.lineNumber(), scanner.nextToken());
                //     break;
        }
    }
}

void Parser::Term(){
    //cout << "state" <<endl;
    if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
    {
        Factor();
        
        switch (scanner.nextToken()) {
            case T_MULTIPLY:
                scanner.eatToken(T_MULTIPLY);
                if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                    Term();
                else parseError(scanner.lineNumber(), scanner.nextToken());
                break;
            case T_DIVIDE:
                scanner.eatToken(T_DIVIDE);
                
                if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                    Term();
                else parseError(scanner.lineNumber(), scanner.nextToken());
                
                break;
                // default:
                
                //     parseError(scanner.lineNumber(), scanner.nextToken());
                //     break;
        }
    }
}

void Parser::Exp(){
    
    if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
    {
        Term();
        switch (scanner.nextToken()) {
            case T_PLUS:
                scanner.eatToken(T_PLUS);
                if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                    Exp();
                else parseError(scanner.lineNumber(), scanner.nextToken());
                break;
            case T_MINUS:
                scanner.eatToken(T_MINUS);
                if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                    Exp();
                else parseError(scanner.lineNumber(), scanner.nextToken());
                break;
                // default:
                //     parseError(scanner.lineNumber(), scanner.nextToken());
                //     break;
        }
    }
}

void Parser::Statement(){
    // cout << "callonce" <<endl;
    
    switch (scanner.nextToken()) {
        case T_M:
            scanner.eatToken(T_M);
            //cout << "hello" <<endl;
            scanner.eatToken(T_OPENBRACKET);
            
            // if (scanner.nextToken() == T_OPENBRACKET)
            //     scanner.eatToken(T_OPENBRACKET);
            // else
            //     parseError(scanner.lineNumber(), scanner.nextToken());
            if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                Exp();
            else parseError(scanner.lineNumber(), scanner.nextToken());
            scanner.eatToken(T_CLOSEBRACKET);
            scanner.eatToken(T_EQUALS);
            
            // if (scanner.nextToken() == T_CLOSEBRACKET)
            //     scanner.eatToken(T_CLOSEBRACKET);
            // else
            //     parseError(scanner.lineNumber(), scanner.nextToken());
            
            // if (scanner.nextToken() == T_EQUALS)
            //     scanner.eatToken(T_EQUALS);
            // else
            //     parseError(scanner.lineNumber(), scanner.nextToken());
            
            if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                Exp();
            else parseError(scanner.lineNumber(), scanner.nextToken());
            break;
            
        case T_PRINT:
            scanner.eatToken(T_PRINT);
            // cout << "ssssssssssssssssssssssssss" <<endl;
            // cout << "1111111111111111111111: " << tokenToString(scanner.nextToken())<< endl;
            if ((scanner.nextToken()==T_M)||(scanner.nextToken()==T_OPENPAREN)||(scanner.nextToken()==T_NUMBER))
                //cout << "2222222222222222222222" <<endl;
                Exp();
            else parseError(scanner.lineNumber(), scanner.nextToken());
            break;
        default:
            //cout << "stateeeeeeeeeeeeeeeeeeeeee" <<endl;
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}

void Parser::States(){
    switch (scanner.nextToken()) {
        case T_SEMICOLON:
            scanner.eatToken(T_SEMICOLON);
            Statement();
            if (scanner.nextToken()==T_SEMICOLON)
                States();
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}

void Parser::Statements(){
    Statement();
    if (scanner.nextToken()==T_SEMICOLON)
        States();
}

void Parser::Start() {
    // This is an example of a recursive-descent function for a
    // non-terminal symbol. In this case, it is just a placeholder
    // which accepts infinite numbers of T_PLUS. You will need to
    // replace this with correct code for the real grammar start symbol.
    
    // WRITEME
    Statements();
}

// WRITEME (The rest of the nonterminal functions will need to be implemented here)

int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        Parser parser(false);
        parser.parse();
    }
    return 0;
}
