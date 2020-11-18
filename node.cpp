#include "node.h"
#include <cmath>
#include <QDebug>
#include <cmath>
#include <algorithm>
#include "cell.h"
//Node statement//////////////////////////////////////////////////////////////////////

using cpp_int = boost::multiprecision::cpp_int;




QVector<Token>& Node_Statement::getCellLinks()
{
    return cellLinks;
}

Node_Statement::Node_Statement( ) : Node()
{
    bIsExeption=false;
}


cpp_int Node_Statement::calculate(const Cell* parentCell, boost::multiprecision::cpp_int leftResult)
{
    qDebug() << "calculate";

        return exprNode->calculate(parentCell);

}

void Node_Statement::setExpressionNode(const QSharedPointer<Node_Expression> &newExprNode)
{
    exprNode = newExprNode;
}

QSharedPointer<Node_Expression> Node_Statement::getExpressionNode() const
{
    return this->exprNode;
}




//Node_ExpresionRight////////////////////////////////////////////////////////////////


cpp_int  Node_ExpressionRight::calculate(const Cell* parentCell, boost::multiprecision::cpp_int leftResult)
{
    cpp_int result;
    if(this->op == TokenType::kPlus)
    {
        leftResult += exprNode->getMultNode()->calculate(parentCell);\
        if(exprNode->getExprRight() == nullptr)
        {
            result = leftResult;
            return result;
        }
        else
        {
            result = exprNode->getExprRight()->calculate(parentCell, leftResult);
            return result;
        }
    }
    else if(this->op == TokenType::kMinus)
    {
        leftResult -= exprNode->getMultNode()->calculate(parentCell);
        if(exprNode->getExprRight() == nullptr)
        {
            result = leftResult;
            return result;
        }
        else
        {
            result = exprNode->getExprRight()->calculate(parentCell, leftResult);
            return result;
        }
    }

//    cpp_int result(0);

//    cpp_int exprNodeCalcRes;
//    if(exprNode == nullptr)
//    {
//       exprNodeCalcRes = 0;
//    }
//    else
//    {
//        exprNodeCalcRes = exprNode->calculate(parentCell);
//    }

//    return exprNodeCalcRes;


//    if(exprNode->getExprRight()->GetOperator() == TokenType::kPlus)
//    {
//        result = multRes +  exprNodeCalcRes;
//    }
//    else if(exprNode->getExprRight()->GetOperator() == TokenType::kMinus)
//    {
//        result = multRes - exprNodeCalcRes;
//    }
//    return result;
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

 Node_ExpressionRight::Node_ExpressionRight()
 {

 }

//Node Expression/////////////////////////////////////////////////////////////////////
cpp_int Node_Expression::calculate(const Cell* parentCell, cpp_int leftResult)
{
    cpp_int result(0);
    cpp_int multRes(multNode->calculate(parentCell));


    leftResult = multRes;


    //cpp_int exprRightNodeCalcRes;

    if(exprRightNode == nullptr )
    {
      result = multRes;
    }
    else
    {
        result = exprRightNode->calculate(parentCell, leftResult);
    }

//    if(exprRightNode == nullptr)
//    {
//        exprRightNodeCalcRes = 0;
//        result = multRes + exprRightNodeCalcRes;
//    }
//    else {
//        exprRightNodeCalcRes = exprRightNode->calculate(parentCell);
//        if(exprRightNode->GetOperator() == TokenType::kPlus)
//        {
//            result = multRes + exprRightNodeCalcRes;
//        }
//        else if(exprRightNode->GetOperator() == TokenType::kMinus)
//        {
//            result = multRes - exprRightNodeCalcRes;
//        }
//    }


    return result;
}

void Node_Expression::setMultNode(QSharedPointer<Node_Multiplication> newMultNode)
{
    multNode = newMultNode;
}

void Node_Expression::setRightExprNode(QSharedPointer<Node_ExpressionRight> newRightExprNode)
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

Node_Expression::Node_Expression()
{

}

//Node_Multiplication/////////////////////////////////////////////////////////////////
cpp_int Node_Multiplication::calculate(const Cell* parentCell, cpp_int leftResult)
{
//    cpp_int result(0);
//    cpp_int powRes;
//    cpp_int multRightNodeCalcRes;

//    if(powerNode == nullptr)
//    {
//        powRes = 0;
//    }
//    else
//    {

//        powRes = powerNode->calculate(parentCell);
//    }

//    if(multRightNode == nullptr)
//    {
//        multRightNodeCalcRes = 1;
//        result = powRes * multRightNodeCalcRes;
//    }
//    else
//    {
//        multRightNodeCalcRes = multRightNode->calculate(parentCell) ;
//        if(multRightNode->GetOperator() == TokenType::kStar)
//        {
//            result = powRes * multRightNodeCalcRes;

//        } else if(multRightNode->GetOperator() == TokenType::kDiv)
//        {
//            result = powRes / multRightNodeCalcRes;
//        }
//    }
    cpp_int result(0);
    cpp_int powRes(powerNode->calculate(parentCell));


    leftResult = powRes;


    //cpp_int exprRightNodeCalcRes;

    if(multRightNode == nullptr )
    {
      result = powRes;
    }
    else
    {
        result = multRightNode->calculate(parentCell, leftResult);
    }


    return result ;
}

void Node_Multiplication::setPowerNode(QSharedPointer<Node_Power> newPowerNode)
{
    powerNode = newPowerNode;
}

void Node_Multiplication::setMultRightNode(QSharedPointer<Node_MultiplicationRight> newMultRightNode)
{
    multRightNode = newMultRightNode;
}

QSharedPointer<Node_Power> Node_Multiplication::getPowerNode()
{
    return powerNode;
}

QSharedPointer<Node_MultiplicationRight> Node_Multiplication::getMultRightNode()
{
    return multRightNode;
}

Node_Multiplication::Node_Multiplication()
{

}

//Node_MultiplicationRight////////////////////////////////////////////////////////////

cpp_int Node_MultiplicationRight::calculate(const Cell* parentCell, cpp_int leftResult)
{
//    cpp_int result(0);

//    cpp_int multRightNodeCalcRes =  multNode->calculate(parentCell);


//    if(multNode->getMultRightNode()->GetOperator() == TokenType::kStar)
//    {
//        result = powRes * multRightNodeCalcRes;
//    } else if(multNode->getMultRightNode()->GetOperator() == TokenType::kDiv)
//    {
//        result = powRes / multRightNodeCalcRes;
//    }
//    return multRightNodeCalcRes;

    cpp_int result;
    if(this->op == TokenType::kStar)
    {
        leftResult *= multNode->getPowerNode()->calculate(parentCell);\
        if(multNode->getMultRightNode() == nullptr)
        {
            result = leftResult;
            return result;
        }
        else
        {
            result = multNode->getMultRightNode()->calculate(parentCell, leftResult);
            return result;
        }
    }
    else if(this->op == TokenType::kDiv)
    {
        leftResult /= multNode->getPowerNode()->calculate(parentCell);
        if(multNode->getMultRightNode() == nullptr)
        {
            result = leftResult;
            return result;
        }
        else
        {
            result = multNode->getMultRightNode()->calculate(parentCell, leftResult);
            return result;
        }
    }

}

void Node_MultiplicationRight::setOperator(TokenType type)
{
    op = type;
}

void Node_MultiplicationRight::setMultiplicationNode(QSharedPointer<Node_Multiplication> newMultNode)
{
    multNode = newMultNode;
}

TokenType Node_MultiplicationRight::GetOperator() const
{
    return op;
}

Node_MultiplicationRight::Node_MultiplicationRight()
{

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

cpp_int Node_Power::calculate(const Cell* parentCell, cpp_int leftResult)
{
    cpp_int result(0);
    cpp_int termRes(termNode->calculate(parentCell) );
    cpp_int powerRightNodeCalcRes;
    if(powerRightNode == nullptr)
    {
        powerRightNodeCalcRes = 1;
        result = power(termRes,  powerRightNodeCalcRes);
    }
    else {
        powerRightNodeCalcRes = powerRightNode->calculate(parentCell) ;
//        if(powerRightNode->GetOperator() == TokenType::kPow)
//        {
            result = power(termRes,  powerRightNodeCalcRes);
//        }
    }

    return result;
}

void Node_Power::setTermNode(QSharedPointer<Node_Term> newTermNode)
{
    termNode = newTermNode;
}

void Node_Power::setPowerRightNode(QSharedPointer<Node_PowerRight> newPowerRightNode)
{
    powerRightNode = newPowerRightNode;
}

Node_Power::Node_Power()
{

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

cpp_int Node_PowerRight::calculate(const Cell* parentCell, cpp_int leftResult)
{
    cpp_int powerNodeCalcRes ;
    if(powerNode == nullptr)
    {
        powerNodeCalcRes = 1;
    }
    else {
        powerNodeCalcRes =  powerNode->calculate(parentCell);
    }


    return powerNodeCalcRes;
}

TokenType Node_PowerRight::GetOperator() const
{
    return op;
}

void Node_PowerRight::setOperator(TokenType type)
{
    op = type;
}

void Node_PowerRight::setPowerNode(QSharedPointer<Node_Power> newPowerNode)
{
    powerNode = newPowerNode;
}

Node_PowerRight::Node_PowerRight()
{

}

//Node_Number///////////////////////////////////////////////////////////////////////
cpp_int Node_Number::calculate(const Cell* parentCell, cpp_int leftResult)
{
    return (numLexema).toInt();
}

Node_Number::Node_Number()
{

}

TokenType Node_Number::getTokenType()
{
    return this->type;
}

QString Node_Number::getLexema()
{
    return this->numLexema;
}

void Node_Number::setLexema(const QString &newLexema)
{
    this->numLexema = newLexema;
}

//Node_CellLink/////////////////////////////////////////////////////////////////////
Node_CellLink::Node_CellLink()
{

}

void Node_CellLink::setLink(const QString &newCellLink)
{
    cellLink = newCellLink;
}

cpp_int Node_CellLink::calculate(const Cell* parentCell, cpp_int leftResult)
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

void Node_Term::setNode(QSharedPointer<Node> newNode, TokenType type)
{
       termNode = newNode;
       termType = type;
}

cpp_int Node_Term::calculate(const Cell* parentCell, cpp_int leftResult)
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

boost::multiprecision::cpp_int Node_FuncWith2Args::calculate(const Cell *parentCell, cpp_int leftResult)
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

void Node_FuncWith2Args::setExpr1(QSharedPointer<Node_Expression> newExpr1)
{
    expr1 = newExpr1;
}

void Node_FuncWith2Args::setExpr2(QSharedPointer<Node_Expression> newExpr2)
{
    expr2 = newExpr2;
}

//Node_FuncWith1Arg/////////////////////////////////////////////////////////////////////////////////////////////

Node_FuncWith1Arg::Node_FuncWith1Arg()
{

}

Node_FuncWith1Arg::Node_FuncWith1Arg(TokenType function) : function(function)
{

}

void Node_FuncWith1Arg::setExprWithBr(QSharedPointer<Node_ExpressionWithBrackets> newExprWithBrackets)
{
    expressionWithBrackets = newExprWithBrackets;
}

boost::multiprecision::cpp_int Node_FuncWith1Arg::calculate(const Cell *parentCell, cpp_int leftResult)
{
    cpp_int arg1 = expressionWithBrackets->calculate(parentCell);
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
void Node_ExpressionWithBrackets::setExpressionNode(QSharedPointer<Node_Expression> newExpression)
{
    expression = newExpression;
}

boost::multiprecision::cpp_int Node_ExpressionWithBrackets::calculate(const Cell *parentCell, cpp_int leftResult)
{
    return expression->calculate(parentCell);
}
