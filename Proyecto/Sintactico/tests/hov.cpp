#pragma once
#include<vector>
#include<iostream>
using namespace std;
class Sintactico
{
public:
	Sintactico()
	{
		
		aritmetics.push_back(Token::OperAdd);
		aritmetics.push_back(Token::OperSub);
		aritmetics.push_back(Token::OperAsterisk);
		 aritmetics.push_back(Token::OpDiv);
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
		
	}

	void program();
	void variableSection();
	void variableDeclaration();
	void lValue();
	void type();
	void arrayType();
	void subProgramDeclaration();
	void subProgramHeader();
	void functionHeader();
	void procedureHeader();
	void argumentDecl();
	void statement();
	void expr();
	void block();
	void assign();
	void conditionalOperator();
	void constant();
	void boolConstant();
	void binOperator();
	bool validate(Token token, bool c);
	bool validates(vector<Token> tokens, bool c);
	void consume();
	void assignOrSupProgram();
	void parse();
private:
	Token cT;
	vector<Token> aritmetics, rels, equals, conditionals, bools, constants;
};

