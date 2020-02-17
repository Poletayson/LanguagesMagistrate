#ifndef LLANALIZATOR_H
#define LLANALIZATOR_H

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

#define NS 101
#define NData 102
#define NSpPar 103
#define NB 104
#define NB1 105
#define NSpIdent 106
#define NC 107
#define NInit 108
#define NBlock 109
#define NOperator 110
#define NCicle 111
#define NInitCycle 112
#define NEndIter 113
#define NPrisv 114
#define NOperand 115
#define NA1 116
#define NA11 117
#define NA2 118
#define NA21 119
#define NA3 120
#define NA31 121
#define NA4 122
#define NA41 123
#define NA5 124
#define NA51 125
#define NA6 126
#define NA7 127
#define NVizFunc 128
#define NSpID2 129
#define ND 130


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

class LLAnalizator
{
public:
    QStack <Lexem> Stack;
    QMultiMap <int, QMultiMap <int, QList<Rule>>> Table;
    QMultiMap <int, std::string> NTerminalsNames;
    LLAnalizator();
    void toAnalize ();


    bool isError;
    int cur;    ///текущая вершина
    int tv;     ///тип выражения. Устанавливается в A7()
    Scanner *scaner;
    QList <Lexem> *lex;
    bool right;
//    Tree* T;
    std::string ErrorText;
};

#endif // LLANALIZATOR_H
