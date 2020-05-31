#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "treell.h"
#include "triad.h"
#include <QFile>
#include <QTextStream>

class Translator
{
    QList <Triad*> triads;  //список сгенерированных триад
    TreeLL *T;  //семантическое дерево

    QString asmCode;    //результирующий код

public:
    Translator(QList <Triad*> triads, TreeLL *T);

    void translate();   //транслировать

private:
    bool registers[4] = {false, false, false, false};  //регистры, заняты или нет
    int registersValues[4] = {-1, -1, -1, -1};  //значения регистров - номера триад
    QMap<int, QString> registersNames;

    /**
     * @brief getInit Пытаемся понять инициализирована ли переменная. Возвращает триаду с инициализацией либо nullptr
     * @param n Узел с этой переменной
     * @return
     */
    Triad* getInit(Node* n);

    /**
     * @brief getRegister Запросить свободный регистр
     * @return Номер регистра, -1 если не нашлось
     */
    int getRegister ();
    /**
     * @brief retRegister Вернуть регистр в пул
     * @param reg Номер освободившегося регистра
     */
    void retRegister (int reg);
    /**
     * @brief getTriadRegister Получить регистр, в котором лежит значение триады
     * @param triadNum
     * @return
     */
    int getTriadRegister (int triadNum);
};

#endif // TRANSLATOR_H
