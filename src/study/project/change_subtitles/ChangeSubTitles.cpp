//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ChangeSubTitles.h"
#include <fstream.h>
#include "Forms\\InfoForm\\InfoForm.cpp"
#include "Forms\\SplashForm\\SplashForm.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChangeSubTitlesForm *ChangeSubTitlesForm;
//---------------------------------------------------------------------------
__fastcall TChangeSubTitlesForm::TChangeSubTitlesForm(TComponent* Owner)
   : TForm(Owner)
{
}
/*/-----------------------------------------------------------------------/*/
/*/Глобальная переменная/*/
Set <char, '0', '9'> SetOfNumber;
/*/Прототипы функций/*/
void __fastcall change(AnsiString &, bool, bool &, TRealTime);
//----------------------------------------------------------------------
void __fastcall TChangeSubTitlesForm::BitBtn1Click(TObject *Sender)
{
   if (OpenDialog1->Execute())
      {
         Edit1->Text = OpenDialog1->FileName;
      }
}
//---------------------------------------------------------------------------
void __fastcall TChangeSubTitlesForm::BitBtn2Click(TObject *Sender)
{
   if (SaveDialog1->Execute())
      {
         Edit2->Text = SaveDialog1->FileName;
      }
}
//---------------------------------------------------------------------------
void __fastcall TChangeSubTitlesForm::RunClick(TObject *Sender)
{
   /*/----------------/*/
   /*/Переменные/*/
   TRealTime ChangeTime;
   bool Error = false, FatalError = false;
   char Buffer[255];
   AnsiString ChangeBuffer;
   bool Summa = false;
   AnsiString MessageLoad = "Невозможно открыть исходный файл: \n" + Edit1->Text;
   AnsiString MessageSave = "Невозможно создать конечный файл: \n" + Edit2->Text;
   /*/----------------/*/
   /*/Необходимые проверки/*/
   if (Edit1->Text == "") {Application->MessageBoxA("Файл субтитров не заргужен!!!", "Остановка программы", MB_OK); return;}
   if (Edit2->Text == "") {Application->MessageBoxA("Не указан сохраняемый файл!!!", "Остановка программы", MB_OK); return;}
   if ( (StringGrid1->Cells[0][1] == "") && (StringGrid1->Cells[1][1] == "") && (StringGrid1->Cells[2][1] == "") && (StringGrid1->Cells[3][1] == "") )
   {Application->MessageBoxA("Приращение времени не задано", "Программа остановлена", MB_OK); return;}
   if (
         ((StringGrid1->Cells[1][1] != "") && (StrToFloat(StringGrid1->Cells[1][1]) >= 60))
      ||
         ((StringGrid1->Cells[2][1] != "") && (StrToFloat(StringGrid1->Cells[2][1]) >= 60))
      ||
         ((StringGrid1->Cells[3][1] != "") && (StrToFloat(StringGrid1->Cells[3][1]) >= 1000))
      )
   {Application->MessageBoxA("   Неверно задано время", "Остановка программы", MB_OK); return;}
   if (StringGrid1->Cells[0][1] == "") {StringGrid1->Cells[0][1] = "00";}
   if (StringGrid1->Cells[1][1] == "") {StringGrid1->Cells[1][1] = "00";}
   if (StringGrid1->Cells[2][1] == "") {StringGrid1->Cells[2][1] = "00";}
   if (StringGrid1->Cells[3][1] == "") {StringGrid1->Cells[3][1] = "000";}
   /*/----------------/*/
   try {
         ChangeTime.Hour = StrToInt(StringGrid1->Cells[0][1]);
         ChangeTime.Minutes = StrToInt(StringGrid1->Cells[1][1]);
         ChangeTime.Secondes = StrToInt(StringGrid1->Cells[2][1]);
         ChangeTime.MilliSec = StrToInt(StringGrid1->Cells[3][1]);
       }
   catch (...)
   {Application->MessageBoxA("Ошибка во вводе приращения времени", "Остановка программы", MB_OK); return;}
   if (Sum->Checked)
      {Summa = true;}
   /*/----------------/*/
   ifstream LoadFile;
   ofstream SaveFile;
   /*/----------------/*/
   LoadFile.open((Edit1->Text).c_str());
   if (LoadFile.fail())
      {
         Application->MessageBoxA(MessageLoad.c_str(), "Остановка программы", MB_OK);
         LoadFile.close();
         return;
      }
   /*/----------------/*/
   if (FileExists(SaveDialog1->FileName))
      {
         if (MessageDlg("Файл с указанным именем уже существует. Заменить имеющийся файл?", mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo) {return;}
      }
   SaveFile.open((Edit2->Text).c_str());
   if (SaveFile.fail())
      {
         Application->MessageBoxA(MessageSave.c_str(), "Остановка программы", MB_OK);
         SaveFile.close();
         return;
      }
   /*/----------------/*/
   while (!LoadFile.eof())
      {

         LoadFile.getline(Buffer, sizeof(Buffer) );
         if (
               (strlen(Buffer) > 28) && (SetOfNumber.Contains(Buffer[0])) && (SetOfNumber.Contains(Buffer[1])) && (SetOfNumber.Contains(Buffer[3])) && (SetOfNumber.Contains(Buffer[4])) &&
               (SetOfNumber.Contains(Buffer[6])) && (SetOfNumber.Contains(Buffer[7])) && (SetOfNumber.Contains(Buffer[9])) && (SetOfNumber.Contains(Buffer[10])) &&
               (SetOfNumber.Contains(Buffer[11]))

            )
            {
               ChangeBuffer = Buffer;
               change(ChangeBuffer, Summa, Error, ChangeTime);
                  if (Error)
                     {
                        Error = false;
                        FatalError = true;
                        SaveFile << "Bad Line !!!" << endl;
                        if ( (MessageDlg("Хотите остановить выполнение программы?", mtWarning,	TMsgDlgButtons() << mbYes << mbNo, 0)) == mrYes )
                           {goto Exit;}
                     }
                  else
                     {
                        strcpy(Buffer, ChangeBuffer.c_str());
                        SaveFile << Buffer << endl;
                     }
            }
         else
            {SaveFile << Buffer << endl;}
      }
   /*/----------------/*/
   LoadFile.close();
   SaveFile.close();
   /*/----------------/*/
   Exit:
   if (FatalError)
      {
         Application->MessageBoxA("Одна или более строк не были изменены", "Нарушение услшовий", MB_OK);
      }
}
//---------------------------------------------------------------------------
/*/Создание необходимого интерфейса/*/
void __fastcall TChangeSubTitlesForm::FormCreate(TObject *Sender)
{
   SetOfNumber << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9';
   StringGrid1->Cells[0][0] = "Часы";
   StringGrid1->Cells[1][0] = "Минуты";
   StringGrid1->Cells[2][0] = "Секунды";
   StringGrid1->Cells[3][0] = "Милли секунды";
}
//---------------------------------------------------------------------------

void __fastcall TChangeSubTitlesForm::ExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TChangeSubTitlesForm::StringGrid1KeyPress(TObject *Sender, char &Key)
{
   if (int(Key) == 13)
      {
         return;
      }
   if ((!SetOfNumber.Contains(Key)) && (int(Key) != 8))
     {
        Application->MessageBoxA("Неизвестный символ - Разрешены только цифры", "Внимание", MB_OK);
        Key = 0;
        return;
     }
}
//---------------------------------------------------------------------------
/*/Изменение времени/*/
void __fastcall change(AnsiString &HelpString, bool _Summa, bool &_Error, TRealTime _ChangeTime)
   {
/*/Прототип функции/*/
void __fastcall ChangeNumber(TClock &, TRealTime , bool, bool &);
/*/----------------/*/
      if (HelpString == "") {_Error = true; return;}
      TClock StartTime, FinishTime;
      AnsiString IntPartStart, FloatPartStart, IntPartFinish, FloatPartFinish;
      int Counter = 0, Index = 1;
      /*/Поиск целой части начала фрагмента субтитров/*/
      while ((Index <= HelpString.Length()) && (Counter < 6))
         {
            if (SetOfNumber.Contains(HelpString[Index]))
               {
                  IntPartStart = IntPartStart + HelpString[Index];
                  Counter++;
               }
            Index++;
         }
      if (Counter != 6) {MessageDlg("Ошибка начального времени фрагмента субтитров (целая часть должна состоять из 6 цифр)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}

      /*/Поиск дробной части начала фрагмента субтитров/*/
      Counter = 0;
      while ((Index <= HelpString.Length()) && (Counter < 3))
         {
            if (SetOfNumber.Contains(HelpString[Index]))
               {
                  FloatPartStart = FloatPartStart + HelpString[Index];
                  Counter++;
               }
            Index++;
         }
      if (Counter != 3) {MessageDlg("Ошибка начального времени фрагмента субтитров (дробная часть должна состоять из 3 цифр)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}
      /*/Поиск целой части конца фрагмента субтитров/*/
      Counter = 0;
      while ((Index <= HelpString.Length()) && (Counter < 6))
         {
            if (SetOfNumber.Contains(HelpString[Index]))
               {
                  IntPartFinish = IntPartFinish + HelpString[Index];
                  Counter++;
               }
            Index++;
         }
      if (Counter != 6) {MessageDlg("Ошибка конечного времени фрагмента субтитров (целая часть должна состоять из 6 цифр)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}
      /*/Поиск дробной части фрагмента субтитров/*/
      Counter = 0;
      while ((Index <= HelpString.Length()) && (Counter < 3))
         {
            if (SetOfNumber.Contains(HelpString[Index]))
               {
                  FloatPartFinish = FloatPartFinish + HelpString[Index];
                  Counter++;
               }
            Index++;
         }
      if (Counter != 3) {MessageDlg("Ошибка конечного времени фрагмента субтитров (дробная часть должна состоять из 3 цифр)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}
      /*/Определение структур/*/
      StartTime.Hour = StartTime.Hour + IntPartStart[1] + IntPartStart[2];
      StartTime.Minutes = StartTime.Minutes + IntPartStart[3] + IntPartStart[4];
      StartTime.Secondes = StartTime.Secondes + IntPartStart[5] + IntPartStart[6];
      StartTime.MilliSec = StartTime.MilliSec + FloatPartStart;
      /*/--------------------/*/
      FinishTime.Hour = FinishTime.Hour + IntPartFinish[1] + IntPartFinish[2];
      FinishTime.Minutes = FinishTime.Minutes + IntPartFinish[3] + IntPartFinish[4];
      FinishTime.Secondes = FinishTime.Secondes + IntPartFinish[5] + IntPartFinish[6];
      FinishTime.MilliSec = FinishTime.MilliSec + FloatPartFinish;
      /*/----------------------------------------------------------------------/*/
      ChangeNumber(StartTime, _ChangeTime, _Summa, _Error);
      if (_Error) {return;}
      ChangeNumber(FinishTime, _ChangeTime, _Summa, _Error);
      if (_Error) {return;}
      HelpString = "";
      HelpString = HelpString + StartTime.Hour + ":" + StartTime.Minutes + ":" + StartTime.Secondes + "," +
                   StartTime.MilliSec + " --> " + FinishTime.Hour + ":" + FinishTime.Minutes + ":" + FinishTime.Secondes +
                   "," + FinishTime.MilliSec;
   }
/*/-----------------------------------------------------------------------/*/
/*/Осуществление действий над разрядами чисел/*/
void __fastcall ChangeNumber(TClock &Time, TRealTime __ChangeTime, bool __Summa, bool &__Error)
   {
      TRealTime Current;
      AnsiString Help;
      /*/Преобразование времени/*/
      try
         {
            Current.Hour = StrToInt(Time.Hour);
            Current.Minutes = StrToInt(Time.Minutes);
            Current.Secondes = StrToInt(Time.Secondes);
            Current.MilliSec = StrToInt(Time.MilliSec);
         }
      catch (...) {MessageDlg("Ошибка преобразования числа", mtError, TMsgDlgButtons() << mbYes, 0); __Error = true; return;}
      if (__Summa)
         {
            Current.Hour = Current.Hour + __ChangeTime.Hour;
            Current.Minutes = Current.Minutes + __ChangeTime.Minutes;
            Current.Secondes = Current.Secondes + __ChangeTime.Secondes;
            Current.MilliSec = Current.MilliSec + __ChangeTime.MilliSec;
         }
      else
         {
            Current.Hour = Current.Hour - __ChangeTime.Hour;
            Current.Minutes = Current.Minutes - __ChangeTime.Minutes;
            Current.Secondes = Current.Secondes - __ChangeTime.Secondes;
            Current.MilliSec = Current.MilliSec - __ChangeTime.MilliSec;
         }
      /*/Выход разрядов времени за пределы/*/
      /*/Миллисекунды/*/
      if (Current.MilliSec > 999)
         {
           Current.Secondes++;
           Current.MilliSec -= 1000;
         }
      else
      if (Current.MilliSec < 0)
         {
            Current.Secondes--;
            Current.MilliSec += 1000;
         }
      /*/----------------------------/*/
      /*/Секунды/*/
      if (Current.Secondes >= 60)
         {
            Current.Minutes++;
            Current.Secondes -= 60;
         }
      else
      if (Current.Secondes < 0)
         {
            Current.Minutes--;
            Current.Secondes +=60;
         }
      /*/----------------------------/*/
      /*/Минуты/*/
      if (Current.Minutes >=60)
         {
             Current.Hour++;
             Current.Minutes -= 60;
         }
      else
      if (Current.Minutes < 0)
         {
            Current.Hour--;
            Current.Minutes +=60;
         }
      /*/----------------------------/*/
      /*/Выход за пределы отрицательно значения общего времени/*/
      if (Current.Hour < 0)
         {
            __Error = true;
            MessageDlg("Выход за пределы времени фильма", mtError, TMsgDlgButtons() << mbYes, 0);
            return;
         }
      /*/----------------------------/*/
      /*/Приводим необходимые строки/*/
      Time.Hour = IntToStr(Current.Hour);
      Time.Minutes = IntToStr(Current.Minutes);
      Time.Secondes = IntToStr(Current.Secondes);
      Time.MilliSec = IntToStr(Current.MilliSec);
      /*/---------------------------------/*/
      /*/Приводим строки в необходимый вид/*/
      /*/---------------------------------/*/
      Help = "";
      switch (Time.Hour.Length())
         {
            case (0):{
                        Time.Hour = "00";
                        break;
                     }
            case (1):{
                        Help = Time.Hour;
                        Time.Hour = "0" + Help;
                        break;
                     }
         }
      Help = "";
      switch (Time.Minutes.Length())
         {
            case (0):{
                        Time.Minutes = "00";
                        break;
                     }
            case (1):{
                        Help = Time.Minutes;
                        Time.Minutes = "0" + Help;
                        break;
                     }
         }
      Help = "";
      switch (Time.Secondes.Length())
         {
            case (0):{
                        Time.Secondes = "00";
                        break;
                     }
            case (1):{
                        Help = Time.Secondes;
                        Time.Secondes = "0" + Help;
                        break;
                     }
         }
      Help = "";
      switch (Time.MilliSec.Length())
         {
            case (0):{
                        Time.MilliSec = "000";
                        break;
                     }
            case (1):{
                        Help = Time.MilliSec;
                        Time.MilliSec = "00" + Help;
                        break;
                     }
            case (2):{
                        Help = Time.MilliSec;
                        Time.MilliSec = "0" + Help;
                        break;
                     }
         }
      /*/----------------------------/*/
   }
/*/----------------------------------------------------------------------/*/
void __fastcall TChangeSubTitlesForm::AboutProgram2Click(TObject *Sender)
{
   TChangeSubTitlesInfoForm *Form = new TChangeSubTitlesInfoForm(this);
   Form->ShowModal();
   delete Form;
   Form = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TChangeSubTitlesForm::About1Click(TObject *Sender)
{
   TSplash *Form = new TSplash(this);
   Form->ShowModal();
   delete Form;
   Form = NULL;
}
//---------------------------------------------------------------------------

