#ifndef NODE_H
#define NODE_H

#include <QSharedPointer>
#include <token.h>
#include "cell.h"
#include <boost/multiprecision/cpp_int.hpp>

class Node_Statement;
class Node_Expression;
class Node_ExpressionRight;
class Node_Multiplication;
class Node_MultiplicationRight;
class Node_Power;
class Node_PowerRight;
class Node_Term;
class Node_Number;
class Node_CellLink;
class Node_function;
class Node_Arg1;
class Node_Arg2;


class Node
{
public:

    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) = 0;
};

class Node_Statement : public Node
{
private:
    Cell* parentCell;
    QSharedPointer<Node_Expression> exprNode;
public:
    Node_Statement( );
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
    void setExpressionNode(const QSharedPointer<Node_Expression>& newExpxrNode);

};

class Node_Expression : public Node
{
private:
    QSharedPointer<Node_Multiplication>  multNode;
    QSharedPointer<Node_ExpressionRight> exprRightNode;
public:
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
    Node_Expression( );

};

class Node_ExpressionRight : public Node
{
private:
    TokenType op;
    QSharedPointer<Node_Multiplication> multNode;
    QSharedPointer<Node_ExpressionRight> exprRightNode;

public:
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
    TokenType GetOperator();
    QSharedPointer<Node_ExpressionRight> GetEsxprRight();
    Node_ExpressionRight( );


};

class  Node_Multiplication : public Node
{
private:
    QSharedPointer<Node_Power> powerNode;
    QSharedPointer<Node_MultiplicationRight> multRightNode;
public:
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
    Node_Multiplication( );

};


class Node_MultiplicationRight : public Node
{
private:
    TokenType op;
    QSharedPointer<Node_Power> powerNode;
    QSharedPointer<Node_MultiplicationRight> multRightNode;
public:
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
    TokenType GetOperator() const;
    Node_MultiplicationRight( );

};

class Node_Power : public Node
{
private:
   QSharedPointer<Node_Term> termNode;
   QSharedPointer<Node_PowerRight> powerRightNode;
   boost::multiprecision::cpp_int power(boost::multiprecision::cpp_int base, boost::multiprecision::cpp_int pow) const;
public:
   virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
   Node_Power( );

};

class Node_PowerRight : public Node
{
private:
   TokenType op;
   QSharedPointer<Node_Term> termNode;
   QSharedPointer<Node_PowerRight> powerRightNode;
   boost::multiprecision::cpp_int power(boost::multiprecision::cpp_int base, boost::multiprecision::cpp_int pow) const;
public:
   virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
   TokenType GetOperator() const;
   Node_PowerRight( );


};

class Node_Term : public Node
{
private:

public:
    Node_Term( );
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
};

class Node_Number : public Node
{
public:
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
private:
    TokenType token;
    QString numLexema;
    Node_Number( );

};

class Node_CellLink : public Node
{
public:
    virtual boost::multiprecision::cpp_int calculate(const Cell* parentCell) override;
private:
    TokenType token;
    QString cellLink;
    Node_CellLink( );

};
#endif // NODE_H
