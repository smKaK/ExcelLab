#ifndef PARSER_H
#define PARSER_H


#include "token.h"
#include <QVector>
#include "node.h"

class Parser
{
public:
    Parser() = delete;
    static QSharedPointer<Node_Statement> parse(const QVector<Token>& inputTokens);
private:
    static QSharedPointer<Node_Statement>       stmt(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it, bool& bIsExeption);
    static QSharedPointer<Node_Expression>      expr(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it, bool& bIsExeption);
    static QSharedPointer<Node_ExpressionRight> exprRight(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it, bool& bIsExeption);
    static QSharedPointer<Node_Multiplication>  mult(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it, bool& bIsExeption);
    static QSharedPointer<Node_MultiplicationRight>  multRight(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it, bool& bIsExeption);
    static QSharedPointer<Node_Power>           power(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it, bool& bIsExeption);

};


#endif // PARSER_H
