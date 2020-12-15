#ifndef _AST_H
#define _AST_H

#include <memory>
#include <string>
#include <iostream>
#include <vector>

enum class ClassType
{
    AddExp,
    SubExp,
    DivExp,
    MultExp,
    Number,
    SeqStm,
    AssignStm,
    IdentExpr,
    Eq,
    NoEq,
    Cond,
    Call,
    Function
};

class ASTNodePtr{
public:
    ASTNodePtr() = default;
    virtual::ClassType GetType() const = 0;
};

using ExprP = ASTNodePtr*;


class CondExpr: public ASTNodePtr
{
public:

    CondExpr(const ExprP& condition,
    const ExprP& stmt1,
    const ExprP& stmt2) : condition(condition), stmt1(stmt1), stmt2(stmt2)
    {}

    ClassType GetType() const override
    {
        return ClassType::Cond;
    }

    ExprP condition;
    ExprP stmt1;
    ExprP stmt2;
};


class EQExpr : public ASTNodePtr{
public:
    EQExpr(const ExprP &expr1,const ExprP &expr2):expr1(expr1),expr2(expr2){}
    ExprP expr1;
    ExprP expr2;


    ClassType GetType() const override
    {
        return ClassType::Eq;
    }
};

class NEQExpr : public ASTNodePtr{
public:
    NEQExpr(const ExprP &expr1,const ExprP &expr2):expr1(expr1),expr2(expr2){}
    ExprP expr1;
    ExprP expr2;


    ClassType GetType() const override
    {
        return ClassType::NoEq;
    }
};

class AddExpr : public ASTNodePtr{
public:
    AddExpr(const ExprP &expr1,const ExprP &expr2):expr1(expr1),expr2(expr2){}
    ExprP expr1;
    ExprP expr2;


    ClassType GetType() const override
    {
        return ClassType::AddExp;
    }
};

class SubExpr : public ASTNodePtr{
public:
    SubExpr(const ExprP &expr1,const ExprP &expr2):expr1(expr1),expr2(expr2){}
    ExprP expr1;
    ExprP expr2;


    ClassType GetType() const override
    {
        return ClassType::SubExp;
    }
};

class MulExpr : public ASTNodePtr{
public:
    MulExpr(const ExprP &expr1,const ExprP &expr2):expr1(expr1),expr2(expr2){}
    ExprP expr1;
    ExprP expr2;


    ClassType GetType() const override
    {
        return ClassType::MultExp;
    }
};

class DivExpr : public ASTNodePtr{
public:
    DivExpr(const ExprP &expr1,const ExprP &expr2):expr1(expr1),expr2(expr2){}
    ExprP expr1;
    ExprP expr2;


    ClassType GetType() const override
    {
        return ClassType::DivExp;
    }
};

class NumExpr : public ASTNodePtr{
public:
    NumExpr(const int &num):num(num){}
    int num;


    ClassType GetType() const override
    {
        return ClassType::Number;
    }
};

class IdentExpr : public ASTNodePtr{
public:
    IdentExpr(const std::string &ident):ident(ident){}
    std::string ident;


    ClassType GetType() const override
    {
        return ClassType::IdentExpr;
    }

};

class AssignStmt : public ASTNodePtr{
    public:
    AssignStmt(std::string id,const ExprP &expr):id(id), expr(expr){}
    std::string id;
    ExprP expr;

    ClassType GetType() const override
    {
        return ClassType::AssignStm;
    }
};


class CallExpr : public ASTNodePtr{
    public:
    CallExpr(std::string id,const std::vector<ExprP> &expr):id(id), expr(expr){}
    std::string id;
    std::vector<ExprP> expr;

    ClassType GetType() const override
    {
        return ClassType::AssignStm;
    }
};

class FuncExpr : public ASTNodePtr{
    public:
    
    FuncExpr(std::string id,const std::vector<std::string> &exprs,const ExprP &expr):id(id), exprs(exprs), expr(expr){}
    std::string id;
    std::vector<std::string> exprs;
    ExprP expr;

    ClassType GetType() const override
    {
        return ClassType::AssignStm;
    }
};


class Stmt;
using StmtPtr = std:: shared_ptr<Stmt>;
class Stmt : public ASTNodePtr
{
public:
    Stmt()
    {}
};

 class SeqStmt: public Stmt
 {
public:
    SeqStmt(const std::vector<StmtPtr>& stmts) : stmts(stmts)
    {}

    SeqStmt(std::vector<StmtPtr>&& stmts) : stmts(move(stmts))
    {}

    ClassType GetType() const override
    {
        return ClassType::SeqStm;
    }
     std::vector<StmtPtr> stmts;
 };
#endif