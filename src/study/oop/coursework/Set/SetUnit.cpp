//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "SetUnit.h"
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
//Указатель на объект множества
TSet *SetOfInt;
//---------------------------------------------------------------------------
//Создание формы
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   SetOfInt = NULL;
}
//---------------------------------------------------------------------------
//Уничтожение формы
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
         delete SetOfInt;
         SetOfInt = NULL;
      }
}
//---------------------------------------------------------------------------
//Кнопка создания множества
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
         if (MessageDlg("Область памяти занята другим множеством. Освободить память ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetOfInt;
               SetOfInt = NULL;
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
      SetOfInt = new TSet(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
//Кнопка "Распечатка множества"
void __fastcall TMainForm::BitBtn5Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
         Edit5->Text = SetOfInt->PrintSet();    
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Кнопка "Добавить в множество"
void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
      try
         {
            SetOfInt->AddElement(StrToInt(Edit3->Text));
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
//Кнопка "Удалить из множества"
void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
      try
         {
            SetOfInt->DelElement(StrToInt(Edit4->Text));
         }
      catch (EConvertError &)
         {
            MessageDlg("Ошибка в написании числа удаляемого из множества", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("Множество не создано", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//Проверка на принадлежность множеству
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
      try
         {
            if (SetOfInt->Check(StrToInt(Edit2->Text)))
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
