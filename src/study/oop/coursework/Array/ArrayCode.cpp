//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "ArrayCode.h"
#include "Class\\ClassTMatrix.h"
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
//���������� ����������
bool GSCH;
namespace SizeArr
   {
      unsigned int Row;
      unsigned int Col;
   }
//---------------------------------------------------------------------------
//��������� �������
void Clear(TStringGrid *);
void PrintTable(TStringGrid *, TMatrix *);
void Order(TMatrix *);
void InsertBegin(TMatrix *, int, unsigned int, unsigned int);
void InsertEnd(TMatrix *, int, unsigned int, unsigned int);
//---------------------------------------------------------------------------
//�����
void __fastcall TMainForm::ButtonExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//��������� ���
void __fastcall TMainForm::RadioButton1Click(TObject *Sender)
{
   if (RadioButton1->Checked)
      {
         LabeledEdit1->ReadOnly = true;
         LabeledEdit1->Color = clSilver;
         LabeledEdit2->ReadOnly = true;
         LabeledEdit2->Color = clSilver;
         GSCH = true;
      }
}
//---------------------------------------------------------------------------
//������ �����
void __fastcall TMainForm::RadioButton2Click(TObject *Sender)
{
   if (RadioButton2->Checked)
      {
         LabeledEdit1->ReadOnly = false;
         LabeledEdit1->Color = clWhite;
         LabeledEdit2->ReadOnly = false;
         LabeledEdit2->Color = clWhite;
         GSCH = false;
      }
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   GSCH = true;
}
//---------------------------------------------------------------------------
//������� ������� �������
void Clear(TStringGrid *Table)
{
   for (int i = 0; i < Table->RowCount; i++)
   for (int j = 0; j < Table->ColCount; j++)
      {
         Table->Cells[j][i] = "";
      }
   Table->RowCount = 2;
   Table->ColCount = 2;
}
//---------------------------------------------------------------------------
//������� ��������� �������
void PrintTable(TStringGrid *Table, TMatrix *_Array)
{
   Table->RowCount = _Array->SizeI();
   Table->ColCount = _Array->SizeJ();
   for (int i = 0; i < _Array->SizeI(); i++)
   for (int j = 0; j < _Array->SizeJ(); j++)
      {
         Table->Cells[j][i] = _Array->GetValue(i, j);
      }
}
//---------------------------------------------------------------------------
//�������������� �������
void __fastcall TMainForm::ButtonDoClick(TObject *Sender)
{
   //������� �����
//   Clear(SourceArray);
   Clear(FinalArray);
   TMatrix *Array;
   //������ � ������ ���
   if (GSCH)
      {
         SizeArr :: Row = 1 + rand() % 100;
         SizeArr :: Col = 1 + rand() % 50;
         LabeledEdit1->Text = SizeArr :: Row;
         LabeledEdit2->Text = SizeArr :: Col;
         Array = new TMatrix();
         Array->SetLength(SizeArr :: Row, SizeArr :: Col);
         for (int i = 0; i < SizeArr :: Row; i++)
         for (int j = 0; j < SizeArr :: Col; j++)
            {
               Array->SetValue(i, j) = rand() - 16383;
            }
         PrintTable(SourceArray, Array);
         Order(Array);
         PrintTable(FinalArray, Array);
         delete Array;
         Array = NULL;
      }
   //������ �����
   else
      {
         try
            {
               SizeArr :: Row = StrToInt(LabeledEdit1->Text);
               SizeArr :: Col = StrToInt(LabeledEdit2->Text);
            }
         catch (...)
            {
               Application->MessageBoxA("            ������ ��������� �����", "��������� ����������� �������");
               return;
            }
         if (
               (SizeArr :: Row <= 0) || (SizeArr :: Row > 100) || (SizeArr :: Col <= 0) || (SizeArr :: Col >50)
            )
            {
               Application->MessageBoxA("      ������ � �������� �����������", "��������� ����������� �������");
            }
         Array = new TMatrix();
         Array->SetLength(SizeArr :: Row, SizeArr :: Col);
         for (int i = 0; i < SizeArr :: Row; i++)
         for (int j = 0; j < SizeArr :: Col; j++)
            {
               try
               {Array->SetValue(i, j) = StrToFloat(SourceArray->Cells[j][i]);}
               catch (...)
               {
                  Application->MessageBoxA("������ ��������� �������� � ������� (�������� ��������� �� ��� ����)", "��������", MB_OK);
                  goto Exit;
               }
            }
         PrintTable(SourceArray, Array);
         Order(Array);
         PrintTable(FinalArray, Array);
         Exit:
         delete Array;
         Array = NULL;
      }
}
//---------------------------------------------------------------------------
//������� ���� �����
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   Clear(SourceArray);
   Clear(FinalArray);
   LabeledEdit1->Text = 2;
   LabeledEdit2->Text = 2;
}
//---------------------------------------------------------------------------
//��������� ������� ����� - ���������� �����
void __fastcall TMainForm::LabeledEdit1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if ((!GSCH) && (LabeledEdit1->Text != ""))
   {
   try
   {SourceArray->RowCount = StrToInt(LabeledEdit1->Text);}
   catch (...)
   {Application->MessageBoxA("             �������� ��������", "������� ���������� �����", MB_OK);}
   }
}
//---------------------------------------------------------------------------
//��������� ������� ����� - ���������� ��������
void __fastcall TMainForm::LabeledEdit2KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if ((!GSCH) && (LabeledEdit2->Text != ""))
   {
   try
   {SourceArray->ColCount = StrToInt(LabeledEdit2->Text);}
   catch(...)
   {Application->MessageBoxA("             �������� ��������", "������� ���������� ��������", MB_OK);}
   }
}
//---------------------------------------------------------------------------
//�������������� �������
void Order(TMatrix *Matrix)
{
   for (int i = 0; i < Matrix->SizeI(); i++)
   for (int j = 0; j < Matrix->SizeJ(); j++)
      {
         if (Matrix->GetValue(i, j) < 0)
            {
               InsertBegin(Matrix, Matrix->GetValue(i, j), i, j);
            }
      //else
      //    {
      //� ������ ������ ������ ������������ ��� ������, ������ ����.
      //       InsertEnd(Matrix, Matrix->GetValue(i, j), i, j);
      //    }
      }
}
//---------------------------------------------------------------------------
//������� � ������
void InsertBegin(TMatrix *_Matrix, int Value, unsigned int _Row, unsigned int _Col)
{
   int Prev = _Matrix->GetValue(0, 0);
   int Current;
   for (int i = 0; i < _Matrix->SizeI(); i++)
   for (int j = 0; j < _Matrix->SizeJ(); j++)
      {
      if ((i == _Row) && (j == _Col))
            {
               //���������� ��������� �������� ������� (�����)
               _Matrix->SetValue(i, j) = Prev;
               return;
            }
       else
            {
               //������� ����� � ������
               if ((i == 0) && (j == 0))
                  {
                     _Matrix->SetValue(0, 0) = Value;
                  }
               //���������� ������������� �������
               else
                  {
                     Current = _Matrix->GetValue(i, j);
                     _Matrix->SetValue(i, j) = Prev;
                     Prev = Current;
                  }
            }
      }
}
//---------------------------------------------------------------------------
//������� � �����
void InsertEnd(TMatrix *_Matrix, int Value, unsigned int _Row, unsigned int _Col)
{
   int Next = _Matrix->GetValue(_Matrix->SizeI() - 1, _Matrix->SizeJ() - 1);
   int Current;
   for (int i = _Matrix->SizeI() - 1; i >= 0; i--)
   for (int j = _Matrix->SizeJ() - 1; j >= 0; j--)
      {
      if ((i == _Row) && (j == _Col))
            {
               //���������� ��������� �������� ������� (�����)
               _Matrix->SetValue(i, j) = Next;
               return;
            }
       else
            {
               //������� ����� � �����
               if ((i == _Matrix->SizeI() - 1) && (j == _Matrix->SizeJ() - 1))
                  {
                     _Matrix->SetValue(_Matrix->SizeI() - 1, _Matrix->SizeJ() - 1) = Value;
                  }
               //���������� ������������� �������
               else
                  {
                     Current = _Matrix->GetValue(i, j);
                     _Matrix->SetValue(i, j) = Next;
                     Next = Current;
                  }
            }
      }
}
//---------------------------------------------------------------------------
