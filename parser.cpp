#include "parser.h"
#include <QSharedPointer>


QSharedPointer<Node_Statement> Parser::parse(const QVector<Token> &inputTokens)
{
     QVector<Token>::const_iterator it = inputTokens.begin();

     QSharedPointer<Node_Statement>  tree;

     tree = stmt(inputTokens, it, tree->bIsExeption);

     return tree;

}

QSharedPointer<Node_Statement> Parser::stmt(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bIsExeption)
{
    QSharedPointer<Node_Statement> statement(new Node_Statement());
     TokenType type = it->getType();
     if(type == TokenType::kNum  ||
        type == TokenType::kMin  ||
        type == TokenType::kMax  ||
        type == TokenType::kCell ||
        type == TokenType::kLb   ||
        type == TokenType::kInc  ||
        type == TokenType::kDec  ||
        type == TokenType::kPlus ||
        type == TokenType::kMinus)
    {
        QSharedPointer<Node_Expression> expressionNode = expr(input, it, bIsExeption);
        statement->setExpressionNode(expressionNode);
        return statement;
     }
     else if(type == TokenType::kEof)
     {
         statement->setExpressionNode(nullptr);
         return statement;
     }
     else
     {
         bIsExeption = true;
         statement->setExpressionNode(nullptr);
         return statement;
     }
}

QSharedPointer<Node_Expression> Parser::expr(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bIsExeption)
{
   QSharedPointer<Node_Expression> expression(new Node_Expression());
    TokenType type = it->getType();
    if(type == TokenType::kNum  ||
       type == TokenType::kMin  ||
       type == TokenType::kMax  ||
       type == TokenType::kCell ||
       type == TokenType::kLb   ||
       type == TokenType::kInc  ||
       type == TokenType::kDec  ||
       type == TokenType::kPlus ||
       type == TokenType::kMinus)
    {
         QSharedPointer<Node_Multiplication> multiplicationNode = mult(input, it, bIsExeption);
         if(bIsExeption)
         {
             return nullptr;
         }
         else
         {
             expression->setMultNode(multiplicationNode);
             QSharedPointer<Node_ExpressionRight> exprRightNode = exprRight(input, ++it, bIsExeption);
             if(bIsExeption)
             {
                 return nullptr;
             }
             else
             {
                 expression->setRightExprNode(exprRightNode);
                 return expression;
             }
         }
     }
     else if(type == TokenType::kEof)
    {
        return nullptr;
    }
     else
     {
        bIsExeption = true;
        return nullptr;
     }
}

QSharedPointer<Node_ExpressionRight> Parser::exprRight(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bIsExeption)
{
    QSharedPointer<Node_ExpressionRight> expressionRight(new Node_ExpressionRight());
    TokenType type = it->getType();
    if( type == TokenType::kPlus ||
        type == TokenType::kMinus)
    {
        expressionRight->setOperator(type);
        QSharedPointer<Node_Expression> expression = expr(input, ++it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            if(expression == nullptr)
            {
                bIsExeption = true;
                return nullptr;
            }
            else
            {
                expressionRight->setRightExprNode(expression);
                return expressionRight;
            }
        }
    }
    else if(type == TokenType::kEof)
    {
        return nullptr;
    }
    else
    {
        bIsExeption = true;
        return nullptr;
    }
}

QSharedPointer<Node_Multiplication> Parser::mult(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    QSharedPointer<Node_Multiplication> multiplication(new Node_Multiplication());
    TokenType type = it->getType();
    if(type == TokenType::kNum  ||
            type == TokenType::kMin  ||
            type == TokenType::kMax  ||
            type == TokenType::kCell ||
            type == TokenType::kLb   ||
            type == TokenType::kInc  ||
            type == TokenType::kDec  ||
            type == TokenType::kPlus ||
            type == TokenType::kMinus)
    {
            QSharedPointer<Node_Power> powerNode = power(input, it, bIsExeption);
            if(bIsExeption)
            {
                return nullptr;
            }
            else
            {
                multiplication->setPowerNode(powerNode);
                QSharedPointer<Node_MultiplicationRight> multRightNode = multRight(input, ++it, bIsExeption);
                if(bIsExeption)
                {
                    return nullptr;
                }
                else
                {
                    multiplication->setMultRightNode(multRightNode);
                    return multiplication;
                }
            }
    }
    else if(type == TokenType::kEof)
    {
        return nullptr;
    }
    else
    {
        bIsExeption = true;
        return nullptr;
    }
}

QSharedPointer<Node_MultiplicationRight> Parser::multRight(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    QSharedPointer<Node_MultiplicationRight> multiplicationRight(new Node_MultiplicationRight());
    TokenType type = it->getType();
    if( type == TokenType::kStar ||
        type == TokenType::kDiv)
    {
        multiplicationRight->setOperator(type);
        QSharedPointer<Node_Multiplication> multiplication = mul(input, ++it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            if(expression == nullptr)
            {
                bIsExeption = true;
                return nullptr;
            }
            else
            {
                expressionRight->setRightExprNode(expression);
                return expressionRight;
            }
        }
    }
    else if(type == TokenType::kEof)
    {
        return nullptr;
    }
    else
    {
        bIsExeption = true;
        return nullptr;
    }
}

QSharedPointer<Node_Power> Parser::power(const QVector<Token> &input, QVector::const_iterator &it, bool &bIsExeption)
{

}
