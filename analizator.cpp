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
    scaner->toScan(lex);         //�������� ������ ������

    QString type;
    for (int i = 0; i < scaner->Errors.count(); i++)         //������� ����������� ������
    {
        std::cout<<'\n';
        std::cout<<"Lexical error in "<<scaner->Errors[i][0]<<":"<<scaner->Errors[i][1];
    }
    T = new Tree ();
    T->Cur = T;


    if(scaner->Errors.count() == 0)      //��� ����������� ������
        while (cur < lex->count() - 1)
        {
            if((*lex)[cur].type != Tvoid)   //�� void - ������ ������
            {
               c = cur;
               if(!Data())
               {
                    cur = c;
                    right = false;
                    //ErrorText = ""
                    break;
               }
               if ((*lex)[cur].type != Tdt)    //если не т.з.
               {
                   right = false;
                   ErrorText = "�������� ������ ;";
                   break;
               }
               cur++;
            }
            else        //void - ������ �������� �������
            {
                cur++;
                if ((*lex)[cur].type == Tmain)      //main
                {///
                    if (!T->semFToTable((*lex)[cur].image))
                    {   ///������������ main
                        T->semError("������������ main", &(*lex)[cur]);
                    }
                 ///
                    cur++;
                    if ((*lex)[cur].type != Tls)
                    {
                        right = false;
                        ErrorText = "�������� ������ (";
                        break;
                    }
                    cur++;
                    if ((*lex)[cur].type != Trs)
                    {
                        right = false;
                        ErrorText = "�������� ������ )";
                        break;
                    }
                    cur++;
                }
                else    //�������
                {
                    if ((*lex)[cur].type != Tid)          //идентификатор
                    {
                        right = false;
                        ErrorText = "�������� �������������";
                        break;
                    }
                    else
            ///
                        if (!T->semFToTable((*lex)[cur].image))
                        {   ///������������ �������
                            T->semError("������������ ��������������", &(*lex)[cur]);
                        }
            ///
                    cur++;
                    if ((*lex)[cur].type != Tls)
                    {
                        right = false;
                        ErrorText = "�������� ������ )";
                        break;
                    }
                    cur++;

                    if ((*lex)[cur].type != Trs)    //�� ������ ������
                        do
                        {
                        ///
                            int t1;
                            int curPtr = cur;
                            t1 = T->semType(&(*lex)[cur]);     //��������� ��� ���������
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
                                ErrorText = "�������� �������������";
                                break;
                            }
                            else ///������� � ������ + �������� ����� ����������
                            {
                                Node *n = new Node ((*lex)[cur].image, t1);
                                if (!T->Cur->FindOneLevel(n))    //�� ���� ������ ���
                                {
                                    T->Cur->semToTable(n);   //�������� � ������� (������)
                                    T->semInc();        //�������� ����� ����������
                                }
                                else
                                {
                                    T->semError("������������ ����� ���������", &(*lex)[cur]);
                                }

                            }
                            ///
                            cur++;
                        } while ((*lex)[cur++].type == Tzap);
                    cur--;
                    if ((*lex)[cur].type != Trs)
                    {
                        right = false;
                        ErrorText = "�������� ������ )";
                        break;
                    }
                    cur++;
                }
//����� ������ ���� ����. ��������
                if (!SOper ())    //��������� �� ����. ��������
                {
                    right = false;
                    break;
                }
                else    //��� ��������� ��������. ����������� ��������
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
            std::cout<<"\n �������������� ������ �� ����������\n";
        else;
    else
        std::cout<<"\n ���������� ������ � "<<(*lex)[cur].str<<":"<<(*lex)[cur].pos<<": "<<ErrorText<<"\n";

    std::cout.flush();




    return;
}

bool Analizator::Data ()
{
    int t1;
    int curPtr = cur;
    t1 = T->semType(&(*lex)[cur]);              //��������� ��� ������

    //Tree *ptr = T->Find((*lex)[cur].image);     //���� �������������
//    if (ptr == nullptr)     //�� �� �������
//        T->semError("������������� �������������", &(*lex)[cur]);
//    else
//        tv = ptr->N->TypeObj;       //��� �������

    if ((*lex)[cur].type != Tint && (*lex)[cur].type != Tchar)
    {
        if ((*lex)[cur].type != Tlong)
        {
            right = false;
            ErrorText = "�������� ���";
            return false;
        }
        cur++;
        if ((*lex)[cur].type != Tlong)
        {
            right = false;
            ErrorText = "�������� long";
            return false;
        }
        cur++;
        if ((*lex)[cur].type != Tint)
        {
            right = false;
            ErrorText = "�������� int";
            return false;
        }

    }
    cur++;

    do
    {
        if ((*lex)[cur].type != Tid)
        {
            right = false;
            ErrorText = "�������� �������������";
            return false;
        }
///
        else        //�������� ������������� � �������
        {
            if (t1 == TypeInt || t1 == TypeChar || t1 == TypeLong)
            {
                T->Cur->semToTable(new Node ((*lex)[cur].image, t1));   //�������� � ������� (������)
            }
            else
            {
                T->semError("������������ ���", &(*lex)[cur]);
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
            ///�������� ���� ��� �������������
            else
            {
                T->semTypeRes(t1, tv, &(*lex)[cur]);       //���� ������������
                   // T->semError("�������������� �����", &(*lex)[cur]);
            }
            ///

        }

    } while ((*lex)[cur++].type == Tzap);
    cur--;
    return true;
}

bool Analizator::SOper ()     //��������� ��������
{
    if ((*lex)[cur].type != Tlf)
    {
        ErrorText = "�������� ������ {";
        return false;
    }
    else
    {
        ///
        T->Cur->addLeft(new Node ("", TypeEmpty));//!!!!!!!!!!!!!!!
        T->Cur = T->Cur->Left;
        T->Cur = T->Cur->Right;    //������ ������ //T->Cur->semToRight();
        ///
    }
    cur++;
    while ((*lex)[cur].type != Trf)
    {
        //c = cur;
        if ((*lex)[cur].type == Tint || (*lex)[cur].type == Tchar || (*lex)[cur].type == Tlong) //���
        {
            if (!Data())         //������ ������
            {
                //cur = c;
                return false;
            }
       //������������� ������
            if ((*lex)[cur].type != Tdt)    //��������� �.�.
            {
                ErrorText = "�������� ������ ;";
                return false;
            }
            cur++;

        }
        else    //������ ��������
        {
            if (!Oper())
                return false;
        }
    }
    if ((*lex)[cur].type != Trf)
    {
        ErrorText = "�������� ������ }";
        return false;
    }
    cur++;
///
    T->Cur->semRep();
///
    return true;
}

bool Analizator::Oper ()     //��������
{
    if ((*lex)[cur].type != Tdt)    //�� ������ ��������
    {
        if ((*lex)[cur].type == Tfor)   //���� for
            if (!Cicle())         //�� ����
                return false;
            else;
        else
            if ((*lex)[cur].type == Tlf)   //���� {
                if (!SOper())       //�� ����. ��������
                    return false;
                else;
            else
                if ((*lex)[cur].type == Tid)   //�������������
                {
                    if ((*lex)[cur+1].type == Teq)    //����� ���� =
                        if (!Prisv()) //не присваивание
                            return false;
                        else;
                    else if ((*lex)[cur+1].type == Tls) //����� ���� (
                            if (!Function()) //не выражение
                                return false;
                            else;
                    else
                            if (!A1()) //���������?
                                return false;
                   if ((*lex)[cur].type != Tdt)
                            {
                                ErrorText = "�������� ������ ;";
                                return false;
                            }
                    else cur++;
                }
        else
                {
                    ErrorText = "������������ ��������";
                    return false;
                }

    }
    else cur++;     //������ ��������
    return true;
}

bool Analizator::Cicle ()     //цикл
{
    if ((*lex)[cur].type != Tfor)
    {
        ErrorText = "�������� for";
        return false;
    }
    cur++;
    if ((*lex)[cur].type != Tls)
    {
        ErrorText = "�������� ������ (";
        return false;
    }
    cur++;
    if (!InitOfCicle())         //не инициализация
    {
        return false;
    }
    if ((*lex)[cur].type != Tdt)
    {
        if (!A1())         //не A1
        {
            return false;
        }

    }
    if ((*lex)[cur].type != Tdt)
    {
        ErrorText = "�������� ������ ;";
        return false;
    }
    cur++;

    if ((*lex)[cur].type != Trs)            //�� ����. ������ - ������ ����� ��������
    {
        if ((*lex)[cur].type == Tid)
            if ((*lex)[cur+1].type == Teq)
                if (!Prisv())         //не выраж.
                {
                    //ErrorText = "��������� ������������";
                    return false;
                }
                else;
            else if (!A1())         //не присваивание
            {
                return false;
            }

    }
    if ((*lex)[cur].type != Trs)
    {
        ErrorText = "�������� ������ )";
        return false;
    }
    cur++;
    if (!Oper())         //не оператор
    {
        //cur = c;        //возвращаем указатель
        return false;
    }
    return true;
}

bool Analizator::InitOfCicle ()     //������������� �����
{
    if ((*lex)[cur].type != Tdt)    //�� �.� - �� �����
    {
        //c = cur;    //запоминаем



        if ((*lex)[cur].type != Tid)        //�������. - ������ ������
            if (!Data())         //не данные
                return false;
            else;
        else
            if (!Prisv())         //не данные
            {
                return false;
            }
        if ((*lex)[cur].type != Tdt)
        {
            ErrorText = "�������� ������ ;";
            return false;
        }
    }
    cur++;
    return true;
}

bool Analizator::Prisv ()     //������������
{
    if ((*lex)[cur].type != Tid)
    {
        ErrorText = "�������� �������������";
        return false;
    }


/////
    Tree *ptr = T->Cur->Find((*lex)[cur].image);     //���� �������������
    int t1;
    if (ptr == nullptr)     //�� �� �������
        T->semError("������������� �������������", &(*lex)[cur]);
    else
        t1 = ptr->N->TypeObj;       //��� �������
////



    cur++;
    if ((*lex)[cur].type != Teq)
    {
        ErrorText = "�������� ������ =";
        return false;
    }
    int curPtr = cur;
    cur++;

    if (!A1())         //не выражение
    {
        return false;
    }
 ////
    if (ptr != nullptr)
        T->semTypeRes(t1, tv, &(*lex)[curPtr]);       //���� ������������
//            T->semError("�������������� �����", &(*lex)[curPtr]);
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
//                    T->semError("�������������� �����", &(*lex)[curPtr]);
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
//                    T->semError("�������������� �����", &(*lex)[curPtr]);
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
//                    T->semError("�������������� �����", &(*lex)[curPtr]);
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
//                    T->semError("�������������� �����", &(*lex)[curPtr]);
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
T->semTypeResOnlyNum(t1, tv, &(*lex)[curPtr]);       //�� �����
//                    T->semError("�������������� �����", &(*lex)[curPtr]);
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
    else    //������ �������� ���. �� ��� ���������� � A7
    {
////
        if (f)      //���� ���������
T->semTypeResUn(tv, &(*lex)[curPtr]);      //�� �����
//                T->semError("������������ ���", &(*lex)[curPtr]);

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
            ErrorText = "��������� ���������";
            return false;
        }
        cur++;
        if (!A1())
            return false;
        if ((*lex)[cur].type != Trs)
        {
            ErrorText = "�������� ������ )";
            return false;
        }
        cur++;
    }
    else
    {
        ////

        if ((*lex)[cur].type != Tid)    //�� id
            tv = T->semType(&(*lex)[cur]);   //��������� ���
        else        //id
        {
            tv = TypeUnKnown;
            Tree *ptr = T->Cur->Find((*lex)[cur].image);     //���� �������������
            //int t1;
            if (ptr == nullptr)     //�� �� �������
                T->semError("������������� �������������", &(*lex)[cur]);
            else
                tv = ptr->N->TypeObj;       //��� �������
        }
///
        cur++;
    }
    return true;
}

bool Analizator::Function ()     //вызов функции
{
    Tree *ptr;
    int t1;
    if ((*lex)[cur].type != Tid)
    {
        ErrorText = "�������� �������������";
        return false;
    }
    else
    {
    /////
        ptr = T->Cur->Find(new Node ((*lex)[cur].image, TypeFunc));     //���� �������

        if (ptr == nullptr)     //�� �� �������
            T->semError("������������� �������", &(*lex)[cur]);
//        else
//            t1 = ptr->N->TypeObj;       //��� �������
    ////
    }
    cur++;
    if ((*lex)[cur].type != Tls)
    {
        ErrorText = "�������� ������ (";
        return false;
    }
    cur++;

    if ((*lex)[cur].type != Trs)        //параметры будут
        if (!A1())         //не ветка с данными
        {
            ErrorText = "��������� ���������";
            return false;
        }

    while ((*lex)[cur].type != Trs)
    {
        if ((*lex)[cur].type == Tzap) //запятая
        {
            cur++;
        }
        else
        {
            ErrorText = "�������� ������ ,";
            return false;
        }

        if (!A1())         //не ветка с данными
        {
            ErrorText = "��������� ���������";
            return false;
        }

    }
    if ((*lex)[cur].type != Trs)
    {
        ErrorText = "�������� ������ )";
        return false;
    }
    cur++;
    return true;
}
