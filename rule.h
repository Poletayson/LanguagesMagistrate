#ifndef RULE_H
#define RULE_H
#include "lexem.h"
#include "QList"

class Rule
{

public:
    QList <Lexem*> *rule;
    Rule();
    Rule(QList<Lexem*>* Cell)
    {
        rule = new QList<Lexem*> (*Cell);
    }
};

#endif // RULE_H
