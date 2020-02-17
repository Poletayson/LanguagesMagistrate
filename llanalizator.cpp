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
    NTerminalsNames.insert(Tid, "�������������");
    NTerminalsNames.insert(Tcchar, "������");
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
    NTerminalsNames.insert(NData, "������");
    NTerminalsNames.insert(NSpPar, "������ ����������");
    NTerminalsNames.insert(NB, "B");
    NTerminalsNames.insert(NB1, "B1");
    NTerminalsNames.insert(NSpIdent, "������ ���������������");
    NTerminalsNames.insert(NC, "C");
    NTerminalsNames.insert(NInit, "�������������");
    NTerminalsNames.insert(NBlock, "����");
    NTerminalsNames.insert(NOperator, "��������");
    NTerminalsNames.insert(NCicle, "����");
    NTerminalsNames.insert(NInitCycle, "����. �����");
    NTerminalsNames.insert(NEndIter, "����� ��������");
    NTerminalsNames.insert(NPrisv, "������������");
    NTerminalsNames.insert(NOperand, "�������");
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
    NTerminalsNames.insert(NVizFunc, "����� �������");
    NTerminalsNames.insert(NSpID2, "������ ���������");
    NTerminalsNames.insert(ND, "D");




    //��������� �������
    QList<Lexem*> Cell;  //���� ������� �������
    QList<Rule> Rules;
    QMultiMap <int, QList<Rule>> Sting;    //������ �������, ��������������� �����������
//���������� S
    Cell.append(new Lexem (NS, true));
    Cell.append(new Lexem (Trf, false));
    Cell.append(new Lexem (NBlock, true));
    Cell.append(new Lexem (Tlf, false));
    Cell.append(new Lexem (Trs, false));
    Cell.append(new Lexem (NSpPar, true));
    Cell.append(new Lexem (Tls, false));
    Cell.append(new Lexem (Tid, false));
    Cell.append(new Lexem (Tvoid, false));
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tvoid, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //int
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tint, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //char
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tchar, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tchar, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //long
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tlong, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //�����
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tend, Rules);      //��������� ������ ������ � ������ ������

    Table.insert(NS, Sting);

//������
    Sting.clear();    //������ �������, ��������������� �����������

    Cell.clear();   //int
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tint, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //char
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tchar, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tchar, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //long
    Cell.append(new Lexem (Tdt, false));
    Cell.append(new Lexem (NSpIdent, true));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tlong, Rules);      //��������� ������ ������ � ������ ������

    Table.insert(NData, Sting);

//������ ����������
    Sting.clear();    //������ �������, ��������������� �����������

    Cell.clear();   //int
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (Tid, false));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tint, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //char
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (Tid, false));
    Cell.append(new Lexem (Tchar, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tchar, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //long
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (Tid, false));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tlong, false));
    Cell.append(new Lexem (Tint, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tlong, Rules);      //��������� ������ ������ � ������ ������

    Table.insert(NSpPar, Sting);

//B
    Sting.clear();    //������ �������, ��������������� �����������

    Cell.clear();   //)
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������

    Cell.clear();   //,
    Cell.append(new Lexem (NB, true));
    Cell.append(new Lexem (NB1, true));
    Cell.append(new Lexem (Tzap, false));
    Rules.clear();
    Rules.append(*new Rule (&Cell));
    Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������

    Table.insert(NB, Sting);

    //B1
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //int
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (Tint, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //char
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (Tchar, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tchar, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //long
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (Tlong, false));
        Cell.append(new Lexem (Tlong, false));
        Cell.append(new Lexem (Tint, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tlong, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NB1, Sting);

//������ �����.
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //id
        Cell.append(new Lexem (NC, true));
        Cell.append(new Lexem (NInit, true));
        Cell.append(new Lexem (Tid, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NSpIdent, Sting);

//C
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //id
        Cell.append(new Lexem (NC, true));
        Cell.append(new Lexem (NInit, true));
        Cell.append(new Lexem (Tid, false));
        Cell.append(new Lexem (Tzap, false));

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NC, Sting);

//�������������
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;

        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //id
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Teq, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Teq, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NInit, Sting);

//����
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //int
        Cell.append(new Lexem (NBlock, true));
        Cell.append(new Lexem (NData, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tlong, Rules);      //��������� ������ ������ � ������ ������
        Cell.clear();   //int
        Cell.append(new Lexem (NBlock, true));
        Cell.append(new Lexem (NOperator, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tfor, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Ttil, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tlf, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //int
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trf, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NBlock, Sting);

//��������
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //int
        Cell.append(new Lexem (NCicle, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tfor, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //rf
        Cell.append(new Lexem (Trf, false));
        Cell.append(new Lexem (NBlock, true));
        Cell.append(new Lexem (Tlf, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tlf, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //dt
        Cell.append(new Lexem (Tdt, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������

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

        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //int
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Ttil, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NOperator, Sting);

//����
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //int
        Cell.append(new Lexem (NOperator, true));
        Cell.append(new Lexem (Trs, false));
        Cell.append(new Lexem (NEndIter, true));
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NInitCycle, true));
        Cell.append(new Lexem (Tls, false));
        Cell.append(new Lexem (Tfor, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tfor, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NCicle, Sting);

//����. �����
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();
        Cell.append(new Lexem (NData, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tlong, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NInitCycle, Sting);

//����� ��������
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
//        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NPrisv, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Cell.clear();   //;
//        Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NEndIter, Sting);

//prisv
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        //Cell.append(new Lexem (Tdt, false));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Teq, false));
        Cell.append(new Lexem (Tid, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NPrisv, Sting);

//�������
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (Tid, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (Tint8, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (Tint10, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (Tint16, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (Tcchar, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NOperand, Sting);

//A1
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA11, true));
        Cell.append(new Lexem (NA2, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA1, Sting);

//A11
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA11, true));
        Cell.append(new Lexem (NA2, true));
        Cell.append(new Lexem (Tvch, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tvch, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA11, Sting);

//A2
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA21, true));
        Cell.append(new Lexem (NA3, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA2, Sting);

//A21
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA21, true));
        Cell.append(new Lexem (NA3, true));
        Cell.append(new Lexem (Tamp, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tamp, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tvch, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA21, Sting);

//A3
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA31, true));
        Cell.append(new Lexem (NA4, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA3, Sting);

//A31
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA31, true));
        Cell.append(new Lexem (NA4, true));
        Cell.append(new Lexem (Tlsd, false));
        Cell.append(new Lexem (Tlsd, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tlsd, Rules);      //��������� ������ ������ � ������ ������
        Cell.clear();   //;
        Cell.append(new Lexem (NA31, true));
        Cell.append(new Lexem (NA4, true));
        Cell.append(new Lexem (Trsd, false));
        Cell.append(new Lexem (Trsd, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trsd, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tvch, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tamp, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA31, Sting);

//A4
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA41, true));
        Cell.append(new Lexem (NA5, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA4, Sting);

//A41
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA41, true));
        Cell.append(new Lexem (NA5, true));
        Cell.append(new Lexem (Tplus, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tplus, Rules);      //��������� ������ ������ � ������ ������
        Cell.clear();   //;
        Cell.append(new Lexem (NA41, true));
        Cell.append(new Lexem (NA5, true));
        Cell.append(new Lexem (Tminus, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tminus, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tvch, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tamp, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tlsd, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trsd, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA41, Sting);

//A5
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (NA6, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA5, Sting);

//A51
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Tmul, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tmul, Rules);      //��������� ������ ������ � ������ ������
        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Tdel, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tdel, Rules);      //��������� ������ ������ � ������ ������
        Cell.clear();   //;
        Cell.append(new Lexem (NA51, true));
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Tpers, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tpers, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tdt, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tvch, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tamp, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tlsd, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Trsd, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tplus, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tminus, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NA51, Sting);

//A6
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NA6, true));
        Cell.append(new Lexem (Ttil, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Ttil, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (NA7, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������


        Table.insert(NA6, Sting);

//A7
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (NOperand, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (Trs, false));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Tls, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������


        Table.insert(NA7, Sting);

//����� �������
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;

        Cell.append(new Lexem (Trs, false));
        Cell.append(new Lexem (NSpID2, true));
        Cell.append(new Lexem (Tls, false));
        Cell.append(new Lexem (Tid, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NVizFunc, Sting);

//������ ���������
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Cell.append(new Lexem (ND, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������

        Cell.append(new Lexem (NA1, true));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tid, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint8, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint10, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tint16, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tcchar, Rules);      //��������� ������ ������ � ������ ������
        Sting.insert(Tls, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(NSpID2, Sting);

//D
        Sting.clear();    //������ �������, ��������������� �����������

        Cell.clear();   //;
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Trs, Rules);      //��������� ������ ������ � ������ ������

        Cell.clear();   //;
        Cell.append(new Lexem (ND, true));
        Cell.append(new Lexem (NA1, true));
        Cell.append(new Lexem (Tzap, false));
        Rules.clear();
        Rules.append(*new Rule (&Cell));
        Sting.insert(Tzap, Rules);      //��������� ������ ������ � ������ ������

        Table.insert(ND, Sting);
}

void LLAnalizator::toAnalize ()
{
    int c;
    scaner->toScan(lex);         //�������� ������ ������
    QString type;
    for (int i = 0; i < scaner->Errors.count(); i++)         //������� ����������� ������
    {
        std::cout<<'\n';
        std::cout<<"Lexical error in "<<scaner->Errors[i][0]<<":"<<scaner->Errors[i][1];
    }
//    T = new Tree ();
//    T->Cur = T;
    Lexem *Lex;
    Lexem *NT;
    if(scaner->Errors.count() == 0)      //��� ����������� ������
    {
        ErrorText = "\n ���������� ������ � ";

        QList<Rule> Rules;
        QMultiMap <int, QList<Rule>> Sting;    //������ �������, ��������������� �����������
        cur = 0;
        isError = false;
        QList <Lexem*> rule;
        Lex = new Lexem (NS, true);
        Stack.append(*Lex);             //������� � ����
        while (Stack.size() > 0 && !isError)        //���� ��������
        {
            Lex = new Lexem (Stack.pop ());     //�������� ������� �� �����
            if (Lex->isNT == true)              //� �������� - ����������
            {
                NT = Lex;
                Sting = Table.value(Lex->type);     //�������� ������ ������ ��� ����� ��
                Rules = Sting.value((*lex)[cur].type);  //������ ������ � ������
                if (Rules.count() > 0)
                {
                    if (Rules.count() == 1) //�� ��������//(!((*lex)[cur].type == Tid && (Lex->type  == NOperator || Lex->type  == NEndIter)))  //������ ��� ��������
                    {
                        rule = *Rules[0].rule;
                        for (int i = 0; i < rule.count(); i++) //�������� ��� �������
                        {
                            Stack.push(*rule[i]);            //��������� � ����
                        }
                    }
                    else    //���������� ��������
                    {
                        if ((*lex)[cur+1].type == Teq)    //������������
                        {
                            rule = *Rules[0].rule;
                        }
                        else if ((*lex)[cur+1].type == Tls && Lex->type == NOperator)   //����� ������� � ���������
                        {
                            rule = *Rules[1].rule;
                        }
                        else
                        {
                            rule = *Rules[2].rule;
                        }
                        for (int i = 0; i < rule.count(); i++) //�������� ��� �������
                        {
                            Stack.push(*rule[i]);            //��������� � ����
                        }
                    }
                }
                else
                {
                    isError = true;
                    ErrorText = ErrorText + std::to_string((*lex)[cur].str) +":" + std::to_string((*lex)[cur].pos) +":";  //<<" � ����������� "<<NTerminalsNames.value(NT->type)<<"\n";//". �������� "<<NTerminalsNames.value(Lex->type)<<"\n";
                    ErrorText = ErrorText + " � ����������� " + NTerminalsNames.value(NT->type) + ", ������� ������������ " + NTerminalsNames.value(Lex->type) + "\n";
                }
            }
            else    //�� �������� ���� ��������
            {
                if (Lex->type == (*lex)[cur].type)
                {
                    cur++;
                }
                else
                {
                    isError = true;
                    ErrorText = ErrorText + std::to_string((*lex)[cur].str) +":" + std::to_string((*lex)[cur].pos);
                    ErrorText = ErrorText + " � ����������� " + NTerminalsNames.value(NT->type) + ": �������� " + NTerminalsNames.value(Lex->type) + "\n";
                }
            }
            if (cur >= lex->count())
            {
                isError = true;
                ErrorText = ErrorText + std::to_string((*lex)[cur].str) +":" + std::to_string((*lex)[cur].pos);
            }
        }
    }

    std::cout << "\n";
    std::cout.flush();

    if (!isError)
        //if ((*lex)[cur].type == Tend)
        std::cout<<"\n �������������� ������ �� ����������\n";
        //else;
    else
    {
        std::cout<<ErrorText;
    }

    std::cout.flush();


    return;
}
