#ifndef _STMT_INTERP_H
#define _STMT_INTERP_H
#include "spl_ast.h"
#include <unordered_map>
#include<map>


class StmtInterp
{
using Table = std::unordered_map<std::string,int>;
public:
Table t;
    StmtInterp(){}
    Table exec(const ASTNodePtr* root)
    {
        eval(root);
        return t;
    };

    int eval(const ASTNodePtr* root);

private:
    int visit(const AddExpr* expr);
    int visit(const SubExpr* expr);
    int visit(const DivExpr* expr);
    int visit(const MulExpr* expr);
    int visit(const NumExpr* expr);
    int visit(const SeqStmt* expr);
    int visit(const AssignStmt* expr);
    int visit(const IdentExpr* expr);
    int visit(const EQExpr* expr);
    int visit(const NEQExpr* expr);
    int visit(const CondExpr* expr);
    int visit(const CallExpr* expr);
    int visit(const FuncExpr* expr);
};

#endif