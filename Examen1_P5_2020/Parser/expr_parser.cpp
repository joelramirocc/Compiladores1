#include "expr_parser.h"

bool Parser::Validate(Symbol t, bool consume)
{
    if(this->cT == t)
    {
        if(consume)
        {
            this->Consume();
        }
        return true;
    }
    
    return false;
}


std::string Parser::Tostring(Symbol s)
{
    switch (s)
    {
        case Symbol::ClosePar:
            return ")";
        case Symbol::Eof:
            return "";
        case Symbol::Eol:
            return ";";
        case Symbol::Ident:
            return "identifier";
        case Symbol::Number:
            return "number";
        case Symbol::OpAdd:
            return "+";
        case Symbol::OpAssign:
            return "=";
        case Symbol::OpDiv:
            return "/";
        case Symbol::OpMul:
            return "*";
        case Symbol::OpSub:
            return "-";
        case Symbol::OpenPar:
            return "(";
        case Symbol::Print:
            return "print";
        case Symbol::SemiColon:
            return ";";
        default:
            return "Unknown";
    }
}

void Parser::Consume()
{
    this->cT = this->lexer.getNextSymbol();
    this->out<<this->Tostring(this->cT);
}

int Parser::parse()
{
    this->Consume();
    this->input();
    if(this->Validate(Symbol::Eof,true))
    {
        std::cout<<"Correcto"<<std::endl;
    }
    else
    {
        throw std::string("Se esperaba EOF");
    }
    return 0;
}



void Parser::input()
{
    smtList();
}

void Parser::smtList()
{
    smt();
    smtListP();
}

void Parser::smtListP()
{
    if(Validate(Symbol::Eol,true))
    {
        smt();
        smtListP();
    }
}

void Parser::smt()
{
    if(Validate(Symbol::Print,true))
    {
        if(Validate(Symbol::OpenPar,true))
        {
            expression();
            if(!Validate(Symbol::ClosePar,true))
            {
                throw std::string("Se esperaba )");
            }
        }
        else
        {
            throw std::string("Se esperaba (");
        }
    }
    else if(Validate(Symbol::Ident,true))
    {
        if(Validate(Symbol::OpAssign,true))
        {
            expression();
        }
        else
        {
            throw std::string("Se esperaba =");
        }
    }
    
}

void Parser::expression()
{
    termino();
    expressionP();
}

void Parser::expressionP()
{
    if(Validate(Symbol::OpAdd,false) || Validate(Symbol::OpSub,false))
    {
        Consume();
        termino();
        expressionP();
    }
}

void Parser::termino()
{
    factor();
    terminoP();
}

void Parser::terminoP()
{
    if(Validate(Symbol::OpMul,false) || Validate(Symbol::OpDiv,false))
    {
        Consume();
        factor();
        terminoP();
    }
}

void Parser::factor()
{
    if(Validate(Symbol::Number,false) || Validate(Symbol::Ident,false))
    {
        Consume();
    }
    else if(Validate(Symbol::OpenPar,true))
    {
        expression();
        if(!Validate(Symbol::ClosePar,true))
        {
            throw std::string("Se esperaba )");
        }
    }
    else
    {
        throw std::string("Se esperaba Number, Ident o (");
    }
    
}