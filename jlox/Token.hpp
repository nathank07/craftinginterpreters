#include <string>
#include <variant>

enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals.
    IDENTIFIER, STRING, NUMBER,

    // Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    END_OF_FILE
};

class Token {
    const TokenType type;
    const std::string lexeme;
    const std::variant<std::string, double> literal;
    const int line;

    public:
        Token(TokenType type, std::string lexeme, std::variant<std::string, double> literal, int line) 
            : type(type), lexeme(lexeme), literal(literal), line(line) {}
        
        std::string toString() {
            std::string literalStr;
            if(std::holds_alternative<std::string>(literal)) {
                literalStr = std::get<std::string>(literal);
            } 
            else if(std::holds_alternative<double>(literal)) {
                literalStr = std::to_string(std::get<double>(literal));
            }
            return "Type: " + std::to_string(type) + " Lexeme: " + lexeme + " Literal: " + literalStr; 
        }
};