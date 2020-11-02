#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

enum class TokenType
{

    kPlus = 0,
    kMinus,
    kStar,
    kDiv,
    kPow,
    kNum,
    kMin,
    kMax,
    kInc,
    kDec,
    kLb,
    kRb,
    kUnd
};

class Token
{

public:

    Token();
    Token(const QString& lexema);
    QString GetLexema() const;
    void setType(TokenType newType);

private:

    QString lexema;
    TokenType type;

};

#endif // TOKEN_H
