#include <vector>

using namespace std;

// Base class for all expression nodes
class ExprAST {
public:
    virtual ~ExprAST() {}
};

// Expression class for numeric literals like "1.0"
class NumberExprAST : public ExprAST {
    double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
};

// Expression class for referencing a variable, like "a"
class VariableExprAST : public ExprAST {
    string Name;

public:
    VariableExprAST(const string &Name) : Name(Name) {}
};

// Expression class for a binary operator
class BinaryExprAST : public ExprAST {
    char Op;
    unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char op,
                  unique_ptr<ExprAST> LHS,
                  unique_ptr<ExprAST> RHS)
        : Op(op), LHS(move(LHS)), RHS(move(RHS)) {}
};

// Expression class for function calls
class CallExprAST : public ExprAST {
    string Callee;
    vector<unique_ptr<ExprAST>> Args;

public:
    CallExprAST(const string &Callee,
                vector<unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(move(Args)) {}
};

// Expression class for function calls
class PrototypeAST {
    string Name;
    vector<string> Args;

  public:
    PrototypeAST(const string &name, vector<string> Args)
        : Name(name), Args(move(Args)) {}
    const string &getName() const { return Name; }
};

// This represents a function definition itself
class FunctionAST {
    unique_ptr<PrototypeAST> Proto;
    unique_ptr<ExprAST> Body;

  public:
    FunctionAST(unique_ptr<PrototypeAST> Proto,
                unique_ptr<ExprAST> Body)
        : Proto(move(Proto)), Body(move(Body)) {}
};
