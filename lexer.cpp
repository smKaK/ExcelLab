#include "lexer.h"
#include <QDebug>

QVector<Token> Lexer::Tokenize(const QString& input)
{
    qDebug() << "Tokenize";
    QVector<Token> v;
    QRegExp rx("(\\ )"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    QStringList query = input.split(rx);
    for(auto& s : query)
    {
       QString buffer;
       auto it = s.begin();
       while(it != s.end())
       {
           if(*it == "+" || *it == "-" || *it == "(" || *it == ")" || *it == "*" ||*it == "/" ||*it == "," ||*it == "^")
           {
               if(buffer.size() > 0)
               {
                   v.push_back(buffer);
               }
               v.push_back(Token(*it));
               buffer.clear();
               ++it;
               continue;
           }

           buffer.push_back(*it);
           ++it;
       }
       if(buffer.size() > 0)
       {
           v.push_back(buffer);
       }
   }
           v.push_back(Token(QString("Eof"),TokenType::kEof));
       return v;
}
