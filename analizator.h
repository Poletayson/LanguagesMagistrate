#ifndef ANALIZATOR_H
#define ANALIZATOR_H


//#define Tvoid 1
//#define Tmain 2
//#define Tfor 3
//#define Tint 4
//#define Tlong 5
//#define Tchar 6
//#define Tid 10
//#define Tcchar 20
//#define Tint10 21
//#define Tint8 28
//#define Tint16 26

//#define Tzap 31
//#define Tdt 32
//#define Tls 33
//#define Trs 34
//#define Tlf 35
//#define Trf 36
//#define Tvch 40
//#define Tamp 41
//#define Tlsd 42
//#define Trsd 43
//#define Tplus 44
//#define Tminus 45
//#define Tdel 46
//#define Tmul 47
//#define Tpers 48
//#define Ttil 49
//#define Teq 50

//#define Tend 100
//#define Terr 200


#include <iostream>
#include <QTextStream>
#include <qdebug.h>
#include "lexem.h"
#include "QList"
#include "scanner.h"
#include "locale.h"
#include "tree.h"

//namespace std:
class Analizator
{
public:

    Analizator();
    int cur;    ///текущая вершина
    int tv;     ///тип выражения. Устанавливается в A7()
    Scanner *scaner;
    QList <Lexem> *lex;
    bool right;
    Tree* T;
    std::string ErrorText;
    void toAnalize ();
    void S ();
    bool Data ();
    bool SOper ();
    bool Oper ();
    bool Cicle ();
    bool Prisv ();

    bool Function ();
    bool InitOfCicle ();
    bool EndOfIter ();
    bool A1 ();
    bool A2 ();
    bool A3 ();
    bool A4 ();
    bool A5 ();
    bool A6 ();
    bool A7 ();


};

#endif // ANALIZATOR_H
