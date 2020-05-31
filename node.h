#ifndef NODE_H
#define NODE_H
#include <QString>

//семантические типы
//#define TypeVoid 0
//#define TypeMain 1
//#define TypeFunc 2
//#define TypeInt 3
//#define TypeLong 4
//#define TypeChar 5

//#define TypeUnKnown -1
//#define TypeEmpty 10

class Node
{
public:
    enum semTypes {TypeVoid = 0, TypeMain, TypeFunc, TypeInt, TypeLong, TypeChar, TypeUnKnown = -1, TypeEmpty = 10};
    QString Id;         //изображение объекта
    QString Id_asm;         //изображение объекта в ассемблере
    int TypeObj;          //тип
    int ParamCount;     //число параметров функции

    int stackOffset;     //смещение от EBP
    Node(QString I, int T, int c = 0);
//    static int getSemType (int type);
};
#endif // NODE_H
