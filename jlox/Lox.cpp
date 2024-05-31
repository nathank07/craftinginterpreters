#include "Lox.hpp"
#include "Scanner.hpp"
#include <fstream>
#include <vector>

bool Lox::hadError = false;

void Lox::runFile(const std::string& filePath) {
    using namespace std;
    ifstream file;
    string source;
    string line;
    file.open(filePath);
    if(!file.is_open()) {
        throw runtime_error("Could not open file");
    }

    while(getline(file, line)) {
        source += line + "\n";
    }
    
    run(source);
    if(hadError) { exit(65); }
}

void Lox::runPrompt() {
    using namespace std;
    for(;;) {
        string line;
        cout << "> ";
        getline(cin, line);
        if(cin.eof()) {
            cout << endl; 
            break; 
        }
        run(line);
        hadError = false;
    }
}

void Lox::run(std::string source) {
    using namespace std;
    Scanner scanner(source);
    vector<Token> tokens = scanner.scanTokens();

    for(auto& token : tokens) {
        cout << token.toString() << endl;
    }
}

int main(int argc, char* argv[]) {
    Lox lox;
    if(argc > 2) {
        std::cout << "Usage: ./jlox [script]" << std::endl;
        exit(64);
    } else if (argc == 2) {
        lox.runFile(argv[1]);
    } else {
        lox.runPrompt();
    }
}
