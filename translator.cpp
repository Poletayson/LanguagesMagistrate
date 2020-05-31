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
}

void Translator::translate()
{
    asmCode = "section .data\n";    //
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

                asmCode += " " + root->N->Id_asm + " DD " + initVal + comment + "\n";    //
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

    asmCode += "\nsection .text\n";    //секция с кодом


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
            case TreeLL::functions::matchPlus:{
                operation = " ADD ";
                //если первый операнд уже есть в регистре
                if(triads[curTriad]->operand1->isLink){
                    int regNum = getTriadRegister(curTriad);
                    operand1 = registersNames.value(regNum);
                }else {
//TODO
}

                asmCode += operation + operand1 + operand2 + "\n";    //
                break;
            }
        case TreeLL::functions::matchLeft:{
            operation = " MOV ";
            operand1 = "[ebp-" + QString::number(triads[curTriad]->operand1->node->stackOffset) + "] ";  //в какую ячейку пишем

            if (triads[curTriad]->operand2->isLink){
                //операнд - ссылка на триаду. Ищем соотв. регистр
                int regNum = getTriadRegister(curTriad);
                operand2 = registersNames.value(regNum);
            }else {
                operand2 = triads[curTriad]->operand2->node->Id;
            }

            asmCode += operation + operand1 + operand2 + "\n";    //
            break;
        }
        }
        curTriad++;
    }





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
