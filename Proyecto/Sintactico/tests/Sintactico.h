#pragma once
#include "tokens.h"
#include<vector>
#include<iostream>
#include "lexer.h"

using namespace std;
class Sintactico
{
public:
	Sintactico(Lexer& lexer): lexer(lexer)
	{
		aritmetics.push_back(Token::OperAdd);
		aritmetics.push_back(Token::OperSub);
		aritmetics.push_back(Token::OperAsterisk);
		 aritmetics.push_back(Token::KwDiv);
		aritmetics.push_back(Token::KwMod);
		aritmetics.push_back(Token::KwShl);
		aritmetics.push_back(Token::KwShr);
		 aritmetics.push_back(Token::LessLessThan);
		 aritmetics.push_back(Token::OperGreaterGreaterThan);


		rels.push_back(Token::OperLessThan);
		rels.push_back(Token::OperGreaterThan);
		rels.push_back(Token::OperLessOrEqualThan);
		rels.push_back(Token::OperGreaterOrEqualThan);


		equals.push_back(Token::OperDifferentThan);
		equals.push_back(Token::OperAssign);


		conditionals.push_back(Token::KwAnd);
		conditionals.push_back(Token::KwOr);
		conditionals.push_back(Token::KwXor);

		bools.push_back(Token::KwTrue);
		bools.push_back(Token::KwFalse);

		constants.push_back(Token::Number);//intconstant
		constants.push_back(Token::charConstant);

		types.push_back(Token::KwInteger);
		types.push_back(Token::KwBoolean);
		types.push_back(Token::KwChar);		

        statements.push_back(Token::ID);
        statements.push_back(Token::KwWrite);
        statements.push_back(Token::KwWriteln);
        statements.push_back(Token::KwRead);
        statements.push_back(Token::KwIf);
        statements.push_back(Token::KwWhile);
        statements.push_back(Token::KwRepeat);
        statements.push_back(Token::KwFor);
        statements.push_back(Token::KwBreak);
        statements.push_back(Token::KwContinue);
        statements.push_back(Token::OperSemiColon);

		this->argumentDeclarations.push_back(Token::KwVar);
		this->argumentDeclarations.push_back(Token::ID);

        assignOrSubPrograms.push_back(Token::ID);
        assignOrSubPrograms.push_back(Token::KwWrite);
        assignOrSubPrograms.push_back(Token::KwWriteln);
        assignOrSubPrograms.push_back(Token::KwRead);

		expressions.push_back(Token::OperSub);
		expressions.push_back(Token::KwNot);
		expressions.push_back(Token::OperOpenPar);
		expressions.push_back(Token::ID);
		expressions.push_back(Token::KwWrite);
		expressions.push_back(Token::KwWriteln);
		expressions.push_back(Token::KwRead);
		expressions.push_back(Token::Number); //intConstant
		expressions.push_back(Token::charConstant);
		expressions.push_back(Token::KwTrue);
		expressions.push_back(Token::KwFalse);


		arguments = expressions;
		arguments.push_back(Token::stringConstant);

		lvalueOrSubProgramCalls.push_back(Token::ID);
		lvalueOrSubProgramCalls.push_back(Token::KwWrite);
		lvalueOrSubProgramCalls.push_back(Token::KwWriteln);
		lvalueOrSubProgramCalls.push_back(Token::KwRead);
	}
	void parse();
	
private:
	void program();
	void variableSection();
	void variableDeclaration();
	void type();
	void arrayType();
	void subProgramDeclaration();
	void subProgramHeader();
	void functionHeader();
	void storeHeader();
	void argumentDeclaration();
	void statement();
	void assignOrSubProgram();
	void block();
	void assign();
	void subProgramCall();
	void argument();
	void lvalue();
	void expr();
	void exprP();
	void lvalueOrSubProgramCall();
	void binOperator();
	void aritOperator();
	void relOperator();
	void equalOperator();
	void conditionalOperator();
	void constant();
	void boolConstant();
	Lexer& lexer;
	bool validate(Token token, bool c);
	bool validates(vector<Token> tokens, bool c);
	void consume();
	Token cT;
	vector<Token> aritmetics, rels, equals, 
	conditionals, bools, constants, types,
	statements,argumentDeclarations, assignOrSubPrograms,
	expressions, arguments, lvalueOrSubProgramCalls;
};

