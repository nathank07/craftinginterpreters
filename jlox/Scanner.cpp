#include "Scanner.hpp"
#include "Lox.hpp"

void Scanner::scanToken() {
    char c = advance();
    switch(c) {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;
        case ',': addToken(COMMA); break;
        case '.': addToken(DOT); break;
        case '-': addToken(MINUS); break;
        case '+': addToken(PLUS); break;
        case ';': addToken(SEMICOLON); break;
        case '*': addToken(STAR); break;
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            if(match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else if(match('*')) {
                comment_blocks += 1;
                while (comment_blocks > 0 && !isAtEnd()) {
                    if(peek() == '/' && peekNext() == '*') comment_blocks += 1;
                    if(peek() == '*' && peekNext() == '/') comment_blocks -= 1;
                    if(peek() == '\n') line += 1;
                    advance();
                }
                advance();
            } else {
                addToken(SLASH);
            }
            break;
        case ' ':  break;
        case '\r': break;
        case '\t': break;
        case '\n':
            line++;
            break;
        case '"': string(); break;
        default:
            if(isdigit(c)) {
                number();
            } else if(isalpha(c)) {
                identifier();
            } else {
                Lox::error(line, "Unexpected character.");
            }
            break; 
    }
}

void Scanner::string() {
    while(peek() != '"' && !isAtEnd()) {
        if(peek() == '\n') line++;
        advance();
    }
    if(isAtEnd()) {
        Lox::error(line, "Unterminated String.");
        return;
    }

    // To consume the other "
    advance();

    // Value inside quotes - "foobar" -> foobar
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(STRING, value);
}

void Scanner::number() {
    while(isdigit(peek())) advance();
    if(peek() == '.' && isdigit(peekNext())) {
        advance();

        while(isdigit(peek())) advance();
    }
    double number = std::stod(source.substr(start, current - start));
    addToken(NUMBER, number);
}

void Scanner::identifier() {
    while(isalnum(peek())) advance();
    std::string text = source.substr(start, current - start);
    TokenType type = keywords[text];
    // type 0 is LEFT_PAREN, but because it is not alnum it's ok
    if(type == 0) type = IDENTIFIER;
    addToken(type);
}

void Scanner::addToken(TokenType type, std::variant<std::string, double> literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

std::vector<Token> Scanner::scanTokens() {
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(END_OF_FILE, "", "", line));
    return tokens;
}

