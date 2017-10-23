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
//Деструктор класса
TSet :: ~TSet()
{
   Max = 0;
   Current = 0;
   //Уничтожение массива, моделирующего множество
   delete []Set;
   Set = NULL;
}
//------------------------------------------------------------------
//Доавление элемента в множество
void TSet :: AddElement(unsigned int _Num)
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
//------------------------------------------------------------------
//Удаление элемента из множества
void TSet :: DelElement(unsigned int _Num)
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
//------------------------------------------------------------------
//Проверка на принадлежность монжеству
bool TSet :: Check(unsigned int _Num)
{
   if (_Num >= Max)
      {
         return false;
      }
   return Set[_Num];
}
//------------------------------------------------------------------
//Распечатка множества
AnsiString TSet :: PrintSet()
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
//------------------------------------------------------------------
#endif