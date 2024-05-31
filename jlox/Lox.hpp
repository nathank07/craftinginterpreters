#include <iostream>

class Lox {
    static bool hadError;
    public:
        void runFile(const std::string& filePath);
        void runPrompt();
        void run(std::string source);
        static void error(int line, std::string message) {
            report(line, "", message);
        }
        static void report(int line, std::string where, std::string message) {
            std::cerr << "[line " << line << "] Error" << where << ": " << message;
            hadError = true;
        }
};