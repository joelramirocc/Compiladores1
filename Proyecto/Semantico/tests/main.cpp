#include <iostream>
#include <fstream>
#include <vector>
#include "lexer.h"
#include "stmtInterp.h"
/*
#define ADD(a,b) std::make_shared<AddExpr>(a,b)
#define SUB(a,b) std::make_shared<SubExpr>(a,b)
#define MULT(a,b) std::make_shared<MultExpr>(a,b)
#define DIV(a,b) std::make_shared<DivExpr>(a,b)
#define NUMBER(n) std::make_shared<NumberExpr>(n)
#define IDEN(n) std::make_shared<IdentExpr>(n)
#define ASSIGN(a,b) std::make_shared<AssignStmt>(a,b)
#define PRINT(n) std::make_shared<PrintStmt>(n)

#define IF(a,b,c) std::make_shared<IfStmt>(a,b,c)
#define WHILE(a,b) std::make_shared<WhileStmt>(a,b)
#define FOR(a,b,c) std::make_shared<ForStmt>(a,b,c)
#define SEQ std::make_shared<SeqStmt>
*/
using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input.is_open())
    {
        std::cerr << "Cannot open '" << argv[1] << "'\n";
        return 1;
    }
    
    try
    {
    }
    catch (const std::string e)
    {
        std::cout<<"Error:"<<e<<std::endl;
    }
}