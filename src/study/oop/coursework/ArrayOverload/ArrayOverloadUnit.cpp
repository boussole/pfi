//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ArrayOverloadUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//���������� ����� �����
typedef int IntType[100][50];
typedef double DoubleType[100][50];
//---------------------------------------------------------------------------
//��������� �������
void ClearTable(TStringGrid *, TLabeledEdit *, TLabeledEdit *);
//������������� ������� ����������� ������� !!!
void Modify(IntType, unsigned short, unsigned short);
void Modify(DoubleType, unsigned short, unsigned short);
void Modify(int *, unsigned short, int, unsigned short);
void Modify(double *, unsigned short, double, unsigned short);
//������������� ������� ������ ������� �� �����
void PrintTable(TStringGrid *, IntType);
void PrintTable(TStringGrid *, DoubleType);
//---------------------------------------------------------------------------
//������� ������ �� ����� ������� (��� ����� �����)
void PrintTable(TStringGrid *Table, DoubleType _Array)
{
   for (int i = 0; i < Table->RowCount; i++)
   for (int j = 0; j < Table->ColCount; j++)
      {
         Table->Cells[j][i] = FloatToStr(_Array[i][j]);
      }
}
//---------------------------------------------------------------------------
//������� ������ �� ����� ������� (��� ������������)
void PrintTable(TStringGrid *Table, IntType _Array)
{
   for (int i = 0; i < Table->RowCount; i++)
   for (int j = 0; j < Table->ColCount; j++)
      {
         Table->Cells[j][i] = IntToStr(_Array[i][j]);
      }
}
//---------------------------------------------------------------------------
//������������� ������� ����������� ������� (��� ����� �����)
void Modify(int *_Array, unsigned short __C, int Value, unsigned short Index)
{
   //���� ����� �������������, �� ��������� ��� � ������
   if (Value < 0)
   {
      int Help = _Array[0], Current;
      for (int i = 0; i < __C; i++)
         {
            if (i == Index)
               {
                  _Array[i] = Help;
                  break;
               }
            else
               {
                  if (i == 0)
                     {
                        _Array[i] = Value;
                     }
                  else
                     {
                        Current = _Array[i];
                        _Array[i] = Help;
                        Help = Current;
                     }
               }
         }
   }
}
//---------------------------------------------------------------------------
//������������� ������� ����������� ������� (��� ����� �����)
void Modify(IntType Array, unsigned short _R, unsigned short _C)
{
   int u;
   for (int i = 0; i < _R; i++)
   for (int j = 0; j < _C; j++)
      {
         Modify(Array[i], _C, Array[i][j], j);
      }
}
//---------------------------------------------------------------------------
//������������� ������� ����������� ������� (��� ������������ �����)
void Modify(double *_Array, unsigned short __C, double Value, unsigned short Index)
{
   //���� ����� �������������, �� ��������� ��� � ������
   if (Value < 0)
   {
      double Help = _Array[0], Current;
      for (int i = 0; i < __C; i++)
         {
            if (i == Index)
               {
                  _Array[i] = Help;
                  break;
               }
            else
               {
                  if (i == 0)
                     {
                        _Array[i] = Value;
                     }
                  else
                     {
                        Current = _Array[i];
                        _Array[i] = Help;
                        Help = Current;
                     }
               }
         }
   }
}
//---------------------------------------------------------------------------
//������������� ������� ����������� ������� (��� ������������ �����)
void Modify(DoubleType Array, unsigned short _R, unsigned short _C)
{
   for (int i = 0; i < _R; i++)
   for (int j = 0; j < _C; j++)
      {
         Modify(Array[i], _C, Array[i][j], j);
      }
}
//---------------------------------------------------------------------------
//������� �������
void ClearTable(TStringGrid *Table, TLabeledEdit *EditRow, TLabeledEdit *EditCol)
{
   for (int i = 0; i < Table->RowCount; i++)
   for (int j = 0; j < Table->ColCount; j++)
      {
         Table->Cells[j][i] = "";
      }
   Table->RowCount = 2;
   Table->ColCount = 2;
   EditRow->Text = 2;
   EditCol->Text = 2;
}
//---------------------------------------------------------------------------
//������ "�����"
void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//������ "��������"
void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
   ClearTable(StringGrid1, LabeledEdit1, LabeledEdit2);
   ClearTable(StringGrid2, LabeledEdit1, LabeledEdit2);
}
//---------------------------------------------------------------------------
//+ ���� ������
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   if (StringGrid1->RowCount < 100)
   {StringGrid1->RowCount += 1; LabeledEdit1->Text = StringGrid1->RowCount;}
}
//---------------------------------------------------------------------------
//- ���� ������
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   if (StringGrid1->RowCount > 1)
   {StringGrid1->RowCount -= 1; LabeledEdit1->Text = StringGrid1->RowCount;}
}
//---------------------------------------------------------------------------
//+ ���� �������
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
   if (StringGrid2->ColCount < 50)
   {StringGrid1->ColCount += 1; LabeledEdit2->Text = StringGrid1->ColCount;}
}
//---------------------------------------------------------------------------
//- ���� �������
void __fastcall TMainForm::Button4Click(TObject *Sender)
{
   if (StringGrid2->ColCount > 1)
   {StringGrid1->ColCount -= 1; LabeledEdit2->Text = StringGrid1->ColCount;}
}
//---------------------------------------------------------------------------
//������ "��������� ��������� �����"
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   ClearTable(StringGrid1, LabeledEdit1, LabeledEdit2);
   LabeledEdit1->Text = IntToStr(rand() % 100);
   LabeledEdit2->Text = IntToStr(rand() % 50);
   StringGrid1->RowCount = StrToInt(LabeledEdit1->Text);
   StringGrid1->ColCount = StrToInt(LabeledEdit2->Text);
   for (int i = 0; i < StringGrid1->RowCount; i++)
   for (int j = 0; j < StringGrid1->ColCount; j++)
      {
         if (RadioButton1->Checked)
         StringGrid1->Cells[j][i] = IntToStr(rand() % 32786 - 16383);
         else
         StringGrid1->Cells[j][i] = FloatToStr( float(rand() % 32786) / float(1 + rand() % 2) - float(rand() % 16383));
      }
}
//---------------------------------------------------------------------------
//������ "���������"
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   ClearTable(StringGrid2, NULL, NULL);
   //��� ����������� �������
   int IntArray[100][50];       //����� �����
   double FloatArray[100][50];  //������������ �����
   //����������� �������
   unsigned short R, C;
   //-----------------------------------------------
   //���������� ��������
   try
      {
         R = StrToInt(LabeledEdit1->Text);
         C = StrToInt(LabeledEdit2->Text);
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� �������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if ((R > 100) || (R < 1) || (C > 50) || (C < 1))
      {
         MessageDlg("����������� ����� ������ ���� � ��������� [1 .. 100], � �������� [1 .. 50]", mtInformation, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   StringGrid2->RowCount = R;
   StringGrid2->ColCount = C;
   for (int i = 0; i < R; i++)
   for (int j = 0; j < C; j++)
      {
         //���������� ����� ����� �������
         if (RadioButton1->Checked)
            {
               try
                  {
                     IntArray[i][j] = StrToInt(StringGrid1->Cells[j][i]);
                  }
               catch (EConvertError &)
                  {
                     MessageDlg("������ � ��������� ����� � �������", mtError, TMsgDlgButtons() << mbOK, 0);
                     return;
                  }
            }
         //���������� ������������ ����� ������� 
         else
            {
               try
                  {
                     FloatArray[i][j] = StrToFloat(StringGrid1->Cells[j][i]);
                  }
               catch (EConvertError &)
                  {
                     MessageDlg("������ � ��������� ����� � �������", mtError, TMsgDlgButtons() << mbOK, 0);
                     return;
                  }
            }
      }
   switch (RadioButton1->Checked)
      {
         case 1:  Modify(IntArray, R, C);
                  PrintTable(StringGrid2, IntArray);
                  break;
         case 0:  Modify(FloatArray, R, C);
                  PrintTable(StringGrid2, FloatArray);
      }

}
//---------------------------------------------------------------------------
