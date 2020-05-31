#include "treell.h"

TreeLL* TreeLL::Cur;
TreeLL* TreeLL::F;

TreeLL::TreeLL()        //по умолчанию - пустая вершина
{
    N = new Node ("", Node::semTypes::TypeEmpty);
    Right = Left = Parent = nullptr;
}

TreeLL::TreeLL(TreeLL *p, TreeLL *l, TreeLL *r, Node *n)
{
    N = n;
    Parent = p;
    Left = l;
    Right = r;
}

TreeLL::TreeLL(Node *n)
{
    N = n;
    Parent = nullptr;
    Left = nullptr;
    Right = nullptr;
}

void TreeLL::addLeft (Node *n)
{
    TreeLL *a = new TreeLL (this, nullptr, new TreeLL (), n);
    a->Right->Parent = a;    //родитель - текущая
    Left = a;
    //Cur = Left;
}
void TreeLL::addRight (Node *n)
{
    TreeLL *a = new TreeLL (this, nullptr, new TreeLL (), n);
    a->Right->Parent = a;        //родитель - текущая
    Right = a;
    //Cur = Right;
}

TreeLL *TreeLL::getRoot()
{
    TreeLL *cur = this->Cur;
    while (cur->Parent != nullptr) {
        cur = cur->Parent;
    }
    return cur;
}
 TreeLL *TreeLL::Find (TreeLL *From, Node* n)     //ищем во всем дереве вверх
{
    TreeLL *cur = From;
    while (cur != nullptr)
         if (n->Id != cur->N->Id || n->TypeObj != cur->N->TypeObj)    //объект таблицы не совпадает с заданным
            cur = cur->Parent;
         else break;
    return cur;
}

 TreeLL *TreeLL::Find (QString name)     //ищем во всем дереве вверх
{
    TreeLL *cur = this;
    while (cur != nullptr)
         if (cur->N->Id != name)    //имя объекта таблицы не совпадает с заданным
            cur = cur->Parent;
         else break;
    return cur;
}

 TreeLL *TreeLL::Find (Node* n)
{
    return Find (this, n);
}


 TreeLL *TreeLL::FindOneLevel (TreeLL *From, Node* n)         //ищем на одном уровне
{
    TreeLL *cur = From;
    while (cur != nullptr)               //пока не дошли до конца или до пустой вершины
        if (cur->Parent != nullptr)
            if (cur->Parent->Right == cur)      //правый потомок
                break;
            else
                 if (n->Id != cur->N->Id || n->TypeObj != cur->N->TypeObj)    //объект таблицы не совпадает с заданным
                    cur = cur->Parent;
                 else break;
        else cur = cur->Parent;
    if (cur != nullptr)
        if (n->Id != cur->N->Id || n->TypeObj != cur->N->TypeObj)
            cur = nullptr;
    return cur;
}

 TreeLL *TreeLL::FindOneLevel (Node* n)
{
     return FindOneLevel (this, n);
 }

 TreeLL *TreeLL::FindOneLevel(QString image)
 {
     TreeLL *cur = this;
     while (cur != nullptr)               //пока не дошли до конца или до пустой вершины
         if (cur->Parent != nullptr)
             if (cur->Parent->Right == cur)      //правый потомок
                 break;
             else
                  if (image != cur->N->Id)    //объект таблицы не совпадает с заданным
                     cur = cur->Parent;
                  else break;
         else cur = cur->Parent;
     if (cur != nullptr)
         if (image != cur->N->Id)
             cur = nullptr;
     return cur;
 }


 TreeLL *TreeLL::FindRightLeft (TreeLL *From, Node* n)        //ищем в правом ряду
{
    TreeLL *cur = From->Right;
    while (cur != nullptr)
         if (n->Id != cur->N->Id || n->TypeObj != cur->N->TypeObj)    //объект таблицы не совпадает с заданным
            cur = cur->Left;
         else break;
    return cur;
}

 TreeLL *TreeLL::FindRightLeft (Node* n)
{
     return FindRightLeft (this, n);
 }

 TreeLL *TreeLL::FindRightLeftNum(TreeLL *From, int num)
 {
     TreeLL *cur = From->Right;
     while (cur != nullptr && num > 0){
             cur = cur->Left;
             num--;
     }
     return cur;
 }

 int TreeLL::semType(Lexem *lex)      //семантический тип лексемы
{
     switch (lex->type)

     {
        case Tint:
         {
            return Node::semTypes::TypeInt;
         }
         case Tint8:
          {
             return Node::semTypes::TypeInt;
          }
         case Tint10:
          {
             return Node::semTypes::TypeInt;
          }
         case Tint16:
          {
             return Node::semTypes::TypeInt;
          }
         case Tchar:
          {
             return Node::semTypes::TypeChar;
          }
         case Tcchar:
          {
             return Node::semTypes::TypeChar;
          }
         case Tlong:
          {
             return Node::semTypes::TypeLong;
          }
         case Tmain:
          {
             return Node::semTypes::TypeMain;
          }
         case Tvoid:
          {
             return Node::semTypes::TypeVoid;
          }
         default:
             return Node::semTypes::TypeUnKnown;
     }
 }

 int TreeLL::semType(int type)
 {
     switch (type)

     {
        case Tint:
         {
            return Node::semTypes::TypeInt;
         }
         case Tint8:
          {
             return Node::semTypes::TypeInt;
          }
         case Tint10:
          {
             return Node::semTypes::TypeInt;
          }
         case Tint16:
          {
             return Node::semTypes::TypeInt;
          }
         case Tchar:
          {
             return Node::semTypes::TypeChar;
          }
         case Tcchar:
          {
             return Node::semTypes::TypeChar;
          }
         case Tlong:
          {
             return Node::semTypes::TypeLong;
          }
         case Tmain:
          {
             return Node::semTypes::TypeMain;
          }
         case Tvoid:
          {
             return Node::semTypes::TypeVoid;
          }
         default:
             return Node::semTypes::TypeUnKnown;
     }
 }

 bool TreeLL::idToTable (Node *n)  //проверка на дублирование, занесение идентификатора вместе с семантическим типом в таблицу
 {
    if (!Cur->FindOneLevel(n->Id))  //узла еще нет
    {
        Cur->addLeft(n);
        Cur = Cur->Left;
        return true;
    }
    else return false;      //дублирование

 }

bool TreeLL::semFToTable (QString name)       //занесение имени функции  в таблицу, создание пустой правой вершины. Устанавливает указатель на правую созданную
{
    Node *ptr = new Node (name, Node::semTypes::TypeFunc);  //создаем
    if (!Cur->Find(name))  //узла еще нет
    {
        Cur->addLeft(ptr);
        Cur = Cur->Left;
        F = Cur;                //указатель на функцию
        Cur = Cur->Right;       //переходим на пустую правую
        return true;
    }
    else return false;      //дублирование
}

void TreeLL::semRep ()     //восстановление указателя на вершину. Поднимаемся по левым связям и подн. на след уровень
{
    TreeLL *c = Cur;
    while (Cur != nullptr)  //пока не дошли до конца цепочки
        if (Cur->Parent != nullptr)
             if (Cur->Parent->Right != Cur)    //не правый потомок
                Cur = Cur->Parent;
             else break;
        else Cur = Cur->Parent;
    if (Cur != nullptr)             //указатель на родителя
            Cur = Cur->Parent;
}
void TreeLL::semToRight()        //добавить вершину справа
{
    Cur->addRight(new Node ("", Node::semTypes::TypeEmpty));     //пустая вершина
    Cur = Cur->Right;
}

void TreeLL::semInc (TreeLL *func)       //увеличить число параметров функции
{
    func->N->ParamCount++;
}
void TreeLL::semInc ()       //увеличить число параметров функции
{
    F->N->ParamCount++;
}

void TreeLL::semSetParAmount (TreeLL* f, int n)
{
    f->N->ParamCount = n;
}

void TreeLL::semError(std::string err, Lexem* L)
{
    QTextStream cout (stdout);

    cout.setCodec(QTextCodec::codecForName("cp866"));

    std::cout<<"\n Семантическая ошибка в "<<L->str<<":"<<L->pos<<": "<<err;
}

int TreeLL::semTypeRes (int o1, int o2)      //проверка результата операции
{
    if (o1 == Node::semTypes::TypeInt && o2 == Node::semTypes::TypeInt)
        return Node::semTypes::TypeInt;
    if (o1 == Node::semTypes::TypeLong && o2 == Node::semTypes::TypeLong)
        return Node::semTypes::TypeLong;
    if (o1 == Node::semTypes::TypeLong && o2 == Node::semTypes::TypeInt)
        return Node::semTypes::TypeLong;
    if (o1 == Node::semTypes::TypeChar && o2 == Node::semTypes::TypeChar)
        return Node::semTypes::TypeChar;
    if (o1 == Node::semTypes::TypeChar && o2 == Node::semTypes::TypeInt)
        return Node::semTypes::TypeChar;
    if (o1 == Node::semTypes::TypeInt && o2 == Node::semTypes::TypeChar)
        return Node::semTypes::TypeInt;
//    if (o1 != Node::semTypes::TypeUnKnown && o2 != Node::semTypes::TypeUnKnown)
//        semError("Несоответствие типов", l);
    return Node::semTypes::TypeUnKnown;
}
int TreeLL::semTypeResOnlyNum (int o1, int o2)      //проверка результата операции
{
    if (o1 == Node::semTypes::TypeInt && o2 == Node::semTypes::TypeInt)
        return Node::semTypes::TypeInt;
    if (o1 == Node::semTypes::TypeLong && o2 == Node::semTypes::TypeLong)
        return Node::semTypes::TypeLong;
    if (o1 == Node::semTypes::TypeLong && o2 == Node::semTypes::TypeInt)
        return Node::semTypes::TypeLong;
//    if (o1 != Node::semTypes::TypeUnKnown && o2 != Node::semTypes::TypeUnKnown)
//        semError("Несоответствие типов", l);
    return Node::semTypes::TypeUnKnown;
}

int TreeLL::semTypeResUn (int o1)      //проверка результата унарной операции
{
    if (o1 == Node::semTypes::TypeInt || o1 == Node::semTypes::TypeLong)
        return o1;
//    if (o1 != Node::semTypes::TypeUnKnown)
//        semError("Несоответствие типов", l);
    return Node::semTypes::TypeUnKnown;
}

void TreeLL::funcSetParamCount(int count)
{
     F->N->ParamCount = count;
}
