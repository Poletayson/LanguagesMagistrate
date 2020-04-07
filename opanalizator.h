#ifndef OPANALIZATOR_H
#define OPANALIZATOR_H

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



#include <iostream>
#include <QTextStream>
#include <qdebug.h>
#include "lexem.h"
#include "QList"
#include "scanner.h"
#include "locale.h"
#include "tree.h"
#include <rule.h>
#include <QStack>

#include <xlsxdocument.h>   //библиотека для Exel
#include <xlsxformat.h>

class OPAnalizator
{
    QList <Lexem> Stack;   //магазин
    QList <int> StackPrecedence; //магазин с отношениями предшествования

    QList <QList<Rule>> grammar;    //грамматика
    QMap<int, QMap<int, QList<int>>> matrixPrecedence;  //матрица предшествования

    QMap <int, QString> lexImages;


private:
    QList<int> getPrecedence (int x1, int x2);  //получить список с отношениями для двух лексем
    int getPrecedence ();   //получить отношениt для двух верхуши магазина и символа цепочки
    int getReduceLength (); //длина редуцируемой цепочки

public:
    enum NTeminals {NS = 101, NData, NSpPar, NSpId, NBlock, NOperator, NCicle, NInitCycle, NEndIter, NPrisv, NOperand, NA1, NA2, NA3, NA4, NA5, NA6, NA7, NVizFunc, NSpID2};
    enum Precedence {LESS_EQUAL = -1, NOT_PRECEDENCE = 0, MORE = 1};

    OPAnalizator();

    void toAnalize ();

    void getGrammar (); //считать грамматику
    void getMatrix ();  //считать матрицу предшествования


    bool isError;
    int cur;    ///текущая вершина
    int tv;     ///тип выражения. Устанавливается в A7()
    Scanner *scaner;
    QList <Lexem> *lex;
    bool right;
//    Tree* T;
    QString ErrorText;
};

#endif // OPANALIZATOR_H
