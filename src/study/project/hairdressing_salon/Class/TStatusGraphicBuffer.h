#ifndef Status_H
#define Status_H
//-----------------------------------------------------------------------
// ||||  ||||
// TType TGraph
//-----------------------------------------------------------------------
enum TType{GraphType, MarkType, CounterType, SMenuType};
enum TGraph{Clear, Stay, BackMov, Mov};
//-----------------------------------------------------------------------
class TCol
{
   public:
      TCol(size_t);
      TCol();
      ~TCol();
      SetLength(size_t);
      bool CheckOdd(size_t);
      unsigned char &operator[] (size_t);
      unsigned char GetHalfByte(size_t);
      void SetTType(size_t, TType);
      void SetTGraph(size_t, TGraph);
      TType GetTType(size_t);
      TGraph GetTGraph(size_t);
      void Zero();
      size_t ColCount(){return (J * 2);}
   private:
      unsigned char *pPointer;
      size_t J;
      unsigned char Mask, ETypeMask, NETypeMask, EGraphMask, NEGraphMask;
};
//-----------------------------------------------------------------------
///Default Constructor
TCol :: TCol()
{
   pPointer = NULL;
   J = 0;
   Mask = 240;
   ETypeMask = 192;
   NETypeMask = 12;
   EGraphMask = 48;
   NEGraphMask = 3;
}
//-----------------------------------------------------------------------
//Constructor
TCol :: TCol(size_t size)
{
   pPointer = NULL;
   if (size != 0)
   {pPointer = new unsigned char[size]; J = size; Zero();}
}
//-----------------------------------------------------------------------
//Destructor
TCol :: ~TCol()
{
   if (pPointer != NULL)
      {delete []pPointer;
      pPointer = NULL;}
}
//-----------------------------------------------------------------------
//SetLength
TCol :: SetLength(size_t size)
{
   if (pPointer != NULL)
      {
         delete []pPointer;
         pPointer = NULL;
      }
   if (size != 0)
      {
          pPointer = new unsigned char[size];
          J = size;
          Zero();
      }
}
//-----------------------------------------------------------------------
//Check even
bool TCol :: CheckOdd(size_t Index)
{
   if ((Index % 2) == 0)
      {
         return true;
      }
   else
      {
         return false;
      }
}
//-----------------------------------------------------------------------
//Index
unsigned char &TCol :: operator[] (size_t Index)
{
   if (Index < J)
      return pPointer[Index];
   else
      {
         MessageDlg("Выход за пределы массива!!!\nПрограмма будет остановлена", mtError, TMsgDlgButtons() << mbOK, 0);
         Abort();
      }
}
//-----------------------------------------------------------------------
//Return the value
unsigned char TCol :: GetHalfByte(size_t Index)
{
   unsigned char Help;
   Help = 0;
   if ((Index / 2) <= J)
      {
         Help = pPointer[(Index / 2)];
         if (CheckOdd(Index))
            {
               Help &= Mask;
               Help >>= 4;
               return Help;
            }
         else
            {
               Help &= ~Mask;
               return Help;
            }
      }
   else
      Abort();
}
//-----------------------------------------------------------------------
void TCol :: Zero()
{
   for (size_t i = 0; i < J; i++)
      {
         pPointer[i] = 0;
      }
}
//-----------------------------------------------------------------------
//Set TType to half byte
void TCol  :: SetTType(size_t Index, TType Value)
{
   if ((Index / 2) <= J)
      {
         if (CheckOdd(Index))
            {
               pPointer[(Index / 2)] &= ~ETypeMask;
               Value <<= 6;
               pPointer[(Index / 2)] |= Value;
            }
         else
            {
               pPointer[(Index / 2)] &= ~NETypeMask;
               Value <<= 2;
               pPointer[(Index / 2)] |= Value;
            }
      }
   else
      {
         MessageDlg("Выход за пределы массива!!!", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//-----------------------------------------------------------------------
//Get TType from the half byte
TType TCol :: GetTType(size_t Index)
{
   unsigned char Help;
   if ((Index / 2) <= J)
         {
            Help = 0;
            Help = pPointer[(Index / 2)];
            if (CheckOdd(Index))
               {
                  Help &= ETypeMask;
                  Help >>= 6;
                  return (Help);
               }
            else
               {
                  Help &= NETypeMask;
                  Help >>= 2;
                  return (Help);
               }
         }
   else
      {
         MessageDlg("Выход за пределы массива!!!", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//-----------------------------------------------------------------------
//Set TGraph ti the half Byte
void TCol :: SetTGraph(size_t Index, TGraph Value)
{
   if ((Index / 2) <= J)
      {
         if (CheckOdd(Index))
            {
               pPointer[(Index / 2)] &= ~EGraphMask;
               Value <<= 4;
               pPointer[(Index / 2)] |= Value;
            }
         else
            {
               pPointer[(Index / 2)] &= ~NEGraphMask;
               pPointer[(Index / 2)] |= Value;
            }
      }
   else
      {
         MessageDlg("Выход за пределы массива!!!", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//-----------------------------------------------------------------------
TGraph TCol :: GetTGraph(size_t Index)
{
   unsigned char Help;
   if ((Index / 2) <= J)
         {
            Help = 0;
            Help = pPointer[(Index / 2)];
            if (CheckOdd(Index))
               {
                  Help &= EGraphMask;
                  Help >>= 4;
                  return (Help);
               }
            else
               {
                  Help &= NEGraphMask;
                  return (Help);
               }
         }
   else
      {
         MessageDlg("Выход за пределы массива!!!", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
class TStatusGraphicBuffer
{
   public:
      TStatusGraphicBuffer();
      TStatusGraphicBuffer(size_t, size_t);
      void SetLength(size_t, size_t);
      ~TStatusGraphicBuffer();
      TCol &operator[] (size_t);
      size_t RowCount(){return I;}
   private:
      TCol *pPointer;
      size_t I;
};
//-----------------------------------------------------------------------
TStatusGraphicBuffer :: TStatusGraphicBuffer()
{
   pPointer = NULL;
   I = 0;
}
//-----------------------------------------------------------------------
TStatusGraphicBuffer :: TStatusGraphicBuffer(size_t i, size_t j)
{
   pPointer = NULL;
   I = i;
   pPointer = new TCol[i];
   for (size_t k = 0; k < i; k++)
      {
         pPointer[k].SetLength(j);
      }
}
//-----------------------------------------------------------------------
TStatusGraphicBuffer :: ~TStatusGraphicBuffer()
{
   if (pPointer != NULL)
      {
         delete []pPointer;
         pPointer = NULL;
      }
}
//-----------------------------------------------------------------------
void TStatusGraphicBuffer :: SetLength(size_t i, size_t j)
{
   I = i;
   pPointer = new TCol[i];
   for (size_t k = 0; k < i; k++)
      {
         pPointer[k].SetLength(j);
      }
}
//-----------------------------------------------------------------------
TCol &TStatusGraphicBuffer :: operator[] (size_t Index)
{
   if (Index < I)
      return (pPointer[Index]);
   else
      {
         MessageDlg("Выход за пределы массива!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return (pPointer[0]);
      }
}
//-----------------------------------------------------------------------
#endif