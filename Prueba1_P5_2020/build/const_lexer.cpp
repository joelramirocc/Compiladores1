#include "const_lexer.h"

enum class State {
    start_q0,
    constants_q0,
    constants_q1,
    constants_q10,
    constants_q2,
    constants_q3,
    constants_q4,
    constants_q6,
    constants_q9,
    Coments_q0,
    Coments_q1,
    Coments_q2,
    Coments_q3,
    Coments_q5,
    Coments_q7,
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
                if ((ch >= '2') && (ch <= '7')) {
                    text += ch;
                    state = State::constants_q2;
                    ch = getNextChar();
                }
                else if (((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
                    text += ch;
                    state = State::constants_q9;
                    ch = getNextChar();
                }
                else if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = State::constants_q1;
                    ch = getNextChar();
                }
                else if ((ch >= '8') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q3;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Coments
                    state = State::Coments_q0;
                }
                break;
            case State::constants_q1:
                if ((ch == 'H') || (ch == 'h')) {
                    text += ch;
                    state = State::constants_q10;
                    ch = getNextChar();
                }
                else if ((ch == 'o') || (ch == 'O')) {
                    text += ch;
                    state = State::constants_q6;
                    ch = getNextChar();
                }
                else if ((ch == 'b') || (ch == 'B')) {
                    text += ch;
                    state = State::constants_q4;
                    ch = getNextChar();
                }
                else if ((ch >= '2') && (ch <= '7')) {
                    text += ch;
                    state = State::constants_q2;
                    ch = getNextChar();
                }
                else if (((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::constants_q9;
                    ch = getNextChar();
                }
                else if ((ch >= '8') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q3;
                    ch = getNextChar();
                }
                else if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = State::constants_q1;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Decimal;
                }
                break;
            case State::constants_q10:
                ungetChar(ch);
                return Token::Hex;
                break;
            case State::constants_q2:
                if ((ch >= '0') && (ch <= '7')) {
                    text += ch;
                    state = State::constants_q2;
                    ch = getNextChar();
                }
                else if ((ch == 'H') || (ch == 'h')) {
                    text += ch;
                    state = State::constants_q10;
                    ch = getNextChar();
                }
                else if ((ch == 'o') || (ch == 'O')) {
                    text += ch;
                    state = State::constants_q6;
                    ch = getNextChar();
                }
                else if ((ch >= '8') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q3;
                    ch = getNextChar();
                }
                else if (((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::constants_q9;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Decimal;
                }
                break;
            case State::constants_q3:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::constants_q3;
                    ch = getNextChar();
                }
                else if ((ch == 'h') || (ch == 'H')) {
                    text += ch;
                    state = State::constants_q10;
                    ch = getNextChar();
                }
                else if (((ch >= 'A') && (ch <= 'F')) || ((ch >= 'a') && (ch <= 'f'))) {
                    text += ch;
                    state = State::constants_q9;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Decimal;
                }
                break;
            case State::constants_q4:
                ungetChar(ch);
                return Token::Binary;
                break;
            case State::constants_q6:
                ungetChar(ch);
                return Token::Octal;
                break;
            case State::constants_q9:
                if (((ch >= '0') && (ch <= '9')) || ((ch >= 'a') && (ch <= 'f')) || ((ch >= 'A') && (ch <= 'F'))) {
                    text += ch;
                    state = State::constants_q9;
                    ch = getNextChar();
                }
                else if ((ch == 'h') || (ch == 'H')) {
                    text += ch;
                    state = State::constants_q10;
                    ch = getNextChar();
                }
                else {
                    // Trying next automaton 'Coments
                    state = State::Coments_q0;
                }
                break;
            // Coments
            case State::Coments_q0:
                if (ch == '(') {
                    state = State::Coments_q1;
                    ch = getNextChar();
                }
                else if (ch == '#') {
                    state = State::Coments_q2;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Coments_q1:
                if (ch == '*') {
                    state = State::Coments_q3;
                    ch = getNextChar();
                }
                else if (ch == '(') {
                    state = State::Coments_q1;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Coments_q2:
                if ((ch == EOF) || (ch == '\n')) {
                    state = State::start_q0;
                    ch = getNextChar();
                }
                else {
                    state = State::Coments_q2;
                    ch = getNextChar();
                }
                break;
            case State::Coments_q3:
                if (ch == '*') {
                    state = State::Coments_q5;
                    ch = getNextChar();
                }
                else {
                    state = State::Coments_q3;
                    ch = getNextChar();
                }
                break;
            case State::Coments_q5:
                if (ch == ')') {
                    state = State::Coments_q7;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    state = State::Coments_q5;
                    ch = getNextChar();
                }
                else {
                    state = State::Coments_q3;
                }
                break;
            case State::Coments_q7:
                ungetChar(ch);
                state = State::start_q0;
                break;
        }
    }

}

const char *Lexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::Octal: return "Octal";
        case Token::Binary: return "Binary";
        case Token::Eof: return "Eof";
        case Token::Hex: return "Hex";
        case Token::Decimal: return "Decimal";
        default: return "Unknown";
    }
    
}
