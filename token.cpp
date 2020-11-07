#include "token.h"
#include <QRegExp>
#include <exception>
#include <QDebug>

Token::Token() : lexema(QString())
{
    type = TokenType::kUnd;
}

Token::Token(const QString& lexema, TokenType type) : lexema(lexema), type(type)
{
    static const QRegExp numberRegExp("0|[1-9][0-9]*");
    static const QRegExp cellRegExp("[A-Z]+[1-9][0-9]*");
    if(lexema == "+")
    {
        setType(TokenType::kPlus);
    } else if(lexema == "-")
    {
        setType(TokenType::kMinus);
    } else if(lexema == "*")
    {
       setType(TokenType::kStar);
    } else if(lexema == "/")
    {
        setType(TokenType::kDiv);
    } else if(lexema == "^")
    {
        setType(TokenType::kPow);
    } else if( numberRegExp.exactMatch(lexema))
    {
        setType(TokenType::kNum);
    }else if(  lexema == "min")
    {
        setType(TokenType::kMin);
    }else if(  lexema == "max")
    {
        setType(TokenType::kMax);
    } else if(lexema == "dec")
    {
        setType(TokenType::kDec);
    } else if(lexema == "inc")
    {
        setType(TokenType::kInc);
    } else if(cellRegExp.exactMatch(lexema))
    {
        setType(TokenType::kCell);
    } else {
        setType(TokenType::kUnd);
    }
}

QString Token::GetLexema() const
{
    return lexema;
}

void Token::setType(TokenType newType)
{
    type = newType;
}

TokenType Token::getType() const
{
    return type;
}


