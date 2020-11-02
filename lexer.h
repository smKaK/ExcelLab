#ifndef LEXER_H
#define LEXER_H

#include <QVector>
#include "token.h"

class Lexer
{
public:
    Lexer() = delete;
    static QVector<Token> Tokenize(const QString& input);
};

#endif // LEXER_H
