//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TemplateFunctionUnit.h"
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
//Прототипы
void ClearTable(TStringGrid *, TLabeledEdit *);
//---------------
//Функции шаблоны !!!!!!!!!!!!!
template <class T>
void Sort(T *, unsigned int, unsigned int);
template <class T>
void Merge(T *_Array, unsigned int Left, unsigned int Split, unsigned int Right);
template <class T>
void PrintTable(TStringGrid *, T *);
//---------------------------------------------------------------------------
//Функция слияния
template <class T>
void Merge(T *_Array, unsigned int Left, unsigned int Split, unsigned int Right)
{
   unsigned int PosL = Left, PosR = Split + 1, PosTemp = 0;
   T *Temp = new T[Right - Left + 1];
   while ((PosL <= Split) && (PosR <= Right))
      {
         if (_Array[PosL] < _Array[PosR])
            {
               Temp[PosTemp++] = _Array[PosL++];
            }
         else
            {
               Temp[PosTemp++] = _Array[PosR++];
            }
      }
   while (PosL <= Split)
      {
         Temp[PosTemp++] = _Array[PosL++];
      }
   while (PosR <= Right)
      {
         Temp[PosTemp++] = _Array[PosR++];
      }
   PosL = Left;
   for (int PosTemp = 0; PosTemp < Right - Left + 1; PosTemp++)
      {
         _Array[PosL++] = Temp[PosTemp];
      }
   delete []Temp;
}
//---------------------------------------------------------------------------
//Функция сортировки
template <class T>
void Sort(T *_Array, unsigned int L, unsigned int R)
{
   unsigned int Split;
   if (R > L)
      {
         Split = L + ((R - L) / 2);
         Sort(_Array, L, Split);
         Sort(_Array, Split + 1, R);
         Merge(_Array, L, Split, R);
      }
}
//---------------------------------------------------------------------------
//Функция распечатки массива
template <class T>
void PrintTable(TStringGrid *Table, T *_Array)
{
   for (int i = 0; i < Table->RowCount; i++)
      {
         Table->Cells[0][i] = T(_Array[i]);
      }
}
//-------------------------------------------------------------------------
//Функция очистки полей
void ClearTable(TStringGrid *Table, TLabeledEdit *Edit)
{
   for (int i = 0; i < Table->RowCount; i++)
      {
         Table->Cells[0][i] = "";
      }
   Table->RowCount = 2;
   Edit->Text = "2";
}
//---------------------------------------------------------------------------
//Увеличение на единицу ячеек
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   if (StringGrid1->RowCount < 50)
      {
         StringGrid1->RowCount += 1;
         LabeledEdit1->Text = StringGrid1->RowCount;
      }
}
//---------------------------------------------------------------------------
//Уменьшение на единицу ячеек
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   if (StringGrid1->RowCount > 1)
      {
         StringGrid1->Cells[0][StringGrid1->RowCount - 1] = "";
         StringGrid1->RowCount -= 1;
         LabeledEdit1->Text = StringGrid1->RowCount;
      }
}
//---------------------------------------------------------------------------
//Кнопка "Выход"
void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//Кнопка очистить
void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
   ClearTable(StringGrid1, LabeledEdit1);
   ClearTable(StringGrid2, LabeledEdit1);
}
//---------------------------------------------------------------------------
//Генератор случайных чисел
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   ClearTable(StringGrid2, LabeledEdit1);
   LabeledEdit1->Text = 1 + rand() % 50;
   StringGrid1->RowCount = StrToInt(LabeledEdit1->Text);
   for (int i = 0; i < StringGrid1->RowCount; i++)
      {
         if (RadioButton1->Checked)
            {
               StringGrid1->Cells[0][i] = (rand() % 32768) - 16384;
            }
         if (RadioButton2->Checked)
            {
               StringGrid1->Cells[0][i] = float((rand() % 32768) / float(1.1 + rand() % 3)) - rand() % 16384;
            }
         if (RadioButton3->Checked)
            {
               StringGrid1->Cells[0][i] = char(32 + rand() % 95);
            }
      }
}
//---------------------------------------------------------------------------
//Кнопка "Выполнить"
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   int *IntArray;
   double *FloatArray;
   char *CharArray;
   unsigned int Size;
   //Присвоение размерности
   try
      {
         Size = StrToInt(LabeledEdit1->Text);
      }
   catch(...)
      {
         MessageDlg("Ошибка написания размерности массива", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   StringGrid1->RowCount = Size;
   if ((Size <= 1) || (Size > 50))
      {
         MessageDlg("Количество строк должно лежать в интервале [2 .. 50]", mtInformation, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (RadioButton1->Checked)
      {IntArray = new int[Size];}
   if (RadioButton2->Checked)
      {FloatArray = new double[Size];}
   if (RadioButton3->Checked)
      {CharArray = new char[Size];}
   //Создание массива
   StringGrid2->RowCount = Size;
   for (int i = 0; i < Size; i++)
      {
         //Присвоение целых чисел
         if (RadioButton1->Checked)
            {
               try
               {IntArray[i] = StrToInt(StringGrid1->Cells[0][i]);}
               catch(EConvertError&)
               {MessageDlg("Ошибка написания целого числа в таблице", mtError, TMsgDlgButtons() << mbOK, 0); goto Exit;}
            }
         //Присвоение вещественных чисел
         if (RadioButton2->Checked)
            {
               try
               {FloatArray[i] = StrToFloat(StringGrid1->Cells[0][i]);}
               catch(EConvertError&)
               {MessageDlg("Ошибка написания вещественного числа в таблице", mtError, TMsgDlgButtons() << mbOK, 0); goto Exit;}
            }
         //Присвоение символов
         if (RadioButton3->Checked)
            {
               CharArray[i] = (StringGrid1->Cells[0][i])[1];
            }
      }
   //----------------
   if (RadioButton1->Checked)
      {Sort(IntArray, 0, Size - 1); PrintTable(StringGrid2, IntArray);}
   if (RadioButton2->Checked)
      {Sort(FloatArray, 0, Size - 1); PrintTable(StringGrid2, FloatArray);}
   if (RadioButton3->Checked)
      {Sort(CharArray, 0, Size - 1); PrintTable(StringGrid2, CharArray);}
   Exit:
   if (RadioButton1->Checked)
      {delete []IntArray;}
   if (RadioButton2->Checked)
      {delete []FloatArray;}
   if (RadioButton3->Checked)
      {delete []CharArray;}
}
//---------------------------------------------------------------------------
