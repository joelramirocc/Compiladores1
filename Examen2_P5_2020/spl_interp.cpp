#include <stdexcept>
#include <iostream>
#include "spl_interp.h"

using namespace std;


int StmtInterp:: eval(const ASTNodePtr* root)
{
    switch(root->GetType())
    {
        case ClassType:: AddExp:
        return this->visit(reinterpret_cast<const AddExpr*> (root));
        break;
        case ClassType:: SubExp:
        return this->visit(reinterpret_cast<const SubExpr*> (root));
        break;
        case ClassType:: MultExp:
        return this->visit(reinterpret_cast<const MulExpr*> (root));
        break;
        case ClassType:: DivExp:
        return this->visit(reinterpret_cast<const DivExpr*> (root));
        break;
        case ClassType:: Number:
        return this->visit(reinterpret_cast<const NumExpr*> (root));
        break;
        case ClassType:: IdentExpr:
        return this->visit(reinterpret_cast<const IdentExpr*> (root));
        break;
        case ClassType:: SeqStm:
        return this->visit(reinterpret_cast<const SeqStmt*> (root));
        break;
        case ClassType:: AssignStm:
        return this->visit(reinterpret_cast<const AssignStmt*> (root));
        break;
        case ClassType:: Eq:
        return this->visit(reinterpret_cast<const EQExpr*> (root));
        break;
        case ClassType:: NoEq:
        return this->visit(reinterpret_cast<const NEQExpr*> (root));
        break;
        case ClassType:: Cond:
        return this->visit(reinterpret_cast<const CondExpr*> (root));
        break;
        case ClassType:: Call:
        return this->visit(reinterpret_cast<const CallExpr*> (root));
        break;
        case ClassType:: Function:
        return this->visit(reinterpret_cast<const FuncExpr*> (root));
        break;
        default:
            throw runtime_error("invalid node");
        break;
    }
}

int  StmtInterp:: visit(const AddExpr* expr)
{
    int n1 = eval(expr->expr1);
    int n2 = eval(expr->expr2);

    return n1+n2;
}

int  StmtInterp:: visit(const SubExpr* expr)
{
    int n1 = eval(expr->expr1);
    int n2 = eval(expr->expr2);

    return n1-n2;
}

int  StmtInterp:: visit(const DivExpr* expr)
{
    int n1 = eval(expr->expr1);
    int n2 = eval(expr->expr2);

    return n1/n2;
}

int  StmtInterp:: visit(const MulExpr* expr)
{
    int n1 = eval(expr->expr1);
    int n2 = eval(expr->expr2);
    return n1*n2;
}

int  StmtInterp:: visit(const NumExpr* expr)
{
    return expr->num;
}


int  StmtInterp:: visit(const CondExpr* stmt)
{
    int cv = eval(stmt->condition);
    if(cv)
        return eval(stmt->stmt1);
    else if (stmt->stmt2 != nullptr)
        return eval(stmt->stmt2);

    return 0;
}

int  StmtInterp:: visit(const SeqStmt* stmt)
{
    for(const auto& s : stmt->stmts)
        eval(s.get());
    
    return 0;
}

int  StmtInterp:: visit(const AssignStmt* stmt)
{
    int cv = eval(stmt->expr);
    t[stmt->id] = cv;
}

int  StmtInterp:: visit(const IdentExpr* expr)
{
    return t[expr->ident];
}

int StmtInterp::visit(const EQExpr* expr)
{
    return 0;
}

int StmtInterp::visit(const NEQExpr* expr)
{
    return 0;
}


int  StmtInterp::visit(const CallExpr* expr)
{
    return 0;
}
int StmtInterp:: visit(const FuncExpr* expr)
{
    return 0;
}
