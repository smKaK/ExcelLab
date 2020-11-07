#include "node.h"
#include <cmath>
#include <QDebug>
#include <cmath>
#include <algorithm>

//Node statement//////////////////////////////////////////////////////////////////////

using cpp_int = boost::multiprecision::cpp_int;




Node_Statement::Node_Statement( ) : Node()
{

}


cpp_int Node_Statement::calculate(const Cell* parentCell)
{
    qDebug() << "calculate";
    return 1000;
    // return exprNode->calculate(parentCell);
}

void Node_Statement::setExpressionNode(const QSharedPointer<Node_Expression> &newExprNode)
{
    exprNode =  newExprNode;
}

QSharedPointer<Node_Expression> Node_Statement::getExpressionNode() const
{
    return this->exprNode;
}




//Node_ExpresionRight////////////////////////////////////////////////////////////////


cpp_int  Node_ExpressionRight::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int multRes(exprNode->getMultNode()->calculate(parentCell));
    cpp_int exprNodeCalcRes = exprNode->calculate(parentCell);
    if(exprNode->getExprRight()->GetOperator() == TokenType::kPlus)
    {
        result = multRes +  exprNodeCalcRes;
    }
    else if(exprNode->getExprRight()->GetOperator() == TokenType::kMinus)
    {
        result = multRes - exprNodeCalcRes;
    }
    return result;
}

 TokenType Node_ExpressionRight::GetOperator()
{
     return op;
 }

 void Node_ExpressionRight::setOperator(TokenType newOp)
 {
     this->op = newOp;
 }


 void Node_ExpressionRight::setRightExprNode(QSharedPointer<Node_Expression> newRightExprNode)
 {
     this->exprNode = newRightExprNode;
 }

//Node Expression/////////////////////////////////////////////////////////////////////
cpp_int Node_Expression::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int multRes(multNode->calculate(parentCell));
    cpp_int exprRightNodeCalcRes = exprRightNode->calculate(parentCell);
    if(exprRightNode->GetOperator() == TokenType::kPlus)
    {
        result = multRes + exprRightNodeCalcRes;
    }
    else if(exprRightNode->GetOperator() == TokenType::kMinus)
    {
        result = multRes - exprRightNodeCalcRes;
    }
    return result;
}

void Node_Expression::setMultNode(QSharedPointer<Node_Multiplication> newMultNode)
{
    multNode = newMultNode;
}

void Node_Expression::setRightExprNode(QSharedPointer<Node_Expression> newRightExprNode)
{
    this->exprRightNode = newRightExprNode;
}

QSharedPointer<Node_Multiplication> Node_Expression::getMultNode()
{
    return multNode;
}

QSharedPointer<Node_ExpressionRight> Node_Expression::getExprRight()
{
    return this->exprRightNode;
}

//Node_Multiplication/////////////////////////////////////////////////////////////////
cpp_int Node_Multiplication::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int powRes(powerNode->calculate(parentCell));
    cpp_int multRightNodeCalcRes = multRightNode->calculate(parentCell) ;
    if(multRightNode->GetOperator() == TokenType::kStar)
    {
        result = powRes * multRightNodeCalcRes;

    } else if(multRightNode->GetOperator() == TokenType::kDiv)
    {
        result = powRes / multRightNodeCalcRes;
    }
    return result ;
}

void Node_Multiplication::setPowerNode(QSharedPointer<Node_Power> newPowerNode)
{
    powerNode = newPowerNode;
}

void Node_Multiplication::setRightMultnode(QSharedPointer<Node_MultiplicationRight> newMultRightNode)
{
    multRightNode = newMultRightNode
}

//Node_MultiplicationRight////////////////////////////////////////////////////////////

cpp_int Node_MultiplicationRight::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int powRes =  powerNode->calculate(parentCell);
    cpp_int multRightNodeCalcRes =  multRightNode->calculate(parentCell);
    if(multRightNode->GetOperator() == TokenType::kStar)
    {
        result = powRes * multRightNodeCalcRes;
    } else if(multRightNode->GetOperator() == TokenType::kDiv)
    {
        result = powRes / multRightNodeCalcRes;
    }
    return result;
}

TokenType Node_MultiplicationRight::GetOperator() const
{
    return op;
}

//Node_Power//////////////////////////////////////////////////////////////////////////

cpp_int Node_Power::power(cpp_int base, cpp_int pow) const
{
    if (pow == 0)
        {
            return 1;
        }

        cpp_int temp = 1;
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
       return   temp * base;

}

cpp_int Node_Power::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int termRes(termNode->calculate(parentCell) );
    cpp_int powerRightNodeCalcRes = powerRightNode->calculate(parentCell) ;
    if(powerRightNode->GetOperator() == TokenType::kPow)
    {
        result = power(termRes,  powerRightNodeCalcRes);
    }
    return result;
}

//Node_PowerRight////////////////////////////////////////////////////////////////////
 cpp_int Node_PowerRight::power(cpp_int base, cpp_int pow) const
{
    if (pow == 0)
        {
            return 1;
        }

        cpp_int temp = 1;
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

cpp_int Node_PowerRight::calculate(const Cell* parentCell)
{
    cpp_int result(0);
    cpp_int termRes(termNode->calculate(parentCell));
    cpp_int powerRightNodeCalcRes =  powerRightNode->calculate(parentCell);
    if(powerRightNode->GetOperator() == TokenType::kPow)
    {
        result = power(termRes, powerRightNodeCalcRes);
    }
    return result;
}

TokenType Node_PowerRight::GetOperator() const
{
    return op;
}

//Node_Number///////////////////////////////////////////////////////////////////////
cpp_int Node_Number::calculate(const Cell* parentCell)
{
    return (numLexema).toInt();
}

//Node_CellLink/////////////////////////////////////////////////////////////////////
cpp_int Node_CellLink::calculate(const Cell* parentCell)
{
    QString column;
    QString row;
    for(int i =0 ; i < this->cellLink.length(); ++i)
    {
        if(cellLink[i].unicode() >= QChar('A').unicode() && cellLink[i].unicode() <= QChar('Z').unicode())
        {
           column.push_back(cellLink[i]);
        } else {
           row.push_back(cellLink[i]);
        }
    }
    int rowNum = row.toInt();
    int columnNum = 0;
    for(int i = column.length()-1; i >= 0; --i)
    {
        columnNum += std::pow(26, column.length() - 1 - i)*(column[i].unicode() - QChar('A').unicode() + 1);
    }

    return cpp_int(parentCell->getAnotherCellData(rowNum, columnNum).toString().toStdString());
}

//Node_Term//////////////////////////////////////////////////////////////////////////
Node_Term::Node_Term(TokenType op) : op(op)
{

}

cpp_int Node_Term::calculate(const Cell* parentCell)
{
    if(this->op == TokenType::kPlus)
    {
        return termNode->calculate(parentCell) * 1;
    } else if(this->op == TokenType::kMin){
        return termNode->calculate(parentCell) * (-1);
    }

}
//Node_FuncWith2Args//////////////////////////////////////////////////////////////////////////////////////////////
Node_FuncWith2Args::Node_FuncWith2Args(TokenType function) : function(function)
{

}

boost::multiprecision::cpp_int Node_FuncWith2Args::calculate(const Cell *parentCell)
{
    cpp_int arg1 = expr1->calculate(parentCell);
    cpp_int arg2 = expr2->calculate(parentCell);
    if(function == TokenType::kMax)
    {
        return std::max(arg1, arg2);
    }
    else
    {
        return std::min(arg1,arg2);
    }
}
//Node_FuncWith1Arg/////////////////////////////////////////////////////////////////////////////////////////////

Node_FuncWith1Arg::Node_FuncWith1Arg(TokenType function) : function(function)
{

}

boost::multiprecision::cpp_int Node_FuncWith1Arg::calculate(const Cell *parentCell)
{
    cpp_int arg1 = expression->calculate(parentCell);
    if(function == TokenType::kDec)
    {
        return --arg1;
    }
    else
    {
        return ++arg1;
    }


}


//Node_ExpressionWithBrackets///////////////////////////////////////////////////////////////////////////////////
boost::multiprecision::cpp_int Node_ExpressionWithBrackets::calculate(const Cell *parentCell)
{
    return expression->calculate(parentCell);
}
