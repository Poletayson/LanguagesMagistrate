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
  };

class Triad
{
    int operation;  //операция
    Operand *operand1, *operand2;

    int resType;    //тип результата триады

public:
    enum operations {CtoI, ItoL, plus, minus, mul, div, mod, eq};

    Triad();
    Triad(int operation, Operand *op1, Operand *op2);
    int getResType() const;
    void setResType(int value);
};

#endif // TRIAD_H
