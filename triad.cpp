#include "triad.h"


int Triad::getType() const
{
    return type;
}

void Triad::setType(int value)
{
    type = value;
}

int Triad::getOperation() const
{
    return operation;
}

void Triad::setOperation(int value)
{
    operation = value;
}

Triad::Triad()
{
    
}

Triad::Triad(int operation, Operand *op1, Operand *op2)
{
    this->operation = operation;
    this->operand1 = op1;
    this->operand2 = op2;
}

Operand::Operand(int triadNum)
{
    number = triadNum;
    isLink = true;  //операнд - ссылка на триаду
}

Operand::Operand(Node *operand)
{
    node = operand;
    isLink = false; //непосредственный операнд
}

int Operand::getType()
{
    return node->TypeObj;
}
