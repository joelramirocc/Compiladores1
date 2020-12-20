#ifndef _AST_NODE_H
#define _AST_NODE_H

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

enum class ClassType {
    AddExp,
    MultExp,
    NumberExp,
    SeqExp,
    AssignExp,
    PrintExp,
    ExponentExp,
    IdentExp,
    ComparExp,
    IfExp,
    ElseExp,
    StringExp,
    InputExp,
    WhileExp,
    ForExp,
    FuncExp,
    ReturnExp,
    FuncCallExp,
    SubExp,
    DivExp,
    PercentExp
};

class ASTNode
{
public:
    virtual ~ASTNode(){}
    virtual ClassType getClassType() const = 0;

protected:
    ASTNode()= default;
};


class Expr;
using ExprPtr =  shared_ptr<Expr>;

class Expr : public ASTNode
{
public:
    Expr()= default;
};
 
 
    class SeqExpr : public Expr {
    public:
        vector<ExprPtr> stmts;
        SeqExpr(vector<ExprPtr>& stmts) 
        : stmts(move(stmts)) {}        
        
        ClassType getClassType() const override { return ClassType::SeqExp; }
    };

    class AssignExpr : public Expr {
    public:
        string variable;
        ExprPtr expr;
        AssignExpr(const string &variable, ExprPtr expr) 
        : variable(variable), expr(expr) {}

        ClassType getClassType() const override { return ClassType::AssignExp; }
    };

    class PrintExpr : public Expr {
    public:
        vector<ExprPtr > expressions;
        PrintExpr(vector<ExprPtr>& expressions)
        : expressions(move(expressions)) {}

        ClassType getClassType() const override { return ClassType::PrintExp; }
    };

    class InputExpr : public Expr {
    public:
        string text;
        InputExpr(const string& text)
        : text(text) {}

        ClassType getClassType() const override { return ClassType::InputExp; }
    };

    class AddExpr : public Expr {
    public:
        vector<ExprPtr > expressions;
        AddExpr(vector<ExprPtr>& expressions) 
        : expressions(move(expressions)) {}    

        ClassType getClassType() const override { return ClassType::AddExp; }
    };

    class SubExpr : public Expr {
    public:
        vector<ExprPtr > expressions;
        SubExpr(vector<ExprPtr>& expressions) 
        : expressions(move(expressions)) {}    

        ClassType getClassType() const override { return ClassType::SubExp; }
    };

    class MultExpr : public Expr {
    public:
        vector<ExprPtr> expressions;
        MultExpr(vector<ExprPtr>& expressions) 
        : expressions(move(expressions)) {}  

        ClassType getClassType() const override { return ClassType::MultExp; }
    };

    class DivExpr : public Expr {
    public:
        vector<ExprPtr> expressions;
        DivExpr(vector<ExprPtr>& expressions) 
        : expressions(move(expressions)) {}  

        ClassType getClassType() const override { return ClassType::DivExp; }
    };

    class PercentExpr : public Expr {
    public:
        vector<ExprPtr> expressions;
        PercentExpr(vector<ExprPtr>& expressions) 
        : expressions(move(expressions)) {}  

        ClassType getClassType() const override { return ClassType::PercentExp; }
    };

    class ExpExpr : public Expr {
    public:
        ExprPtr expr1;
        ExprPtr expr2;
        ExpExpr(ExprPtr expr1, ExprPtr expr2) 
        : expr1(expr1), expr2(expr2) {}  

        ClassType getClassType() const override { return ClassType::ExponentExp; }
    };

    class Number : public Expr {
    public:
        int value;
        Number(int value)
        : value(value) {}

        ClassType getClassType() const override { return ClassType::NumberExp; }
    };

    class StringExpr : public Expr {
    public:
        string value;
        StringExpr(const string &value)
        : value(value) {}

        ClassType getClassType() const override { return ClassType::StringExp; }
    };

    class IdentExpr : public Expr {
    public:
        string text;

        IdentExpr(const string &text)
        : text(text) {}

        ClassType getClassType() const override { return ClassType::IdentExp; }
    };

    class CompExpr : public Expr {
    public:
        ExprPtr expr1;
        ExprPtr expr2;
        string compareSymbol;
    
        CompExpr(ExprPtr expr1, ExprPtr expr2, string compareSymbol) 
        : expr1(expr1), expr2(expr2), compareSymbol(compareSymbol) { }

        ClassType getClassType() const override { return ClassType::ComparExp; }
    };

    class IfExpr : public Expr {
    public:
        ExprPtr ifComparison;
        ExprPtr ifBlock;
        vector<ExprPtr> elseIfs;
        ExprPtr elseBlock;
        IfExpr(ExprPtr ifComparison, ExprPtr ifBlock,
            vector<ExprPtr>& elseIfs, ExprPtr elseBlock)
            : ifComparison(ifComparison), ifBlock(ifBlock),
            elseIfs(move(elseIfs)), elseBlock(elseBlock) { }

        ClassType getClassType() const override { return ClassType::IfExp; }
    };

    class ElseExpr : public Expr {
    public:
        ExprPtr elseIfComparison;
        ExprPtr elseIfBlock;
        ElseExpr(ExprPtr elseIfComparison, ExprPtr elseIfBlock)
        : elseIfComparison(elseIfComparison), elseIfBlock(elseIfBlock) { }

        ClassType getClassType() const override { return ClassType::ElseExp; }
    };

    class WhileExpr : public Expr {
    public:
        ExprPtr comparison;
        ExprPtr block;
        WhileExpr(ExprPtr comparison, ExprPtr block) 
        : comparison(comparison), block(block) {}

        ClassType getClassType() const override { return ClassType::WhileExp; }
    };

    class ForExpr : public Expr {
    public:
        ExprPtr assign;
        ExprPtr loopLimit;
        ExprPtr block;

        ForExpr(ExprPtr assign, ExprPtr loopLimit, ExprPtr block) 
        : assign(assign), loopLimit(loopLimit), block(block) {}

        ClassType getClassType() const override { return ClassType::ForExp; }
    };

    class FuncDecl : public Expr {
    public:
        string identifier;
        vector<ExprPtr> args;
        ExprPtr stmts;
        FuncDecl(const string &identifier, vector<ExprPtr> args, ExprPtr stmts)
        : identifier(identifier), args(move(args)), stmts(stmts) {}

        ClassType getClassType() const override { return ClassType::FuncExp; }
    };

    class FuncCall : public Expr {
    public:
        string identifier;
        vector<ExprPtr> args;
        FuncCall(const string &identifier, vector<ExprPtr> args)
        : identifier(identifier), args(move(args)) {}

        ClassType getClassType() const override { return ClassType::FuncCallExp; }
    };

    class Return : public Expr {
    public:
        ExprPtr expr;
        Return(ExprPtr expr)
        : expr(expr) {}

        ClassType getClassType() const override { return ClassType::ReturnExp; }
    };
 
 #endif