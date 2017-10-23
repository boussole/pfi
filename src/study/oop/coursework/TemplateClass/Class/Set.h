#ifndef Set_H
#define Set_H
//------------------------------------------------------------------
//Определение шаблона класса
template <class T>
class TSet
   {
      //Открытые функции методы класса
      public:
         //Конструктор, создает пустое множество из n - элементов
         TSet(unsigned int);
         //Конструктор копировщик
         TSet(const TSet &);
         //Деструктор, удаляет множество из динамической памяти
         ~TSet();
         //Проверка на принадлежность множеству
         bool Check(T);
         //Распечатка множества
         AnsiString PrintSet();
         //Количество элементов в множестве
         unsigned int GetMax() {if (this != NULL) return Max;}
         //-------------------------------------------------------
         //Перегружаемые операторы
         //-----------------------
         //Операция объединения
         TSet<T> *operator +(TSet<T> &);
         //Операция пересечения
         TSet<T> *operator *(TSet<T> &);
         //Удаление элемента из множества
         void operator -(T);
         //Добавление элемента в множество
         void operator +(T);
         //Операция присвоения множеств
         TSet<T> &operator =(const TSet<T> &);
         //-------------------------------------------------------
      //Закрытые члены
      private:
         //Максимальное колиество
         int Max;
         //Количество в множестве
         unsigned int Current;
         //Массив
         bool *Set;
   };
//------------------------------------------------------------------
//Конструктор класса
template <class T>
TSet<T> :: TSet(unsigned int _Max)
{
   //Указание максимального значения
   Max = _Max;
   //Количество элементов в множестве, принадлежащих
   Current = 0;
   //Создание множества
   Set = new bool[Max];
   for (int i = 0; i < Max; i++)
      {
         Set[i] = false;
      }
}
//------------------------------------------------------------------
//Конструктор копировщик
template <class T>
TSet<T> :: TSet(const TSet &rhs)
{
   Max = rhs.Max;
   Current = rhs.Current;
   Set = new bool[Max];
   for (int i = 0; i < Max; i++)
      {
         Set[i] = rhs.Set[i];
      }
}
//------------------------------------------------------------------
//Деструктор класса
template <class T>
TSet<T> :: ~TSet()
{
   if (this != NULL)
   {
      Max = 0;
      Current = 0;
      //Уничтожение массива, моделирующего множество
      delete []Set;
      Set = NULL;
   }
}
//------------------------------------------------------------------
//Перегруженный оператор добавления элемента в множество
template <class T>
void TSet<T> :: operator+(T _Num)
{
   if (this != NULL)
   {
   unsigned int Help = int(_Num);
   if (Help >= Max)
      {
         MessageDlg("Выход за пределы множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (Set[Help] != true)
      {
         Set[Help] = true;
         Current++;
      }
   }
}
//------------------------------------------------------------------
//Перегруженный оператор удаления элемента из множества
template <class T>
void TSet<T> :: operator-(T _Num)
{
   if (this != NULL)
   {
   unsigned int Help = int(_Num);
   if (Help >= Max)
      {
         MessageDlg("Выход за пределы множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (Set[Help] != false)
      {
         Set[Help] = false;
         Current--;
      }
   }
}
//------------------------------------------------------------------
//Проверка на принадлежность множеству
template <class T>
bool TSet<T> :: Check(T _Num)
{
   if (this != NULL)
   {
   if (unsigned int(_Num) >= Max)
      {
         return false;
      }
   return Set[unsigned int(_Num)];
   }
}
//------------------------------------------------------------------
//Распечатка множества
template <class T>
AnsiString TSet<T> :: PrintSet()
{
   if (this != NULL)
   {
   AnsiString Help;
   unsigned Index = 0;
   Help += '{';
   for (int i = 0; i < Max; i++)
      {
            if (Set[i] == true)
            {
               Help += T(i);
               Index++;
               if (Index < Current)
                  Help += ", ";
            }
      }
   Help += '}';
   return Help;
   }
   else
      {
         MessageDlg("Множество не создано", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//------------------------------------------------------------------
//Присвоение множеств
template <class T>
TSet<T> &TSet<T> :: operator =(const TSet<T> &_rhs)
{
   if (&_rhs == NULL)
      {
         MessageDlg("Множество не создано", mtError, TMsgDlgButtons() << mbOK, 0);
         return *this;
      }
   //Попытка присвоить этот же объект самому себе
   if (&_rhs == this)
      {
         return *this;
      }
   //Присвоение объекта
   else
      {
         Max = _rhs.Max;
         Current = _rhs.Current;
         for (int i = 0; i < Max; i++)
         {
            Set[i] = _rhs.Set[i];
         }
         return *this;
      }
}
//------------------------------------------------------------------
//Операция объединения
template <class T>
TSet<T> *TSet<T> :: operator +(TSet<T> &rhs)
{
   if ((this != NULL) && (&rhs)!= NULL)
   {
      TSet<T> *temp = new TSet<T>(Max + rhs.Max);
      //Объединение множества 1
      for (int i = 0; i < this->Max; i++)
         {
            if ((this->Set[i]) && (!temp->Set[i]))
               {
                  temp->Set[i] = this->Set[i];
                  temp->Current++;
               }
         }
      //Объединение множества 2
      for (int i = 0; i < rhs.Max; i++)
         {
            if ((rhs.Set[i]) && (!temp->Set[i]))
               {
                  temp->Set[i] = rhs.Set[i];
                  temp->Current++;
               }
         }
      return temp;
   }
   else
   {
      if ((this == NULL) && (&rhs) == NULL)
         return NULL;
      if ((this != NULL) && (&rhs) == NULL)
         {
            TSet *temp = new TSet(*this);
            return temp;
         }
      if ((this == NULL) && (&rhs) != NULL)
         {
            TSet *temp = new TSet(rhs);
            return temp;
         }
   }
}
//------------------------------------------------------------------
//Пересечение множеств
template <class T>
TSet<T> *TSet<T> :: operator *(TSet<T> &rhs)
{
   if ((this != NULL) && (&rhs)!= NULL)
   {
      TSet<T> *temp = new TSet<T>(Max);
      for (int i = 0, j = 0; i < Max, j < rhs.Max; i++, j++)
         {
            if ( (this->Set[i]) && (rhs.Set[j]) && (i == j))
               {
                  temp->Set[i] = true;
                  temp->Current++;
               }
         }
      return temp;
   }
   else
   {
      if ((this == NULL) && (&rhs) == NULL)
         return NULL;
      if (
            ((this != NULL) && (&rhs) == NULL)
            ||
            ((this == NULL) && (&rhs) != NULL)
         )
         {
            MessageDlg("Невозможно построить пересечение множеств. Не хватает одного из множеств!!!", mtError, TMsgDlgButtons()<< mbOK, 0);
            return NULL;
         }
   }
}
//------------------------------------------------------------------
#endif
