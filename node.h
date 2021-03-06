#ifndef NODE_H
#define NODE_H

#include <QSharedPointer>
#include <token.h>
#include <QVector>
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
class Node_FuncWith2Args;
class Node_FuncWith1Arg;
class Node_ExpressionWithBrackets;

class Cell;

class Node
{
public:

    virtual boost::multiprecision::cpp_int calculate( Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) = 0;
    virtual ~Node(){}
};

class Node_Statement : public Node
{
private:
    Cell* parentCell;
    QSharedPointer<Node_Expression> exprNode;
    QVector<Token> cellLinks;

public:
    bool bIsExeption;
    QVector<Token>& getCellLinks();
    Node_Statement();
    virtual boost::multiprecision::cpp_int calculate( Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
    void setExpressionNode(const QSharedPointer<Node_Expression>& newExprNode);
    QSharedPointer<Node_Expression> getExpressionNode() const;
    ~Node_Statement() override;
};

class Node_Expression : public Node
{
private:
    QSharedPointer<Node_Multiplication>  multNode;
    QSharedPointer<Node_ExpressionRight> exprRightNode;
public:

    virtual boost::multiprecision::cpp_int calculate( Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
    void setMultNode(QSharedPointer<Node_Multiplication> newMultNode);
    void setRightExprNode(QSharedPointer<Node_ExpressionRight> newRightExprNode);
    QSharedPointer<Node_Multiplication> getMultNode();
    QSharedPointer<Node_ExpressionRight> getExprRight();
    Node_Expression( );
    ~Node_Expression() override;
};

class Node_ExpressionRight : public Node
{
private:
    TokenType op;
    QSharedPointer<Node_Expression> exprNode;

public:
    virtual boost::multiprecision::cpp_int calculate( Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
    TokenType GetOperator();
    void setOperator(TokenType newOp);

    void setRightExprNode(QSharedPointer<Node_Expression> newRightExprNode);
    QSharedPointer<Node_ExpressionRight> GetEsxprRight();
    Node_ExpressionRight( );
    ~Node_ExpressionRight() override;

};

class  Node_Multiplication : public Node
{
private:
    QSharedPointer<Node_Power> powerNode;
    QSharedPointer<Node_MultiplicationRight> multRightNode;
public:
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 1) override;
    void setPowerNode(QSharedPointer<Node_Power>);
    void setMultRightNode(QSharedPointer<Node_MultiplicationRight> newMultRightNode);
    QSharedPointer<Node_Power> getPowerNode();
    QSharedPointer<Node_MultiplicationRight> getMultRightNode();
    Node_Multiplication( );
    ~Node_Multiplication() override;
};


class Node_MultiplicationRight : public Node
{
private:
    TokenType op;
    QSharedPointer<Node_Multiplication> multNode;
public:
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 1) override;
    void setOperator(TokenType type);
    void setMultiplicationNode(QSharedPointer<Node_Multiplication> newMultNode);
    TokenType GetOperator() const;
    Node_MultiplicationRight( );
    ~Node_MultiplicationRight() override;
};

class Node_Power : public Node
{
private:
   QSharedPointer<Node_Term> termNode;
   QSharedPointer<Node_PowerRight> powerRightNode;
   boost::multiprecision::cpp_int power(boost::multiprecision::cpp_int base, boost::multiprecision::cpp_int pow) const;
public:
   virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 1) override;
   void setTermNode(QSharedPointer<Node_Term> newTermNode);
   void setPowerRightNode(QSharedPointer<Node_PowerRight> newPowerRightNode);
   Node_Power( );
   ~Node_Power() override;
};

class Node_PowerRight : public Node
{
private:
   TokenType op;
   QSharedPointer<Node_Power> powerNode;
   boost::multiprecision::cpp_int power(boost::multiprecision::cpp_int base, boost::multiprecision::cpp_int pow) const;
public:
   virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 1) override;
   TokenType GetOperator() const;
   void setOperator(TokenType type);
   void setPowerNode(QSharedPointer<Node_Power> newPowerNode);
   Node_PowerRight( );
   ~Node_PowerRight() override;

};

class Node_Term : public Node
{
private:
    TokenType op;
    QSharedPointer<Node> termNode;
    TokenType termType;
public:
    Node_Term(TokenType op = TokenType::kPlus);
    ~Node_Term() override;
    void setNode(QSharedPointer<Node> newNode, TokenType type);
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
};

class Node_Number : public Node
{
public:
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
    Node_Number( );
    ~Node_Number() override;
    TokenType getTokenType();
    QString getLexema();
    void setLexema(const QString& newLexema);
private:
    TokenType type;
    QString numLexema;


};

class Node_CellLink : public Node
{
public:
    Node_CellLink();
    ~Node_CellLink() override;
    void setLink(const QString& newCellLink);
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
private:

    TokenType token;
    QString cellLink;

};

class Node_FuncWith2Args : public Node{
public:
    Node_FuncWith2Args(TokenType function);
    ~Node_FuncWith2Args() override;
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
    void setExpr1(QSharedPointer<Node_Expression> newExpr1);
    void setExpr2(QSharedPointer<Node_Expression> newExpr2);
private:
    QSharedPointer<Node_Expression> expr1;
    QSharedPointer<Node_Expression> expr2;
    TokenType function;
};

class Node_FuncWith1Arg : public Node{

public:
    Node_FuncWith1Arg();
    ~Node_FuncWith1Arg() override;
    Node_FuncWith1Arg(TokenType function);
    void setExprWithBr(QSharedPointer<Node_ExpressionWithBrackets> newExprWithBrackets);
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
private:
    QSharedPointer<Node_ExpressionWithBrackets> expressionWithBrackets;
    TokenType function;
};

class Node_ExpressionWithBrackets : public Node
{
private:
    QSharedPointer<Node_Expression> expression;

public:
    void setExpressionNode(QSharedPointer<Node_Expression> newExpression);
    virtual boost::multiprecision::cpp_int calculate(Cell* parentCell, boost::multiprecision::cpp_int leftResult = 0) override;
    ~Node_ExpressionWithBrackets() override;
};

#endif // NODE_H


