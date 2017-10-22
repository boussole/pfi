#ifndef ClassTMatrixH
#define ClassTMatrixH
#include <vcl.h>
/*/---------------------------------------------------------------------/*/
typedef unsigned short int UInt;
//-------------------------------------------------------------------------
//����� ��� ����������� ������� ������������ �����
class TMatrix
   {
      public:
         TMatrix();
         ~TMatrix();
         void SetLength(unsigned short int, unsigned short int);
         unsigned short int Length(void);
         double GetValue(unsigned short int, unsigned short int);
         double &SetValue(unsigned short int, unsigned short int);
         unsigned short int SizeI(void);
         unsigned short int SizeJ(void);
         void Clear();
      private:
         unsigned short int Row;
         unsigned short int Col;
         bool Init;
         double **Pointer;
   };
//------------------------------------------------
//����������
//------------------------------------------------
//�����������
TMatrix::TMatrix()
{
   Pointer = NULL;
   Init = false;
}
//------------------------------------------------
//����������
TMatrix::~TMatrix()
{
   Clear();
}
//-------------------------------------------------
//������� SetLength
void TMatrix::SetLength(unsigned short int _R, unsigned short int _C)
   {
      if (!Init)
      {
         Row = _R;
         Col = _C;
         Pointer = new double *[_R];
         for (int i = 0; i < _R; i++)
            {
               Pointer[i] = new double[_C];
            }
         Init = true;
      }
      else
      {
         Clear();
         SetLength(_R, _C);
      }
   }
//-------------------------------------------------
//������� �������
unsigned short int TMatrix::Length(void)
   {
      return (Row);
   }
//-------------------------------------------------------------------------
//������� ��������
double TMatrix::GetValue(unsigned short int _R, unsigned short int _C)
   {
      if (((_R + 1) <= Row) && ((_C + 1) <= Col)) {return(Pointer[_R][_C]);}
      else {ShowMessage("����� �� ������� ������� - ������� ��������"); return 0;}
   }
//-------------------------------------------------------------------------
//��������� ��������
double &TMatrix::SetValue(unsigned short int _R, unsigned short int _C)
   {
    if (((_R + 1) <= Row) && ((_C + 1) <= Col)) {return (Pointer[_R][_C]);}
    else {ShowMessage("����� �� ������� ������� - ��������� ��������");}
   }
//-------------------------------------------------------------------------
unsigned short int TMatrix::SizeI(void)
   {
      return Row;
   }
//-------------------------------------------------------------------------
unsigned short int TMatrix::SizeJ(void)
   {
      return Col;
   }
//-------------------------------------------------------------------------
//������� ������
void TMatrix::Clear()
   {
      if (Pointer != NULL)
         {
         for(int i = 0; i < Row; i++ )
            {
               delete []Pointer[i];
            }
            delete []Pointer;
            Pointer = NULL;
            Init = false;
         }
      else
         {/*/ShowMessage("������ �� ��� ������!!!");/*/ Init = false;}
   }
//-------------------------------------------------------------------------
#endif
