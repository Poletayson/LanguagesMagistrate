#include "opanalizator.h"

//получить список с отношениями для двух лексем
QList<int> OPAnalizator::getPrecedence(int x1, int x2)
{
    matrixPrecedence.value(x1).value(x2);
}

//получить список с отношениями для двух верхних лексем из магазина
int OPAnalizator::getPrecedence()
{
    int x1 = 0; //пропустим аксиомы, ибо они прозрачны
    while (Stack[Stack.length() - 1 - x1].type == NS)
        x1++;


    QList <int> gotPrecedence = matrixPrecedence.value(Stack[Stack.length() - 1 - x1].type).value((*lex)[cur].type);
    if (gotPrecedence.length() == 0)
        return NOT_PRECEDENCE;
    if (gotPrecedence.length() == 1)
        return gotPrecedence[0];
    else {
        //коллизии с закрывающейся правой скобкой
        if (Stack[Stack.length() - 1 - x1].type == Trs){
            //со знаками операций
            if((*lex)[cur].type >= Tvch && (*lex)[cur].type <= Tpers){
                if (Stack[Stack.length() - 2 - x1].type == NS)   //внутри скобок A1, нужно свернуть до A7
                    return MORE;
                else
                    return LESS_EQUAL;
            }
            //точка с запятой
            if ((*lex)[cur].type == Tdt){
                bool isDt = false;  //
                int c = Stack.length() - 2;
                //ищем точку с запятой либо открыв. скобку
                while (c >= 0){
                    if (Stack[c].type == Tdt){
                        isDt = true;
                        break;
                    }
                    if (Stack[c].type == Tls){
                        break;
                    }
                    c--;
                }
                //если тз, значит это описание цикла, нужно продолжать
                if (isDt)
                    return LESS_EQUAL;
                else
                    return MORE;

            }
            //id
            if ((*lex)[cur].type == Tid){
                bool isDt = false;  //
                int c = Stack.length() - 2;
                //ищем точку с запятой
                while (c >= 0){
                    if (Stack[c].type == Tdt){
                        isDt = true;
                        break;
                    }
                    c--;
                }
                //если тз, значит это описание цикла, нужно продолжать
                if (isDt)
                    return LESS_EQUAL;
                else
                    return MORE;

            }
            //{. Редуцировать нужно тольо если начинается блок, следующий за циклом вместе с оператором
            if ((*lex)[cur].type == Tlf){
                bool isS = false;  //
                if (Stack.last().type == NS)
                    isS = true;
                //сворачиваем, если между ) и { еще есть S
                if (isS)
                    return MORE;
                else
                    return LESS_EQUAL;

            }
        }

        //коллизии с ;
        if (Stack[Stack.length() - 1 - x1].type == Tdt){
            //с id и ;. <= если в описании цикла
            if ((*lex)[cur].type == Tid || (*lex)[cur].type == Tdt){
                bool isLs = false;  //есть ли в магазине левая скобка
                int c = Stack.length() - 2;
                //ищем открыв. скобку
                while (c >= 0){
                    if (Stack[c].type == Trs){
                        break;
                    }
                    if (Stack[c].type == Tls){
                        isLs = true;
                        break;
                    }
                    c--;
                }
                //если левая скобка, значит это описание цикла, нужно продолжать
                if (isLs)
                    return LESS_EQUAL;
                else
                    return MORE;
            }
        }

        //коллизии с =
        if (Stack[Stack.length() - 1 - x1].type == Teq){
            //с ;. <= если в описании цикла
            if ((*lex)[cur].type == Tdt){
                bool isLs = false;  //есть ли в магазине левая скобка
                int c = Stack.length() - 1;
                //ищем } или S
                while (c >= 0){
                    if (Stack[c].type == Trs){
                        break;
                    }
                    if (Stack[c].type == Trf || Stack[c].type == NS){
                        isLs = true;
                        break;
                    }
                    c--;
                }
                //если левая скобка, значит это описание цикла, нужно продолжать
                if (isLs)
                    return MORE;
                else
                    return LESS_EQUAL;
            }
        }

        //коллизии с int char
        if (Stack[Stack.length() - 1 - x1].type == Tint || Stack[Stack.length() - 1 - x1].type == Tchar){
            //с ;. <= если в описании цикла
            if ((*lex)[cur].type == Tdt){
                bool isLs = false;  //есть ли в магазине левая скобка и for - то свернем
                int c = Stack.length() - 2;
                //ищем открыв. скобку
                while (c >= 0){
                    if (Stack[c].type == Trs){
                        break;
                    }
                    if (Stack[c].type == Tls && Stack[c - 1].type == Tfor){
                        isLs = true;
                        break;
                    }
                    c--;
                }
                //если левая скобка, значит это описание цикла, нужно сворачивать
                if (isLs)
                    return  MORE;
                else
                    return LESS_EQUAL;
            }
        }
        return NOT_PRECEDENCE;
    }
}

//длина редуцируемой цепочки
int OPAnalizator::getReduceLength()
{
    int n = __min (Stack.length(), grammar.length() - 1);
    int counter;

    bool isSP = false;  //список параметров ли перед нами, или же идентификаторов. Проверяем, т.к. у нас есть правило, нарушающее принцип слабого предш.
    for (int i = 0; i < Stack.length() - 2; i++){
        if (Stack[Stack.length() - 1 - i].type == Trs)
            break;
        //ищем id ( или for (
        if (Stack[Stack.length() - 1 - i].type == Tls && (Stack[Stack.length() - 2 - i].type == Tid || Stack[Stack.length() - 2 - i].type == Tfor)){
            isSP = true;    //список параметров
            //qDebug() << "\nisSP\n";
            break;
        }
    }
    bool isPrisv = false;  //присваивание ли перед нами
    if (Stack.length() > 3){
        if (Stack[Stack.length() - 1].type == NS && Stack[Stack.length() - 2].type == Teq && Stack[Stack.length() - 3].type == Tid && Stack[Stack.length() - 4].type == NS)
            isPrisv = true;
    }

    while (n > 0) {
        counter = 0;
        QList <Rule> rules = grammar[n];    //список правил заданной длины

        foreach(Rule rule, rules){
            bool flag = true;   //изначально считаем что правило соответствует верхушке
            //проходим
            for (int i = 0; i < n; i++){
                if (Stack[Stack.length() - 1 - i].type != (*rule.rule)[(*rule.rule).length() - 1 - i]->type){
                    flag = false;   //нет, попалось несоответствие
                    break;
                }
            }

            //если не список параметров/описание цикла - правила придется откинуть
            ///
            if (!isSP){
                if (n >= 2)
                    if (((*rule.rule)[(*rule.rule).length() - 1]->type == Tid || (*rule.rule)[(*rule.rule).length() - 1]->type == NS) && ((*rule.rule)[(*rule.rule).length() - 2]->type == Tint || (*rule.rule)[(*rule.rule).length() - 2]->type == Tchar )){
                        flag = false;
                        //qDebug() << "\nOUT\n";
                    }



                if (n >= 4)
                    if (((*rule.rule)[(*rule.rule).length() - 1]->type == Tid || (*rule.rule)[(*rule.rule).length() - 1]->type == NS) && (*rule.rule)[(*rule.rule).length() - 2]->type == Tint && (*rule.rule)[(*rule.rule).length() - 3]->type == Tlong){
                        flag = false;
                        //qDebug() << "\nOUT\n";
                    }
            }

            if (isPrisv){
                //чтобы не пропустить присваивание - оно захватывает ;
                if (n >= 3)
                    if ((*rule.rule)[(*rule.rule).length() - 1]->type == NS && (*rule.rule)[(*rule.rule).length() - 2]->type == Teq){
                        flag = false;
                        //qDebug() << "\nOUT\n";
                    }
            }
            ///


            //если несоответствий не было, т.е. правило подошло
            if (flag){
                counter++;  //добавляем в счетчик
                break;
            }
        }

        if (counter > 0)
            break;  //выходим, правило найдено

        n--;
    }

    return n;
}


OPAnalizator::OPAnalizator()
{
    scaner = new Scanner ("input.txt");
    lex = new QList <Lexem> ();
    right = true;

    lexImages.insert(Tvoid, "void");
    lexImages.insert(Tmain, "main");
    lexImages.insert(Tfor, "for");
    lexImages.insert(Tint, "int");
    lexImages.insert(Tlong, "long");
    lexImages.insert(Tchar, "char");
    lexImages.insert(Tid, "идентификатор");
    lexImages.insert(Tcchar, "символ");
    lexImages.insert(Tint10, "int10");
    lexImages.insert(Tint8, "int8");
    lexImages.insert(Tint16, "int16");
    lexImages.insert(Tzap, ",");
    lexImages.insert(Tdt, ";");
    lexImages.insert(Tls, "(");
    lexImages.insert(Trs, ")");
    lexImages.insert(Tlf, "{");
    lexImages.insert(Trf, "}");
    lexImages.insert(Tvch, "|");
    lexImages.insert(Tamp, "&");
    lexImages.insert(Tlsd, "<");
    lexImages.insert(Trsd, ">");
    lexImages.insert(Tplus, "+");
    lexImages.insert(Tminus, "-");
    lexImages.insert(Tdel, "/");
    lexImages.insert(Tmul, "*");
    lexImages.insert(Tpers, "%");
    lexImages.insert(Ttil, "~");
    lexImages.insert(Teq, "=");
    lexImages.insert(Tend, "#");

    lexImages.insert(NS, "S");
    lexImages.insert(NData, "Данные");
    lexImages.insert(NSpPar, "Список параметров");
    lexImages.insert(NSpId, "Список идентификаторов");
    lexImages.insert(NBlock, "Блок");
    lexImages.insert(NOperator, "Оператор");
    lexImages.insert(NCicle, "Цикл");
    lexImages.insert(NInitCycle, "Иниц. цикла");
    lexImages.insert(NEndIter, "Конец итерации");
    lexImages.insert(NPrisv, "Присваивание");
    lexImages.insert(NOperand, "Операнд");
    lexImages.insert(NA1, "A1");
    lexImages.insert(NA2, "A2");
    lexImages.insert(NA3, "A3");
    lexImages.insert(NA4, "A4");
    lexImages.insert(NA5, "A5");
    lexImages.insert(NA6, "A6");
    lexImages.insert(NA7, "A7");
    lexImages.insert(NVizFunc, "Вызов функции");
    lexImages.insert(NSpID2, "Список выражений");


    getGrammar();
//    qDebug() << "---------------------------";
    getMatrix();

}

void OPAnalizator::toAnalize()
{
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


    QList <int> gotPrecedence;      //полученное отношение
    int precedenceLast;
    if(scaner->Errors.count() == 0)      //нет лексических ошибок
    {
        ErrorText = "\n Обнаружена ошибка в ";
        Stack.append(Lexem (Tend, false));   //в начале кладем знак конца цепочки


        //цепочка непустая
        if (lex->length() > 1){
            cur = 0;        //теущая лесема
            isError = false;
            precedenceLast = getPrecedence();
            //отношение не найдено
            if (precedenceLast == NOT_PRECEDENCE){
                isError = true;
                ErrorText = "Не найдено отношение в таблице между " + lexImages.value(Stack[Stack.length() - 1].type) + " и " + lexImages.value((*lex)[cur].type);
                goto errorLabel;
            }
            StackPrecedence.append(precedenceLast);


            while (cur < lex->length() - 1 && !isError)        //пока не прошли всю цепочку
            {


                //в верхуше магазина отношение <= - значит продолжим считывать цепочку
                if (StackPrecedence.last() == LESS_EQUAL){
                    Stack.append((*lex)[cur]); //кладем лексему цепочки
                    cur++;
                    if (cur == lex->length() - 1)
                        int t = 5+5;
                    precedenceLast = getPrecedence();
                    if (precedenceLast == NOT_PRECEDENCE){
                        isError = true;
                        ErrorText = "Не найдено отношение в таблице между " + lexImages.value(Stack[Stack.length() - 1].type) + " и " + lexImages.value((*lex)[cur].type);
                        goto errorLabel;
                    }
                    StackPrecedence.append(precedenceLast);
                }
                else {
                    //в верхуше магазина отношение > - пора редуцировать цепочку

//                    outStream<< QString("\n\nРедуцируем");;
//                    foreach (Lexem l, Stack) {
//                        outStream<< lexImages.value(l.type) << " ";
//                    }
//                    outStream<< "\n++++++";


                    int reduceLength = getReduceLength();
                    if (reduceLength == 0){
                        isError = true;
                        ErrorText = "Невозможно редуцировать цепочку!";
                        goto errorLabel;
                    }
                    for (int i = 0; i < reduceLength; i++){
                        int lastType = Stack.last().type;   //тип последнего символа в магазине
                        Stack.removeLast();
                        //удаляем отношение только если был терминал, ибо нетерминалы в операторном предшествовании прозрачны
                        if (lastType != NS)
                            StackPrecedence.removeLast();
                    }
                    Stack.append(Lexem(NS, true));  //кладем в магазин нетерминал-аксиому

//                    foreach (Lexem l, Stack) {
//                        outStream<< lexImages.value(l.type) << " ";
//                    }
//                    outStream<< "\n++++++++";

                    //сворачиваем дальше, сколько возможно
                    reduceLength = getReduceLength();
                    while (reduceLength > 0) {
                        //чтобы не зациклиться на сворачивании аксиомы
                        if (reduceLength == 1 && Stack.last().type == NS)
                            break;
                        for (int i = 0; i < reduceLength; i++){
                            int lastType = Stack.last().type;   //тип последнего символа в магазине
                            Stack.removeLast();
                            //удаляем отношение только если был терминал, ибо нетерминалы в операторном предшествовании прозрачны
                            if (lastType != NS)
                                StackPrecedence.removeLast();
                        }
                        Stack.append(Lexem(NS, true));  //кладем в магазин нетерминал-аксиому

//                        foreach (Lexem l, Stack) {
//                            outStream<< lexImages.value(l.type) << " ";
//                        }
//                        outStream<< "\n++++++++";


                        reduceLength = getReduceLength();
                    }
                }
            }
            //досворачиваем то, что осталось в магазине
            if (StackPrecedence.last() == MORE){
                //в верхуше магазина отношение > - пора редуцировать цепочку


//                outStream<< QString("\n\nРедуцируем в конце");
//                foreach (Lexem l, Stack) {
//                    outStream<< lexImages.value(l.type) << " ";
//                }
//                outStream<< "\n++++++";


                int reduceLength = getReduceLength();
                if (reduceLength == 0){
                    isError = true;
                    ErrorText = "Невозможно редуцировать цепочку!";
                    goto errorLabel;
                }
                for (int i = 0; i < reduceLength; i++){
                    int lastType = Stack.last().type;   //тип последнего символа в магазине
                    Stack.removeLast();
                    //удаляем отношение только если был терминал, ибо нетерминалы в операторном предшествовании прозрачны
                    if (lastType != NS)
                        StackPrecedence.removeLast();
                }
                Stack.append(Lexem(NS, true));  //кладем в магазин нетерминал-аксиому

                //сворачиваем дальше, сколько возможно
                reduceLength = getReduceLength();
                while (reduceLength > 0) {
                    //чтобы не зациклиться на сворачивании аксиомы
                    if (reduceLength == 1 && Stack.last().type == NS)
                        break;
                    for (int i = 0; i < reduceLength; i++){
                        int lastType = Stack.last().type;   //тип последнего символа в магазине
                        Stack.removeLast();
                        //удаляем отношение только если был терминал, ибо нетерминалы в операторном предшествовании прозрачны
                        if (lastType != NS)
                            StackPrecedence.removeLast();
                    }
                    Stack.append(Lexem(NS, true));  //кладем в магазин нетерминал-аксиому

//                    foreach (Lexem l, Stack) {
//                        outStream<< lexImages.value(l.type) << " ";
//                    }
//                    outStream<< "\n++++++";

//                    reduceLength = getReduceLength();
                }
            }


        }

        if(Stack.first().type == Tend)
            Stack.removeFirst();    //удаляем символ начала/онца цепочки

        if (Stack.length() > 1){
            isError = true;
            ErrorText = "После анализа в магазине что-то осталось! Размер - " + QString::number(Stack.length());
            goto errorLabel;
        }

        //сюда переходим в случае ошибки
errorLabel:
        if (isError)
            ErrorText =  QString::number((*lex)[cur].str) +":" + QString::number((*lex)[cur].pos) + " " + ErrorText + "\n";
    }

    outStream << QString("\n");
    outStream.flush();

    if (!isError)
        outStream<<QString("\n Синтаксических ошибок не обнаружено\n");
    else
    {
        outStream<< ErrorText << "\n";
//        foreach (Lexem l, Stack) {
//            outStream<< lexImages.value(l.type) << " ";
//        }

    }

   outStream.flush();

    return;
}

void OPAnalizator::getGrammar()
{
    QFile file ("grammar.txt");
    file.open(QIODevice::ReadOnly);

    QString gram = file.readAll();
    QRegExp rx("[\r\n|]");
    QStringList rules = gram.split(rx, QString::SplitBehavior::SkipEmptyParts);  //разбиваем по строкам

    //создаем по списку для правил каждой длины. Будем считать что длинее 20 правил нет
    for (int i = 0; i < 20; i++){
        grammar.append(QList<Rule> ());
    }

    QRegExp rxRem("*->");
    QRegExp rxSpaces("[ \t|]");
    QRegExp rxNt("<*>");
    rxRem.setPatternSyntax(QRegExp::Wildcard);
    rxNt.setPatternSyntax(QRegExp::Wildcard);

    lexImages.insert(Tpers, "%");
    lexImages.insert(Tamp, "&");
    lexImages.insert(Tls, "(");
    lexImages.insert(Trs, ")");
    lexImages.insert(Tmul, "*");
    lexImages.insert(Tplus, "+");
    lexImages.insert(Tminus, "-");
    lexImages.insert(Tzap, ",");
    lexImages.insert(Tdel, "/");
    lexImages.insert(Tdt, ";");
    lexImages.insert(Teq, "=");
    lexImages.insert(Tchar, "char");
    lexImages.insert(Tfor, "for");
    lexImages.insert(Tid, "id");
    lexImages.insert(Tint, "int");
    lexImages.insert(Tlong, "long");
    lexImages.insert(Tmain, "main");
    lexImages.insert(Tvoid, "void");
    lexImages.insert(Tint10, "x10число");
    lexImages.insert(Tint16, "x16число");
    lexImages.insert(Tint8, "x8число");
    lexImages.insert(Tlf, "{");
    lexImages.insert(Trf, "}");
    lexImages.insert(Ttil, "~");
    lexImages.insert(Tvch, "вч");
    lexImages.insert(Tlsd, "сдл");
    lexImages.insert(Trsd, "сдп");
    lexImages.insert(Tcchar, "символ");
    lexImages.insert(Tend, "#");
    lexImages.insert(NS, "S");

    QList<Lexem*> Cell;  //одно правило таблицы

    QList<QStringList> rulesLexems;
    for (int i = 0; i < rules.length(); i++){
        rules[i].remove(rxRem);
        rulesLexems.append(rules[i].split(rxSpaces, QString::SplitBehavior::SkipEmptyParts));

        Cell.clear();   //очищаем
        //для каждой лексемы выводимой цепочки
        foreach (QString lex, rulesLexems.last()){
            int curLex = lexImages.key(lex);
            if (curLex != 0){
                Cell.append(new Lexem (curLex, false));
            }
            else {
                Cell.append(new Lexem (NS, true));
            }
        }
        grammar[Cell.length()].append(Rule (&Cell));    //добавляем правило в грамматику
        //rules[i].replace(rxNt, "<#S#>");
    }

//        //отладочный вывод
//    foreach (QList<Rule> ruleList, grammar) {
//        foreach (Rule rule, ruleList) {
//            foreach (Lexem* lexeme, *rule.rule) {
//                qDebug() << lexImages.value( lexeme->type);
//            }
//            qDebug() << "\n";
//        }
//    }

}

void OPAnalizator::getMatrix()
{
    QXlsx::Document document ("matrix.xlsx");
    QList<QString> terminalsList;       //список терминалов, как они идут в матрице
    QList<int> terminalsNumsList;       //список терминалов, как они идут в матрице
    for (int i = 2; i < 31; i++){
//        qDebug() << document.read(i, 1).toString();
        terminalsList.append(document.read(i, 1).toString());   //список всех терминалов в эксельке
        terminalsNumsList.append(lexImages.key(terminalsList.last()));   //список всех терминалов в эксельке, но в виде числовых кодов

    }

    //проходим все строки
    for (int i = 0; i < terminalsList.size(); i++){
        QMap<int, QList<int>> oneString;    //одна строка матрицы
        oneString.clear();
        QList<int> oneCell; //одна ячейка
        //проходим все столбцы
        for (int j = 0; j < terminalsList.size(); j++){
            oneCell.clear();
            QString cell = document.read(i + 2, j + 2).toString();  //читаем ячейку
            for (int k = 0; k < cell.length(); k++){
                if ((cell[k] == '<' || cell[k] == '=') && !oneCell.contains(LESS_EQUAL)){
                    oneCell.append(LESS_EQUAL);
                }
                else if (cell[k] == '>') {
                    oneCell.append(MORE);
                }
            }

            oneString.insert(terminalsNumsList[j], oneCell);
        }




        matrixPrecedence.insert(lexImages.key(terminalsList[i]), oneString);    //добавляем строку

//        QMap<int, QList<int>> ptrString = matrixPrecedence.value(lexImages.key(terminalsList[i]));    //одна строка матрицы
//        //отладочный вывод
//        qDebug() << terminalsList[i];
//        qDebug() << "+++++++++++++";
//        for (int n = 0; n < terminalsNumsList.length(); n++){
//            foreach (int m, ptrString.value(terminalsNumsList[n])) {
//               qDebug() << terminalsList[n] << " " << m << " " <<lexImages.key(terminalsList[i]) << " " << terminalsNumsList[n];
//            }
//            qDebug() << "- - - - -";
//        }

    }


}
