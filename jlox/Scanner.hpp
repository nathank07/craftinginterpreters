#include "Token.hpp"
#include <string>
#include <vector>
#include <map>

class Scanner {
    std::string source;
    std::vector<Token> tokens;
    std::map<std::string, TokenType> keywords = {
        { "and",    AND },
        { "class",  CLASS },
        { "else",   ELSE },
        { "false",  FALSE },
        { "for",    FOR },
        { "fun",    FUN },
        { "if",     IF },
        { "nil",    NIL },
        { "or",     OR },
        { "print",  PRINT },
        { "return", RETURN },
        { "super",  SUPER },
        { "this",   THIS },
        { "true",   TRUE },
        { "var",    VAR },
        { "while",  WHILE }
    };
    int start = 0;
    int current = 0; 
    int line = 1;
    int comment_blocks = 0;
    void scanToken();
    void string();
    void number();
    void identifier();
    void addToken(TokenType type, std::variant<std::string, double> literal);
    char advance() {
        return source.at(current++);
    }
    char peek() {
        if(isAtEnd()) return '\0';
        return source.at(current);
    }
    char peekNext() {
        if(current + 1 >= source.length()) return '\0';
        return source.at(current + 1);
    }
    bool match(char expected) {
        if(isAtEnd()) return false;
        if(source.at(current) != expected) return false;
        current++;
        return true;
    }
    bool isAtEnd() {
        return current >= source.length();
    }
    void addToken(TokenType type) {
        addToken(type, "");
    }
    
    public:
        Scanner(std::string source)
            : source(source) {}
        std::vector<Token> scanTokens();
};