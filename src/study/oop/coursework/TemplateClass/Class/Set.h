#ifndef Set_H
#define Set_H
//------------------------------------------------------------------
//����������� ������� ������
template <class T>
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
         //�������� �� �������������� ���������
         bool Check(T);
         //���������� ���������
         AnsiString PrintSet();
         //���������� ��������� � ���������
         unsigned int GetMax() {if (this != NULL) return Max;}
         //-------------------------------------------------------
         //������������� ���������
         //-----------------------
         //�������� �����������
         TSet<T> *operator +(TSet<T> &);
         //�������� �����������
         TSet<T> *operator *(TSet<T> &);
         //�������� �������� �� ���������
         void operator -(T);
         //���������� �������� � ���������
         void operator +(T);
         //�������� ���������� ��������
         TSet<T> &operator =(const TSet<T> &);
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
template <class T>
TSet<T> :: TSet(unsigned int _Max)
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
//���������� ������
template <class T>
TSet<T> :: ~TSet()
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
template <class T>
void TSet<T> :: operator+(T _Num)
{
   if (this != NULL)
   {
   unsigned int Help = int(_Num);
   if (Help >= Max)
      {
         MessageDlg("����� �� ������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
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
//������������� �������� �������� �������� �� ���������
template <class T>
void TSet<T> :: operator-(T _Num)
{
   if (this != NULL)
   {
   unsigned int Help = int(_Num);
   if (Help >= Max)
      {
         MessageDlg("����� �� ������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
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
//�������� �� �������������� ���������
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
//���������� ���������
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
         MessageDlg("��������� �� �������", mtError, TMsgDlgButtons() << mbOK, 0);
      }
}
//------------------------------------------------------------------
//���������� ��������
template <class T>
TSet<T> &TSet<T> :: operator =(const TSet<T> &_rhs)
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
template <class T>
TSet<T> *TSet<T> :: operator +(TSet<T> &rhs)
{
   if ((this != NULL) && (&rhs)!= NULL)
   {
      TSet<T> *temp = new TSet<T>(Max + rhs.Max);
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
            MessageDlg("���������� ��������� ����������� ��������. �� ������� ������ �� ��������!!!", mtError, TMsgDlgButtons()<< mbOK, 0);
            return NULL;
         }
   }
}
//------------------------------------------------------------------
#endif
