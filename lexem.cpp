#include "lexem.h"

Lexem::Lexem()
{
    isNT = false;
}

Lexem::Lexem(int t, QString i)
{
    image = i;
    type = t;
    isNT = false;
}
Lexem::Lexem(int t, bool isN)
{
    type = t;
    isNT = isN;
}
