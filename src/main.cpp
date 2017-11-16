#include <iostream>
#include "expr.h"
#include "llvm/ADT/STLExtras.h"

using namespace std;


enum Token {
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
};

static string IdentifierStr;
static double NumVal;

static int gettok() {
    static int LastChar = ' ';

    // skip any white space
    while (isspace(LastChar)) {
        LastChar = getchar();
    }

    if (isalpha(LastChar)) {
        IdentifierStr = LastChar;
        while (isalnum(LastChar = getchar())) {
            IdentifierStr += LastChar;
        }

        if (IdentifierStr == "def") {
            return tok_def;
        }
        if (IdentifierStr == "extern") {
            return tok_extern;
        }
        return tok_identifier;
    }

    if (isdigit(LastChar) || LastChar == '.') {
        std::string NumStr;
        do {
            NumStr += LastChar;
            LastChar = getchar();
        } while(isdigit(LastChar) || LastChar == '.');
        NumVal = strtod(NumStr.c_str(), 0);
        return tok_number;
    }

    if (LastChar == '#') {
        // Comment until end of line
        do {
            LastChar = getchar();
        } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if (LastChar != EOF) {
            return gettok();
        }
    }

    if (LastChar == EOF) {
        return tok_eof;
    }

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}

void printToken(int token) {
    switch (token) {
    case tok_eof:
        printf("EOF!\n");
        break;
    case tok_def:
        printf("def!\n");
        break;
    case tok_extern:
        printf("extern!\n");
        break;
    case tok_identifier:
        printf("identifier\n");
        break;
    case tok_number:
        printf("number!\n");
        break;
    default:
        printf("@@ something else @@\n");
    }
}

static int CurTok;
static int getNextToken() {
    return CurTok = gettok();
}

unique_ptr<ExprAST> LogError(const char *Str) {
    fprintf(stderr, "LogError: %s\n", Str);
    return nullptr;
}

unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
    LogError(Str);
    return nullptr;
}

static unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = llvm::make_unique<NumberExprAST>(NumVal);
    getNextToken();
    return move(Result);
}

int main() {
    int t;
    do {
        t = gettok();
        printToken(t);
    } while (t != tok_eof);
    return 0;
}
