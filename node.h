#ifndef NODE_H
#define NODE_H
#include <QString>

#define TypeVoid 0
#define TypeMain 1
#define TypeFunc 2
#define TypeInt 3
#define TypeLong 4
#define TypeChar 5

#define TypeUnKnown -1
#define TypeEmpty 10

class Node
{
public:
    QString Id;         //изображение объекта
    int TypeObj;          //тип
    int ParamCount;     //число параметров функции
    Node(QString I, int T, int c = 0);
};
#endif // NODE_H
