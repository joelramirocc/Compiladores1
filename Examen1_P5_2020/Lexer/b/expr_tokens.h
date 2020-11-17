#ifndef __EXPR_TOKENS_H__
#define __EXPR_TOKENS_H__

enum class Token {
    Ident,
    OpMul,
    ClosePar,
    OpenPar,
    Number,
    OpSub,
    Eof,
    OpAdd,
    OpDiv,
    Eol,
};
#endif