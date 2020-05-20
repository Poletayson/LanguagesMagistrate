#include "analizator.h"

Analizator::Analizator()
{
    scaner = new Scanner ("input.txt");
    lex = new QList <Lexem> ();
    cur = 0;
    right = true;
}

void Analizator::S ()
{
    int c;
    scaner->toScan(lex);         //получаем список лексем

    QString type;
    for (int i = 0; i < scaner->Errors.count(); i++)         //выводим лексические ошибки
    {
        std::cout<<'\n';
        std::cout<<"Lexical error in "<<scaner->Errors[i][0]<<":"<<scaner->Errors[i][1];
    }
    T = new Tree ();
    T->Cur = T;


    if(scaner->Errors.count() == 0)      //нет лексических ошибок
        while (cur < lex->count() - 1)
        {
            if((*lex)[cur].type != Tvoid)   //не void - значит данные
            {
               c = cur;
               if(!Data())
               {
                    cur = c;
                    right = false;
                    //ErrorText = ""
                    break;
               }
               if ((*lex)[cur].type != Tdt)    //РµСЃР»Рё РЅРµ С‚.Р·.
               {
                   right = false;
                   ErrorText = "Ожидался символ ;";
                   break;
               }
               cur++;
            }
            else        //void - значит описание функции
            {
                cur++;
                if ((*lex)[cur].type == Tmain)      //main
                {///
                    if (!T->semFToTable((*lex)[cur].image))
                    {   ///дублирование main
                        T->semError("Дублирование main", &(*lex)[cur]);
                    }
                 ///
                    cur++;
                    if ((*lex)[cur].type != Tls)
                    {
                        right = false;
                        ErrorText = "Ожидался символ (";
                        break;
                    }
                    cur++;
                    if ((*lex)[cur].type != Trs)
                    {
                        right = false;
                        ErrorText = "Ожидался символ )";
                        break;
                    }
                    cur++;
                }
                else    //Функция
                {
                    if ((*lex)[cur].type != Tid)          //РёРґРµРЅС‚РёС„РёРєР°С‚РѕСЂ
                    {
                        right = false;
                        ErrorText = "Ожидался идентификатор";
                        break;
                    }
                    else
            ///
                        if (!T->semFToTable((*lex)[cur].image))
                        {   ///дублирование функции
                            T->semError("Дублирование идентификатора", &(*lex)[cur]);
                        }
            ///
                    cur++;
                    if ((*lex)[cur].type != Tls)
                    {
                        right = false;
                        ErrorText = "Ожидался символ (";
                        break;
                    }
                    cur++;

                    if ((*lex)[cur].type != Trs)    //Не правая скобка
                        do
                        {
                        ///
                            int t1;
                            int curPtr = cur;
                            t1 = T->semType(&(*lex)[cur]);     //определим тип параметра
                        ///
                            if ((*lex)[cur].type != Tint && (*lex)[cur].type != Tchar)
                            {
                                if ((*lex)[cur].type != Tlong)
                                {
                                    right = false;
                                }
                                cur++;
                                if ((*lex)[cur].type != Tlong)
                                {
                                    right = false;
                                }
                                cur++;
                                if ((*lex)[cur].type != Tint)
                                {
                                    right = false;
                                }
                            }
                            cur++;
                            if ((*lex)[cur].type != Tid)
                            {
                                right = false;
                                ErrorText = "Ожидался идентификатор";
                                break;
                            }
                            else ///заносим в дерево + увеличим число параметров
                            {
                                Node *n = new Node ((*lex)[cur].image, t1);
                                if (!T->Cur->FindOneLevel(n))    //на этом уровне нет
                                {
                                    T->Cur->semToTable(n);   //помещаем в таблицу (дерево)
                                    T->semInc();        //увеличим число параметров
                                }
                                else
                                {
                                    T->semError("Дублирование имени параметра", &(*lex)[cur]);
                                }

                            }
                            ///
                            cur++;
                        } while ((*lex)[cur++].type == Tzap);
                    cur--;
                    if ((*lex)[cur].type != Trs)
                    {
                        right = false;
                        ErrorText = "Ожидался символ )";
                        break;
                    }
                    cur++;
                }
//далее должен идти сост. оператор
                if (!SOper ())    //проверяем на сост. оператор
                {
                    right = false;
                    break;
                }
                else    //был составной оператор. Восстановим уазатель
                {
///
                    T->semRep();
///
                }
            }
        }

    std::cout << "\n";
    std::cout.flush();


    if (right == true)
        if ((*lex)[cur].type == Tend)
            std::cout<<"\n Синтаксических ошибок не обнаружено\n";
        else;
    else
        std::cout<<"\n Обнаружена ошибка в "<<(*lex)[cur].str<<":"<<(*lex)[cur].pos<<": "<<ErrorText<<"\n";

    std::cout.flush();




    return;
}

bool Analizator::Data ()
{
    int t1;
    int curPtr = cur;
    t1 = T->semType(&(*lex)[cur]);              //определим тип данных

    //Tree *ptr = T->Find((*lex)[cur].image);     //ищем идентификатор
//    if (ptr == nullptr)     //ид не нашелся
//        T->semError("Необъявленный идентификатор", &(*lex)[cur]);
//    else
//        tv = ptr->N->TypeObj;       //тип объекта

    if ((*lex)[cur].type != Tint && (*lex)[cur].type != Tchar)
    {
        if ((*lex)[cur].type != Tlong)
        {
            right = false;
            ErrorText = "Ожидался тип";
            return false;
        }
        cur++;
        if ((*lex)[cur].type != Tlong)
        {
            right = false;
            ErrorText = "Ожидался long";
            return false;
        }
        cur++;
        if ((*lex)[cur].type != Tint)
        {
            right = false;
            ErrorText = "Ожидался int";
            return false;
        }

    }
    cur++;

    do
    {
        if ((*lex)[cur].type != Tid)
        {
            right = false;
            ErrorText = "Ожидался идентификатор";
            return false;
        }
///
        else        //помещаем идентификатор в таблицу
        {
            if (t1 == Node::semTypes::TypeInt || t1 == Node::semTypes::TypeChar || t1 == Node::semTypes::TypeLong)
            {
                T->Cur->semToTable(new Node ((*lex)[cur].image, t1));   //помещаем в таблицу (дерево)
            }
            else
            {
                T->semError("Недопустимый тип", &(*lex)[cur]);
            }
        }
///
        cur++;
        if ((*lex)[cur].type == Teq)
        {
            cur++;
            if (!A1())
            {
                right = false;
                return false;
            }
            ///проверим типы при инициализации
            else
            {
                T->semTypeRes(t1, tv, &(*lex)[cur]);       //типы несовместимы
                   // T->semError("Несоответствие типов", &(*lex)[cur]);
            }
            ///

        }

    } while ((*lex)[cur++].type == Tzap);
    cur--;
    return true;
}

bool Analizator::SOper ()     //составной оператор
{
    if ((*lex)[cur].type != Tlf)
    {
        ErrorText = "Ожидался символ {";
        return false;
    }
    else
    {
        ///
        T->Cur->addLeft(new Node ("", Node::semTypes::TypeEmpty));//!!!!!!!!!!!!!!!
        T->Cur = T->Cur->Left;
        T->Cur = T->Cur->Right;    //уходим вправо //T->Cur->semToRight();
        ///
    }
    cur++;
    while ((*lex)[cur].type != Trf)
    {
        //c = cur;
        if ((*lex)[cur].type == Tint || (*lex)[cur].type == Tchar || (*lex)[cur].type == Tlong) //тип
        {
            if (!Data())         //значит данные
            {
                //cur = c;
                return false;
            }
       //действительно данные
            if ((*lex)[cur].type != Tdt)    //требуется т.з.
            {
                ErrorText = "Ожидался символ ;";
                return false;
            }
            cur++;

        }
        else    //значит оператор
        {
            if (!Oper())
                return false;
        }
    }
    if ((*lex)[cur].type != Trf)
    {
        ErrorText = "Ожидался символ }";
        return false;
    }
    cur++;
///
    T->Cur->semRep();
///
    return true;
}

bool Analizator::Oper ()     //оператор
{
    if ((*lex)[cur].type != Tdt)    //не пустой оператор
    {
        if ((*lex)[cur].type == Tfor)   //есть for
            if (!Cicle())         //не цикл
                return false;
            else;
        else
            if ((*lex)[cur].type == Tlf)   //есть {
                if (!SOper())       //Не сост. оператор
                    return false;
                else;
            else
                if ((*lex)[cur].type == Tid)   //идентификатор
                {
                    if ((*lex)[cur+1].type == Teq)    //после идет =
                        if (!Prisv()) //РЅРµ РїСЂРёСЃРІР°РёРІР°РЅРёРµ
                            return false;
                        else;
                    else if ((*lex)[cur+1].type == Tls) //после идет (
                            if (!Function()) //РЅРµ РІС‹СЂР°Р¶РµРЅРёРµ
                                return false;
                            else;
                    else
                            if (!A1()) //выражение?
                                return false;
                   if ((*lex)[cur].type != Tdt)
                            {
                                ErrorText = "Ожидался символ ;";
                                return false;
                            }
                    else cur++;
                }
        else
                {
                    ErrorText = "Недопустимый оператор";
                    return false;
                }

    }
    else cur++;     //пустой оператор
    return true;
}

bool Analizator::Cicle ()     //С†РёРєР»
{
    if ((*lex)[cur].type != Tfor)
    {
        ErrorText = "Ожидался for";
        return false;
    }
    cur++;
    if ((*lex)[cur].type != Tls)
    {
        ErrorText = "Ожидался символ (";
        return false;
    }
    cur++;
    if (!InitOfCicle())         //РЅРµ РёРЅРёС†РёР°Р»РёР·Р°С†РёСЏ
    {
        return false;
    }
    if ((*lex)[cur].type != Tdt)
    {
        if (!A1())         //РЅРµ A1
        {
            return false;
        }

    }
    if ((*lex)[cur].type != Tdt)
    {
        ErrorText = "Ожидался символ ;";
        return false;
    }
    cur++;

    if ((*lex)[cur].type != Trs)            //не закр. скобка - значит конец итерации
    {
        if ((*lex)[cur].type == Tid)
            if ((*lex)[cur+1].type == Teq)
                if (!Prisv())         //РЅРµ РІС‹СЂР°Р¶.
                {
                    //ErrorText = "Ожидалось присваивание";
                    return false;
                }
                else;
            else if (!A1())         //РЅРµ РїСЂРёСЃРІР°РёРІР°РЅРёРµ
            {
                return false;
            }

    }
    if ((*lex)[cur].type != Trs)
    {
        ErrorText = "Ожидался символ )";
        return false;
    }
    cur++;
    if (!Oper())         //РЅРµ РѕРїРµСЂР°С‚РѕСЂ
    {
        //cur = c;        //РІРѕР·РІСЂР°С‰Р°РµРј СѓРєР°Р·Р°С‚РµР»СЊ
        return false;
    }
    return true;
}

bool Analizator::InitOfCicle ()     //инициализация цикла
{
    if ((*lex)[cur].type != Tdt)    //не т.з - не пусто
    {
        //c = cur;    //Р·Р°РїРѕРјРёРЅР°РµРј



        if ((*lex)[cur].type != Tid)        //идентиф. - значит данные
            if (!Data())         //РЅРµ РґР°РЅРЅС‹Рµ
                return false;
            else;
        else
            if (!Prisv())         //РЅРµ РґР°РЅРЅС‹Рµ
            {
                return false;
            }
        if ((*lex)[cur].type != Tdt)
        {
            ErrorText = "Ожидался символ ;";
            return false;
        }
    }
    cur++;
    return true;
}

bool Analizator::Prisv ()     //присваивание
{
    if ((*lex)[cur].type != Tid)
    {
        ErrorText = "Ожидался идентификатор";
        return false;
    }


/////
    Tree *ptr = T->Cur->Find((*lex)[cur].image);     //ищем идентификатор
    int t1;
    if (ptr == nullptr)     //ид не нашелся
        T->semError("Необъявленный идентификатор", &(*lex)[cur]);
    else
        t1 = ptr->N->TypeObj;       //тип объекта
////



    cur++;
    if ((*lex)[cur].type != Teq)
    {
        ErrorText = "Ожидался символ =";
        return false;
    }
    int curPtr = cur;
    cur++;

    if (!A1())         //РЅРµ РІС‹СЂР°Р¶РµРЅРёРµ
    {
        return false;
    }
 ////
    if (ptr != nullptr)
        T->semTypeRes(t1, tv, &(*lex)[curPtr]);       //типы несовместимы
//            T->semError("Несоответствие типов", &(*lex)[curPtr]);
////
    return true;
}


bool Analizator::A1 ()     //A1
{
    if (!A2())
    {
        return false;
    }
    int t1 = tv;
    int curPtr;
    while ((*lex)[cur].type == Tvch)
    {
        curPtr = cur;
        cur++;

        if (!A2())
            return false;
        else
        {
            ////
T->semTypeResOnlyNum(t1, tv, &(*lex)[curPtr]);
//                    T->semError("Несоответствие типов", &(*lex)[curPtr]);
            ////
        }
    }
    return true;
}

bool Analizator::A2 ()     //A1
{
    if (!A3())
        return false;
    int t1 = tv;
    int curPtr;
    while ((*lex)[cur].type == Tamp)
    {
        curPtr = cur;
        cur++;

        if (!A3())
            return false;
        else
        {
//            ////
T->semTypeResOnlyNum(t1, tv, &(*lex)[curPtr]);
//                    T->semError("Несоответствие типов", &(*lex)[curPtr]);
//            ////
        }
    }
    return true;
}

bool Analizator::A3 ()     //A3
{
    if (!A4())
        return false;
    int t1 = tv;
    int curPtr;
    while ((*lex)[cur].type == Tlsd || (*lex)[cur].type == Trsd)
    {
        curPtr = cur;
        cur++;

        if (!A4())
            return false;
        else
        {
            ////
T->semTypeResOnlyNum(t1, tv, &(*lex)[curPtr]);
//                    T->semError("Несоответствие типов", &(*lex)[curPtr]);
            ////
        }
    }
    return true;
}
bool Analizator::A4 ()     //A1
{
    if (!A5())
    {
        return false;
    }
    int t1 = tv;
    int curPtr;
    while ((*lex)[cur].type == Tplus || (*lex)[cur].type == Tminus)
    {
        curPtr = cur;
        cur++;

        if (!A5())
        {
            return false;
        }

        else
        {
            ////
T->semTypeRes(t1, tv, &(*lex)[curPtr]);
//                    T->semError("Несоответствие типов", &(*lex)[curPtr]);
            ////
        }
    }
    return true;
}
bool Analizator::A5 ()     //A5
{
    if (!A6())
    {
        return false;
    }
    int t1 = tv;
    int curPtr;
    while ((*lex)[cur].type == Tpers || (*lex)[cur].type == Tmul || (*lex)[cur].type == Tdel)
    {
        curPtr = cur;
        cur++;

        if (!A6())
        {
            return false;
        }
        else
        {
            ////
T->semTypeResOnlyNum(t1, tv, &(*lex)[curPtr]);       //не число
//                    T->semError("Несоответствие типов", &(*lex)[curPtr]);
            ////
        }
    }
    return true;
}

bool Analizator::A6 ()     //A1
{
    bool f = false;
    while ((*lex)[cur].type == Ttil)
    {
        f = true;
        cur++;
    }
    int curPtr = cur;
    if (!A7())
        return false;
    else    //сейчас проверим тип. Он уже установлен в A7
    {
////
        if (f)      //есть отрицание
T->semTypeResUn(tv, &(*lex)[curPtr]);      //не число
//                T->semError("Неподходящий тип", &(*lex)[curPtr]);

////
    }

    return true;
}

bool Analizator::A7 ()     //A7
{
    if ((*lex)[cur].type != Tint8 && (*lex)[cur].type != Tint10 && (*lex)[cur].type != Tint16
            && (*lex)[cur].type != Tcchar && (*lex)[cur].type != Tid)   //
    {
        if ((*lex)[cur].type != Tls)
        {
            ErrorText = "Ожидалось выражение";
            return false;
        }
        cur++;
        if (!A1())
            return false;
        if ((*lex)[cur].type != Trs)
        {
            ErrorText = "Ожидался символ )";
            return false;
        }
        cur++;
    }
    else
    {
        ////

        if ((*lex)[cur].type != Tid)    //не id
            tv = T->semType(&(*lex)[cur]);   //определим тип
        else        //id
        {
            tv = Node::semTypes::TypeUnKnown;
            Tree *ptr = T->Cur->Find((*lex)[cur].image);     //ищем идентификатор
            //int t1;
            if (ptr == nullptr)     //ид не нашелся
                T->semError("Необъявленный идентификатор", &(*lex)[cur]);
            else
                tv = ptr->N->TypeObj;       //тип объекта
        }
///
        cur++;
    }
    return true;
}

bool Analizator::Function ()     //РІС‹Р·РѕРІ С„СѓРЅРєС†РёРё
{
    Tree *ptr;
    int t1;
    if ((*lex)[cur].type != Tid)
    {
        ErrorText = "Ожидался идентификатор";
        return false;
    }
    else
    {
    /////
        ptr = T->Cur->Find(new Node ((*lex)[cur].image, Node::semTypes::TypeFunc));     //ищем функцию

        if (ptr == nullptr)     //ид не нашелся
            T->semError("Необъявленная функция", &(*lex)[cur]);
//        else
//            t1 = ptr->N->TypeObj;       //тип объекта
    ////
    }
    cur++;
    if ((*lex)[cur].type != Tls)
    {
        ErrorText = "Ожидался символ (";
        return false;
    }
    cur++;

    if ((*lex)[cur].type != Trs)        //РїР°СЂР°РјРµС‚СЂС‹ Р±СѓРґСѓС‚
        if (!A1())         //РЅРµ РІРµС‚РєР° СЃ РґР°РЅРЅС‹РјРё
        {
            ErrorText = "Ожидалось выражение";
            return false;
        }

    while ((*lex)[cur].type != Trs)
    {
        if ((*lex)[cur].type == Tzap) //Р·Р°РїСЏС‚Р°СЏ
        {
            cur++;
        }
        else
        {
            ErrorText = "Ожидался символ ,";
            return false;
        }

        if (!A1())         //РЅРµ РІРµС‚РєР° СЃ РґР°РЅРЅС‹РјРё
        {
            ErrorText = "Ожидалось выражение";
            return false;
        }

    }
    if ((*lex)[cur].type != Trs)
    {
        ErrorText = "Ожидался символ )";
        return false;
    }
    cur++;
    return true;
}
