#ifndef _PARSER_H
#define _PARSER_H

#include <iosfwd>
#include "expr_lexer.h"

class Parser
{
public:
    Parser(Lexer& lexer, std::ostream& out): lexer(lexer), out(out)
    {}

    int parse();

private:
    Lexer& lexer;
    std::ostream& out;
    Symbol cT;
    bool Validate(Symbol t, bool consume);
    void Consume();
    void input();
    void smtList();
    void smtListP();
    void smt();
    void expression();
    void expressionP();
    void termino();
    void terminoP();
    void factor();
    std::string Tostring(Symbol s);
};

#endif
