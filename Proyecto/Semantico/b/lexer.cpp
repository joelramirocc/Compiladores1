#include "lexer.h"

enum class State {
    start_q0,
    Analizer_q0,
    Analizer_q1,
    Analizer_q13,
    Analizer_q15,
    Analizer_q17,
    Analizer_q2,
    Analizer_q3,
    Analizer_q4,
    Analizer_q5,
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
                    // Trying next automaton 'Analizer
                    state = State::Analizer_q0;
                }
                break;
            // Analizer
            case State::Analizer_q0:
                if (ch == '/') {
                    text += ch;
                    state = State::Analizer_q15;
                    ch = getNextChar();
                }
                else if (ch == ';') {
                    text += ch;
                    state = State::Analizer_q17;
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
                else if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Analizer_q5;
                    ch = getNextChar();
                }
                else if (ch == '*') {
                    text += ch;
                    state = State::Analizer_q2;
                    ch = getNextChar();
                }
                else if (ch == '+') {
                    text += ch;
                    state = State::Analizer_q1;
                    ch = getNextChar();
                }
                else if (ch == '-') {
                    text += ch;
                    state = State::Analizer_q13;
                    ch = getNextChar();
                }
                else {
                    reportError(ch);
                    ch = getNextChar();
                    state = State::start_q0;
                }
                break;
            case State::Analizer_q1:
                ungetChar(ch);
                return Token::Add;
                break;
            case State::Analizer_q13:
                ungetChar(ch);
                return Token::Sub;
                break;
            case State::Analizer_q15:
                ungetChar(ch);
                return Token::Div;
                break;
            case State::Analizer_q17:
                ungetChar(ch);
                return Token::SemiColon;
                break;
            case State::Analizer_q2:
                ungetChar(ch);
                return Token::Asterisco;
                break;
            case State::Analizer_q3:
                ungetChar(ch);
                return Token::POpen;
                break;
            case State::Analizer_q4:
                ungetChar(ch);
                return Token::PClosed;
                break;
            case State::Analizer_q5:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = State::Analizer_q5;
                    ch = getNextChar();
                }
                else {
                    ungetChar(ch);
                    return Token::Num;
                }
                break;
        }
    }

}

const char *Lexer::tokenToString(Token tk)
{
    switch (tk) {
        case Token::Num: return "Num";
        case Token::Add: return "Add";
        case Token::Eof: return "Eof";
        case Token::PClosed: return "PClosed";
        case Token::Div: return "Div";
        case Token::POpen: return "POpen";
        case Token::SemiColon: return "SemiColon";
        case Token::Sub: return "Sub";
        case Token::Asterisco: return "Asterisco";
        default: return "Unknown";
    }
    
}
