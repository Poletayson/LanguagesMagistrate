#ifndef TREE_H
#define TREE_H
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


class Tree
{
public:
    enum functions {startDecl = 201, setIdent, endDecl, setFunct, setNewLevel, returnLevel, endFunct, match, find, constType, push_t, matchLeft};   //семантические функции

    Node *N;
    Tree *Parent, *Left, *Right;
    static Tree * Cur;      //текущая вершина
    static Tree * F;        //текущая функция
    Tree();
    Tree(Node *n);
    Tree(Tree *p, Tree *l, Tree *r, Node *n);
    void addLeft (Node *n);             //вставить потомка
    void addRight (Node *n);
    Tree *Find (Tree *From, Node* n);   //поиск в таблице. Может вернуть null если нету
    Tree *Find (QString name);   //поиск в таблице. Может вернуть null если нету
    Tree *Find (Node* n);   //поиск в таблице. Может вернуть null если нету
    Tree *FindOneLevel (Tree *From, Node* n);   //поиск в таблице. Может вернуть null если нету
    Tree *FindOneLevel (Node* n);   //поиск в таблице. Может вернуть null если нету
    Tree *FindRightLeft (Tree *From, Node* n);   //поиск среди прямых потомков. Может вернуть null если нету
    Tree *FindRightLeft (Node* n);   //поиск среди прямых потомков. Может вернуть null если нету
    int semType (Lexem *lex);   //определение семантического типа
    bool semToTable (Node *n);  //проверка на дублирование, занесение идентификатора вместе с семантическим типом в таблицу
    bool semFToTable (QString name); //занесение имени функции вместе с типом возвращаемого значения в таблицу, создание пустой правой вершины. Возвращает указатель на созданную
    void semSetParAmount (Tree* f, int n);    //установить число параметров
    void semRep ();     ///восстановление указателя на вершину. Поднимаемся по левым связям и подн. на след уровень
    void semToRight ();     //уйти вправо
    void semInc (Tree *func);       //увеличить число параметров функции
    void semInc ();       //увеличить число параметров функции
    void semError (std::string err, Lexem* L);
    bool semSearch (Node* n);       //поиск узла
    bool semParAccord ();       ///проверка соотв. параметров
    int semTypeRes (int o1, int o2, Lexem* l);      //проверка результата операции
    int semTypeResOnlyNum (int o1, int o2, Lexem* l);      //проверка результата для ТОЛЬКО числовых операций
    int semTypeResUn (int o1, Lexem* l);      //проверка результата для унарных операций
};

#endif // TREE_H
