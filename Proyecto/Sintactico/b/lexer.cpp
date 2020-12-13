#include "lexer.h"
using namespace std;
enum class State {
    start_q0,
    comments_q0,
    comments_q1,
    comments_q2,
    comments_q3,
    comments_q6,
    comments_q9,
    number_q0,
    number_q1,
    number_q2,
    number_q3,
    number_q6,
    number_q7,
    operators_q0,
    operators_q1,
    operators_q10,
    operators_q11,
    operators_q13,
    operators_q15,
    operators_q16,
    operators_q19,
    operators_q2,
    operators_q20,
    operators_q21,
    operators_q23,
    operators_q3,
    operators_q33,
    operators_q36,
    operators_q38,
    operators_q4,
    operators_q40,
    operators_q42,
    operators_q44,
    operators_q5,
    operators_q7,
    operators_q8,
    operators_q9,
    identifier_q0,
    identifier_q1,
    strCharConstant_q0,
    strCharConstant_q1,
    strCharConstant_q12,
    strCharConstant_q13,
    strCharConstant_q3,
    strCharConstant_q4,
    strCharConstant_q8,
    strCharConstant_q9,
};

Token Lexer::getNextToken()
{
    text = "";
    State state = State::start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // start
            case State::start_q0:
                if ((ch == '\n') || (ch == ' ')) {
                    state = State::start_q0;
                    ch = getNextChar();
                }
                else if (ch == EOF) {
                    text += ch;
                    return Token::Eof;
                }
                else {
                    // Trying next automaton 'comments
                    state = State::comments_q0;
                }
                break;
            // comments
            case State::comments_q0:
                if (ch == '/') {
                    text += ch;
                    state = State::comments_q1;
                    ch = getNextChar();
                }
                else if (ch == '{') {
                    state = State::comments_q6;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'number
                    state = State::number_q0;
                }
                break;
            case State::comments_q1:
                if (ch == '/') {
                    state = State::comments_q2;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OpDiv;
                }
                break;
            case State::comments_q2:
                text="";;
                if ((ch == '\n') || (ch == EOF)) {
                    state = State::comments_q3;
                    ch = getNextChar();
                }
                else {
                    state = State::comments_q2;
                    ch = getNextChar();
                }
                break;
            case State::comments_q3:
                state = State::start_q0;
                break;
            case State::comments_q6:
                if (ch == '}') {
                    state = State::comments_q9;
                    ch = getNextChar();
                }
                else {
                    state = State::comments_q6;
                    ch = getNextChar();
                }
                break;
            case State::comments_q9:
                state = State::start_q0;
                break;
            // number
            case State::number_q0:
                if (ch == '%') {
                    text += ch;
                    state = State::number_q1;
                    ch = getNextChar();
                }
                else if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::number_q2;
                    ch = getNextChar();
                }
                else if (ch == '$') {
                    text += ch;
                    state = State::number_q3;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'operators
                    state = State::operators_q0;
                }
                break;
            case State::number_q1:
                if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = State::number_q7;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'operators
                    state = State::operators_q0;
                }
                break;
            case State::number_q2:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::number_q2;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            case State::number_q3:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
                    text += ch;
                    state = State::number_q6;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'operators
                    state = State::operators_q0;
                }
                break;
            case State::number_q6:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::number_q6;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            case State::number_q7:
                if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = State::number_q7;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            // operators
            case State::operators_q0:
                if (ch == ',') {
                    text += ch;
                    state = State::operators_q3;
                    ch = getNextChar();
                }
                else if (ch == '+') {
                    text += ch;
                    state = State::operators_q4;
                    ch = getNextChar();
                }
                else if (ch == '=') {
                    text += ch;
                    state = State::operators_q1;
                    ch = getNextChar();
                }
                else if (ch == '[') {
                    text += ch;
                    state = State::operators_q2;
                    ch = getNextChar();
                }
                else if (ch == ']') {
                    text += ch;
                    state = State::operators_q7;
                    ch = getNextChar();
                }
                else if (ch == ')') {
                    text += ch;
                    state = State::operators_q20;
                    ch = getNextChar();
                }
                else if (ch == ':') {
                    text += ch;
                    state = State::operators_q19;
                    ch = getNextChar();
                }
                else if (ch == '(') {
                    text += ch;
                    state = State::operators_q21;
                    ch = getNextChar();
                }
                else if (ch == '-') {
                    text += ch;
                    state = State::operators_q9;
                    ch = getNextChar();
                }
                else if (ch == '<') {
                    text += ch;
                    state = State::operators_q13;
                    ch = getNextChar();
                }
                else if (ch == '>') {
                    text += ch;
                    state = State::operators_q5;
                    ch = getNextChar();
                }
                else if (ch == '.') {
                    text += ch;
                    state = State::operators_q42;
                    ch = getNextChar();
                }
                else if (ch == ';') {
                    text += ch;
                    state = State::operators_q8;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    text += ch;
                    state = State::operators_q10;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'identifier
                    state = State::identifier_q0;
                }
                break;
            case State::operators_q1:
                ungetChar(ch);
                return Token::OperAssign;
                break;
            case State::operators_q10:
                ungetChar(ch);
                return Token::OperAsterisk;
                break;
            case State::operators_q11:
                ungetChar(ch);
                return Token::OperGreaterOrEqualThan;
                break;
            case State::operators_q13:
                if (ch == '=') {
                    text += ch;
                    state = State::operators_q16;
                    ch = getNextChar();
                }
                else if (ch == '<') {
                    text += ch;
                    state = State::operators_q38;
                    ch = getNextChar();
                }
                else if (ch == '>') {
                    text += ch;
                    state = State::operators_q15;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OperLessThan;
                }
                break;
            case State::operators_q15:
                ungetChar(ch);
                return Token::OperDifferentThan;
                break;
            case State::operators_q16:
                ungetChar(ch);
                return Token::OperLessOrEqualThan;
                break;
            case State::operators_q19:
                if (ch == '=') {
                    text += ch;
                    state = State::operators_q40;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OperColon;
                }
                break;
            case State::operators_q2:
                ungetChar(ch);
                return Token::OperOpenSquare;
                break;
            case State::operators_q20:
                ungetChar(ch);
                return Token::OperClosePar;
                break;
            case State::operators_q21:
                if (ch == '*') {
                    text += ch;
                    state = State::operators_q23;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OperOpenPar;
                }
                break;
            case State::operators_q23:
                text="";;
                if (ch == '*') {
                    state = State::operators_q33;
                    ch = getNextChar();
                }
                else {
                    state = State::operators_q23;
                    ch = getNextChar();
                }
                break;
            case State::operators_q3:
                ungetChar(ch);
                return Token::OperComma;
                break;
            case State::operators_q33:
                if (ch == ')') {
                    state = State::start_q0;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    state = State::operators_q33;
                    ch = getNextChar();
                }
                else {
                    state = State::operators_q23;
                }
                break;
            case State::operators_q36:
                ungetChar(ch);
                return Token::OperGreaterGreaterThan;
                break;
            case State::operators_q38:
                ungetChar(ch);
                return Token::LessLessThan;
                break;
            case State::operators_q4:
                ungetChar(ch);
                return Token::OperAdd;
                break;
            case State::operators_q40:
                ungetChar(ch);
                return Token::OpColonAssign;
                break;
            case State::operators_q42:
                if (ch == '.') {
                    text += ch;
                    state = State::operators_q44;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OpPoint;
                }
                break;
            case State::operators_q44:
                ungetChar(ch);
                return Token::OpPointPoint;
                break;
            case State::operators_q5:
                if (ch == '>') {
                    text += ch;
                    state = State::operators_q36;
                    ch = getNextChar();
                }
                else if (ch == '=') {
                    text += ch;
                    state = State::operators_q11;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OperGreaterThan;
                }
                break;
            case State::operators_q7:
                ungetChar(ch);
                return Token::OperCloseSquare;
                break;
            case State::operators_q8:
                ungetChar(ch);
                return Token::OperSemiColon;
                break;
            case State::operators_q9:
                ungetChar(ch);
                return Token::OperSub;
                break;
            // identifier
            case State::identifier_q0:
                if (((ch >= 'a') && (ch <= 'z')) || (ch == '_') || ((ch >= 'A') && (ch <= 'Z'))) {
                    text += ch;
                    state = State::identifier_q1;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'strCharConstant
                    state = State::strCharConstant_q0;
                }
                break;
            case State::identifier_q1:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::identifier_q1;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return findKeyword(text);
                }
                break;
            // strCharConstant
            case State::strCharConstant_q0:
                if (ch == '\'') {
                    text += ch;
                    state = State::strCharConstant_q1;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::strCharConstant_q1:
                if ((ch == EOF) || (ch == '\n')) {
                    state = State::strCharConstant_q4;
                    ch = getNextChar();
                }
                else if (ch == '\'') {
                    state = State::strCharConstant_q8;
                    ch = getNextChar();
                }
                else {
                    text += ch;
                    state = State::strCharConstant_q3;
                    ch = getNextChar();
                }
                break;
            case State::strCharConstant_q12:
                std::cerr<<"No valid empty stringConstant \n";text="";;
                state = State::strCharConstant_q13;
                break;
            case State::strCharConstant_q13:
                state = State::start_q0;
                break;
            case State::strCharConstant_q3:
                if (ch == '\'') {
                    text += ch;
                    state = State::strCharConstant_q9;
                    ch = getNextChar();
                }
                else if ((ch == '\n') || (ch == EOF)) {
                    state = State::strCharConstant_q4;
                    ch = getNextChar();
                }
                else {
                    text += ch;
                    state = State::strCharConstant_q3;
                    ch = getNextChar();
                }
                break;
            case State::strCharConstant_q4:
                std::cerr<<"Invalid stringConstant \n";text="";;
                state = State::start_q0;
                break;
            case State::strCharConstant_q8:
                if ((ch == EOF) || (ch == '\n')) {
                    state = State::strCharConstant_q12;
                    ch = getNextChar();
                }
                else if (ch == '\'') {
                    text += ch;
                    state = State::strCharConstant_q3;
                    ch = getNextChar();
                }
                else {
                    text += ch;
                    state = State::strCharConstant_q12;
                    ch = getNextChar();
                }
                break;
            case State::strCharConstant_q9:
                if (ch == '\'') {
                    state = State::strCharConstant_q3;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return charOrString(text);
                }
                break;
        }
    }

}


Token Lexer::charOrString(const std::string& str)
{
    if(str.length() == 3 && int(str[2]) >= 32 && int(str[2]) <= 126)
    {
        return Token::charConstant;
    }
    else
    {
        return Token::stringConstant;
    }
}

Token Lexer::findKeyword(const std::string& txt)
{
    std::string str = txt;
    for(int i = 0; i < txt.length(); i++)
    {
        str[i] = tolower(txt[i]);
    }

    if(str == "and")
    {
        return Token::KwAnd;
    }
    else if(str == "array")
    {
        return Token::KwArray;
    }
    else if(str == "begin")
    {
        return Token::KwBegin;
    }
    else if(str == "boolean")
    {
        return Token::KwBoolean;
    }
    else if(str == "break")
    {
        return Token::KwBreak;
    }
    else if(str == "char")
    {
        return Token::KwChar;
    }
    else if(str == "continue")
    {
        return Token::KwContinue;
    }
    else if(str == "div")
    {
        return Token::KwDiv;
    }
    else if(str == "do")
    {
        return Token::KwDo;
    }
    else if(str == "else")
    {
        return Token::KwElse;
    }
    else if(str == "end")
    {
        return Token::KwEnd;
    }
    else if(str == "false")
    {
        return Token::KwFalse;
    }
    else if(str == "for")
    {
        return Token::KwFor;
    }
    else if(str == "function")
    {
        return Token::KwFunction;
    }
    else if(str == "if")
    {
        return Token::KwIf;
    }
    else if(str == "integer")
    {
        return Token::KwInteger;
    }
    else if(str == "mod")
    {
        return Token::KwMod;
    }
    else if(str == "not")
    {
        return Token::KwNot;
    }
    else if(str == "of")
    {
        return Token::KwOf;
    }
    else if(str == "or")
    {
        return Token::KwOr;
    }
    else if(str == "procedure")
    {
        return Token::KwProcedure;
    }
    else if(str == "program")
    {
        return Token::KwProgram;
    }
    else if(str == "read")
    {
        return Token::KwRead;
    }
    else if(str == "repeat")
    {
        return Token::KwRepeat;
    }
    else if(str == "shl")
    {
        return Token::KwShl;
    }
    else if(str == "shr")
    {
        return Token::KwShr;
    }
    else if(str == "then")
    {
        return Token::KwThen;
    }
    else if(str == "to")
    {
        return Token::KwTo;
    }
    else if(str == "true")
    {
        return Token::KwTrue;
    }
    else if(str == "until")
    {
        return Token::KwUntil;
    }
    else if(str == "var")
    {
        return Token::KwVar;
    }
    else if(str == "while")
    {
        return Token::KwWhile;
    }
    else if(str == "write")
    {
        return Token::KwWrite;
    }
    else if(str == "writeln")
    {
        return Token::KwWriteln;
    }
    else if(str == "xor")
    {
        return Token::KwXor;
    }
    else 
    {
        return Token::ID;
    }
}

const char *Lexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::OperSub: return "OperSub";
        case Token::OperCloseSquare: return "OperCloseSquare";
        case Token::OpPoint: return "OpPoint";
        case Token::OpColonAssign: return "OpColonAssign";
        case Token::OperAdd: return "OperAdd";
        case Token::OperGreaterGreaterThan: return "OperGreaterGreaterThan";
        case Token::OperComma: return "OperComma";
        case Token::OperOpenSquare: return "OperOpenSquare";
        case Token::OperLessThan: return "OperLessThan";
        case Token::OperAsterisk: return "OperAsterisk";
        case Token::OperAssign: return "OperAssign";
        case Token::OpDiv: return "OpDiv";
        case Token::Number: return "Number";
        case Token::KwVar: return "Keyword 'var'";
        case Token::KwUntil: return "Keyword 'until'";
        case Token::KwShr: return "Keyword 'shr'";
        case Token::LessLessThan: return "LessLessThan";
        case Token::stringConstant: return "stringConstant";
        case Token::OperSemiColon: return "OperSemiColon";
        case Token::KwNot: return "Keyword 'not'";
        case Token::KwDiv: return "Keyword 'div'";
        case Token::KwChar: return "Keyword 'char'";
        case Token::KwThen: return "Keyword 'then'";
        case Token::OperOpenPar: return "OperOpenPar";
        case Token::Unknown: return "Unknown";
        case Token::KwIf: return "Keyword 'if'";
        case Token::KwDo: return "Keyword 'do'";
        case Token::KwTrue: return "Keyword 'true'";
        case Token::ID: return "Identifier";
        case Token::KwBoolean: return "Keyword 'boolean'";
        case Token::KwFalse: return "Keyword 'false'";
        case Token::KwWriteln: return "Keyword 'writeln'";
        case Token::OperDifferentThan: return "OperDifferentThan";
        case Token::KwBreak: return "Keyword 'break'";
        case Token::KwWrite: return "Keyword 'write'";
        case Token::KwXor: return "Keyword 'xor'";
        case Token::KwElse: return "Keyword 'else'";
        case Token::KwContinue: return "Keyword 'continue'";
        case Token::OperGreaterThan: return "OperGreaterThan";
        case Token::KwAnd: return "Keyword 'and'";
        case Token::KwRead: return "Keyword 'read'";
        case Token::charConstant: return "charConstant";
        case Token::OpPointPoint: return "OpPointPoint";
        case Token::KwInteger: return "Keyword 'integer'";
        case Token::KwEnd: return "Keyword 'end'";
        case Token::KwWhile: return "Keyword 'while'";
        case Token::KwArray: return "Keyword 'array'";
        case Token::Eof: return "Eof";
        case Token::KwFor: return "Keyword 'for'";
        case Token::KwOf: return "Keyword 'of'";
        case Token::KwFunction: return "Keyword 'function'";
        case Token::OperClosePar: return "OperClosePar";
        case Token::OperColon: return "OperColon";
        case Token::OperGreaterOrEqualThan: return "OperGreaterOrEqualThan";
        case Token::KwBegin: return "Keyword 'begin'";
        case Token::KwOr: return "Keyword 'or'";
        case Token::KwProcedure: return "Keyword 'procedure'";
        case Token::OperLessOrEqualThan: return "OperLessOrEqualThan";
        case Token::KwMod: return "Keyword 'mod'";
        case Token::KwProgram: return "Keyword 'program'";
        case Token::KwRepeat: return "Keyword 'repeat'";
        case Token::KwShl: return "Keyword 'shl'";
        case Token::KwTo: return "Keyword 'to'";
        default: return "Unknown";
    }
    
}
