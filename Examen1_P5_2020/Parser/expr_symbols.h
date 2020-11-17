#ifndef __EXPR_SYMBOLS_H__
#define __EXPR_SYMBOLS_H__

enum class Symbol {
    Print,
    SemiColon,
    OpenPar,
    ClosePar,
    Eol,
    OpAssign,
    OpAdd,
    OpSub,
    OpMul,
    OpDiv,
    Number,
    Ident,
    Unknown,
    Eof
};
#endif