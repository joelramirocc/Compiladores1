#include "expr_lexer.h"

enum class State {
    start_q0,
    constants_q0,
    constants_q1,
    constants_q2,
    constants_q4,
    Analizer_q0,
    Analizer_q1,
    Analizer_q10,
    Analizer_q11,
    Analizer_q15,
    Analizer_q16,
    Analizer_q17,
    Analizer_q18,
    Analizer_q19,
    Analizer_q2,
    Analizer_q20,
    Analizer_q21,
    Analizer_q3,
    Analizer_q4,
    Analizer_q5,
    ident_q0,
    ident_q1,
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
                    // Trying next automaton 'constants
                    state = State::constants_q0;
                }
                break;
            // constants
            case State::constants_q0:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q4;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Analizer
                    state = State::Analizer_q0;
                }
                break;
            case State::constants_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q2;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Analizer
                    state = State::Analizer_q0;
                }
                break;
            case State::constants_q2:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q2;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            case State::constants_q4:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q4;
                    ch = getNextChar();
                }
                else if (ch == '.') {
                    text += ch;
                    state = State::constants_q1;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Number;
                }
                break;
            // Analizer
            case State::Analizer_q0:
                if (ch == '/') {
                    text += ch;
                    state = State::Analizer_q10;
                    ch = getNextChar();
                }
                else if (ch == '+') {
                    text += ch;
                    state = State::Analizer_q1;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    text += ch;
                    state = State::Analizer_q5;
                    ch = getNextChar();
                }
                else if (ch == '-') {
                    text += ch;
                    state = State::Analizer_q2;
                    ch = getNextChar();
                }
                else if (ch == '\n') {
                    text += ch;
                    state = State::Analizer_q11;
                    ch = getNextChar();
                }
                else if (ch == ')') {
                    text += ch;
                    state = State::Analizer_q4;
                    ch = getNextChar();
                }
                else if (ch == '(') {
                    text += ch;
                    state = State::Analizer_q3;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'ident
                    state = State::ident_q0;
                }
                break;
            case State::Analizer_q1:
                ungetChar(ch);
                return Token::OpAdd;
                break;
            case State::Analizer_q10:
                if (ch == '!') {
                    state = State::Analizer_q15;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::OpDiv;
                }
                break;
            case State::Analizer_q11:
                if (ch == '\n') {
                    text += ch;
                    state = State::Analizer_q11;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Eol;
                }
                break;
            case State::Analizer_q15:
                text= "";;
                if (ch == '!') {
                    state = State::Analizer_q16;
                    ch = getNextChar();
                }
                else {
                    state = State::Analizer_q17;
                }
                break;
            case State::Analizer_q16:
                if (ch == '!') {
                    state = State::Analizer_q20;
                    ch = getNextChar();
                }
                else {
                    state = State::Analizer_q16;
                    ch = getNextChar();
                }
                break;
            case State::Analizer_q17:
                if ((ch == '\n') || (ch == EOF)) {
                    state = State::Analizer_q18;
                    ch = getNextChar();
                }
                else {
                    state = State::Analizer_q17;
                    ch = getNextChar();
                }
                break;
            case State::Analizer_q18:
                state = State::start_q0;
                break;
            case State::Analizer_q19:
                state = State::start_q0;
                break;
            case State::Analizer_q2:
                ungetChar(ch);
                return Token::OpSub;
                break;
            case State::Analizer_q20:
                if (ch == '!') {
                    state = State::Analizer_q21;
                    ch = getNextChar();
                }
                else {
                    state = State::Analizer_q16;
                }
                break;
            case State::Analizer_q21:
                if (ch == '/') {
                    state = State::Analizer_q19;
                    ch = getNextChar();
                }
                else if (ch == '!') {
                    state = State::Analizer_q21;
                    ch = getNextChar();
                }
                else {
                    state = State::Analizer_q16;
                }
                break;
            case State::Analizer_q3:
                ungetChar(ch);
                return Token::OpenPar;
                break;
            case State::Analizer_q4:
                ungetChar(ch);
                return Token::ClosePar;
                break;
            case State::Analizer_q5:
                ungetChar(ch);
                return Token::OpMul;
                break;
            // ident
            case State::ident_q0:
                if ((ch == '$') || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::ident_q1;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::ident_q1:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || (ch == '_')) {
                    text += ch;
                    state = State::ident_q1;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Ident;
                }
                break;
        }
    }

}

const char *Lexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::Ident: return "Ident";
        case Token::OpMul: return "OpMul";
        case Token::ClosePar: return "ClosePar";
        case Token::OpenPar: return "OpenPar";
        case Token::Number: return "Number";
        case Token::OpSub: return "OpSub";
        case Token::Eof: return "Eof";
        case Token::OpAdd: return "OpAdd";
        case Token::OpDiv: return "OpDiv";
        case Token::Eol: return "Eol";
        default: return "Unknown";
    }
    
}
