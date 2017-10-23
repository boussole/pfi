#ifndef Set_H
#define Set_H
//------------------------------------------------------------------
//����������� ������
class TSet
   {
      //�������� ������� ������ ������
      public:
         //�����������, ������� ������ ��������� �� n - ���������
         TSet(unsigned int);
         //����������� ����������
         TSet(const TSet &);
         //����������, ������� ��������� �� ������������ ������
         ~TSet();
         //���������� �������� � ���������
         void AddElement(unsigned int);
         //�������� �������� �� ���������
         void DelElement(unsigned int);
         //�������� �� �������������� ���������
         bool Check(unsigned int);
         //���������� ���������
         AnsiString PrintSet();
         //���������� ��������� � ���������
         unsigned int GetMax() {if (this != NULL) return Max;}
         //-------------------------------------------------------
         //������������� ���������
         //-----------------------
         //�������� �����������
         TSet *operator +(TSet &);
         //�������� �����������
         TSet *operator *(TSet &);
         //�������� �������� �� ���������
         void operator -(unsigned int);
         //���������� �������� � ���������
         void operator +(unsigned int);
         //�������� ���������� ��������
         TSet &operator =(const TSet &);
         //-------------------------------------------------------
      //�������� �����
      private:
         //������������ ���������
         int Max;
         //���������� � ���������
         unsigned int Current;
         //������
         bool *Set;
   };
//------------------------------------------------------------------
//����������� ������
TSet :: TSet(unsigned int _Max)
{
   //�������� ������������� ��������
   Max = _Max;
   //���������� ��������� � ���������, �������������
   Current = 0;
   //�������� ���������
   Set = new bool[Max];
   for (int i = 0; i < Max; i++)
      {
         Set[i] = false;
      }
}
//------------------------------------------------------------------
//����������� ����������
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
//���������� ������
TSet :: ~TSet()
{
   if (this != NULL)
   {
      Max = 0;
      Current = 0;
      //����������� �������, ������������� ���������
      delete []Set;
      Set = NULL;
   }
}
//------------------------------------------------------------------
//������������� �������� ���������� �������� � ���������
void TSet :: operator+(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("����� �� ������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
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
//���������� �������� � ���������
void TSet :: AddElement(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("����� �� ������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
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
//������������� �������� �������� �������� �� ���������
void TSet :: operator-(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("����� �� ������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
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
//�������� �������� �� ���������
void TSet :: DelElement(unsigned int _Num)
{
   if (this != NULL)
   {
   if (_Num >= Max)
      {
         MessageDlg("����� �� ������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
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
//�������� �� �������������� ���������
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
//���������� ���������
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
         MessageDlg("��������� �� �������", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//------------------------------------------------------------------
//���������� ��������
TSet &TSet :: operator =(const TSet &_rhs)
{
   if (&_rhs == NULL)
      {
         MessageDlg("��������� �� �������", mtError, TMsgDlgButtons() << mbOK, 0);
         return *this;
      }
   //������� ��������� ���� �� ������ ������ ����
   if (&_rhs == this)
      {
         return *this;
      }
   //���������� �������
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
//�������� �����������
TSet *TSet :: operator +(TSet &rhs)
{
   if ((this != NULL) && (&rhs)!= NULL)
   {
      TSet *temp = new TSet(Max + rhs.Max);
      //����������� ��������� 1
      for (int i = 0; i < this->Max; i++)
         {
            if ((this->Set[i]) && (!temp->Set[i]))
               {
                  temp->Set[i] = this->Set[i];
                  temp->Current++;
               }
         }
      //����������� ��������� 2
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
//����������� ��������
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
            MessageDlg("���������� ��������� ����������� ��������. �� ������� ������ �� ��������!!!", mtError, TMsgDlgButtons()<< mbOK, 0);
            return NULL;
         }
   }
}
//------------------------------------------------------------------
#endif
