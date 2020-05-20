#ifndef TREELL_H
#define TREELL_H
#include <node.h>
#include <iostream>
#include <QTextStream>
#include <QTextCodec>
#include <lexem.h>

#define Tvoid 1
#define Tmain 2
#define Tfor 3
#define Tint 4
#define Tlong 5
#define Tchar 6
#define Tid 10
#define Tcchar 20
#define Tint10 21
#define Tint8 28
#define Tint16 26

#define Tzap 31
#define Tdt 32
#define Tls 33
#define Trs 34
#define Tlf 35
#define Trf 36
#define Tvch 40
#define Tamp 41
#define Tlsd 42
#define Trsd 43
#define Tplus 44
#define Tminus 45
#define Tdel 46
#define Tmul 47
#define Tpers 48
#define Ttil 49
#define Teq 50

#define Tend 100
#define Terr 200


class TreeLL
{
public:
    enum functions {startDecl = 201, setIdent, endDecl, setFunct, setNewLevel, returnLevel, endFunct, match, matchNumOnly, matchUn, find, findFunc, constType, push_t, matchLeft, startParam, setParam, stopParam, matchParamCount, matchParamType};   //семантические функции

    Node *N;
    TreeLL *Parent, *Left, *Right;
    static TreeLL * Cur;      //текущая вершина
    static TreeLL * F;        //текущая функция

    TreeLL();
    TreeLL(Node *n);
    TreeLL(TreeLL *p, TreeLL *l, TreeLL *r, Node *n);
    void addLeft (Node *n);             //вставить потомка
    void addRight (Node *n);
    TreeLL *Find (TreeLL *From, Node* n);   //поиск в таблице. Может вернуть null если нету
    TreeLL *Find (QString name);   //поиск в таблице. Может вернуть null если нету
    TreeLL *Find (Node* n);   //поиск в таблице. Может вернуть null если нету
    TreeLL *FindOneLevel (TreeLL *From, Node* n);   //поиск в таблице. Может вернуть null если нету
    TreeLL *FindOneLevel (Node* n);   //поиск в таблице. Может вернуть null если нету
    TreeLL *FindOneLevel (QString image);   //поиск в таблице. Может вернуть null если нету
    TreeLL *FindRightLeft (TreeLL *From, Node* n);   //поиск среди прямых потомков. Может вернуть null если нету
    TreeLL *FindRightLeft (Node* n);   //поиск среди прямых потомков. Может вернуть null если нету
    TreeLL *FindRightLeftNum (TreeLL *From, int num);   //поиск среди прямых потомков узла с номером num. Может вернуть null если нету
    int semType (Lexem *lex);   //определение семантического типа
    bool idToTable (Node *n);  //проверка на дублирование, занесение идентификатора вместе с семантическим типом в таблицу
    bool semFToTable (QString name); //занесение имени функции вместе с типом возвращаемого значения в таблицу, создание пустой правой вершины. Возвращает указатель на созданную
    void semSetParAmount (TreeLL* f, int n);    //установить число параметров
    void semRep ();     //восстановление указателя на вершину. Поднимаемся по левым связям и подн. на след уровень
    void semToRight ();     //уйти вправо, создав новый уровень
    void semInc (TreeLL *func);       //увеличить число параметров функции
    void semInc ();       //увеличить число параметров функции
    void semError (std::string err, Lexem* L);
    bool semSearch (Node* n);       //поиск узла
    bool semParAccord ();       ///проверка соотв. параметров
    int semTypeRes (int o1, int o2);      //проверка результата операции
    int semTypeResOnlyNum (int o1, int o2);      //проверка результата для ТОЛЬКО числовых операций
    int semTypeResUn (int o1);      //проверка результата для унарных операций

    void funcSetParamCount(int count);  //установить число параметров для текущей описываемой функции
};

#endif // TREELL_H

