#ifndef _EXPR_PARSER_H
#define _EXPR_PARSER_H

#include <iosfwd>
#include "lexer.h"

class Parser
{
public:
    Parser(Lexer& l): l(l)
    {
    };

    void parse();

private:
    Token cT;
    bool Validate(Token t, bool consume);
    void Consume();
    Lexer& l;
    void input();
    void stmt_list();
    void stmt_listP();
    void stmt();
    void assign();
    void arg();
    void expr();
    void exprP();
    void term();
    void termP();
    void factor();
};

#endif
