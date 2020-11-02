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
    static QSharedPointer<Node_Statement>  stmt(const QVector<Token>& input,
                               QVector<Token>::const_iterator& it);
    static QSharedPointer<Node_Expression> expr(const QVector<Token>& input,
                                                QVector<Token>::const_iterator& it){};

};


#endif // PARSER_H
