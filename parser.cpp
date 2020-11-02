#include "parser.h"
#include <QSharedPointer>


QSharedPointer<Node_Statement> Parser::parse(const QVector<Token> &inputTokens)
{
   // QVector<Token>::const_iterator it = inputTokens.begin();

    //QSharedPointer<Node_Statement>  tree = stmt(inputTokens, it);

    //return tree;

    return QSharedPointer<Node_Statement>(new Node_Statement());
}

QSharedPointer<Node_Statement> Parser::stmt(const QVector<Token> &input, QVector<Token>::const_iterator &it)
{
//    QSharedPointer<Node_Statement> statement(new Node_Statement());
//     TokenType type = it->type;
//     if(type == TokenType::kNum ||
//        type == TokenType::kMin ||
//        type == TokenType::kMax ||
//        type == TokenType::kLb )
//    {
//     QSharedPointer<Node_Expression> expressionNode = expr(input, it);
//     statement->setExpressionNode(expressionNode);
//    }
     //return statement;
    return QSharedPointer<Node_Statement>(new Node_Statement());
}
