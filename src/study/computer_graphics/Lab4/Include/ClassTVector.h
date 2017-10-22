#ifndef ClassTVectorH
#define ClassTVectorH
//--------------------------------------------------------------------
//����� ��� ����������� ������� ������������ �����
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
//����������
//--------------------------------------------------------------------
//�����������
TVector::TVector()
{
   Pointer = NULL;
   Init = false;
}
//����������
TVector::~TVector()
{
   Clear();
}
//-------------------------------------------------
//������� SetLength
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
//������� �������
unsigned short int TVector::Length(void)
   {
      return (Row);
   }
//-------------------------------------------------------------------------
//������� ��������
double TVector::GetValue(unsigned short int _R)
   {
      if ((_R + 1) <= Row) {return(Pointer[_R]);}
      else {ShowMessage("����� �� ������� �������"); return NULL;}
   }
//-------------------------------------------------------------------------
//��������� ��������
double &TVector::SetValue(unsigned short int _R)
   {
    if ((_R + 1) <= Row) {return (Pointer[_R]);}
    else {ShowMessage("����� �� ������� �������");}
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
         {/*/ShowMessage("������ �� ��� ������!!!");/*/ Init = false;}
   }
//-------------------------------------------------------------------------
#endif
