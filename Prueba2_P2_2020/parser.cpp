#include "parser.h"

bool Parser::Validate(Token t, bool consume)
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

void Parser::parse()
{
    this->Consume();
    this->input();
    if(this->Validate(Token::Eof,true))
    {
        std::cout<<"Correcto"<<std::endl;
    }
    else
    {
        throw std::string("Se esperaba EOF");
    }
}

void Parser::Consume()
{
    this->cT = this->l.getNextToken();
}

void Parser::input()
{
    stmt_list();
}

void Parser::stmt_list()
{
    stmt();
    stmt_listP();
}

void Parser::stmt_listP()
{
    stmt();
    if(this->Validate(Token::Semicolon,true))
    {
        stmt_listP();
    }
}

void Parser::stmt()
{
    if(this->Validate(Token::KwPrint,true))
    {
        expr();
    }
    else if(this->Validate(Token::Ident,true))
    {
        assign();
    }    
}

void Parser::assign()
{
    if(this->Validate(Token::OpAssign,true))
    {
        expr();
    }
    else if(this->Validate(Token::OpenPar,true))
    {
            arg();
             if(this->Validate(Token::ClosePar,true))
             {
                  if(this->Validate(Token::OpAssign,true))
                  {
                      expr();
                  }
                    else
                    {
                        throw std::string("Se esperaba =");
                    }
             }
            else
            {
                throw std::string("Se esperaba )");
            }
    }
    else
    {
        throw std::string("Se esperaba = o (");
    }
}

void Parser::arg()
{
    if(this->Validate(Token::Number,false) || this->Validate(Token::Ident,false))
    {
        this->Consume();
    }
    else
    {
        throw std::string("Se esperaba Number o Identifier");
    }
}

void Parser::expr()
{
    term();
    exprP();
}

void Parser::exprP()
{
    if(this->Validate(Token::OpAdd,false) || this->Validate(Token::OpSub,false))
    {
        this->Consume();
        term();
        exprP();
    }
}

void Parser::term()
{
    factor();
    termP();
}

void Parser::termP()
{
    if(this->Validate(Token::OpMul,true))
    {
        factor();
        termP();
    }
}

void Parser::factor()
{
    if(this->Validate(Token::Number,false) || this->Validate(Token::Ident,false))
    {
        this->Consume();
    }
    else if(this->Validate(Token::OpenPar,true))
    {
        expr();
        if(!this->Validate(Token::ClosePar,true))
        {
            throw std::string("Se esperaba )");
        }
    }
    else
    {
        throw std::string("Se esperaba Number, Identifier o (");
    }
}