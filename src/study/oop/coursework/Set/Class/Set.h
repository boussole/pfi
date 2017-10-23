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
//���������� ������
TSet :: ~TSet()
{
   Max = 0;
   Current = 0;
   //����������� �������, ������������� ���������
   delete []Set;
   Set = NULL;
}
//------------------------------------------------------------------
//��������� �������� � ���������
void TSet :: AddElement(unsigned int _Num)
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
//------------------------------------------------------------------
//�������� �������� �� ���������
void TSet :: DelElement(unsigned int _Num)
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
//------------------------------------------------------------------
//�������� �� �������������� ���������
bool TSet :: Check(unsigned int _Num)
{
   if (_Num >= Max)
      {
         return false;
      }
   return Set[_Num];
}
//------------------------------------------------------------------
//���������� ���������
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