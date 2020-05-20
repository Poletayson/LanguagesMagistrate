#include "llanalizator.h"


LLAnalizator::LLAnalizator()
{
    scaner = new Scanner ("input.txt");
    lex = new QList <Lexem> ();
    cur = 0;
    right = true;

#define Tplus 44
#define Tminus 45
#define Tdel 46
#define Tmul 47
#define Tpers 48
#define Ttil 49
#define Teq 50

    NTerminalsNames.insert(Tvoid, "void");
    NTerminalsNames.insert(Tmain, "main");
    NTerminalsNames.insert(Tfor, "for");
    NTerminalsNames.insert(Tint, "int");
    NTerminalsNames.insert(Tlong, "long");
    NTerminalsNames.insert(Tchar, "char");
    NTerminalsNames.insert(Tid, "идентификатор");
    NTerminalsNames.insert(Tcchar, "символ");
    NTerminalsNames.insert(Tint10, "int10");
    NTerminalsNames.insert(Tint8, "int8");
    NTerminalsNames.insert(Tint16, "int16");
    NTerminalsNames.insert(Tzap, ",");
    NTerminalsNames.insert(Tdt, ";");
    NTerminalsNames.insert(Tls, "(");
    NTerminalsNames.insert(Trs, ")");
    NTerminalsNames.insert(Tlf, "{");
    NTerminalsNames.insert(Trf, "}");
    NTerminalsNames.insert(Tvch, "|");
    NTerminalsNames.insert(Tamp, "&");
    NTerminalsNames.insert(Tlsd, "<");
    NTerminalsNames.insert(Trsd, ">");
    NTerminalsNames.insert(Tplus, "+");
    NTerminalsNames.insert(Tminus, "-");
    NTerminalsNames.insert(Tdel, "/");
    NTerminalsNames.insert(Tmul, "*");
    NTerminalsNames.insert(Tpers, "%");
    NTerminalsNames.insert(Ttil, "~");
    NTerminalsNames.insert(Teq, "=");



    NTerminalsNames.insert(NS, "S");
    NTerminalsNames.insert(NData, "Данные");
    NTerminalsNames.insert(NSpPar, "Список параметров");
    NTerminalsNames.insert(NB, "B");
    NTerminalsNames.insert(NB1, "B1");
    NTerminalsNames.insert(NSpIdent, "Список идентификаторов");
    NTerminalsNames.insert(NC, "C");
    NTerminalsNames.insert(NInit, "Инициализация");
    NTerminalsNames.insert(NBlock, "Блок");
    NTerminalsNames.insert(NOperator, "Оператор");
    NTerminalsNames.insert(NCicle, "Цикл");
    NTerminalsNames.insert(NInitCycle, "Иниц. цикла");
    NTerminalsNames.insert(NEndIter, "Конец итерации");
    NTerminalsNames.insert(NPrisv, "Присваивание");
    NTerminalsNames.insert(NOperand, "Операнд");
    NTerminalsNames.insert(NA1, "A1");
    NTerminalsNames.insert(NA11, "A11");
    NTerminalsNames.insert(NA2, "A2");
    NTerminalsNames.insert(NA21, "A21");
    NTerminalsNames.insert(NA3, "A3");
    NTerminalsNames.insert(NA31, "A31");
    NTerminalsNames.insert(NA4, "A4");
    NTerminalsNames.insert(NA41, "A41");
    NTerminalsNames.insert(NA5, "A5");
    NTerminalsNames.insert(NA51, "A51");
    NTerminalsNames.insert(NA6, "A6");
    NTerminalsNames.insert(NA7, "A7");
    NTerminalsNames.insert(NVizFunc, "Вызов функции");
    NTerminalsNames.insert(NSpID2, "Список выражений");
    NTerminalsNames.insert(ND, "D");




 //заполняем управляющую таблицу
    QList<Lexem*> Cell;  //одно правило таблицы
    QList<Rule> Rules;  //список правил для одной ячейки
    QMultiMap <int, QList<Rule>> Sting;    //строка таблицы, соответствующая нетерминалу
//нетерминал S
    Cell.append(new Lexem (NS, true));
    Cell.append(new Lexem (TreeLL::functions::endFunct, true));
    Cell.append(new Lexem (TreeLL::functions::returnLevel, true));
//    Cell.append(new Lexem (TreeLL::functions::returnLevel, true));
    Cell.append(new Lexem (Trf, false));
    Cell.append(new Lexem (NBlock, true));
    Cell.append(new Lexem (TreeLL::functions::setNewLevel, true));
    Cell.append(new Lexem (Tlf, false));
    Cell.append(new Lexem (Trs, false));
    Cell.append(new Lexem (TreeLL::functions::stopParam, true));
    Cell.append(new Lexem (NSpPar, true));
    Cell.append(new Lexem (TreeLL::functions::startParam, true));
//    Cell.append(new Lexem (TreeLL::functions::setNewLevel, true));
    Cell.append(new Lexem (Tls, false));
    Cell.append(new Lexem (TreeLL::functions::setFunct, true));
    Cell.append(new Lexem (Tid, false));
    Cell.append(new Lexem (Tvoid, false));
    Rules.append(*new Rule (&Cell));    //добавляем правило
    Sting.insert(Tvoid, Rules);      //добавляем список правил в ячейку строки

    Cell.append(new Lexem (NS, true));
    Cell.append(new Lexem (TreeLL::functions::endFunct, true));
    Cell.append(new Lexem (TreeLL::functions::returnLevel, true));
//    Cell.append(new Lexem (TreeLL::functions::returnLevel, true));
    Cell.append(new Lexem (Trf, false));
    Cell.append(new Lexem (NBlock, true));
    Cell.append(new Lexem (TreeLL::functions::setNewLevel, true));
    Cell.append(new Lexem (Tlf, false));
    Cell.append(new Lexem (Trs, false));
    Cell.append(new Lexem (NSpPar, true));
//    Cell.append(new Lexem (TreeLL::functions::setNewLevel, true));
    Cell.append(new Lexem (Tls, false));
    Cell.append(new Lexem (Tmain, false));
    Cell.append(new Lexem (Tvoid, false));
    Rules.append(*new Rule (&Cell));    //добавляем правило
    Sting.insert(Tvoid, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //int
    Cell.append(new Lexem (NS, true));
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tint, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //char
    Cell.append(new Lexem (NS, true));
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));  
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tchar, false));

    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tchar, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //long
    Cell.append(new Lexem (NS, true));
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tint, false));
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tlong, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tlong, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //конец
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tend, Rules);      //добавляем список правил в ячейку строки

    Table.insert(NS, Sting);

//Данные
    Sting.clear();    //строка таблицы, соответствующая нетерминалу

    Cell.clear();   //int
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tint, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //char
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tchar, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tchar, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //long
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tint, false));
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tlong, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tlong, Rules);      //добавляем список правил в ячейку строки

    Table.insert(NData, Sting);

//Список параметров
    Sting.clear();    //строка таблицы, соответствующая нетерминалу

    Cell.clear();   //int
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (TreeLL::functions::setParam, true));
    Cell.append(new Lexem (Tid, false)); 
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tint, false));

    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tint, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //char
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (TreeLL::functions::setParam, true));
    Cell.append(new Lexem (Tid, false)); 
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tchar, false));

    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tchar, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //long
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (TreeLL::functions::setParam, true));
    Cell.append(new Lexem (Tid, false));    
    Cell.append(new Lexem (Tint, false));
    Cell.append(new Lexem (TreeLL::functions::startDecl, true));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tlong, false));

    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tlong, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //)
    Cell.append(new Lexem (NB, true));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки

    Table.insert(NSpPar, Sting);

//B
    Sting.clear();    //строка таблицы, соответствующая нетерминалу

    Cell.clear();   //)
    Cell.append(new Lexem (TreeLL::functions::endDecl, true));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки

    Cell.clear();   //,
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (NB1, true));
    Cell.append(new Lexem (Tzap, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки

    Table.insert(NB, Sting);

    //B1
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //int
        Cell.append(new Lexem (TreeLL::functions::setParam, true));
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (TreeLL::functions::startDecl, true));
        Cell.append(new Lexem (Tint, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //char
        Cell.append(new Lexem (TreeLL::functions::setParam, true));
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (TreeLL::functions::startDecl, true));
        Cell.append(new Lexem (Tchar, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tchar, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //long
        Cell.append(new Lexem (TreeLL::functions::setParam, true));
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (Tint, false));
        Cell.append(new Lexem (TreeLL::functions::startDecl, true));
        Cell.append(new Lexem (Tlong, false));
        Cell.append(new Lexem (Tlong, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tlong, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NB1, Sting);

//Список идент.
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //id
        Cell.append(new Lexem (NC, true));
        Cell.append(new Lexem (NInit, true));
        Cell.append(new Lexem (TreeLL::functions::setIdent, true));
        Cell.append(new Lexem (Tid, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NSpIdent, Sting);

//C
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //id
        Cell.append(new Lexem (NC, true));
        Cell.append(new Lexem (NInit, true));
        Cell.append(new Lexem (TreeLL::functions::setIdent, true));
        Cell.append(new Lexem (Tid, false));       
        Cell.append(new Lexem (Tzap, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NC, Sting);

//Инициализация
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //id
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Teq, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Teq, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NInit, Sting);

//Блок
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //int
        Cell.append(new Lexem (NBlock, true));
        Cell.append(new Lexem (NData, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tlong, Rules);      //добавляем список правил в ячейку строки
        Cell.clear();   //int
        Cell.append(new Lexem (NBlock, true));
        Cell.append(new Lexem (NOperator, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tfor, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Ttil, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tlf, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //int
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trf, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NBlock, Sting);

//Оператор
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //int
        Cell.append(new Lexem (NCicle, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tfor, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //rf
        Cell.append(new Lexem (Trf, false));
        Cell.append(new Lexem (NBlock, true));
        Cell.append(new Lexem (Tlf, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tlf, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //dt
        Cell.append(new Lexem (Tdt, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки

           //id
        Cell.append(new Lexem (NPrisv, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Cell.clear();   //int
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NVizFunc, true));
        Rules.append(*new Rule (&Cell));
        Cell.clear();   //int
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        Rules.append(*new Rule (&Cell));

        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //int
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Ttil, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NOperator, Sting);

//Цикл
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //int
        Cell.append(new Lexem (TreeLL::functions::returnLevel, true));
        Cell.append(new Lexem (NOperator, true));
        Cell.append(new Lexem (Trs, false));
        Cell.append(new Lexem (NEndIter, true));
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        //Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NInitCycle, true));
        Cell.append(new Lexem (TreeLL::functions::setNewLevel, true));
        Cell.append(new Lexem (Tls, false));
        Cell.append(new Lexem (Tfor, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tfor, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NCicle, Sting);

//Иниц. цикла
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();
        Cell.append(new Lexem (NData, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tlong, Rules);      //добавляем список правил в ячейку строки


        Cell.clear();
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NPrisv, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (Tdt, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NInitCycle, Sting);

//Конец итерации
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (NPrisv, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Cell.clear();   //;
        Cell.append(new Lexem (NA1, true));
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NEndIter, Sting);

//Присваивание
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //id
        //Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (TreeLL::functions::matchLeft, true));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Teq, false));
        Cell.append(new Lexem (TreeLL::functions::find, true));
        Cell.append(new Lexem (Tid, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NPrisv, Sting);

//Операнд
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //id
        Cell.append(new Lexem (TreeLL::functions::push_t, true));
        Cell.append(new Lexem (TreeLL::functions::find, true));
        Cell.append(new Lexem (Tid, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (TreeLL::functions::push_t, true));
        Cell.append(new Lexem (TreeLL::functions::constType, true));
        Cell.append(new Lexem (Tint8, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (TreeLL::functions::push_t, true));
        Cell.append(new Lexem (TreeLL::functions::constType, true));
        Cell.append(new Lexem (Tint10, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (TreeLL::functions::push_t, true));
        Cell.append(new Lexem (TreeLL::functions::constType, true));
        Cell.append(new Lexem (Tint16, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (TreeLL::functions::push_t, true));
        Cell.append(new Lexem (TreeLL::functions::constType, true));
        Cell.append(new Lexem (Tcchar, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NOperand, Sting);

//A1
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA11, true));
        Cell.append(new Lexem (NA2, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA1, Sting);

//A11
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA11, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA2, true));
        Cell.append(new Lexem (Tvch, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tvch, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA11, Sting);

//A2
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA21, true));
        Cell.append(new Lexem (NA3, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA2, Sting);

//A21
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA21, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA3, true));
        Cell.append(new Lexem (Tamp, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tamp, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tvch, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA21, Sting);

//A3
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA31, true));
        Cell.append(new Lexem (NA4, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA3, Sting);

//A31
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA31, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA4, true));
        Cell.append(new Lexem (Tlsd, false));
        Cell.append(new Lexem (Tlsd, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tlsd, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (NA31, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA4, true));
        Cell.append(new Lexem (Trsd, false));
        Cell.append(new Lexem (Trsd, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trsd, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tvch, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tamp, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA31, Sting);

//A4
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA41, true));
        Cell.append(new Lexem (NA5, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA4, Sting);

//A41
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA41, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA5, true));
        Cell.append(new Lexem (Tplus, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tplus, Rules);      //добавляем список правил в ячейку строки
        Cell.clear();   //;
        Cell.append(new Lexem (NA41, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA5, true));
        Cell.append(new Lexem (Tminus, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tminus, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tvch, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tamp, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tlsd, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trsd, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA41, Sting);

//A5
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (NA6, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA5, Sting);

//A51
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Tmul, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tmul, Rules);      //добавляем список правил в ячейку строки
        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Tdel, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdel, Rules);      //добавляем список правил в ячейку строки
        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (TreeLL::functions::match, true));
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Tpers, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tpers, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tdt, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tvch, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tamp, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tlsd, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Trsd, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tplus, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tminus, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NA51, Sting);

//A6
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Ttil, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Ttil, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (NA7, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки


        Table.insert(NA6, Sting);

//A7
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (NOperand, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (Trs, false));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Tls, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки


        Table.insert(NA7, Sting);

//Вызов функции
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;

        Cell.append(new Lexem (Trs, false));
        Cell.append(new Lexem (TreeLL::functions::matchParamCount, true));
        Cell.append(new Lexem (NSpID2, true));
        Cell.append(new Lexem (Tls, false));
        Cell.append(new Lexem (TreeLL::functions::findFunc, true));
        Cell.append(new Lexem (Tid, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NVizFunc, Sting);

//Список выражений
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Cell.append(new Lexem (ND, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки

        Cell.append(new Lexem (TreeLL::functions::matchParamType, true));
        Cell.append(new Lexem (NA1, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint8, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint10, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tint16, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tcchar, Rules);      //добавляем список правил в ячейку строки
        Sting.insert(Tls, Rules);      //добавляем список правил в ячейку строки

        Table.insert(NSpID2, Sting);

//D
        Sting.clear();    //строка таблицы, соответствующая нетерминалу

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trs, Rules);      //добавляем список правил в ячейку строки

        Cell.clear();   //;
        Cell.append(new Lexem (ND, true));
        Cell.append(new Lexem (TreeLL::functions::matchParamType, true));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Tzap, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //добавляем список правил в ячейку строки

        Table.insert(ND, Sting);
}

void LLAnalizator::toAnalize ()
{
    //int c;
    scaner->toScan(lex);         //получаем список лексем
    QString type;
    QTextStream outStream(stdout);

    //выставляем кодировку для потока IO
    #ifndef QT_NO_TEXTCODEC
        outStream.setCodec("csIBM866");
    #endif

    for (int i = 0; i < scaner->Errors.count(); i++)         //выводим лексические ошибки
    {

        outStream<<'\n';
        outStream<<"Lexical error in "<<scaner->Errors[i][0]<<":"<<scaner->Errors[i][1];
    }
    T = new TreeLL ();  //дерево
    T->Cur = T;
    Lexem *Lex;
    Lexem *NT;
    if(scaner->Errors.count() == 0)      //нет лексических ошибок
    {
        ErrorText = "\n Обнаружена ошибка в ";
        ErrorSem = "\n Семантическая ошибка в ";

        QList<Rule> Rules;
        QMultiMap <int, QList<Rule>> Sting;    //строка таблицы, соответствующая нетерминалу
        cur = 0;
        isError = false;
        isSemError = false;
        QList <Lexem*> rule;
        Lex = new Lexem (NS, true);
        Stack.append(*Lex);             //аксиому в стек
        while (cur < lex->count() - 1 && !isError && !isSemError)        //пока не прошли всю цепочку и нет ошибок
        {
            Lex = new Lexem (Stack.pop ());     //получаем лексему из стека
            if (Lex->isNT == true)              //в магазине - нетерминал
            {
                //сем. функция
                if (Lex->type >= TreeLL::functions::startDecl){
                    switch (Lex->type) {
                        case TreeLL::functions::startDecl:{
                            startDecl();
                            break;
                        }
                        case TreeLL::functions::endDecl:{
                            endDecl();
                            break;
                        }
                        case TreeLL::functions::setIdent:{
                            if(!setIdent()){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": повторное объявление переменной\n";
                            }
                            break;
                        }
                        case TreeLL::functions::setNewLevel:{
                            setNewLevel();
                            break;
                        }
                        case TreeLL::functions::returnLevel:{
                            returnLevel();
                            break;
                        }
                        case TreeLL::functions::setFunct:{
                            if (!setFunct())    //дублирование функции
                            {
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": повторное определение функции\n";
                            }
                            break;
                        }
                        case TreeLL::functions::find:{
                            TreeLL* id = findId();
                            if (id == nullptr)    //Необъявленная  переменная
                            {
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": необъявленная  переменная\n";
                            }
                            else {
                                type1 = id->N->TypeObj; //тип
                                types.push(id->N->TypeObj); //кладем тип в стек
                            }
                            break;
                        }

                        case TreeLL::functions::findFunc:{
                            if (findFunc() == nullptr)    //Неопределенная функция
                            {
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": вызов неописанной  функции\n";
                            }
                            break;
                        }
                        case TreeLL::functions::constType:{
                            int t = constType();
                            if (t != Node::semTypes::TypeInt && t != Node::semTypes::TypeChar && t != Node::semTypes::TypeLong){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": некорректный тип константы: " + t + "\n";
                            }
                            break;
                        }
                        case TreeLL::functions::push_t:{

                            break;
                        }
                        case TreeLL::functions::match:{
                            if (match() == Node::semTypes::TypeUnKnown){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие типов\n";
                            }
                            break;
                        }
                        case TreeLL::functions::matchNumOnly:{
                            if (matchNumOnly() == Node::semTypes::TypeUnKnown){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие типов\n";
                            }
                            break;
                        }
                        case TreeLL::functions::matchUn:{
                            if (matchUn() == Node::semTypes::TypeUnKnown){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие типов\n";
                            }
                            break;
                        }
                        case TreeLL::functions::matchLeft:{
                            if (match() == Node::semTypes::TypeUnKnown){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие типов\n";
                            }
                            break;
                        }
                        case TreeLL::functions::startParam:{
                            paramCount = 0; //обнуляем счетчик параметров
                            break;
                        }
                        case TreeLL::functions::setParam:{
                            if(!setParam()){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": повторное определение параметра\n";
                            }
                            break;
                        }
                        case TreeLL::functions::stopParam:{
                            T->funcSetParamCount(paramCount);
                            break;
                        }
                        case TreeLL::functions::matchParamCount:{
                            if(!matchParamCount()){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие числа параметров\n";
                            }
                            break;
                        }
                        case TreeLL::functions::matchParamType:{
                            paramCount++;
                            TreeLL *curPar = T->FindRightLeftNum(findedFunc, paramCount); //ищем очередной параметр этой функции
                            if (curPar == nullptr){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие числа параметров\n";
                                break;
                            }
                            types.push(curPar->N->TypeObj); //кладем типы формального и фактического параметров в стек
//                            types.push(T->semType(&(*lex)[cur - 1]));
                            //проверяем соответствие
                            if (match() == Node::semTypes::TypeUnKnown){
                                isSemError = true;
                                ErrorSem = ErrorSem + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + ": несоответствие типов формального и фактического параметров " + findedFunc->N->Id + " " + QString::number(findedFunc->N->ParamCount) + " " + QString::number(paramCount) + "\n";
                            }
                            break;
                        }
                    }
                }
                //просто НТ
                else {
                    NT = Lex;
                    Sting = Table.value(Lex->type);     //получаем строку правил для этого НТ
                    Rules = Sting.value((*lex)[cur].type);  //список правил в ячейке
                    if (Rules.count() > 0)
                    {
                        if (Rules.count() == 1) //ячейка без коллизий
                        {
                            rule = *Rules[0].rule;
                            for (int i = 0; i < rule.count(); i++) //проходим все правило
                            {
                                Stack.push(*rule[i]);            //добавляем в стек
                            }
                        }
                        else    //рассмотрим коллизию
                        {
                            switch (Lex->type) {
                                case NS:{
                                    if ((*lex)[cur+1].type == Tid)    //присваивание
                                    {
                                        rule = *Rules[0].rule;
                                    }
                                    else if ((*lex)[cur+1].type == Tmain)   //вызов функции в Операторе
                                    {
                                        rule = *Rules[1].rule;
                                    }
                                    break;
                                }
                                default:{
                                    if ((*lex)[cur+1].type == Teq)    //присваивание
                                    {
                                        rule = *Rules[0].rule;
                                    }
                                    else if ((*lex)[cur+1].type == Tls && Lex->type == NOperator)   //вызов функции в Операторе
                                        {
                                            rule = *Rules[1].rule;
                                        }
                                        else
                                        {
                                            rule = *Rules[2].rule;
                                        }
                                    break;
                                }
                            }


                            for (int i = 0; i < rule.count(); i++) //проходим все правило
                            {
                                Stack.push(*rule[i]);            //добавляем в стек
                            }
                        }
                    }
                    else
                    {
                        isError = true;
                        ErrorText = ErrorText + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) +":";  //<<" в конструкции "<<NTerminalsNames.value(NT->type)<<"\n";//". Ожидался "<<NTerminalsNames.value(Lex->type)<<"\n";
                        ErrorText = ErrorText + " в конструкции " + NTerminalsNames.value(NT->type) + ", неверно используется " + NTerminalsNames.value(Lex->type) + "\n";
                    }
                }


            }
            else    //из магазина взят терминал
            {
                if (Lex->type == (*lex)[cur].type)
                {
                    cur++;
                }
                else
                {
                    isError = true;
                    ErrorText = ErrorText + QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos);
                    ErrorText = ErrorText + " в конструкции " + NTerminalsNames.value(NT->type) + ": ожидался " + NTerminalsNames.value(Lex->type) + "\n";
                }
            }
            if (cur >= lex->count())
            {
                isError = true;
                ErrorText = ErrorText + (*lex)[cur].str +":" + (*lex)[cur].pos;
            }
        }
    }

    outStream << QString("\n");
    outStream.flush();

    if (!isError && !isSemError)
        //if ((*lex)[cur].type == Tend)
        outStream<<QString("\n Ошибок не обнаружено\n");
        //else;
    else
    {   if (isError)
            outStream<< ErrorText;
        else
            outStream<< ErrorSem;
    }

   outStream.flush();


   return;
}

void LLAnalizator::startDecl()
{
    isDecl = true;
    //определяем семантический тип
    int type = Node::semTypes::TypeUnKnown;
    switch ((*lex)[cur - 1].type) {
        case Tint:{
            type = Node::semTypes::TypeInt;
            break;
        }
        case Tlong:{
            type = Node::semTypes::TypeLong;
            break;
        }
        case Tchar:{
            type = Node::semTypes::TypeChar;
            break;
        }
    }

    type1 = type;   //запоминаем тип
}

bool LLAnalizator::setIdent()
{
    return T->idToTable(new Node ((*lex)[cur - 1].image, type1));   //проверяем на дублирование и заносим с определенным ранее семантическим типом
}

bool LLAnalizator::setParam()
{
    bool result = T->idToTable(new Node ((*lex)[cur - 1].image, type1));   //проверяем на дублирование и заносим с определенным ранее семантическим типом
    if (result)
        paramCount++;   //увеличиваем счетчик в случае успеха
    return result;
}

void LLAnalizator::endDecl()
{
    isDecl = false;
}

void LLAnalizator::setNewLevel()
{
    T->semToRight();
}

void LLAnalizator::returnLevel()
{
    T->semRep();
}

bool LLAnalizator::setFunct()
{
    return T->semFToTable((*lex)[cur - 1].image);
}

TreeLL* LLAnalizator::findId()
{
    return  T->Cur->Find((*lex)[cur - 1].image);     //ищем идентификатор
}

TreeLL *LLAnalizator::findFunc()
{
    TreeLL *ptr = T->Cur->Find(new Node ((*lex)[cur - 1].image, Node::semTypes::TypeFunc));     //ищем функцию
    findedFunc = ptr;
    paramCount = 0; //обнуляем число параметров
    return ptr;
}

int LLAnalizator::constType()
{
    types.push(T->semType(&(*lex)[cur - 1]));   //определяем тип
    return types.last();
}

int LLAnalizator::match()
{
    //берем верхние типы, проверяем и кладем результат
    int t2 = types.pop();
    int t1 = types.pop();
    types.push(T->semTypeRes(t1, t2));
    return types.last();
}

int LLAnalizator::matchNumOnly()
{
    //берем верхние типы, проверяем и кладем результат
    int t2 = types.pop();
    int t1 = types.pop();
    types.push(T->semTypeResOnlyNum(t1, t2));
    return types.last();
}

int LLAnalizator::matchUn()
{
    types.push(T->semTypeResUn(types.pop()));
    return types.last();
}

bool LLAnalizator::matchParamCount()
{
    return findedFunc->N->ParamCount == paramCount;
}
