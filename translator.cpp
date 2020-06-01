#include "translator.h"


Translator::Translator(QList<Triad *> triads, TreeLL *T)
{
    this->T = T;
    this->triads = triads;

    registersNames.insert(-1, "INVALID_REGISTER");
    registersNames.insert(0, "EAX");
    registersNames.insert(1, "EBX");
    registersNames.insert(2, "ECX");
    registersNames.insert(3, "EDX");


    operationsDesignation.insert(TreeLL::functions::matchPlus, "+");
    operationsDesignation.insert(TreeLL::functions::matchMinus, "-");
    operationsDesignation.insert(TreeLL::functions::matchMul, "*");
    operationsDesignation.insert(TreeLL::functions::matchDiv, "/");
    operationsDesignation.insert(TreeLL::functions::matchMod, "%");

    operationsDesignation.insert(TreeLL::functions::matchLeft, "=");
    operationsDesignation.insert(TreeLL::functions::pushParam, "push");
    operationsDesignation.insert(TreeLL::functions::call, "call");

    operationsDesignation.insert(TreeLL::functions::proc, "proc");
    operationsDesignation.insert(TreeLL::functions::prolog, "prolog");
    operationsDesignation.insert(TreeLL::functions::epilog, "epilog");
    operationsDesignation.insert(TreeLL::functions::ret, "ret");
    operationsDesignation.insert(TreeLL::functions::endp, "endp");

    operationsDesignation.insert(TreeLL::functions::cycleLabel, "cycleLabel");
    operationsDesignation.insert(TreeLL::functions::gotoNop, "gotoNop");
    operationsDesignation.insert(TreeLL::functions::o2ToPtr, "o2ToPtr");
    operationsDesignation.insert(TreeLL::functions::o2Transfer, "o2Transfer");
    operationsDesignation.insert(TreeLL::functions::loop, "loop");
    operationsDesignation.insert(TreeLL::functions::nop, "nop");

    operationsDesignation.insert(TreeLL::functions::CharToInt, "CharToInt");
    operationsDesignation.insert(TreeLL::functions::LongToInt, "LongToInt");
    operationsDesignation.insert(TreeLL::functions::IntToChar, "IntToChar");
    operationsDesignation.insert(TreeLL::functions::IntToLong, "IntToLong");
    operationsDesignation.insert(TreeLL::functions::CharToLong, "CharToLong");
    operationsDesignation.insert(TreeLL::functions::LongToChar, "LongToChar");
}

void Translator::translate()
{
    asmCode = "%include \"io.inc\"\n\nsection .data\n";    //
    TreeLL *root = T->getRoot();

    while (root != nullptr){

        Triad *init = getInit(root->N); //ищем инициализацию
        QString initVal, comment;


        switch (root->N->TypeObj){
            case Node::semTypes::TypeInt:{

                initVal = init != nullptr ? init->operand2->node->Id : "0";
                comment = init != nullptr ? " ;переменная инициализирована значением" : " ;переменная инициализирована нулем";

                asmCode += " " + root->N->Id_asm + " DD " + initVal + comment + "\n";    //
                break;
            }
            case Node::semTypes::TypeChar:{
                initVal = init != nullptr ? init->operand2->node->Id : "0";
                comment = init != nullptr ? " ;переменная инициализирована значением" : " ;переменная инициализирована нулем";

                asmCode += " " + root->N->Id_asm + " DB " + initVal + comment + "\n";    //
                break;
            }
            case Node::semTypes::TypeLong:{
                initVal = init != nullptr ? triads[init->operand2->number]->operand1->node->Id : "0";   //здесь приведение типов
                comment = init != nullptr ? " ;переменная инициализирована значением" : " ;переменная инициализирована нулем";

                asmCode += " " + root->N->Id_asm + " DQ " + initVal + comment + "\n";    //
                break;
            }
        }
        root = root->Left;
    }

    asmCode += "\nsection .text\n"
               "global CMAIN\n"
               "CMAIN:\n"
               " mov ebp, esp ;for correct debugging\n";    //секция с кодом


    int curTriad = 0;
    //переходим к началу main
    while (curTriad < triads.count()){
        if (triads[curTriad]->operation == TreeLL::functions::proc)
            if (triads[curTriad]->operand1->node->Id == "main"){
                break;
            }
        curTriad++;
    }

    QString operation, operand1, operand2;
    while (curTriad < triads.count()){

        switch (triads[curTriad]->operation){
            case TreeLL::functions::CharToInt:{
                int regNum;

                //если первый операнд уже есть в регистре
                if(triads[curTriad]->operand1->isLink){
                    regNum = getTriadRegister(triads[curTriad]->operand1->number);  //
                    setRegister(regNum, curTriad);
//                    qDebug()<<"*"<<QString::number(triads[curTriad]->operand1->number)<<" "<<QString::number(curTriad)<<" "<<QString::number(registersValues[0])<<" "<<QString::number(registersValues[1]);
                }
                break;
            }
            case TreeLL::functions::IntToChar:{
                int regNum;

                //если первый операнд уже есть в регистре
                if(triads[curTriad]->operand1->isLink){
                    regNum = getTriadRegister(triads[curTriad]->operand1->number);
                    setRegister(regNum, curTriad);
//                    qDebug()<<"*"<<QString::number(triads[curTriad]->operand1->number)<<" "<<QString::number(curTriad);
                }
                break;
            }



            case TreeLL::functions::matchPlus:{
                int regNum1, regNum2;

                //если первый операнд уже есть в регистре
                if(triads[curTriad]->operand1->isLink){
                    int tr = triads[curTriad]->operand1->number;

                    regNum1 = getTriadRegister(tr);
                    setRegister(regNum1, curTriad); //занимаем его
                    operand1 = registersNames.value(regNum1);
                }else {
                    //нет - нужно сначала загрузить из памяти
                    operation = " MOV ";

                    //находим свободный регистр
                    regNum1 = getRegister();
                    setRegister(regNum1, curTriad); //занимаем его
                    operand1 = registersNames.value(regNum1);

                    operand2 = "[ebp-" + QString::number(triads[curTriad]->operand1->node->stackOffset) + "]";  //в какую ячейку пишем

                    asmCode += operation + operand1 + "," + operand2 + "\n";    //
                }

                //если второй операнд уже есть в регистре
                if(triads[curTriad]->operand2->isLink){

                    int tr = triads[curTriad]->operand2->number;

                    regNum2 = getTriadRegister(tr);
                    operand2 = registersNames.value(regNum2);
                }else {
                    //нет - нужно сначала загрузить из памяти
                    operation = " MOV ";

                    //находим свободный регистр
                    regNum2 = getRegister();
                    setRegister(regNum2, curTriad); //занимаем его
                    QString operand1tmp = registersNames.value(regNum2);

                    //если константа
                    if (triads[curTriad]->operand2->node->Id[0].isDigit() || triads[curTriad]->operand2->node->Id[0] == '\'')
                        operand2 = triads[curTriad]->operand2->node->Id;
                    else
                        operand2 = "[ebp-" + QString::number(triads[curTriad]->operand2->node->stackOffset) + "]";  //какую ячейку берем


                    asmCode += operation + operand1tmp + "," + operand2 + "\n";    //
                    operand2 = operand1tmp;

                }

                operation = " ADD ";


                QString txt1 = "", txt2 = "";
                Operand *op1 = triads[curTriad]->operand1;
                if (op1 != nullptr){
                    if (op1->isLink){
                        txt1 = QString ("(") + QString::number(op1->number + 1) + QString (")");
                    } else {
                        txt1 = op1->node->Id;
                    }
                }

                Operand *op2 = triads[curTriad]->operand2;
                if (op2 != nullptr){
                    if (op2->isLink){
                        txt2 = QString ("(") + QString::number(op2->number + 1) + QString (")");
                    } else {
                        txt2 = op2->node->Id;
                    }
                }


                asmCode += operation + operand1 + "," + operand2 + " ;+ " + txt1 + " " + txt2 + "\n";    //
                retRegister(regNum2);    //вернем второй регистр
                break;
            }
            case TreeLL::functions::matchMinus:{
                int regNum1, regNum2;

                //если первый операнд уже есть в регистре
                if(triads[curTriad]->operand1->isLink){
                    int tr = triads[curTriad]->operand1->number;
//                    if (triads[tr]->operation == TreeLL::functions::CharToInt || triads[tr]->operation == TreeLL::functions::CharToLong || triads[tr]->operation == TreeLL::functions::IntToChar || triads[tr]->operation == TreeLL::functions::IntToLong || triads[tr]->operation == TreeLL::functions::LongToInt || triads[tr]->operation == TreeLL::functions::LongToChar)
//                        tr--;

                    regNum1 = getTriadRegister(tr);
                    operand1 = registersNames.value(regNum1);
                }else {
                    //нет - нужно сначала загрузить из памяти
                    operation = " MOV ";

                    //находим свободный регистр
                    regNum1 = getRegister();
                    setRegister(regNum1, curTriad); //занимаем его
                    operand1 = registersNames.value(regNum1);

                    operand2 = " [ebp-" + QString::number(triads[curTriad]->operand1->node->stackOffset) + "]";  //в какую ячейку пишем

                    asmCode += operation + operand1 + "," + operand2 + "\n";    //
                }

                //если второй операнд уже есть в регистре
                if(triads[curTriad]->operand2->isLink){

                    int tr = triads[curTriad]->operand2->number;
//                    if (triads[tr]->operation == TreeLL::functions::CharToInt || triads[tr]->operation == TreeLL::functions::CharToLong || triads[tr]->operation == TreeLL::functions::IntToChar || triads[tr]->operation == TreeLL::functions::IntToLong || triads[tr]->operation == TreeLL::functions::LongToInt || triads[tr]->operation == TreeLL::functions::LongToChar)
//                        tr--;

                    regNum2 = getTriadRegister(tr);
                    operand2 = registersNames.value(regNum2);
                }else {
                    //нет - нужно сначала загрузить из памяти
                    operation = " MOV ";

                    //находим свободный регистр
                    regNum2 = getRegister();
                    setRegister(regNum2, curTriad); //занимаем его
                    QString operand1tmp = registersNames.value(regNum2);

                    //если константа
                    if (triads[curTriad]->operand2->node->Id[0].isDigit() || triads[curTriad]->operand2->node->Id[0] == '\'')
                        operand2 = triads[curTriad]->operand2->node->Id;
                    else
                        operand2 = "[ebp-" + QString::number(triads[curTriad]->operand2->node->stackOffset) + "]";  //какую ячейку берем


                    asmCode += operation + operand1tmp + "," + operand2 + "\n";    //
                    operand2 = operand1tmp;

                }

                operation = " SUB ";


                QString txt1 = "", txt2 = "";
                Operand *op1 = triads[curTriad]->operand1;
                if (op1 != nullptr){
                    if (op1->isLink){
                        txt1 = QString ("(") + QString::number(op1->number + 1) + QString (")");
                    } else {
                        txt1 = op1->node->Id;
                    }
                }

                Operand *op2 = triads[curTriad]->operand2;
                if (op2 != nullptr){
                    if (op2->isLink){
                        txt2 = QString ("(") + QString::number(op2->number + 1) + QString (")");
                    } else {
                        txt2 = op2->node->Id;
                    }
                }


                asmCode += operation + operand1 + "," + operand2 + " ;- " + txt1 + " " + txt2 + "\n";    //
                retRegister(regNum2);    //вернем второй регистр
                break;
            }
        case TreeLL::functions::matchLeft:{
            operation = " MOV ";
            QString size = "";
            operand1 = "[ebp-" + QString::number(triads[curTriad]->operand1->node->stackOffset) + "]";  //в какую ячейку пишем
            int regNum;

            if (triads[curTriad]->operand2->isLink){
                //операнд - ссылка на триаду. Ищем соотв. регистр

                int tr = triads[curTriad]->operand2->number;
                regNum = getTriadRegister(tr);
                operand2 = registersNames.value(regNum);
            }else {

                //если константа
                if (triads[curTriad]->operand2->node->Id[0].isDigit() || triads[curTriad]->operand2->node->Id[0] == '\''){
                    size =  triads[curTriad]->operand1->node->TypeObj == Node::semTypes::TypeChar ? "byte " : "dword ";
                    operand2 = triads[curTriad]->operand2->node->Id;
                }
                else {
                     //загружаем в регистр
                    QString operationTmp = " MOV ";

                    //находим свободный регистр
                    regNum = getRegister();
                    setRegister(regNum, curTriad); //занимаем его
                    QString operand1tmp = registersNames.value(regNum);

                    operand2 = "[ebp-" + QString::number(triads[curTriad]->operand2->node->stackOffset) + "]";  //какую ячейку берем



                    QString txt1 = "", txt2 = "";
                    Operand *op1 = triads[curTriad]->operand1;
                    if (op1 != nullptr){
                        if (op1->isLink){
                            txt1 = QString ("(") + QString::number(op1->number + 1) + QString (")");
                        } else {
                            txt1 = op1->node->Id;
                        }
                    }

                    Operand *op2 = triads[curTriad]->operand2;
                    if (op2 != nullptr){
                        if (op2->isLink){
                            txt2 = QString ("(") + QString::number(op2->number + 1) + QString (")");
                        } else {
                            txt2 = op2->node->Id;
                        }
                    }

                    asmCode += operation + operand1tmp + "," + operand2 + " ;= " + txt1 + " " + txt2 + "\n";    //
                    operand2 = operand1tmp;

                    retRegister(regNum);    //освобождаем регистр
                }
            }

            asmCode += operation + size + operand1 + "," + operand2 + "\n";    //
            retRegister(regNum);    //освобождаем регистр

            break;
        }
        }
        curTriad++;
    }
    asmCode += "\n ret";





    QFile file ("out.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream ts (&file);
    ts << asmCode;
    file.close();
}

Triad *Translator::getInit(Node *n)
{
    Triad* retT = nullptr;
    bool functionFlag = false;  //флаг того, что находимся в функции
    foreach (Triad* t, triads) {
        //определяем в функции ли мы находимся
        if (t->type == TreeLL::functions::proc)
            functionFlag = true;
        else if (t->type == TreeLL::functions::endp)
            functionFlag = false;

        if (t->operation == TreeLL::functions::matchLeft)
            if (t->operand1->node->Id_asm == n->Id_asm && !functionFlag){
                retT = t;
                break;
            }

    }
    return retT;
}

int Translator::getRegister()
{
    //ищем какой регистр можно занять, и занимаем
    for (int i = 0; i < 4; i++)
        if (registers[i] == false){
            registers[i] = true;
            return i;
        }
    return -1;
}

void Translator::setRegister(int regNum, int triadNum)
{
    registersValues[regNum] = triadNum;
}

void Translator::retRegister(int reg)
{
    registers[reg] = false;
}

int Translator::getTriadRegister(int triadNum)
{
    int regNum = -1;
    for (int i = 0; i < 4; i++){
        if (registersValues[i] == triadNum){
            regNum = i;
            break;
        }
    }
    return regNum;
}
