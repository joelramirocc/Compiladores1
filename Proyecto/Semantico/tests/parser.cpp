#include "tokens.h"
#include "parser.h"

void Sintactico :: parse()
{
    consume();
    program();
    if(cT != Token::Eof)
    {
          throw string("Error logico EOF.");
    }
}

void Sintactico :: consume()
{
    this->cT = this->lexer.getNextToken();
}

bool Sintactico:: validates(std::vector<Token> tokens, bool c)
{
    bool found = false;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if(tokens[i] == this->cT)
        {
            found = true;
            break;
        }
    }
    if(found)
    {
        if(c)
            this->consume();
        return true;
    }
    return false;
}

bool  Sintactico :: validate(Token t, bool c)
{
    if(this->cT == t)
    {
        if(c)
            this->consume();
        return true;
    }
    return false;
}

ExprPtr Sintactico :: program()
{
    if(this->validate(Token::KwProgram,true))
    {
        if(this->validate(Token::ID,true))
        {
            if(this->validate(Token::OperSemiColon,true))
            {
                if(this->validate(Token::KwVar,false))
                {
                    this->variableSection();
                }

                vector<Token> subProgramDeclarations;
                subProgramDeclarations.push_back(Token::KwFunction);
                subProgramDeclarations.push_back(Token::KwProcedure);

                while (this->validates(subProgramDeclarations,false))
                {
                    this->subProgramDeclaration();
                }

                if(this->validate(Token::KwBegin,true))
                {
                    while (this->validates(statements,false))
                    {
                        this->statement();
                    }

                    if(this->validate(Token::KwEnd,true))
                    {
                        if(this->validate(Token::OpPoint,true))
                        {
                        }
                        else
                        {
                            throw string("Se esperaba [.]");
                        }
                    }
                    else
                    {
                        throw string("Se esperaba [end]");
                    }
                }
                else
                {
                    throw string("Se esperaba [begin]");
                }
            }
            else
            {
                throw string("Se esperaba [;]");
            }
        }
        else
        {
            throw string("Se esperaba [ID]");
        }
    }
    else
    {
        throw string("Se esperaba [program]");
    }
}

ExprPtr Sintactico :: variableSection()
{
    if(this->validate(Token::KwVar,true))
    {         
        if(this->validate(Token::ID,false))
        {
            while (this->validate(Token::ID,false))
            {
                this->variableDeclaration();
            }        
        }
        else
        {
            throw string("Se esperaba por lo menos un [ID]");
        }
    }
    else
    {
        throw string("Se esperaba [var]");
    }
}

ExprPtr Sintactico :: variableDeclaration()
{       
    if(this->validate(Token::ID,false))
    {
        while (this->validate(Token::ID,true))
        {
            if(this->validate(Token::OperComma,true))
            {
            }
            else
            {
                break;
            }
        }      

        if(this->validate(Token::OperColon,true))
        {
            this->type();

            if(this->validate(Token::OperSemiColon,true))
            {
            }
            else
            {
                throw string("Se esperaba [;]");
            }
        }
        else
        {
            throw string("Se esperaba [:]");
        }
          
    }
    else
    {
        throw string("Se esperaba por lo menos un [ID]");
    }
}

ExprPtr Sintactico :: type()
{
    if (this->validates(types,false))
    {
        this->consume();
    }
    else if(this->validate(Token::KwArray,false))
    {
        this->arrayType();
    }
    else
    {
        throw string("Se esperaba un tipo");
    }    
}

ExprPtr Sintactico :: arrayType()
{
    if(this->validate(Token::KwArray,true))
    {
        if(this->validate(Token::OperOpenSquare,true))
        {
            if(this->validate(Token::Number,true)) //intConstant
            {
                if(this->validate(Token::OpPointPoint,true))
                {
                    if(this->validate(Token::Number,true)) //intConstant
                    {
                        if(this->validate(Token::OperCloseSquare,true))
                        {
                            if(this->validate(Token::KwOf,true))
                            {
                                this->type();
                            }
                            else
                            {
                                throw string("Se esperaba [of]");
                            } 
                        }
                        else
                        {
                            throw string("Se esperaba [ ] ]");
                        }  
                    }
                    else
                    {
                        throw string("Se esperaba [intConstant]");
                    }  
                }
                else
                {
                    throw string("Se esperaba [..]");
                }  
            }
            else
            {
                throw string("Se esperaba [intConstant]");
            }  
        }
        else
        {
            throw string("Se esperaba [ [ ]");
        }  
    }
    else
    {
        throw string("Se esperaba [array]");
    }  
}

ExprPtr Sintactico :: subProgramDeclaration()
{
    this->subProgramHeader();

    if(this->validate(Token::KwVar,false))
    {
        this->variableSection();
    }

    if(this->validate(Token::KwBegin,true))
    {

        while (this->validates(statements,false))
        {
            this->statement();
        }
        
        if(this->validate(Token::KwEnd,true))
        {
            if(this->validate(Token::OperSemiColon,true))
            {

            }
            else
            {
                throw string("Se esperaba [;]");
            }  
        }
        else
        {
            throw string("Se esperaba [end]");
        }  
    }
    else
    {
        throw string("Se esperaba [begin]");
    }  
}

ExprPtr Sintactico :: subProgramHeader()
{
    if(this->validate(Token::KwFunction,false))
    {
        this->functionHeader();
    }
    else if(this->validate(Token::KwProcedure,false))
    {
        this->storeHeader();
    }
    else
    {
        throw string("Se esperaba header de subprograma");
    }
}

ExprPtr Sintactico :: functionHeader()
{
    if(this->validate(Token::KwFunction,true))
    {
        if(this->validate(Token::ID,true))
        {
            
            if(this->validate(Token::OperOpenPar,true))
            {

                while(this->validates(this->argumentDeclarations,false))
                {
                    this->argumentDeclaration();
                    
                    if(this->validate(Token::OperSemiColon,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }

                if(this->validate(Token::OperClosePar,true))
                {
                }
                else
                {
                    throw string("Se esperaba [)]");
                }
            }

            if(this->validate(Token::OperColon,true))
            {
                this->type();

                if(this->validate(Token::OperSemiColon,true))
                {
                }
                else
                {
                    throw string("Se esperaba [;]");
                }
            }
            else
            {
                throw string("Se esperaba [:]");
            }
        }
        else
        {
            throw string("Se esperaba [ID]");
        }
    }
    else
    {
        throw string("Se esperaba [function]");
    }
}

ExprPtr Sintactico :: storeHeader()
{
    if(this->validate(Token::KwProcedure,true))
    {
        if(this->validate(Token::ID,true))
        {
            
            if(this->validate(Token::OperOpenPar,true))
            {

                while(this->validates(this->argumentDeclarations,false))
                {
                    this->argumentDeclaration();
                    
                    if(this->validate(Token::OperSemiColon,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }

                if(this->validate(Token::OperClosePar,true))
                {
                }
                else
                {
                    throw string("Se esperaba [)]");
                }
            }

            if(this->validate(Token::OperSemiColon,true))
            {
            }
            else
            {
                throw string("Se esperaba [;]");
            }
        }
        else
        {
            throw string("Se esperaba [ID]");
        }
    }
    else
    {
        throw string("Se esperaba [procedure]");
    }
}

ExprPtr Sintactico :: argumentDeclaration()
{
    if(this->validate(Token::KwVar,true))
    {
        if(this->validate(Token::ID,true))
        {
            if(this->validate(Token::OperColon,true))
            {
                this->type();
            }
            else
            {
                throw string("Se esperaba [:]");
            }
        }
        else
        {
            throw string("Se esperaba [ID]");
        }
    }
    else  if(this->validate(Token::ID,true))
    {
        if(this->validate(Token::OperColon,true))
        {
            this->type();
        }
        else
        {
            throw string("Se esperaba [:]");
        }
    }
    else
    {
        throw string("Se esperaba [var] o [ID]");
    }
}

ExprPtr Sintactico :: statement()
{
    if (this->validates(this->statements,false))
    {
        if(this->validates(assignOrSubPrograms,false))
        {
            this->assignOrSubProgram();

            if (this->validate(Token::OperSemiColon,true))
            {
                
            }
            else
            {
                throw string("Se esperaba [;]");
            }
        }
        else if (this->validate(Token::KwIf,true))
        {
            this->expr();

            if (this->validate(Token::KwThen,true))
            {
                this->block();

                if (this->validate(Token::KwElse,true))
                {
                    this->block();
                }
            }
            else
            {
                throw string("Se esperaba [then]");
            }
        }
        else if (this->validate(Token::KwWhile,true))
        {
            this->expr();

            if (this->validate(Token::KwDo,true))
            {
                this->block();
            }
            else
            {
                throw string("Se esperaba [do]");
            }
        }
        else if (this->validate(Token::KwRepeat,true))
        {
            this->block();

            if (this->validate(Token::KwUntil,true))
            {
                this->expr();

                if (this->validate(Token::OperSemiColon,true))
                {
                    
                }
                else
                {
                    throw string("Se esperaba [;]");
                }
            }
            else
            {
                throw string("Se esperaba [until]");
            }
        }
        else if (this->validate(Token::KwFor,true))
        {
            this->assign();
            this->expr();

            if (this->validate(Token::KwTo,true))
            {
                this->expr();

                if (this->validate(Token::KwDo,true))
                {
                    this->block();
                }
                else
                {
                    throw string("Se esperaba [do]");
                }
            }
            else
            {
                throw string("Se esperaba [to]");
            }
        }
        else if (this->validate(Token::KwBreak,true))
        {
            if (this->validate(Token::OperSemiColon,true))
            {
                
            }
            else
            {
                throw string("Se esperaba [;]");
            }
        }
        else if (this->validate(Token::KwContinue,true))
        {
            if (this->validate(Token::OperSemiColon,true))
            {
                
            }
            else
            {
                throw string("Se esperaba [;]");
            }
        }
        else if (this->validate(Token::OperSemiColon,true))
        {}
    }
    else
    {
        throw string("Se esperaba statement");
    }
}

ExprPtr Sintactico :: assignOrSubProgram()
{
    if (this->validate(Token::ID,true))
        {
            vector <Token> options;
            options.push_back(Token::OperOpenSquare);
            options.push_back(Token::OpColonAssign);

            if (this->validates(options,false))
            {
                if (this->validate(Token::OperOpenSquare,true))
                {
                    this->expr();

                    if (this->validate(Token::OperCloseSquare,true))
                    {
                        
                    }
                    else
                    {
                        throw string("Se esperaba [ ] ]");
                    }
                }

                if (this->validate(Token::OpColonAssign,true))
                {
                    this->expr();
                }
                else
                {
                    throw string("Se esperaba [ := ]");
                }
            }
            else if (this->validate(Token::OperOpenPar,true))
            {
                if(this->validates(expressions,false))
                {
                    while(this->validates(expressions,false))
                    {
                        this->expr();
                        if(this->validate(Token::OperComma,true))
                        {
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if (this->validate(Token::OperClosePar,true))
                {
                    
                }
                else
                {
                    throw string("Se esperaba [)]");
                }
            }
            else
            {
            }
        }
    else if(this->validate(Token::KwWrite,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            if(this->validates(arguments,false))
            {
                while (this->validates(arguments,false))
                {
                    this->argument();
                    if(this->validate(Token::OperComma,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                throw string("Se espera por lo menos 1 argumento");
            }

            if(this->validate(Token::OperClosePar,true))
            {

            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else if(this->validate(Token::KwWriteln,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            while (this->validates(arguments,false))
            {
                this->argument();
                if(this->validate(Token::OperComma,true))
                {
                }
                else
                {
                    break;
                }
            }    

            if(this->validate(Token::OperClosePar,true))
            {
            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
    }
    else if(this->validate(Token::KwRead,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            if (this->validates(arguments,false))
            {
                while (this->validates(arguments,false))
                {
                    this->argument();
                    if(this->validate(Token::OperComma,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }

                if(this->validate(Token::OperClosePar,true))
                {
                }
                else
                {
                    throw string("Se esperaba [)]");
                }
            }
            else
            {
                throw string("Se espera por lo menos un argumento");
            }  
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else
    {
        throw string("Se esperaba [asignment] o [subProgram]");
    }
}

ExprPtr Sintactico :: block()
{
    if (this->validates(statements,false))
    {
        this->statement();
    }
    else if(this->validate(Token::KwBegin,true))
    {
        while(this->validates(statements,false))
        {
            this->statement();
        } 

        if(this->validate(Token::KwEnd,true))
        {
        }
        else
        {
            throw string("Se esperaba [end]");
        }
    }
    else
    {
        throw string("Se esperaba [begin] o [statement]");
    }
}

ExprPtr Sintactico :: assign()
{
    this->lvalue();
    
    if(this->validate(Token::OpColonAssign,true))
    {
        this->expr();
    }
    else
    {
        throw string("Se esperaba [:=]");
    }
}

ExprPtr Sintactico :: subProgramCall()
{
    if(this->validate(Token::ID,true))
    {
        if (this->validate(Token::OperOpenPar,true))
        {
            while(this->validates(expressions,false))
            {
                this->expr();
                if(this->validate(Token::OperComma,true))
                {
                }
                else
                {
                    break;
                }
            }
            
            
            if (this->validate(Token::OperClosePar,true))
            {
                
            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
    }
    else if(this->validate(Token::KwWrite,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            if(this->validates(arguments,false))
            {
                while (this->validates(arguments,false))
                {
                    this->argument();
                    if(this->validate(Token::OperComma,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                throw string("Se espera por lo menos 1 argumento");
            }

            if(this->validate(Token::OperClosePar,true))
            {

            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else if(this->validate(Token::KwWriteln,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            while (this->validates(arguments,false))
            {
                this->argument();
                if(this->validate(Token::OperComma,true))
                {
                }
                else
                {
                    break;
                }
            }    

            if(this->validate(Token::OperClosePar,true))
            {
            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
    }
    else if(this->validate(Token::KwRead,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            if (this->validates(arguments,false))
            {
                while (this->validates(arguments,false))
                {
                    this->argument();
                    if(this->validate(Token::OperComma,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }

                if(this->validate(Token::OperClosePar,true))
                {
                }
                else
                {
                    throw string("Se esperaba [)]");
                }
            }
            else
            {
                throw string("Se espera por lo menos un argumento");
            }  
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else
    {
        throw string("Se esperaba [asignment] o [subProgram]");
    }
}

ExprPtr Sintactico :: argument()
{
    if(this->validate(Token::stringConstant,true))
    {

    }
    else if(this->validates(expressions,false))
    {
        this->expr();
    }
    else
    {
        throw string("Se esperaba [stringConstant] o [expression]");
    }
}

ExprPtr Sintactico :: lvalue()
{
    if(this->validate(Token::ID,true))
    {
        if(this->validate(Token::OperOpenSquare,true))
        {
            this->expr();

            if(this->validate(Token::OperCloseSquare,true))
            {
            }
            else
            {
                throw string("Se esperaba [ ] ]");
            }
        }
    }
    else
    {
        throw string("Se esperaba [ID]");
    }
}

ExprPtr Sintactico :: expr()
{
    if(this->validates(lvalueOrSubProgramCalls,false))
    {
        this->lvalueOrSubProgramCall();
        this->exprP();
    }
    else if (this->validates(constants,false))
    {
        this->constant();
        this->exprP();
    }
    else if (this->validate(Token::OperSub,true))
    {
        this->expr();
        this->exprP();
    }
    else if (this->validate(Token::KwNot,true))
    {
        this->expr();
        this->exprP();
    }
    else if (this->validate(Token::OperOpenPar,true))
    {
        this->expr();

        if(this->validate(Token::OperClosePar,true))
        {
            this->exprP();
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else
    {
        throw string("Se esperaba [expression]");
    }
}

ExprPtr Sintactico :: exprP()
{
    if(this->validates(this->aritmetics,false))
    {
        this->binOperator();
        this->expr();
        this->exprP();
    } else if(this->validates(this->rels,false))
    {
        this->binOperator();
        this->expr();
        this->exprP();
    }else if(this->validates(this->equals,false))
    {
        this->binOperator();
        this->expr();
        this->exprP();
    }else if(this->validates(this->conditionals,false))
    {
        this->binOperator();
        this->expr();
        this->exprP();
    }
}

ExprPtr Sintactico :: lvalueOrSubProgramCall()
{
    if(this->validate(Token::ID,true))
    {
        if(this->validate(Token::OperOpenSquare,true))
        {
            this->expr();

            if(this->validate(Token::OperCloseSquare,true))
            {
            }
            else
            {
                throw string("Se esperaba [ ] ]");
            }
        }
        else if(this->validate(Token::OperOpenPar,true))
        {
            while (this->validates(this->expressions,false))
            {
                this->expr();

                if(this->validate(Token::OperComma,true))
                {

                }
                else
                {
                    break;
                }
            }
            

            if(this->validate(Token::OperClosePar,true))
            {
            }
            else
            {
                throw string("Se esperaba [ ) ]");
            }
        }
        else
        {

        }
    }
    else if(this->validate(Token::KwWrite,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            if(this->validates(arguments,false))
            {
                while (this->validates(arguments,false))
                {
                    this->argument();
                    if(this->validate(Token::OperComma,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                throw string("Se espera por lo menos 1 argumento");
            }

            if(this->validate(Token::OperClosePar,true))
            {

            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else if(this->validate(Token::KwWriteln,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            while (this->validates(arguments,false))
            {
                this->argument();
                if(this->validate(Token::OperComma,true))
                {
                }
                else
                {
                    break;
                }
            }    

            if(this->validate(Token::OperClosePar,true))
            {
            }
            else
            {
                throw string("Se esperaba [)]");
            }
        }
    }
    else if(this->validate(Token::KwRead,true))
    {
        if(this->validate(Token::OperOpenPar,true))
        {
            if (this->validates(arguments,false))
            {
                while (this->validates(arguments,false))
                {
                    this->argument();
                    if(this->validate(Token::OperComma,true))
                    {
                    }
                    else
                    {
                        break;
                    }
                }

                if(this->validate(Token::OperClosePar,true))
                {
                }
                else
                {
                    throw string("Se esperaba [)]");
                }
            }
            else
            {
                throw string("Se espera por lo menos un argumento");
            }  
        }
        else
        {
            throw string("Se esperaba [(]");
        }
    }
    else
    {
        throw string("Se esperaba [lvalue] o [subProgramCall]");
    }
}

ExprPtr Sintactico :: binOperator()
{
    if(this->validates(aritmetics,false))
    {
        this->aritOperator();
    }
    else if(this->validates(rels,false))
    {
        this->relOperator();
    }
    else if(this->validates(equals,false))
    {
        this->equalOperator();
    }
    else if(this->validates(conditionals,false))
    {
        this->conditionalOperator();
    }
    else 
    {
        throw string("Se esperaba operador binario");
    }
}

ExprPtr Sintactico :: aritOperator()
{
    if(this->validates(aritmetics,false))
    {
        this->consume();
    }
    else
    {
        throw string("Se esperaba operador aritmetrico");
    }
}

ExprPtr Sintactico :: relOperator()
{
    if(this->validates(rels,false))
    {
        this->consume();
    }
    else
    {
        throw string("Se esperaba operador relacional");
    }
}

ExprPtr Sintactico :: equalOperator()
{
    if(this->validates(equals,false))
    {
        this->consume();
    }
    else
    {
        throw string("Se esperaba operador de igualdad");
    }
}

ExprPtr Sintactico :: conditionalOperator()
{
    if(this->validates(conditionals,false))
    {
        this->consume();
    }
    else
    {
        throw string("Se esperaba operador condicional");
    }
}

ExprPtr Sintactico :: constant()
{
    if(this->validates(constants,false))
    {
        this->consume();
    }
    else if (this->validates(bools,false))
    {
        this->boolConstant();
    }
    else
    {
        throw string("Se esperaba constante");
    }
}

ExprPtr Sintactico :: boolConstant()
{
    if(this->validates(this->bools,false))
    {
        switch (this->cT)
        {
        default:
            break;
        }

        this->consume();
    }
    else
    {
        throw string("Se esperaba boolean");
    }
}