#ifndef LEXEM_H
#define LEXEM_H
#include <QString>

class Lexem
{
public:
    int type;
    QString image;
    int str;
    int pos;
    bool isNT;
    Lexem();
    Lexem(int t, QString i);
    Lexem(int t, bool isN);
};

#endif // LEXEM_H
