#include "parser.h"
#include <QSharedPointer>


QSharedPointer<Node_Statement> Parser::parse(const QVector<Token> &inputTokens)
{

    QVector<Token>::const_iterator it = inputTokens.begin();

     QSharedPointer<Node_Statement>  tree(new Node_Statement);

     tree = stmt(inputTokens, it, tree->bIsExeption);

     for(const auto& el : inputTokens)
     {
         if(el.getType() == TokenType::kCell)
         {
             tree->getCellLinks().push_back(el);
         }
     }
     if(it->getType() != TokenType::kEof)
     {
         tree->bIsExeption = true;
         tree->setExpressionNode(nullptr);
     }

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
        statement->bIsExeption = bIsExeption;
        return statement;
     }
     else if(type == TokenType::kEof)
     {
         statement->setExpressionNode(nullptr);
         statement->bIsExeption = bIsExeption;
         return statement;
     }
     else
     {
         bIsExeption = true;
         statement->setExpressionNode(nullptr);
         statement->bIsExeption = bIsExeption;
         return statement;
     }
}

QSharedPointer<Node_Expression> Parser::expr(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool& bIsExeption)
{
   QSharedPointer<Node_Expression> expression(new Node_Expression);
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
             if(it->getType() == TokenType::kEof){
                 expression->setRightExprNode(nullptr);
                 return expression;
             }
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
    QSharedPointer<Node_ExpressionRight> expressionRight(new Node_ExpressionRight);
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
    else if(type == TokenType::kEof||
            type == TokenType::kRb ||
            type == TokenType::kComa)
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
    QSharedPointer<Node_Multiplication> multiplication(new Node_Multiplication);
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
                if(it->getType() == TokenType::kEof){
                    multiplication->setMultRightNode(nullptr);
                    return multiplication;
                }
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
    QSharedPointer<Node_MultiplicationRight> multiplicationRight(new Node_MultiplicationRight);
    TokenType type = it->getType();
    if( type == TokenType::kStar ||
        type == TokenType::kDiv)
    {
        multiplicationRight->setOperator(type);
        QSharedPointer<Node_Multiplication> multiplication = mult(input, ++it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            if(multiplication == nullptr)
            {
                bIsExeption = true;
                return nullptr;
            }
            else
            {
                multiplicationRight->setMultiplicationNode(multiplication);
                return multiplicationRight;
            }
        }
    }
    else if(type == TokenType::kEof)
    {

        return nullptr;
    }
    else
    {
        --it;
        return nullptr;
    }
//    else
//    {
//        bIsExeption = true;
//        return nullptr;
//    }
}

QSharedPointer<Node_Power> Parser::power(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    QSharedPointer<Node_Power> powerNode(new Node_Power);
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
            QSharedPointer<Node_Term> termNode = term(input, it, bIsExeption);
            if(bIsExeption)
            {
                return nullptr;
            }
            else
            {
                powerNode->setTermNode(termNode);
                if(it->getType() == TokenType::kEof){
                    powerNode->setPowerRightNode(nullptr);
                    return powerNode;
                }
                QSharedPointer<Node_PowerRight> powerRightNode = powerRight(input, ++it, bIsExeption);
                if(bIsExeption)
                {
                    return nullptr;
                }
                else
                {
                    powerNode->setPowerRightNode(powerRightNode);
                    return powerNode;
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

QSharedPointer<Node_PowerRight> Parser::powerRight(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    QSharedPointer<Node_PowerRight> powerRightNode(new Node_PowerRight);
    TokenType type = it->getType();
    if( type == TokenType::kPow)
    {
        powerRightNode->setOperator(type);
        QSharedPointer<Node_Power> powerNode = power(input, ++it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            if(powerNode == nullptr)
            {
                bIsExeption = true;
                return nullptr;
            }
            else
            {
                powerRightNode->setPowerNode(powerNode);
                return powerRightNode;
            }
        }
    }
    else if(type == TokenType::kEof)

    {

        return nullptr;
    }
    else
    {
           --it;
        return nullptr;
    }
//    else
//    {
//        bIsExeption = true;
//        return nullptr;
//    }
}

QSharedPointer<Node_Term> Parser::term(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    QSharedPointer<Node_Term> termNode(new Node_Term);
    TokenType type = it->getType();
    if(type == TokenType::kNum)
    {
        QSharedPointer<Node_Number> numberNode = termNum(input, it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            termNode->setNode(numberNode, type);
            return termNode;
        }
    }
    else if(type == TokenType::kCell)
    {
            QSharedPointer<Node_CellLink> cellNode = termCell(input, it, bIsExeption);
            if(bIsExeption)
            {
                return nullptr;
            }
            else
            {
                termNode->setNode(cellNode, type);
                return termNode;
            }
     }
    else if(type == TokenType:: kMin ||
            type == TokenType:: kMax)
    {
        QSharedPointer<Node_FuncWith2Args> funcNode = termFunc2Args(input, it, bIsExeption);
        if(false)
        {
            return nullptr;
        }
        else
        {
            termNode->setNode(funcNode, type);
            return termNode;
        }
    }
    else if(type == TokenType:: kDec ||
            type == TokenType:: kInc)
    {
        QSharedPointer<Node_FuncWith1Arg> funcNode = termFunc1Arg(input, it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            termNode->setNode(funcNode, type);
            return termNode;
        }
    }
    else if(type == TokenType::kLb)
    {
        QSharedPointer<Node_ExpressionWithBrackets> brExpression = exprWithBrackets(input, it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else
        {
            termNode->setNode(brExpression, type);
            return termNode;
        }
    }
}

//    else if(type == TokenType:: kPlus ||
//            type == TokenType:: kMinus)
//    {
//        QSharedPointer<Node_UnaryOperator> unOpNode = termUnOp(input, it, bIsExeption);
//        if(bIsExeption)
//        {
//            return nullptr;
//        }
//        else
//        {
//            termNode->setNode(unOpNode, type);
//            return termNode;
//        }
//    }




QSharedPointer<Node_Number> Parser::termNum(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    QSharedPointer<Node_Number> numNode(new Node_Number);
    numNode->setLexema(it->GetLexema());
    return numNode;

}

QSharedPointer<Node_CellLink> Parser::termCell(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
   QSharedPointer<Node_CellLink> cellNode(new Node_CellLink);
   cellNode->setLink(it->GetLexema());
   return  cellNode;

}

QSharedPointer<Node_FuncWith2Args> Parser::termFunc2Args(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    TokenType type = it->getType();
    QSharedPointer<Node_FuncWith2Args> funcWith2Args(new Node_FuncWith2Args(it->getType()));

    ++it;
    type = it->getType();
    if(type == TokenType::kLb)
    {
        QSharedPointer<Node_Expression> expression1 = expr(input, ++it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else if (it->getType() == TokenType::kComa)
        {

            QSharedPointer<Node_Expression> expression2 = expr(input, ++it, bIsExeption);
            if(bIsExeption)
            {
                return nullptr;
            }
            else
            {
                funcWith2Args->setExpr1(expression1);
                funcWith2Args->setExpr2(expression2);
                return funcWith2Args;
            }
//            exprWithBracketsNode->setExpressionNode(expression);
//            return exprWithBracketsNode;
        }
        else
        {
            bIsExeption = true;
            return nullptr;
        }
    }
    else
    {
        bIsExeption = true;
        return nullptr;
    }
}

QSharedPointer<Node_FuncWith1Arg> Parser::termFunc1Arg(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
     QSharedPointer<Node_FuncWith1Arg> funcWith1ArgNode(new Node_FuncWith1Arg(it->getType()));
     QSharedPointer<Node_ExpressionWithBrackets> exprWithBr = exprWithBrackets(input, ++it, bIsExeption);
     if(bIsExeption)
     {
         return nullptr;
     }
     else
     {
         funcWith1ArgNode->setExprWithBr(exprWithBr);
         return  funcWith1ArgNode;
     }

}

QSharedPointer<Node_ExpressionWithBrackets> Parser::exprWithBrackets(const QVector<Token> &input, QVector<Token>::const_iterator &it, bool &bIsExeption)
{
    TokenType type = it->getType();
    QSharedPointer<Node_ExpressionWithBrackets> exprWithBracketsNode(new Node_ExpressionWithBrackets);
    if(type == TokenType::kLb)
    {
        QSharedPointer<Node_Expression> expression = expr(input, ++it, bIsExeption);
        if(bIsExeption)
        {
            return nullptr;
        }
        else if (it->getType() == TokenType::kRb)
        {
            exprWithBracketsNode->setExpressionNode(expression);
            return exprWithBracketsNode;
        }
        else
        {
            bIsExeption = true;
            return nullptr;
        }
    }
    else
    {
        bIsExeption = true;
        return nullptr;
    }
}
