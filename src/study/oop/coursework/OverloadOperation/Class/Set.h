#ifndef Set_H
#define Set_H
//------------------------------------------------------------------
//Определение класса
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
         //Добавление элемента в множество
         void AddElement(unsigned int);
         //Удаление элемента из множества
         void DelElement(unsigned int);
         //Проверка на принадлежность множеству
         bool Check(unsigned int);
         //Распечатка множества
         AnsiString PrintSet();
         //Количество элементов в множестве
         unsigned int GetMax() {if (this != NULL) return Max;}
         //-------------------------------------------------------
         //Перегружаемые операторы
         //-----------------------
         //Операция объединения
         TSet *operator +(TSet &);
         //Операция пересечения
         TSet *operator *(TSet &);
         //Удаление элемента из множества
         void operator -(unsigned int);
         //Добавление элемента в множество
         void operator +(unsigned int);
         //Операция присвоения множеств
         TSet &operator =(const TSet &);
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
TSet :: TSet(unsigned int _Max)
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
TSet :: TSet(const TSet &rhs)
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
TSet :: ~TSet()
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
void TSet :: operator+(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("Выход за пределы множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (Set[_Num] != true)
      {
         Set[_Num] = true;
         Current++;
      }
   }
}
//------------------------------------------------------------------
//Добавление элемента в множество
void TSet :: AddElement(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("Выход за пределы множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (Set[_Num] != true)
      {
         Set[_Num] = true;
         Current++;
      }
   }
}
//------------------------------------------------------------------
//Перегруженный оператор удаления элемента из множества
void TSet :: operator-(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("Выход за пределы множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (Set[_Num] != false)
      {
         Set[_Num] = false;
         Current--;
      }
   }
}
//------------------------------------------------------------------
//Удаление элемента из множества
void TSet :: DelElement(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("Выход за пределы множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (Set[_Num] != false)
      {
         Set[_Num] = false;
         Current--;
      }
   }
}
//------------------------------------------------------------------
//Проверка на принадлежность монжеству
bool TSet :: Check(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         return false;
      }
   return Set[_Num];
   }
}
//------------------------------------------------------------------
//Распечатка множества
AnsiString TSet :: PrintSet()
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
               Help += i;
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
TSet &TSet :: operator =(const TSet &_rhs)
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
TSet *TSet :: operator +(TSet &rhs)
{
   if ((this != NULL) && (&rhs)!= NULL)
   {
      TSet *temp = new TSet(Max + rhs.Max);
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
TSet *TSet :: operator *(TSet &rhs)
{
   if ((this != NULL) && (&rhs)!= NULL)
   {
      TSet *temp = new TSet(Max);
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
