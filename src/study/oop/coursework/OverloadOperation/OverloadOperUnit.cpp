//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "OverloadOperUnit.h"
#include "Class\\Set.h"
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
//Глобальные указатели на множество
TSet *Set_1, *Set_2, *Set_3;
//---------------------------------------------------------------------------
//Создание формы
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   Set_1 = NULL;
   Set_2 = NULL;
   Set_3 = NULL;   
}
//---------------------------------------------------------------------------
//Уничтожение формы
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   if (Set_1 != NULL)
      {
         delete Set_1;
         Set_1 = NULL;
      }
   if (Set_2 != NULL)
      {
         delete Set_2;
         Set_2 = NULL;
      }
   if (Set_3 != NULL)
      {
         delete Set_3;
         Set_3 = NULL;
      }
}
//---------------------------------------------------------------------------
//Создание множества 1
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
         if (MessageDlg("Область памяти занята другим множеством. Освободить память ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_1;
               Set_1 = NULL;
            }
         else
            {
               MessageDlg("Новое множество создано не было", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit1->Text) <= 0)
            {
               MessageDlg("Размерность множества должна быть положительной!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("Ошибка в написании размерности множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      Set_1 = new TSet(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
//Распечатка множества 1
void __fastcall TMainForm::BitBtn5Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
         Edit5->Text = Set_1->PrintSet();
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Проверка числа на принадлежность множеству 1
void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
      try
         {
            if (Set_1->Check(StrToInt(Edit3->Text)))
               {
                  Application->MessageBoxA("              Число принадлежит множеству", "Проверка на принадлежность множеству", MB_OK);
               }
            else
               {
                  Application->MessageBoxA("              Число не принадлежит множеству", "Проверка на принадлежность множеству", MB_OK);
               }
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа проверяемого на принадлежность множеству", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Создание множества 2
void __fastcall TMainForm::BitBtn6Click(TObject *Sender)
{
if (Set_2 != NULL)
      {
         if (MessageDlg("Область памяти занята другим множеством. Освободить память ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_2;
               Set_2 = NULL;
            }
         else
            {
               MessageDlg("Новое множество создано не было", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit6->Text) <= 0)
            {
               MessageDlg("Размерность множества должна быть положительной!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("Ошибка в написании размерности множества", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      Set_2 = new TSet(StrToInt(Edit6->Text));
}
//---------------------------------------------------------------------------
//Распечатка множества 2
void __fastcall TMainForm::BitBtn10Click(TObject *Sender)
{
   if (Set_2 != NULL)
      {
         Edit10->Text = Set_2->PrintSet();
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Проверка на принадлежность числа множеству 2
void __fastcall TMainForm::BitBtn8Click(TObject *Sender)
{
   if (Set_2 != NULL)
      {
      try
         {
            if (Set_2->Check(StrToInt(Edit8->Text)))
               {
                  Application->MessageBoxA("              Число принадлежит множеству", "Проверка на принадлежность множеству", MB_OK);
               }
            else
               {
                  Application->MessageBoxA("              Число не принадлежит множеству", "Проверка на принадлежность множеству", MB_OK);
               }
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа проверяемого на принадлежность множеству", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Добавление элемента множеству 1
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
      try
         {
            (*Set_1) + StrToInt(Edit2->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа добавляемого в  множество", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Удаление элемента из множества 1
void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
if (Set_1 != NULL)
      {
      try
         {
            (*Set_1) - StrToInt(Edit4->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа, удаляемого из множества", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Добавить числа из множества 2
void __fastcall TMainForm::BitBtn7Click(TObject *Sender)
{
   if (Set_2 != NULL)
      {
      try
         {
            (*Set_2) + StrToInt(Edit7->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа добавляемого в  множество", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Удаление элемента из множества
void __fastcall TMainForm::BitBtn9Click(TObject *Sender)
{
   if (Set_2 != NULL)
      {
      try
         {
            (*Set_2) - StrToInt(Edit9->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа, удаляемого из множества", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Присвоение множеству 3 = множество 1
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("Множество 3 уже содержит данные. Желаете очистить эти данные?", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("Множество создано не было !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = new TSet(Set_1->GetMax());
   *Set_3 = *Set_1;
   Edit11->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------
//Присовение множеству 3 = множество 2
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("Множество 3 уже содержит данные. Желаете очистить эти данные?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("Множество создано не было !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = new TSet(Set_2->GetMax());
   *Set_3 = *Set_2;
   Edit11->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------
//Объекдинение множеств
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("Множество 3 уже содержит данные. Желаете очистить эти данные?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("Множество создано не было !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = *Set_1 + *Set_2;
   Edit12->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------
//Создание пересечения множеств
void __fastcall TMainForm::Button4Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("Множество 3 уже содержит данные. Желаете очистить эти данные?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("Множество создано не было !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = *Set_1 * *Set_2;
   Edit13->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------

