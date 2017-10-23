//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SortArrayCode.h"
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
void Clear(TStringGrid *, TLabeledEdit *);
void Sort(int *, unsigned int, unsigned int);
void PrintTable(TStringGrid *, int *);
void Merge(int *_Array, unsigned int Left, unsigned int Split, unsigned int Right);
//---------------------------------------------------------------------------
//Функция сортировки
void Merge(int *_Array, unsigned int Left, unsigned int Split, unsigned int Right)
{
   unsigned int PosL = Left, PosR = Split + 1, PosTemp = 0;
   int *Temp = new int[Right - Left + 1];
   //Сравнение пока оба массива заполнены
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
   //Копирование остальных элементов
   while (PosL <= Split)
      {
         Temp[PosTemp++] = _Array[PosL++];
      }
   while (PosR <= Right)
      {
         Temp[PosTemp++] = _Array[PosR++];
      }
   //Копирование временного массива в основной
   PosL = Left;
   for (int PosTemp = 0; PosTemp < Right - Left + 1; PosTemp++)
      {
         _Array[PosL++] = Temp[PosTemp];
      }
   delete []Temp;
}
//---------------------------------------------------------------------------
//Функция распечатки массива
void PrintTable(TStringGrid *Table, int *_Array)
{
   for (int i = 0; i < Table->RowCount; i++)
      {
         Table->Cells[0][i] = _Array[i];
      }
}
//---------------------------------------------------------------------------
//Функция сортировки
void Sort(int *_Array, unsigned int L, unsigned int R)
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
//Функция очистки полей
void Clear(TStringGrid *Table, TLabeledEdit *Edit)
{
   for (int i = 0; i < Table->RowCount; i++)
      {
         Table->Cells[0][i] = "";
      }
   Table->RowCount = 2;
   Edit->Text = "2";
}
//---------------------------------------------------------------------------
//Конпка "выход"
void __fastcall TMainForm::ExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//Кнопка "Очистить"
void __fastcall TMainForm::ClearStringGridClick(TObject *Sender)
{
   Clear(StringGrid1, LabeledEdit1);
   Clear(StringGrid2, LabeledEdit1);
}
//---------------------------------------------------------------------------
//Кнопка "Сортировать"
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   int *Array;
   unsigned int Size;
   //Задание размерности
   try
      {
         Size = StrToInt(LabeledEdit1->Text);
      }
   catch(...)
      {
         MessageDlg("Ошибка написания числа размерности массива", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if ((Size <= 1) || (Size > 50))
      {
         MessageDlg("Размерность массива должна лежать в интервале [2 .. 50]", mtInformation, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   //Создание динамического массива
   Array = new int[Size];
   StringGrid2->RowCount = Size;
   for (int i = 0; i < Size; i++)
      {
         try
         {Array[i] = StrToInt(StringGrid1->Cells[0][i]);}
         catch(EConvertError&)
         {MessageDlg("Ошибка написания значения в таблице, возможно присутствуют пустые поля", mtError, TMsgDlgButtons() << mbOK, 0); goto Exit;}
      }
   //----------------
   Sort(Array, 0, Size - 1);
   PrintTable(StringGrid2, Array);
   Exit:
   //Удаление массива
   delete []Array;
}
//---------------------------------------------------------------------------
//Кнопка "ГСЧ"
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   LabeledEdit1->Text = 1 + rand() % 50;
   StringGrid1->RowCount = StrToInt(LabeledEdit1->Text);
   for (int i = 0; i < StringGrid1->RowCount; i++)
      {
         StringGrid1->Cells[0][i] = (rand() % 32768) - 16384;
      }
}
//---------------------------------------------------------------------------
//Добавление одной строчки в таблицу
void __fastcall TMainForm::AddTableClick(TObject *Sender)
{
   if (StringGrid1->RowCount < 50)
      {
         StringGrid1->RowCount = StringGrid1->RowCount + 1;
         LabeledEdit1->Text = StringGrid1->RowCount;
      }
}
//---------------------------------------------------------------------------
//Удаление лжглй строчки в таблице
void __fastcall TMainForm::DeleteTableClick(TObject *Sender)
{
   if (StringGrid1->RowCount > 2)
      {
         StringGrid1->Cells[0][StringGrid1->RowCount - 1] = "";
         StringGrid1->RowCount = StringGrid1->RowCount - 1;
         LabeledEdit1->Text = StringGrid1->RowCount;
      }
}
//---------------------------------------------------------------------------
