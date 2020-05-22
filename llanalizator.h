#ifndef LLANALIZATOR_H
#define LLANALIZATOR_H


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


#include "treell.h"
#include "triad.h"
#include <iostream>
#include <QTextStream>
#include <qdebug.h>
#include "QList"
#include "scanner.h"
#include <rule.h>

#include "locale.h"
#include <QStack>

class LLAnalizator
{
public:
    QStack <Lexem> Stack;
    QMultiMap <int, QMultiMap <int, QList<Rule>>> Table;
    QMultiMap <int, QString> NTerminalsNames;
    LLAnalizator();
    void toAnalize ();


    bool isError;
    bool isSemError;
    int cur;    ///текущая вершина
    /**
     * @brief тип выражения. Устанавливается в A7()
     */
    int tv;

    bool isDecl = false;
    int type1;
    int type2;
    QStack <int> types; //стек типов
    QStack <Operand> operands;  //стек операндов


    Scanner *scaner;
    QList <Lexem> *lex;
    bool right;
    TreeLL *T;
    QString ErrorText;
    QString ErrorSem;
private:
    int paramCount; //счетчик параметров функции
    TreeLL *findedFunc;

    QList <Triad*> triads;  //список сгенерированных триад
    Operand *result;   // очередной результат

    /**
     * @brief установить флаг описания данных и запомнить тип в глобальной  переменной dataType
     */
    void startDecl();
    /**
     * @brief проверить дублирование, занести идентификатор в семантическую таблицу с dataType
     */
    bool setIdent();
    /**
     * @brief проверить дублирование, занести идентификатор в семантическую таблицу с dataType и увеличить счетчик параметров
     */
    bool setParam();
    /**
     * @brief сбросить флаг описания данных
     */
    void endDecl();
    /**
     * @brief перейти на новый уровень в дереве
     */
    void setNewLevel ();
    /**
     * @brief подняться на предыдущий уровень в дереве
     */
    void returnLevel ();
    /**
     * @brief проверить дублирование,добавить функцию в семантическую таблицу
     */
    bool setFunct ();
    /**
     * @brief Находит
     * @return
     */
    TreeLL* findId ();

    /**
     * @brief ищет функцию и присваивает найденный узел findedFunc
     * @return найденный узел либо null
     */
    TreeLL* findFunc ();
    /**
     * @brief определить тип константы и поместить в магазин
     * @return
     */
    int constType ();
    /**
     * @brief
     * @return приведенный тип
     */
    int match ();

    int matchPlus ();
    int matchMinus ();
    int matchMul ();
    int matchDiv ();
    int matchMod ();
    /**
     * @brief
     * @return приведенный тип
     */
    int matchNumOnly ();
    /**
     * @brief
     * @return приведенный тип
     */
    int matchUn ();

    bool matchParamCount ();
};

#endif // LLANALIZATOR_H
