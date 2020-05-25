#ifndef TRIAD_H
#define TRIAD_H

#include "node.h"

struct Operand {
    bool isLink; // непосредственный операнд или ссылка

    int number;    // номер триады- ссылки
    Node *node; // непосредственный операнд - узел дерева

public:
    Operand(int triadNum);  //операнд - ссылка на триаду
    Operand(Node *operand); //непосредственный операнд
    int getType (); //получить тип, либо непосредственного операнда, либо триады
  };

class Triad
{
public:
    int operation;  //операция
    Operand *operand1, *operand2;

    int type;    //тип результата триады


    enum operations {CtoI, ItoL, plus, minus, mul, div, mod, eq};

    Triad();
    Triad(int operation, Operand *op1, Operand *op2);
    int getType() const;
    void setType(int value);
    int getOperation() const;
    void setOperation(int value);

    QString toString ();
};

#endif // TRIAD_H
