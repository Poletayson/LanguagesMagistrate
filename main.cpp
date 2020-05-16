#include <QCoreApplication>
#include <lexem.h>
#include <scanner.h>
#include <analizator.h>
#include <QList>
#include <iostream>
#include <QTextStream>
#include <stdio.h>
#include <locale.h>
#include <llanalizator.h>
//#include <opanalizator.h>
#include "stdio.h"
//using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Analizator A;
//    A.S();

    LLAnalizator A;
    A.toAnalize();

//    OPAnalizator A;
//    A.toAnalize();

    system("pause");
    return 0;
}
