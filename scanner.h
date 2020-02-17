#ifndef SCANNER_H
#define SCANNER_H

#include <qfile.h>
#include <QString>
#include <QList>
#include <lexem.h>
#include <QMultiMap>
#include <iostream>
#include <QTextStream>

#define MaxLenth 10

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





class Scanner
{
public:
    QFile *file;
    QString *text;
    QMultiMap <int, QString> Types;
    QMultiMap <int, QString> KeyWords;          //ключевые слова
    QMultiMap <int, QChar> Symbols;          //символы
    QMultiMap <int, QChar> IgnoreSymbols;   //игнорируемые символы

    int lexLenth;
    QList <int*> Errors;
    Scanner();
    Scanner(QString fileName = "input.txt");
    void toScan (QList <Lexem> *lex);
};

#endif // SCANNER_H

