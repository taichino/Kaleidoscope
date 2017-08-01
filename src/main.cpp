#include <iostream>

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

int main() {
    cout << "hello world" << endl;
    return 0;
}
