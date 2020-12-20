#ifndef _STMT_INTERP_H
#define _STMT_INTERP_H
#include "ASTNode.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <stack>
#include <memory>
#include <math.h>

class StmtInterp
{
public:
    StmtInterp(){}

    int eval(const ASTNode* root);
    string toString(const ExprPtr &node);

private:
    int visit(const SeqExpr* expr);
    int visit(const AssignExpr* expr);
    int visit(const PrintExpr* expr);
    int visit(const InputExpr* expr);
    int visit(const AddExpr* expr);
    int visit(const SubExpr* expr);
    int visit(const MultExpr* expr);
    int visit(const DivExpr* expr);
    int visit(const PercentExpr* expr);
    int visit(const ExpExpr* expr);
    int visit(const Number* expr);
    int visit(const StringExpr* expr);
    int visit(const IdentExpr* expr);
    int visit(const CompExpr* expr);
    int visit(const IfExpr* expr);
    int visit(const ElseExpr* expr);
    int visit(const WhileExpr* expr);
    int visit(const ForExpr* expr);
    int visit(const FuncDecl* expr);
    int visit(const FuncCall* expr);
    int visit(const Return* expr);
    
    vector<const FuncDecl*> funcs;
    unordered_map<string,int> vars;
    stack<map<string, int>> stacks;
    int retVal; 
    bool reT = false;
};

#endif