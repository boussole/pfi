#ifndef ClassTVectorH
#define ClassTVectorH
//--------------------------------------------------------------------
//Класс для определения вектора произвольной длины
class TVector
   {
      public:
         TVector();
         ~TVector();
         void SetLength(unsigned short int);
         unsigned short int Length(void);
         double GetValue(unsigned short int);
         double &SetValue(unsigned short int);
         unsigned short int SizeI(void);
         void Clear();
      private:
         unsigned short int Row;
         double *Pointer;
         bool Init;
   };
//--------------------------------------------------------------------
//Реализация
//--------------------------------------------------------------------
//Конструктор
TVector::TVector()
{
   Pointer = NULL;
   Init = false;
}
//Деструктор
TVector::~TVector()
{
   Clear();
}
//-------------------------------------------------
//Функция SetLength
void TVector::SetLength(unsigned short int _R)
   {
      if (!Init)
         {
            Row = _R;
            Pointer = new double[Row];
            Init = true;
         }
      else
         {
            Clear();
            SetLength(_R);
         }
   }
//-------------------------------------------------
//Возврат порядка
unsigned short int TVector::Length(void)
   {
      return (Row);
   }
//-------------------------------------------------------------------------
//Возврат значения
double TVector::GetValue(unsigned short int _R)
   {
      if ((_R + 1) <= Row) {return(Pointer[_R]);}
      else {ShowMessage("Выход за границы массива"); return NULL;}
   }
//-------------------------------------------------------------------------
//Установка значения
double &TVector::SetValue(unsigned short int _R)
   {
    if ((_R + 1) <= Row) {return (Pointer[_R]);}
    else {ShowMessage("Выход за границы массива");}
   }
//-------------------------------------------------------------------------
unsigned short int TVector::SizeI(void)
   {
      return Row;
   }
//-------------------------------------------------------------------------
void TVector::Clear()
   {
      if (Pointer != NULL)
         {
            delete [] Pointer;
            Pointer = NULL;
            Init = false;
         }
      else
         {/*/ShowMessage("Объект не был создан!!!");/*/ Init = false;}
   }
//-------------------------------------------------------------------------
#endif
