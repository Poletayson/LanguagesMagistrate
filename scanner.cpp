#include "scanner.h"

Scanner::Scanner()
{

}
Scanner::Scanner(QString fileName)      //получить текст из файла
{
    file = new QFile (fileName);
    file->open(QIODevice::ReadOnly);

    Types.insert(1, "Tvoid");
    Types.insert(2, "Tmain");
    Types.insert(3, "Tfor");
    Types.insert(4, "Tint");
    Types.insert(5, "Tlong");
    Types.insert(6, "Tchar");
    Types.insert(10, "Tid");
    Types.insert(20, "Tcchar");
    Types.insert(21, "Tint10");
    Types.insert(28, "Tint8");
    Types.insert(26, "Tint16");
    Types.insert(31, "Tzap");
    Types.insert(32, "Tdt");
    Types.insert(33, "Tls");
    Types.insert(34, "Trs");
    Types.insert(35, "Tlf");
    Types.insert(36, "Trf");
    Types.insert(40, "Tvch");
    Types.insert(41, "Tamp");
    Types.insert(42, "Tlsd");
    Types.insert(43, "Trsd");
    Types.insert(44, "Tplus");
    Types.insert(45, "Tminus");
    Types.insert(46, "Tdel");
    Types.insert(47, "Tmul");
    Types.insert(48, "Tpers");
    Types.insert(49, "Ttil");
    Types.insert(50, "Teq");
    Types.insert(100, "Tend");
    Types.insert(200, "Terr");

    KeyWords.insert(1, "void");
    KeyWords.insert(2, "main");
    KeyWords.insert(3, "for");
    KeyWords.insert(4, "int");
    KeyWords.insert(5, "long");
    KeyWords.insert(6, "char");


    Symbols.insert(31, ',');
    Symbols.insert(32, ';');
    Symbols.insert(33, '(');
    Symbols.insert(34, ')');
    Symbols.insert(35, '{');
    Symbols.insert(36, '}');
    Symbols.insert(40, '|');
    Symbols.insert(41, '&');
    //Symbols.insert(42, "Tlsd");
    //Symbols.insert(43, "Trsd");
    Symbols.insert(44, '+');
    Symbols.insert(45, '-');
    Symbols.insert(46, '/');
    Symbols.insert(47, '*');
    Symbols.insert(48, '%');
    Symbols.insert(49, '~');
    Symbols.insert(50, '=');

    IgnoreSymbols.insert(1, ' ');
    IgnoreSymbols.insert(2, '\n');
    IgnoreSymbols.insert(3, '\r');
    IgnoreSymbols.insert(4, '\t');

    text = new QString ();
    text->append(file->readAll());
    text->append('\0');
    file->close();
}

void Scanner::toScan (QList <Lexem> *lex)
{
    QTextStream cout (stdout);
    int uk = 0;
    int str = 1;
    int pos = 1;
    int posb,strb;
    QString LexIm;         //изображение лексемы
    while (uk < text->length())         //проходим весь текст
    {
        lexLenth = 0;
 N0:    LexIm.clear();
        while ( IgnoreSymbols.key((*text)[uk]) > 0)         //пропускаем незн. символы
        {
            if ((*text)[uk++]=='\n')
            {
                str++;
                pos = 1;
            }
        }

        if ((*text)[uk]=='\0')          //конец модуля
            {
                lex->append(*new Lexem (Tend, ""));
                return;
            }

        else if ((*text)[uk] == '/')  //черта
        {
            if ((*text)[uk+1] == '/')     //вторая черта - значит комментарий
            {
                pos+=2;
                uk+=2;
                while ((*text)[uk] != '\n' && (*text)[uk] != '\0')         //пропускаем все символы, кроме конца строки и модуля
                {
                    uk++;
                    pos++;
                }
            }
            else    //не комментарий
            {
                goto next;
            }
        }

       else
        {
            posb = pos;
            strb = str;
next:       if ((*text)[uk] == '0')     //цифра 0
            {
                LexIm.append(((*text)[uk]));
                uk++;
                pos++;
                if ((*text)[uk] == 'x')         //стоит x
                {
                    LexIm.append((*text)[uk]);
                    uk++;
                    if ((*text)[uk].isDigit() || ((*text)[uk] >= 'A' && (*text)[uk] <= 'F' ))   //второй символ
                    {
                        LexIm.append((*text)[uk++]);
                        pos++;
                    }
                    else
                    {
                        //goto err
                    }
                    while ((*text)[uk].isDigit() || ((*text)[uk] >= 'A' && (*text)[uk] <= 'F' ))
                    {
                        if (lexLenth <= MaxLenth)
                        {
                            LexIm.append((*text)[uk++]);
                        }
                        else
                            goto errors;
                            //uk++;
                        pos++;
                        lexLenth++;
                    }
                    lex->append (*new Lexem (Tint16, LexIm));           // x16 число
                }
                else
                {
                    while ((*text)[uk].isDigit() && !(((*text)[uk] == '9' || (*text)[uk] == '8' )))
                    {
                        if (lexLenth <= MaxLenth)
                            LexIm.append((*text)[uk++]);
                        else
                            goto errors;
                            //uk++;
                        lexLenth++;
                        pos++;
                    }
                    lex ->append (*new Lexem (Tint8, LexIm));           // x8 число
                }
            }
            else if ((*text)[uk].isDigit())     //цифра
            {
                while ((*text)[uk].isDigit())
                {
                    if (lexLenth <= MaxLenth)
                        LexIm.append((*text)[uk++]);
                    else
                        goto errors;
                        //uk++;
                    lexLenth++;
                    pos++;
                }
//                if (!(IgnoreSymbols.key((*text)[uk]) > 0) && )
//                    goto errors;
                lex->append (*new Lexem (Tint10, LexIm));           //x10 число
            }

            else if ((*text)[uk].isLetter() || (*text)[uk] == '_')            //буква
            {
                while ((*text)[uk].isLetter() || (*text)[uk].isDigit() || (*text)[uk] == '_') //считываем буквы и цифры
                {
                    if (lexLenth <= MaxLenth * 2)         //ограничение вдвое больше чем для чисел
                        LexIm.append((*text)[uk++]);
                    else
                        goto errors;
                        //uk++;
                    pos++;
                    lexLenth++;
                }
                int typeKeyWord = KeyWords.key(LexIm);      //получаем ключ ключевого слова
                if (typeKeyWord > 0)
                {
                    lex->append (*new Lexem (typeKeyWord, LexIm));           //некоторое ключевое слово
                }
                else
                    lex->append (*new Lexem (Tid, LexIm));           //идентификатор
            }
            else if ((*text)[uk] == '\'')            //кавычка
            {
                LexIm.append((*text)[uk++]);
                LexIm.append((*text)[uk++]);
                LexIm.append((*text)[uk++]);
                pos +=3;
                if ((*text)[uk-1] == '\'')        //тоже кавычка
                {

                    lex->append (*new Lexem  (Tcchar, LexIm));
                }
                else            //ошибка
                {
                    goto errors;
                }
                //uk++;

            }

            else if ((*text)[uk] == '<')  //знак операции
            {
                LexIm.append((*text)[uk++]);
                pos++;
                if ((*text)[uk] == '<')
                {
                    LexIm.append((*text)[uk++]);
                    pos++;
                    lex->append (*new Lexem  (Tlsd, LexIm));      //влево
                }
                else
                {
                    goto errors;
                }
            }

            else if ((*text)[uk] == '>')  //знак операции
            {
                LexIm.append((*text)[uk++]);
                pos++;
                if ((*text)[uk] == '>')
                {
                    LexIm.append((*text)[uk++]);
                    pos++;
                    lex->append (*new Lexem  (Trsd, LexIm));      //вправо
                }
                else
                {
                    goto errors;
                }
            }

            else if (Symbols.key((*text)[uk]) > 0)  //знак операции
            {

                LexIm = (*text)[uk];
                lex->append (*new Lexem  (Symbols.key((*text)[uk++]), LexIm));      //знак и его номер
                pos++;
            }

            else                    //ошибка
            {
                   goto errors;
            }



        } // конец Scaner
        if (!lex->isEmpty())
        {
            lex->back().pos = posb;          //записываем позицию и строку
            lex->back().str = strb;
        }

goto N1;
        errors:
        Errors.append(new int [2]{str, pos});  //очередная ошибка
            while ( !(IgnoreSymbols.key((*text)[uk]) > 0) && (*text)[uk] != '\0')         //пока не попался игнорируемый символ
            {
                LexIm.append((*text)[uk++]);
                pos++;
            }
            lex->append (*new Lexem  (Terr, LexIm));
N1:;
    }
    lex->append (*new Lexem  (Tend, ""));
    //дошли до конца текста
}
