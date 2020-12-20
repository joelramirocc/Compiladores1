#include <stdexcept>
#include <iostream>
#include "stmtInterp.h"
using namespace std;

string  StmtInterp:: toString(const ExprPtr &node)
{
    switch(node->getClassType())
    {
        case ClassType::AddExp: 
        {
            string value = "";
            std::shared_ptr<AddExpr> n = std::dynamic_pointer_cast<AddExpr>(node);
            int min = n->expressions.size();
            int i = 0;
            for(const auto s : n->expressions) {
                if(i <= 0) {
                    value += "("+toString(s) + ")";
                }
                else {
                    value += "("+toString(s) + ") +";
                }
                i++;
            }
            value += "\n";
            return value;
        }
        case ClassType::SeqExp : 
        {
            string value = "";
            std::shared_ptr<SeqExpr> n = std::dynamic_pointer_cast<SeqExpr>(node);
            for(const auto s :  n.get()->stmts)
            {
                value += toString(s) + "\n";
            }
            return value;
        }
        case ClassType::AssignExp : 
        {
            std::shared_ptr<AssignExpr> n = std::dynamic_pointer_cast<AssignExpr>(node);
            return n->variable + " = " + toString(n->expr);
        }
        case ClassType::SubExp : 
        {
            string value = "";
            std::shared_ptr<SubExpr> n = std::dynamic_pointer_cast<SubExpr>(node);
            int min = n->expressions.size();
            int i = 0;
            for(const auto s : n->expressions) {
                if(i <= 0) {
                    value += "("+toString(s) + ")";
                }
                else {
                    value += "("+toString(s) + ") -";
                }
                i++;
            }
            value += "\n";
            return value;
        }
        case ClassType::PrintExp : 
        {
            string value = "print";
            std::shared_ptr<PrintExpr> n = std::dynamic_pointer_cast<PrintExpr>(node);
            for(const auto s : n->expressions)
            {
                value += toString(s) + ", ";
            }
            return value;
        }
        case ClassType::InputExp : 
        {
            std::shared_ptr<InputExpr> n = std::dynamic_pointer_cast<InputExpr>(node);
            return "input " + n->text + "\n";
        }
        case ClassType::MultExp : 
        {
            string value = "";
            std::shared_ptr<SubExpr> n = std::dynamic_pointer_cast<SubExpr>(node);
            int min = n->expressions.size();
            int i = 0;
            for(const auto s : n->expressions) {
                if(i <= 0) {
                    value += "("+toString(s) + ")";
                }
                else {
                    value += "("+toString(s) + ") *";
                }
                i++;
            }
            value += "\n";
            return value;
        }
        case ClassType::DivExp : 
        {
            string value = "";
            std::shared_ptr<DivExpr> n = std::dynamic_pointer_cast<DivExpr>(node);
            int min = n->expressions.size();
            int i = 0;
            for(const auto s : n->expressions) {
                if(i <= 0) {
                    value += "("+toString(s) + ")";
                }
                else {
                    value += "("+toString(s) + ") /";
                }
                i++;
            }
            value += "\n";
            return value;
        }
        case ClassType::PercentExp : 
        {
            string value = "";
            std::shared_ptr<PercentExpr> n = std::dynamic_pointer_cast<PercentExpr>(node);
            int min = n->expressions.size();
            int i = 0;
            for(const auto s : n->expressions) {
                if(i <= 0) {
                    value += "("+toString(s) + ")";
                }
                else {
                    value += "("+toString(s) + ") %";
                }
                i++;
            }
            value += "\n";
            return value;
        }
        case ClassType::ExponentExp : 
        {
            std::shared_ptr<ExpExpr> n = std::dynamic_pointer_cast<ExpExpr>(node);
            return "("+toString(n->expr1)+")**"+toString(n->expr2);
        }
        case ClassType::NumberExp : 
        {
            std::shared_ptr<Number> n = std::dynamic_pointer_cast<Number>(node);
            return std::to_string(n->value);
        }
        case ClassType::StringExp : 
        {
            std::shared_ptr<StringExpr> n = std::dynamic_pointer_cast<StringExpr>(node);
            return n->value;
        }
        case ClassType::IdentExp : 
        {
            std::shared_ptr<IdentExpr> n = std::dynamic_pointer_cast<IdentExpr>(node);
            return n->text;
        }
        case ClassType::ComparExp : 
        {
            std::shared_ptr<CompExpr> n = std::dynamic_pointer_cast<CompExpr>(node);
            return "("+toString(n->expr1)+")"+n->compareSymbol+"("+toString(n->expr2)+")";
        }
        case ClassType::IfExp : 
        {
            std::shared_ptr<IfExpr> n = std::dynamic_pointer_cast<IfExpr>(node);
            std::string str = "if "+toString(n->ifComparison)+"\n";
            str += toString(n->ifBlock);
            for(auto s: n->elseIfs) {
                str += toString(s)+"\n";
            }
            str += "else: \n"+toString(n->elseBlock);
            return str;
        }
        case ClassType::ElseExp : 
        {
            std::shared_ptr<ElseExpr> n = std::dynamic_pointer_cast<ElseExpr>(node);
            std::string str = "elif "+toString(n->elseIfComparison)+"\n";
            str += toString(n->elseIfBlock);
            return str;
        }
        case ClassType::WhileExp : 
        {
            std::shared_ptr<WhileExpr> n = std::dynamic_pointer_cast<WhileExpr>(node);
            return "while "+toString(n->comparison)+"\n"+toString(n->block);
        }
        case ClassType::ForExp : 
        {
            std::shared_ptr<ForExpr> n = std::dynamic_pointer_cast<ForExpr>(node);
            std::shared_ptr<AssignExpr> assign = std::dynamic_pointer_cast<AssignExpr>(n->assign);
            return "for "+assign->variable+" in range ("+toString(assign->expr)+", "+toString(n->loopLimit)+"):\n"+toString(n->block);
        }
        case ClassType::FuncExp : 
        {
            std::shared_ptr<FuncDecl> n = std::dynamic_pointer_cast<FuncDecl>(node);
            std::string str = "def "+n->identifier+"(";
            for(auto s : n->args) {
                str += toString(s)+",";
            }
            str += ")\n"+toString(n->stmts);
            return str;
        }
        case ClassType::FuncCallExp : 
        {
            std::shared_ptr<FuncCall> n = std::dynamic_pointer_cast<FuncCall>(node);
            std::string str = n->identifier+"(";
            for(auto s : n->args) {
                str += toString(s)+",";
            }
            str += ")\n";
            return str;
        }
        case ClassType::ReturnExp : 
        {
            std::shared_ptr<Return> n = std::dynamic_pointer_cast<Return>(node);
            return "return " + toString(n->expr);
        }

        default:
            throw runtime_error("invalid node");
        break;
    }
}




int  StmtInterp:: eval(const ASTNode* root)
{
    switch(root->getClassType())
    {
        case ClassType::AddExp: return this->visit(reinterpret_cast<const AddExpr*> (root));
        case ClassType::SeqExp : return this->visit(reinterpret_cast<const SeqExpr*> (root));
        case ClassType::AssignExp : return this->visit(reinterpret_cast<const AssignExpr*> (root));
        case ClassType::SubExp : return this->visit(reinterpret_cast<const SubExpr*> (root));
        case ClassType::PrintExp : return this->visit(reinterpret_cast<const PrintExpr*> (root));
        case ClassType::InputExp : return this->visit(reinterpret_cast<const InputExpr*> (root));
        case ClassType::MultExp : return this->visit(reinterpret_cast<const MultExpr*> (root));
        case ClassType::DivExp : return this->visit(reinterpret_cast<const DivExpr*> (root));
        case ClassType::PercentExp : return this->visit(reinterpret_cast<const PercentExpr*> (root));
        case ClassType::ExponentExp : return this->visit(reinterpret_cast<const ExpExpr*> (root));
        case ClassType::NumberExp : return this->visit(reinterpret_cast<const Number*> (root));
        case ClassType::StringExp : return this->visit(reinterpret_cast<const StringExpr*> (root));
        case ClassType::IdentExp : return this->visit(reinterpret_cast<const IdentExpr*> (root));
        case ClassType::ComparExp : return this->visit(reinterpret_cast<const CompExpr*> (root));
        case ClassType::IfExp : return this->visit(reinterpret_cast<const IfExpr*> (root));
        case ClassType::ElseExp : return this->visit(reinterpret_cast<const ElseExpr*> (root));
        case ClassType::WhileExp : return this->visit(reinterpret_cast<const WhileExpr*> (root));
        case ClassType::ForExp : return this->visit(reinterpret_cast<const ForExpr*> (root));
        case ClassType::FuncExp : return this->visit(reinterpret_cast<const FuncDecl*> (root));
        case ClassType::FuncCallExp : return this->visit(reinterpret_cast<const FuncCall*> (root));
        case ClassType::ReturnExp : return this->visit(reinterpret_cast<const Return*> (root));

        default:
            throw runtime_error("invalid node");
        break;
    }
}


int StmtInterp:: visit(const SeqExpr* expr)
{
    for(auto s : expr->stmts) {
        if(!this->reT) {
            if(s->getClassType() == ClassType::ReturnExp) {
                retVal = eval(s.get());
                this->reT = true;
                return 0;
            }
            else {
                eval(s.get());
            }  
        }  
    }
    return 0;
}

int StmtInterp:: visit(const AssignExpr* expr)
{
    if(!stacks.empty()) {
        auto it = stacks.top().find(expr->variable);
        if(it == stacks.top().end()) {
            stacks.top().insert(std::make_pair(expr->variable, eval(expr->expr.get())));
        }
        else {
            stacks.top()[expr->variable] = eval(expr->expr.get());
        }
    }

    int cv = eval(expr->expr.get());
    vars[expr->variable] = cv;

    return 0;
}

int StmtInterp:: visit(const PrintExpr* expr)
{
    for(const auto s : expr->expressions) {
        if(s->getClassType() == ClassType::StringExp) {
            std::cout << dynamic_pointer_cast<StringExpr>(s)->value;
        }
        else {
            std::cout << eval(s.get());
        }
    }
    std::cout << "" << std::endl;
    return 0;
}

int StmtInterp:: visit(const InputExpr* expr)
{
    std::cout << expr->text;
    int val;
    std::cin >> val;
    return val;
}

int StmtInterp:: visit(const AddExpr* expr)
{
    int tot = 0;
    for(const auto s : expr->expressions) {
        tot += eval(s.get());
    }
    return tot;
}

int StmtInterp:: visit(const SubExpr* expr)
{
    int tot = 0;
    for(const auto s : expr->expressions) {
        tot -= eval(s.get());
    }
    return tot;
}

int StmtInterp:: visit(const MultExpr* expr)
{
    int tot = 0, i = 0;
    for(const auto s : expr->expressions) {
        if(i == 0)
            tot = eval(s.get());
        else
            tot *= eval(s.get());        
    }
    return tot;
}

int StmtInterp:: visit(const PercentExpr* expr)
{
    int tot = 0, i = 0;
    for(const auto s : expr->expressions) {
        if(i == 0)
            tot = eval(s.get());
        else
            tot %= eval(s.get());        
    }
    return tot;
}

int StmtInterp:: visit(const DivExpr* expr)
{
    int tot = 0, i = 0;
    for(const auto s : expr->expressions) {
        if(i == 0)
            tot = eval(s.get());
        else
        {
            int val =eval(s.get());
            if(val == 0)
                 throw string("Divid by zero is not posible");
            tot /= eval(s.get());
        }
    }
    return tot;
}

int StmtInterp:: visit(const ExpExpr* expr)
{
    return pow(eval(expr->expr1.get()), eval(expr->expr2.get()));
}

int StmtInterp:: visit(const Number* expr)
{
    return expr->value;
}

int StmtInterp:: visit(const StringExpr* expr)
{
    return 0;
}

int StmtInterp:: visit(const IdentExpr* expr)
{
    if(!stacks.empty()) {
        auto it = stacks.top().find(expr->text);
        if(it != stacks.top().end()) {
            return it->second;
        }
    }

    return vars[expr->text];
}

int StmtInterp:: visit(const CompExpr* expr)
{
    if(expr->compareSymbol == "<") {
        return eval(expr->expr1.get()) < eval(expr->expr2.get());
    }
    else if(expr->compareSymbol == ">") {
        return eval(expr->expr1.get()) > eval(expr->expr2.get());
    }
    else if(expr->compareSymbol == "==") {
        return eval(expr->expr1.get()) == eval(expr->expr2.get());
    }
    else if(expr->compareSymbol == "<=") {
        return eval(expr->expr1.get()) <= eval(expr->expr2.get());
    }
    else if(expr->compareSymbol == ">=") {
        return eval(expr->expr1.get()) >= eval(expr->expr2.get());
    }
    else if(expr->compareSymbol == "!=") {
        return eval(expr->expr1.get()) != eval(expr->expr2.get());
    }

    return 0;
}

int StmtInterp:: visit(const IfExpr* expr)
{
    if(eval(expr->ifComparison.get())) {
        eval(expr->ifBlock.get());
    }
    else 
    {
        for(auto s : expr->elseIfs) {
            if(eval(s.get()) == 0) {
                return 0;
            }
        }
        eval(expr->elseBlock.get());
    }
    return 0;
}

int StmtInterp:: visit(const ElseExpr* expr)
{
    if(eval(expr->elseIfComparison.get())) {
        eval(expr->elseIfBlock.get());
        return 0;
    }

    return 1;
}

int StmtInterp:: visit(const WhileExpr* expr)
{
    while(eval(expr->comparison.get()))
    {
        eval(expr->block.get());
    }
    return 0;
}

int StmtInterp:: visit(const ForExpr* expr)
{
    shared_ptr<AssignExpr> assign = dynamic_pointer_cast<AssignExpr>(expr->assign);

    int s1 = eval(assign.get());
    int s2 = eval(expr->loopLimit.get());
 
    for(int i = s1; i < s2; i++) {
        eval(expr->block.get());
        vars[assign.get()->variable]++;
    }
    return 0;
}

int StmtInterp:: visit(const FuncDecl* expr)
{
    for(auto s : this->funcs) {
        if(s->identifier == expr->identifier) {
            throw string("Function already exist");
        }
    }

    funcs.push_back(expr);
    return 0;
}

int StmtInterp:: visit(const FuncCall* expr)
{
    if(expr->identifier == "len") {
        return this->retVal;
    }
    for(auto s : this->funcs) {
        if(s->identifier == expr->identifier) {
            if(expr->args.size() == s->args.size()) {
                std::map<std::string, int> funcVariables;
                for(int i = 0; i < s->args.size(); i++) {
                    funcVariables.insert(std::make_pair(toString(s->args[i]), eval(expr->args[i].get())));
                }
                stacks.push(funcVariables);
                eval(s->stmts.get());
                stacks.pop();
                int r = this->retVal;
                retVal = 0;
                this->reT = false;
                return r;
            }
            else if(expr->args.size() > s->args.size()){
                throw std::string("No same number of arguments passed");
            }
            else {
                throw std::string("No same number of arguments passed");
            }
        }
    }
    throw std::string("Function doesn't exist");
}

int StmtInterp:: visit(const Return* expr)
{
    return eval(expr->expr.get());
}