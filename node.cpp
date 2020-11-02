#include "node.h"
#include <cmath>
#include <QDebug>
//Node statement//////////////////////////////////////////////////////////////////////




Node_Statement::Node_Statement( ) : Node()
{

}

int Node_Statement::calculate(const Cell* parentCell)
{
    qDebug() << "calculate";
    return  123;
    //return exprNode->calculate(parentCell);
}

void Node_Statement::setExpressionNode(const QSharedPointer<Node_Expression> &newExprNode)
{
    exprNode = newExprNode;
}




//Node_ExpresionRight////////////////////////////////////////////////////////////////


int Node_ExpressionRight::calculate(const Cell* parentCell)
{
    int result(0);
    int multRes = multNode->calculate(parentCell);
    if(exprRightNode->GetOperator() == TokenType::kPlus)
    {
        result = multRes + exprRightNode->calculate(parentCell);
    } else if(exprRightNode->GetOperator() == TokenType::kMinus)
    {
        result = multRes - exprRightNode->calculate(parentCell);
    }
    return result;
}

 TokenType Node_ExpressionRight::GetOperator()
{
    return op;
}

//Node Expression/////////////////////////////////////////////////////////////////////
int Node_Expression::calculate(const Cell* parentCell)
{
    int result(0);
    int multRes = multNode->calculate(parentCell);
    if(exprRightNode->GetOperator() == TokenType::kPlus)
    {
        result = multRes + exprRightNode->calculate(parentCell);
    } else if(exprRightNode->GetOperator() == TokenType::kMinus)
    {
        result = multRes - exprRightNode->calculate(parentCell);
    }
    return result;
}

//Node_Multiplication/////////////////////////////////////////////////////////////////
int Node_Multiplication::calculate(const Cell* parentCell)
{
    int result(0);
    int powRes = powerNode->calculate(parentCell);
    if(multRightNode->GetOperator() == TokenType::kStar)
    {
        result = powRes * multRightNode->calculate(parentCell);
    } else if(multRightNode->GetOperator() == TokenType::kDiv)
    {
        result = powRes / multRightNode->calculate(parentCell);
    }
    return result;
}

//Node_MultiplicationRight////////////////////////////////////////////////////////////

int Node_MultiplicationRight::calculate(const Cell* parentCell)
{
    int result(0);
    int powRes = powerNode->calculate(parentCell);
    if(multRightNode->GetOperator() == TokenType::kStar)
    {
        result = powRes * multRightNode->calculate(parentCell);
    } else if(multRightNode->GetOperator() == TokenType::kDiv)
    {
        result = powRes / multRightNode->calculate(parentCell);
    }
    return result;
}

TokenType Node_MultiplicationRight::GetOperator() const
{
    return op;
}

//Node_Power//////////////////////////////////////////////////////////////////////////

int Node_Power::power(int base, int pow) const
{
    if (pow == 0)
        {
            return 1;
        }

        int temp = 1;
        while (pow != 1)
        {
            if (pow % 2 == 0)
            {
                pow /= 2;
                base *= base;
            }
            else
            {
                pow -= 1;
                temp *= base;
            }
        }
        return base * temp;
}

int Node_Power::calculate(const Cell* parentCell)
{
    int result(0);
    int termRes = termNode->calculate(parentCell);
    if(powerRightNode->GetOperator() == TokenType::kPow)
    {
        result = power(termRes, powerRightNode->calculate(parentCell));
    }
    return result;
}

//Node_PowerRight////////////////////////////////////////////////////////////////////
int Node_PowerRight::power(int base, int pow) const
{
    if (pow == 0)
        {
            return 1;
        }

        int temp = 1;
        while (pow != 1)
        {
            if (pow % 2 == 0)
            {
                pow /= 2;
                base *= base;
            }
            else
            {
                pow -= 1;
                temp *= base;
            }
        }
        return base * temp;
}

int Node_PowerRight::calculate(const Cell* parentCell)
{
    int result(0);
    int termRes = termNode->calculate(parentCell);
    if(powerRightNode->GetOperator() == TokenType::kPow)
    {
        result = power(termRes, powerRightNode->calculate(parentCell));
    }
    return result;
}

TokenType Node_PowerRight::GetOperator() const
{
    return op;
}

//Node_Number///////////////////////////////////////////////////////////////////////
int Node_Number::calculate(const Cell* parentCell)
{
    return (numLexema).toInt();
}

//Node_CellLink/////////////////////////////////////////////////////////////////////
int Node_CellLink::calculate(const Cell* parentCell)
{
    return 1;
}

//Node_Term//////////////////////////////////////////////////////////////////////////
int Node_Term::calculate(const Cell* parentCell)
{
    return 1;
}
