//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RegistryReportUnit.h"
#include "Report.h"
#include "SplashForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfMain *fMain;
//---------------------------------------------------------------------------
__fastcall TfMain::TfMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
double GetSum(TStringGrid *);
AnsiString GetNumber(AnsiString, size_t);
//---------------------------------------------------------------------------
AnsiString GetNumber(AnsiString Str, size_t Count)
{
   size_t i = 1, j = 0;
   AnsiString Help;
   while ((i <= Str.Length()) && (Str[i] != ','))
      {
         Help += Str[i++];
      }
   if ((i - 1 == Str.Length()) || (Count == 0))
      return Help;
   while ((i <= Str.Length()) && (j <= Count))
      {
         Help += Str[i++];
         j++;
      }
   return Help;
}
//---------------------------------------------------------------------------
double GetSum(TStringGrid *Table)
{
   double Sum = 0;
   for (int i = 0; i < Table->RowCount; i++)
      {
         if (Table->Cells[0][i] == "") {Table->Cells[0][i] = "0";}
         try
            {Sum = StrToFloat(Table->Cells[0][i]) + Sum;}
         catch (...)
            {return (-1);}
      }
   return (Sum);
}
//---------------------------------------------------------------------------
void __fastcall TfMain::FormCreate(TObject *Sender)
{
   StringGrid1->Cells[0][0] = "Пользователи";
   StringGrid1->Cells[0][1] = "Арендаторы всего:";
   StringGrid1->Cells[0][2] = "                          арендаторы";
   StringGrid1->Cells[0][3] = "                          гаражи";
   StringGrid1->Cells[0][4] = "                          подсветка";
   StringGrid1->Cells[0][5] = "                          арендатор";
   StringGrid1->Cells[0][7] = "Домохозяйство:";
   StringGrid1->Cells[0][10] = "Силовая эл. энергия:";
   StringGrid1->Cells[0][11] = "                         жильцы";
   StringGrid1->Cells[0][12] = "                         арендаторы";
   StringGrid1->Cells[0][14] = "                                 ИТОГО:";
   StringGrid1->Cells[1][0] = "                Группа";
   StringGrid1->Cells[2][0] = "                Тариф";
   StringGrid1->Cells[3][0] = "    Количество кВт, факт";
   StringGrid1->Cells[4][0] = "   По счету: сумма с НДС";
}
//---------------------------------------------------------------------------
void __fastcall TfMain::BitBtn1Click(TObject *Sender)
{
   fRep->FormCreate(Owner);
   if (CheckBox1->Checked) {fRep->QRLabel4->Caption = LabeledEdit1->Text;}
   else {fRep->QRLabel4->Caption = "";}
   if (CheckBox2->Checked) {fRep->QRLabel5->Caption = LabeledEdit2->Text;}
   else {fRep->QRLabel5->Caption = "200";}
   //-----------------------------------------------------
   //variables
   double dv, fact, podsvetka, arendator, garage, arendators, ArendatorAll, x, y, se, gilci, arend, domohoz, gilproc, help;
   //-----------------------------------------------------
   if (Edit1->Text == "0") {MessageDlg("Договорная величина не должна иметь нулевое значение!!!", mtWarning, TMsgDlgButtons() << mbOK, 0);return;}
   if (Edit2->Text == "0") {MessageDlg("Факт не должен иметь нулевое значение!!!", mtWarning, TMsgDlgButtons() << mbOK, 0);return;}
   if (Edit5->Text == "") {Edit5->Text = "0";};
   if (Edit6->Text == "") {Edit6->Text = "0";};
   try
      {dv = StrToFloat(Edit1->Text);}
   catch (...)
      {
         MessageDlg("Неверное значение поля 'Договорная величина'!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   try
      {fact = StrToFloat(Edit2->Text);}
   catch (...)
      {
         MessageDlg("Неверное значение поля 'Факт'!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   try
      {podsvetka = StrToFloat(Edit5->Text);}
   catch (...)
      {
         MessageDlg("Неверное значение поля 'Подсветка'!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   try
      {arendator = StrToFloat(Edit6->Text);}
   catch (...)
      {
         MessageDlg("Неверное значение поля 'Арендатор'!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   try
      {gilproc = StrToFloat(Edit7->Text);}
   catch (...)
      {
         MessageDlg("Неверное значение поля 'Процент жильцов'!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if ( (garage = GetSum(StringGrid2)) < 0)
      {
         MessageDlg("Неверное значение таблицы 'Гаражи'!!!\nВозможно сущестует незаполненное поле...", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if ( (arendators = GetSum(StringGrid3)) < 0)
      {
         MessageDlg("Неверное значение таблицы 'Арендаторы'!!!\nВозможно существует незаполненное поле...", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   ArendatorAll = arendators + garage + podsvetka + arendator;
   x = fact * 100 / dv;
   y = fact - ArendatorAll;
   se = y * x / 100;
   gilci = se * gilproc / 100;
   arend = se - gilci;
   domohoz = fact - ArendatorAll - se;
   //------------------------------------------------------
   //print
   StringGrid1->Cells[3][1] = GetNumber(FloatToStr(ArendatorAll), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][2] = GetNumber(FloatToStr(arendators), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][3] = GetNumber(FloatToStr(garage), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][4] = GetNumber(FloatToStr(podsvetka), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][5] = GetNumber(FloatToStr(arendator), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][7] = GetNumber(FloatToStr(domohoz), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][10] = GetNumber(FloatToStr(se), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][11] = GetNumber(FloatToStr(gilci), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][12] = GetNumber(FloatToStr(arend), StrToInt(Edit8->Text));
   StringGrid1->Cells[3][14] = GetNumber(FloatToStr(ArendatorAll + se + domohoz), StrToInt(Edit8->Text));
   //------------------------------------------------------
   //Group
   fRep->QRImage1->Canvas->TextOutA(205, 25, StringGrid1->Cells[1][1]);
   fRep->QRImage1->Canvas->TextOutA(205, 45, StringGrid1->Cells[1][2]);
   fRep->QRImage1->Canvas->TextOutA(205, 65, StringGrid1->Cells[1][3]);
   fRep->QRImage1->Canvas->TextOutA(205, 85, StringGrid1->Cells[1][4]);
   fRep->QRImage1->Canvas->TextOutA(205, 105, StringGrid1->Cells[1][5]);
   fRep->QRImage1->Canvas->TextOutA(205, 145, StringGrid1->Cells[1][7]);
   fRep->QRImage1->Canvas->TextOutA(205, 205, StringGrid1->Cells[1][10]);
   fRep->QRImage1->Canvas->TextOutA(205, 265, StringGrid1->Cells[1][11]);
   fRep->QRImage1->Canvas->TextOutA(205, 285, StringGrid1->Cells[1][12]);
   fRep->QRImage1->Canvas->TextOutA(205, 325, StringGrid1->Cells[1][14]);
   //------------------------------------------------------
   //Tarif
   if (StringGrid1->Cells[2][1] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 25, StringGrid1->Cells[2][1]);
           try
                {help = ArendatorAll * StrToFloat(StringGrid1->Cells[2][1]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении Арендаторы всего -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][1] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 25, StringGrid1->Cells[4][1]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 25, StringGrid1->Cells[3][1]);
   //---------------------------------
   if (StringGrid1->Cells[2][2] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 45, StringGrid1->Cells[2][2]);
           try
                {help = arendators * StrToFloat(StringGrid1->Cells[2][2]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении арендаторы -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][2] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 45, StringGrid1->Cells[4][2]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 45, StringGrid1->Cells[3][2]);
   //----------------------------------
   if (StringGrid1->Cells[2][3] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 65, StringGrid1->Cells[2][3]);
           try
                {help = garage * StrToFloat(StringGrid1->Cells[2][3]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении гаражи -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][3] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 65, StringGrid1->Cells[4][3]);
        }
    fRep->QRImage1->Canvas->TextOutA(365, 65, StringGrid1->Cells[3][3]);
   //----------------------------------
   if (StringGrid1->Cells[2][4] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 85, StringGrid1->Cells[2][4]);
           try
                {help = podsvetka * StrToFloat(StringGrid1->Cells[2][4]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении подсветка -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][4] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 85, StringGrid1->Cells[4][4]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 85, StringGrid1->Cells[3][4]);
   //----------------------------------
   if (StringGrid1->Cells[2][5] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 105, StringGrid1->Cells[2][5]);
           try
                {help = arendator * StrToFloat(StringGrid1->Cells[2][5]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении арендатор -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][5] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 105, StringGrid1->Cells[4][5]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 105, StringGrid1->Cells[3][5]);
   //----------------------------------
   if (StringGrid1->Cells[2][7] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 145, StringGrid1->Cells[2][7]);
           try
                {help = domohoz * StrToFloat(StringGrid1->Cells[2][7]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении домохозяйство -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][7] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 145, StringGrid1->Cells[4][7]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 145, StringGrid1->Cells[3][7]);
   //----------------------------------
   if (StringGrid1->Cells[2][10] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 205, StringGrid1->Cells[2][10]);
           try
                {help = se * StrToFloat(StringGrid1->Cells[2][10]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении Силовая энергия -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][10] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 205, StringGrid1->Cells[4][10]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 205, StringGrid1->Cells[3][10]);
   //----------------------------------
   if (StringGrid1->Cells[2][11] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 265, StringGrid1->Cells[2][11]);
           try
                {help = gilci * StrToFloat(StringGrid1->Cells[2][11]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении жильцы -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][11] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 265, StringGrid1->Cells[4][11]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 265, StringGrid1->Cells[3][11]);
   //----------------------------------
   if (StringGrid1->Cells[2][12] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 285, StringGrid1->Cells[2][12]);
           try
                {help = arend * StrToFloat(StringGrid1->Cells[2][12]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении арендаторы -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][12] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 285, StringGrid1->Cells[4][12]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 285, StringGrid1->Cells[3][12]);
   //----------------------------------
   if (StringGrid1->Cells[2][14] != "")
        {
           fRep->QRImage1->Canvas->TextOutA(285, 325, StringGrid1->Cells[2][14]);
           try
                {help = (ArendatorAll + se + domohoz) * StrToFloat(StringGrid1->Cells[2][14]);}
           catch(...)
                {
                        MessageDlg("Ошибка в значении Итого -> Тариф", mtError, TMsgDlgButtons() << mbOK, 0);
                        return;
                }
           StringGrid1->Cells[4][14] = GetNumber(FloatToStr(help), StrToInt(Edit8->Text));
           fRep->QRImage1->Canvas->TextOutA(505, 325, StringGrid1->Cells[4][14]);
        }
   fRep->QRImage1->Canvas->TextOutA(365, 325, StringGrid1->Cells[3][14]);
   //------------------------------------------------------
   PageControl1->ActivePage = TabSheet1;
}
//---------------------------------------------------------------------------

void __fastcall TfMain::UpDown1Click(TObject *Sender,
      TUDBtnType Button)
{
   StringGrid2->RowCount = StrToInt(Edit3->Text);
}
//---------------------------------------------------------------------------

void __fastcall TfMain::UpDown2Click(TObject *Sender,
      TUDBtnType Button)
{
   StringGrid3->RowCount = StrToInt(Edit4->Text);   
}
//---------------------------------------------------------------------------
void __fastcall TfMain::BitBtn2Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::BitBtn3Click(TObject *Sender)
{
        fRep->QuickRep1->PreviewModal();
}
//---------------------------------------------------------------------------
void __fastcall TfMain::CheckBox1Click(TObject *Sender)
{
        if (CheckBox1->Checked)
                {
                        LabeledEdit1->ReadOnly = false;
                        LabeledEdit1->Color = clWindow;
                }
        else
                {
                        LabeledEdit1->ReadOnly = true;
                        LabeledEdit1->Color = clInactiveCaptionText;
                }
}
//---------------------------------------------------------------------------

void __fastcall TfMain::CheckBox2Click(TObject *Sender)
{
        if (CheckBox2->Checked)
                {
                        LabeledEdit2->ReadOnly = false;
                        LabeledEdit2->Color = clWindow;
                }
        else
                {
                        LabeledEdit2->ReadOnly = true;
                        LabeledEdit2->Color = clInactiveCaptionText;
                }
}
//---------------------------------------------------------------------------
void __fastcall TfMain::N7Click(TObject *Sender)
{
        Splash = new TSplash(Owner);
        Splash->ShowModal();
        delete Splash;
        Splash = NULL;
}
//---------------------------------------------------------------------------

