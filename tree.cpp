#include "tree.h"

Tree* Tree::Cur;
Tree* Tree::F;

Tree::Tree()        //по умолчанию - пустая вершина
{
    N = new Node ("", TypeEmpty);
    Right = Left = Parent = nullptr;
}

Tree::Tree(Tree *p, Tree *l, Tree *r, Node *n)
{
    N = n;
    Parent = p;
    Left = l;
    Right = r;
}

Tree::Tree(Node *n)
{
    N = n;
    Parent = nullptr;
    Left = nullptr;
    Right = nullptr;
}

void Tree::addLeft (Node *n)
{
    Tree *a = new Tree (this, nullptr, new Tree (), n);
    a->Right->Parent = a;    //родитель - текущая
    Left = a;
    //Cur = Left;
}
void Tree::addRight (Node *n)
{
    Tree *a = new Tree (this, nullptr, new Tree (), n);
    a->Right->Parent = a;        //родитель - текущая
    Right = a;
    //Cur = Right;
}
 Tree *Tree::Find (Tree *From, Node* n)     //ищем во всем дереве вверх
{
    Tree *cur = From;
    while (cur != nullptr)
         if (n->Id != cur->N->Id || n->TypeObj != cur->N->TypeObj)    //объект таблицы не совпадает с заданным
            cur = cur->Parent;
         else break;
    return cur;
}

 Tree *Tree::Find (QString name)     //ищем во всем дереве вверх
{
    Tree *cur = this;
    while (cur != nullptr)
         if (cur->N->Id != name)    //имя объекта таблицы не совпадает с заданным
            cur = cur->Parent;
         else break;
    return cur;
}

 Tree *Tree::Find (Node* n)
{
    return Find (this, n);
}


 Tree *Tree::FindOneLevel (Tree *From, Node* n)         //ищем на одном уровне
{
    Tree *cur = From;
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

 Tree *Tree::FindOneLevel (Node* n)
{
    return FindOneLevel (this, n);
}


 Tree *Tree::FindRightLeft (Tree *From, Node* n)        //ищем в правом ряду
{
    Tree *cur = From->Right;
    while (cur != nullptr)
         if (n->Id != cur->N->Id || n->TypeObj != cur->N->TypeObj)    //объект таблицы не совпадает с заданным
            cur = cur->Left;
         else break;
    return cur;
}

 Tree *Tree::FindRightLeft (Node* n)
{
    return FindRightLeft (this, n);
}

 int Tree::semType(Lexem *lex)      //семантический тип лексемы
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

 bool Tree::semToTable (Node *n)  //проверка на дублирование, занесение идентификатора вместе с семантическим типом в таблицу
 {
    if (!Cur->FindOneLevel(n))  //узла еще нет
    {
        Cur->addLeft(n);
        Cur = Cur->Left;
        return true;
    }
    else return false;      //дублирование

 }

bool Tree::semFToTable (QString name)       //занесение имени функции  в таблицу, создание пустой правой вершины. Устанавливает указатель на правую созданную
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

void Tree::semRep ()     ///восстановление указателя на вершину. Поднимаемся по левым связям и подн. на след уровень
{
    Tree *c = Cur;
    while (Cur != nullptr)  //пока не дошли до конца цепочки
        if (Cur->Parent != nullptr)
             if (Cur->Parent->Right != Cur)    //не правый потомок
                Cur = Cur->Parent;
             else break;
        else Cur = Cur->Parent;
    if (Cur != nullptr)             //указатель на родителя
            Cur = Cur->Parent;
}
void Tree::semToRight()        //добавить вершину справа
{
    Cur->addRight(new Node ("", TypeEmpty));     //пустая вершина
    Cur = Cur->Right;
}

void Tree::semInc (Tree *func)       //увеличить число параметров функции
{
    func->N->ParamCount++;
}
void Tree::semInc ()       //увеличить число параметров функции
{
    F->N->ParamCount++;
}

void Tree::semSetParAmount (Tree* f, int n)
{
    f->N->ParamCount = n;
}

void Tree::semError(std::string err, Lexem* L)
{
    QTextStream cout (stdout);

    cout.setCodec(QTextCodec::codecForName("cp866"));

    std::cout<<"\n Семантическая ошибка в "<<L->str<<":"<<L->pos<<": "<<err;
}

int Tree::semTypeRes (int o1, int o2, Lexem* l)      //проверка результата операции
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
int Tree::semTypeResOnlyNum (int o1, int o2, Lexem* l)      //проверка результата операции
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

int Tree::semTypeResUn (int o1, Lexem* l)      //проверка результата унарной операции
{
    if (o1 == TypeInt || o1 == TypeLong)
        return o1;
    if (o1 != TypeUnKnown)
        semError("Несоответствие типов", l);
    return TypeUnKnown;
}
