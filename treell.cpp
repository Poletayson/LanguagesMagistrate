#include "treell.h"

TreeLL* TreeLL::Cur;
TreeLL* TreeLL::F;

TreeLL::TreeLL()        //по умолчанию - пустая вершина
{
    N = new Node ("", TypeEmpty);
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

 int TreeLL::semType(Lexem *lex)      //семантический тип лексемы
{
     switch (lex->type)

     {
        case Tint:
         {
            return TypeInt;
         }
     case Tint8:
      {
         return TypeInt;
      }
     case Tint10:
      {
         return TypeInt;
      }
     case Tint16:
      {
         return TypeInt;
      }
     case Tchar:
      {
         return TypeChar;
      }
     case Tcchar:
      {
         return TypeChar;
      }
     case Tlong:
      {
         return TypeLong;
      }
     case Tmain:
      {
         return TypeMain;
      }
     case Tvoid:
      {
         return TypeVoid;
      }
     default:
         return TypeUnKnown;
     }
}

 bool TreeLL::semToTable (Node *n)  //проверка на дублирование, занесение идентификатора вместе с семантическим типом в таблицу
 {
    if (!Cur->FindOneLevel(n))  //узла еще нет
    {
        Cur->addLeft(n);
        Cur = Cur->Left;
        return true;
    }
    else return false;      //дублирование

 }

bool TreeLL::semFToTable (QString name)       //занесение имени функции  в таблицу, создание пустой правой вершины. Устанавливает указатель на правую созданную
{
    Node *ptr = new Node (name, TypeFunc);  //создаем
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

void TreeLL::semRep ()     ///восстановление указателя на вершину. Поднимаемся по левым связям и подн. на след уровень
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
    Cur->addRight(new Node ("", TypeEmpty));     //пустая вершина
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

int TreeLL::semTypeRes (int o1, int o2, Lexem* l)      //проверка результата операции
{
    if (o1 == TypeInt && o2 == TypeInt)
        return TypeInt;
    if (o1 == TypeLong && o2 == TypeLong)
        return TypeLong;
    if (o1 == TypeLong && o2 == TypeInt)
        return TypeLong;
    if (o1 == TypeChar && o2 == TypeChar)
        return TypeChar;
    if (o1 == TypeChar && o2 == TypeInt)
        return TypeChar;
    if (o1 == TypeInt && o2 == TypeChar)
        return TypeInt;
    if (o1 != TypeUnKnown && o2 != TypeUnKnown)
        semError("Несоответствие типов", l);
    return TypeUnKnown;
}
int TreeLL::semTypeResOnlyNum (int o1, int o2, Lexem* l)      //проверка результата операции
{
    if (o1 == TypeInt && o2 == TypeInt)
        return TypeInt;
    if (o1 == TypeLong && o2 == TypeLong)
        return TypeLong;
    if (o1 == TypeLong && o2 == TypeInt)
        return TypeLong;
    if (o1 != TypeUnKnown && o2 != TypeUnKnown)
        semError("Несоответствие типов", l);
    return TypeUnKnown;
}

int TreeLL::semTypeResUn (int o1, Lexem* l)      //проверка результата унарной операции
{
    if (o1 == TypeInt || o1 == TypeLong)
        return o1;
    if (o1 != TypeUnKnown)
        semError("Несоответствие типов", l);
    return TypeUnKnown;
}
