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
    kCell,
    kComa,
    kNum,
    kMin,
    kMax,
    kInc,
    kDec,
    kLb,
    kRb,
    kUnd,
    kEof
};

class Token
{

public:

    Token();
    Token(const QString& lexema, TokenType type = TokenType::kUnd);
    QString GetLexema() const;
    void setType(TokenType newType);
    TokenType getType() const;

private:

    QString lexema;
    TokenType type;

};

#endif // TOKEN_H
