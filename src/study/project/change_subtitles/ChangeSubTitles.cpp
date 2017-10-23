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
/*/���������� ����������/*/
Set <char, '0', '9'> SetOfNumber;
/*/��������� �������/*/
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
   /*/����������/*/
   TRealTime ChangeTime;
   bool Error = false, FatalError = false;
   char Buffer[255];
   AnsiString ChangeBuffer;
   bool Summa = false;
   AnsiString MessageLoad = "���������� ������� �������� ����: \n" + Edit1->Text;
   AnsiString MessageSave = "���������� ������� �������� ����: \n" + Edit2->Text;
   /*/----------------/*/
   /*/����������� ��������/*/
   if (Edit1->Text == "") {Application->MessageBoxA("���� ��������� �� ��������!!!", "��������� ���������", MB_OK); return;}
   if (Edit2->Text == "") {Application->MessageBoxA("�� ������ ����������� ����!!!", "��������� ���������", MB_OK); return;}
   if ( (StringGrid1->Cells[0][1] == "") && (StringGrid1->Cells[1][1] == "") && (StringGrid1->Cells[2][1] == "") && (StringGrid1->Cells[3][1] == "") )
   {Application->MessageBoxA("���������� ������� �� ������", "��������� �����������", MB_OK); return;}
   if (
         ((StringGrid1->Cells[1][1] != "") && (StrToFloat(StringGrid1->Cells[1][1]) >= 60))
      ||
         ((StringGrid1->Cells[2][1] != "") && (StrToFloat(StringGrid1->Cells[2][1]) >= 60))
      ||
         ((StringGrid1->Cells[3][1] != "") && (StrToFloat(StringGrid1->Cells[3][1]) >= 1000))
      )
   {Application->MessageBoxA("   ������� ������ �����", "��������� ���������", MB_OK); return;}
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
   {Application->MessageBoxA("������ �� ����� ���������� �������", "��������� ���������", MB_OK); return;}
   if (Sum->Checked)
      {Summa = true;}
   /*/----------------/*/
   ifstream LoadFile;
   ofstream SaveFile;
   /*/----------------/*/
   LoadFile.open((Edit1->Text).c_str());
   if (LoadFile.fail())
      {
         Application->MessageBoxA(MessageLoad.c_str(), "��������� ���������", MB_OK);
         LoadFile.close();
         return;
      }
   /*/----------------/*/
   if (FileExists(SaveDialog1->FileName))
      {
         if (MessageDlg("���� � ��������� ������ ��� ����������. �������� ��������� ����?", mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo) {return;}
      }
   SaveFile.open((Edit2->Text).c_str());
   if (SaveFile.fail())
      {
         Application->MessageBoxA(MessageSave.c_str(), "��������� ���������", MB_OK);
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
                        if ( (MessageDlg("������ ���������� ���������� ���������?", mtWarning,	TMsgDlgButtons() << mbYes << mbNo, 0)) == mrYes )
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
         Application->MessageBoxA("���� ��� ����� ����� �� ���� ��������", "��������� ��������", MB_OK);
      }
}
//---------------------------------------------------------------------------
/*/�������� ������������ ����������/*/
void __fastcall TChangeSubTitlesForm::FormCreate(TObject *Sender)
{
   SetOfNumber << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9';
   StringGrid1->Cells[0][0] = "����";
   StringGrid1->Cells[1][0] = "������";
   StringGrid1->Cells[2][0] = "�������";
   StringGrid1->Cells[3][0] = "����� �������";
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
        Application->MessageBoxA("����������� ������ - ��������� ������ �����", "��������", MB_OK);
        Key = 0;
        return;
     }
}
//---------------------------------------------------------------------------
/*/��������� �������/*/
void __fastcall change(AnsiString &HelpString, bool _Summa, bool &_Error, TRealTime _ChangeTime)
   {
/*/�������� �������/*/
void __fastcall ChangeNumber(TClock &, TRealTime , bool, bool &);
/*/----------------/*/
      if (HelpString == "") {_Error = true; return;}
      TClock StartTime, FinishTime;
      AnsiString IntPartStart, FloatPartStart, IntPartFinish, FloatPartFinish;
      int Counter = 0, Index = 1;
      /*/����� ����� ����� ������ ��������� ���������/*/
      while ((Index <= HelpString.Length()) && (Counter < 6))
         {
            if (SetOfNumber.Contains(HelpString[Index]))
               {
                  IntPartStart = IntPartStart + HelpString[Index];
                  Counter++;
               }
            Index++;
         }
      if (Counter != 6) {MessageDlg("������ ���������� ������� ��������� ��������� (����� ����� ������ �������� �� 6 ����)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}

      /*/����� ������� ����� ������ ��������� ���������/*/
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
      if (Counter != 3) {MessageDlg("������ ���������� ������� ��������� ��������� (������� ����� ������ �������� �� 3 ����)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}
      /*/����� ����� ����� ����� ��������� ���������/*/
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
      if (Counter != 6) {MessageDlg("������ ��������� ������� ��������� ��������� (����� ����� ������ �������� �� 6 ����)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}
      /*/����� ������� ����� ��������� ���������/*/
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
      if (Counter != 3) {MessageDlg("������ ��������� ������� ��������� ��������� (������� ����� ������ �������� �� 3 ����)", mtError, TMsgDlgButtons() << mbYes, 0); _Error = true; return;}
      /*/����������� ��������/*/
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
/*/������������� �������� ��� ��������� �����/*/
void __fastcall ChangeNumber(TClock &Time, TRealTime __ChangeTime, bool __Summa, bool &__Error)
   {
      TRealTime Current;
      AnsiString Help;
      /*/�������������� �������/*/
      try
         {
            Current.Hour = StrToInt(Time.Hour);
            Current.Minutes = StrToInt(Time.Minutes);
            Current.Secondes = StrToInt(Time.Secondes);
            Current.MilliSec = StrToInt(Time.MilliSec);
         }
      catch (...) {MessageDlg("������ �������������� �����", mtError, TMsgDlgButtons() << mbYes, 0); __Error = true; return;}
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
      /*/����� �������� ������� �� �������/*/
      /*/������������/*/
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
      /*/�������/*/
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
      /*/������/*/
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
      /*/����� �� ������� ������������ �������� ������ �������/*/
      if (Current.Hour < 0)
         {
            __Error = true;
            MessageDlg("����� �� ������� ������� ������", mtError, TMsgDlgButtons() << mbYes, 0);
            return;
         }
      /*/----------------------------/*/
      /*/�������� ����������� ������/*/
      Time.Hour = IntToStr(Current.Hour);
      Time.Minutes = IntToStr(Current.Minutes);
      Time.Secondes = IntToStr(Current.Secondes);
      Time.MilliSec = IntToStr(Current.MilliSec);
      /*/---------------------------------/*/
      /*/�������� ������ � ����������� ���/*/
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

