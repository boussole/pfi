//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "HairdressingSalonCode.h"
#include "stdlib.h"
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
//Start program
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   Image1->Canvas->Refresh();
   Image2->Canvas->Refresh();
   I = 0; J = 0; ISt = 0; JSt = 0;
   Gorizontal->Max = 0;
   Vertical->Max = 0;
   GorizontalStatus->Max = 0;
   VerticalStatus->Max = 0;
   Render = NULL; StringBuffer = NULL; PictureBuffer = NULL;
   Channel = NULL; Sit = NULL; R = NULL; L = NULL, S = NULL;
   Model = NULL; Reject = NULL; StatusBuffer = NULL; RenderStatus = NULL; LeaveSystem = NULL; Fifteen = NULL;
   StringGrid1->ColWidths[0] = 20; StringGrid1->Cells[0][0] = "№";
   StringGrid1->Cells[1][0] = "Начало (час)";  StringGrid1->Cells[2][0] = "Начало (минут)";
   StringGrid1->Cells[3][0] = "Величина перерыва";
   StringGrid1->Cells[0][1] = "1";  StringGrid1->Cells[0][2] = "2"; StringGrid1->Cells[0][3] = "3";
   SetOfChar << 8 << 48 << 49 << 50 << 51 << 52 << 53 << 54 << 55 << 56 << 57;
   NCount = StrToInt(Edit2->Text); MCount = StrToInt(Edit3->Text);
   RestChannel = NULL; Splash = NULL;
}
//---------------------------------------------------------------------------
//Gorizontal Move;
void __fastcall TMainForm::GorizontalChange(TObject *Sender)
{
   if (Render != NULL)
      {
         I = Gorizontal->Position;
         Render->RePaint(I, J);
      }
}
//---------------------------------------------------------------------------
//Vertical Move
void __fastcall TMainForm::VerticalChange(TObject *Sender)
{
   if (Render != NULL)
      {
         J = Vertical->Position;
         Render->RePaint(I, J);
      }
}
//---------------------------------------------------------------------------
//Increment / decriment NCount
void __fastcall TMainForm::Edit2Change(TObject *Sender)
{
   if ( (StrToInt(Edit2->Text) >= 1) && (StrToInt(Edit2->Text) < 11) )
      {
         StringGrid1->Cells[0][StrToInt(Edit2->Text) + 1] = "";
         StringGrid1->Cells[1][StrToInt(Edit2->Text) + 1] = "";
         StringGrid1->Cells[2][StrToInt(Edit2->Text) + 1] = "";
         StringGrid1->Cells[3][StrToInt(Edit2->Text) + 1] = "";
         StringGrid1->RowCount = StrToInt(Edit2->Text) + 1;
         StringGrid1->Cells[0][StrToInt(Edit2->Text)] = Edit2->Text;
         NCount = StrToInt(Edit2->Text);
      }
}
//---------------------------------------------------------------------------
//Control enter data
void __fastcall TMainForm::StringGrid1KeyPress(TObject *Sender, char &Key)
{
   if (!SetOfChar.Contains(Key))
      {
         MessageDlg("Только целые числа!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         Key = 0;
      }
}
//---------------------------------------------------------------------------
//Free Memory
void __fastcall TMainForm :: ClearMemory()
{
   if (Render != NULL) {delete Render; Render = NULL;}
   if (StringBuffer != NULL) {delete StringBuffer; StringBuffer = NULL;}
   if (PictureBuffer != NULL) {delete PictureBuffer; PictureBuffer = NULL;}
   if (Channel != NULL) {delete []Channel; Channel = NULL;}
   if (Sit != NULL) {delete []Sit; Sit = NULL;}
   if (R != NULL) {delete R; R = NULL;}
   if (L != NULL) {delete L; L = NULL;}
   if (S != NULL) {delete S; S = NULL;}
   if (RestChannel != NULL) {delete []RestChannel; RestChannel = NULL;}
   if (Reject != NULL) {delete Reject; Reject = NULL;}
   if (StatusBuffer != NULL) {delete StatusBuffer; StatusBuffer = NULL;}
   if (RenderStatus != NULL) {delete RenderStatus; RenderStatus = NULL;}
   if (LeaveSystem != NULL) {delete LeaveSystem; LeaveSystem = NULL;}
   if (Fifteen != NULL) {delete Fifteen; Fifteen = NULL;}
   Gorizontal->Max = 0;
   Gorizontal->Position = 0;
   Vertical->Max = 0;
   Vertical->Position = 0;
   GorizontalStatus->Max = 0;
   GorizontalStatus->Position = 0;
   VerticalStatus->Max = 0;
   VerticalStatus->Position = 0;
   I = 0; J = 0; ISt = 0; JSt = 0;
}
//---------------------------------------------------------------------------
//Destroy programm
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   ClearMemory();
}
//---------------------------------------------------------------------------
//Increment / Decriment MCount
void __fastcall TMainForm::Edit3Change(TObject *Sender)
{
   MCount = StrToInt(Edit3->Text);
}
//---------------------------------------------------------------------------
//Modelling is process
void __fastcall TMainForm::ModellingButtonClick(TObject *Sender)
{
   ClearMemory();
   //-------------
   //Settings
   //-------------
   //Set Hot Hours
   THotHours HotHours;
   if ((StrToInt(Edit7->Text) >= StrToInt(Edit5->Text)) && (StrToInt(Edit7->Text) >= StrToInt(Edit5->Text)) && (StrToInt(Edit8->Text) > 0))
      {HotHours.Do = true;
       HotHours.Begin = (HoursToMinutes(StrToInt(Edit7->Text) - StrToInt(Edit5->Text), 0)) / StrToInt(Edit4->Text);
       HotHours.Duration = (HoursToMinutes(StrToInt(Edit8->Text), 0)) / StrToInt(Edit4->Text);}
   //-------------
   StringBuffer = new TStringBuffer(NCount, MCount);
   PictureBuffer = new TPictureBuffer();
   Channel = new TArrayChannel<TChannel>[NCount];
   Sit = new TArrayChannel<TSit>[MCount];
   Reject = new TArrayChannel<TLeave>;
   LeaveSystem = new TArrayChannel<TSit>[MCount];
   Fifteen = new TArrayChannel<TSit>[MCount];
   R = new TValueBuffer();
   L = new TValueBuffer();
   S = new TValueBuffer();
   //--------------
   //Set the rest of the channels
   RestChannel = new TRest[NCount];
   SetRest();
   //--------------
   Model = new TModel(PictureBuffer, R, L, S, Channel, Sit, Reject, NCount, MCount, (HoursToMinutes(StrToInt(Edit6->Text) - StrToInt(Edit5->Text), 0) / StrToInt(Edit4->Text)), HotHours, RestChannel, StrToInt(Edit4->Text), LeaveSystem, Fifteen);
   if (!Model->Modelling())
      {
         Render = new TRendering(Image1, PictureBuffer, StringBuffer, R, L, S, Channel, Sit, Gorizontal, Vertical);
         Render->RePaint(0, 0);
         SetRest();
         PrintStatistic();
         StatusBuffer = new TStatusGraphicBuffer();
         RenderStatus = new TRenderer(Image2, StatusBuffer, S, GorizontalStatus, VerticalStatus, NCount, MCount);
         RenderStatus->RePaint(0, 0);
      }
   else
      {
         MessageDlg("Моделирование завершилось неудачно!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         ClearMemory();
      }
   delete Model;
   Model = NULL;
}
//---------------------------------------------------------------------------
//Convert Hour to Minutes
size_t __fastcall TMainForm :: HoursToMinutes(size_t _Hour, size_t _Minutes)
{
   return (_Hour * 60 + _Minutes);
}
//---------------------------------------------------------------------------
//Convert Minutes to Hours
size_t __fastcall TMainForm :: MinutesToHours(size_t _Minutes)
{
   return (_Minutes / 60);
}
//---------------------------------------------------------------------------
//Return Minutes without hours
size_t __fastcall TMainForm :: MinutesWithoutHours(size_t _Minutes)
{
   return (_Minutes % 60);
}
//---------------------------------------------------------------------------
//Control low Limit of the worktime
void __fastcall TMainForm::Edit5Change(TObject *Sender)
{
   if (StrToInt(Edit5->Text) == StrToInt(Edit6->Text))
      {
         Edit6->Text = IntToStr(StrToInt(Edit5->Text) + UpDown4->Increment);
      }
}
//---------------------------------------------------------------------------
//Control high limit of the worktime
void __fastcall TMainForm::Edit6Change(TObject *Sender)
{
if (StrToInt(Edit6->Text) == StrToInt(Edit5->Text))
      {
         Edit5->Text = IntToStr(StrToInt(Edit6->Text) - UpDown5->Increment);
      }
}
//---------------------------------------------------------------------------
//Set Rest time
void __fastcall TMainForm :: SetRest()
{
   //Clear spaces, check
   for (size_t i = 1; i < StringGrid1->RowCount; i++)
   for (size_t j = 1; j < StringGrid1->ColCount; j++)
      {
         //Space = 0
         if (StringGrid1->Cells[j][i] == "")
            {
               StringGrid1->Cells[j][i] = 0;
            }
         //---------
         if ((j == 1) && (StrToInt(StringGrid1->Cells[j][i]) > 24))
            {StringGrid1->Cells[j][i] = 24;}
         //---------
         if (((j == 2) || (j == 3)) && (StrToInt(StringGrid1->Cells[j][i]) > 59))
            {StringGrid1->Cells[j][i] = 59;}
         //---------
         if ((j == 2) || (j == 3))
            {StringGrid1->Cells[j][i] = IntToStr(StrToInt(StringGrid1->Cells[j][i]) - StrToInt(StringGrid1->Cells[j][i]) % StrToInt(Edit4->Text));}
      }
   //-----------
   //Set
   for (size_t i = 1; i < StringGrid1->RowCount; i++)
      {
         if ((StrToInt(StringGrid1->Cells[1][i]) >= StrToInt(Edit5->Text)) && (StrToInt(StringGrid1->Cells[1][i]) < StrToInt(Edit6->Text)) && (StrToInt(StringGrid1->Cells[3][i]) > 0))
            {
               RestChannel[i - 1].Do = true;
               RestChannel[i - 1].Begin = (HoursToMinutes(StrToInt(StringGrid1->Cells[1][i]) - StrToInt(Edit5->Text), StrToInt(StringGrid1->Cells[2][i]))) / StrToInt(Edit4->Text);
               RestChannel[i - 1].Duration = (StrToInt(StringGrid1->Cells[3][i])) / (StrToInt(Edit4->Text));
            }
      }
}
//---------------------------------------------------------------------------
//Print the RichEdit of the statistic
void __fastcall TMainForm :: PrintStatistic()
{
   Memo1->Clear();
   char *Help = new char[1];
   Help[0] = (char)9;
   Memo1->Lines->Add("Эмулятор 'Парикмахерская' v.1.0.0. Файл статистики.");
   Memo1->Lines->Add("==================================================");
   Memo1->Lines->Add("Общее время моделирования (такт): " + IntToStr(Render->GetWidth() - 2));
   Memo1->Lines->Add("Время одного такта (мин.): " + Edit4->Text);
   Memo1->Lines->Add("Количество каналов обслуживания: " + IntToStr(NCount));
   Memo1->Lines->Add("Количество мест ожидания: " + IntToStr(MCount));
   Memo1->Lines->Add("==================================================");
   for (size_t i = 0; i < StrToInt(NCount); i++)
      {
         Memo1->Lines->Add("Работа канала №" + IntToStr(i + 1));
         if (RestChannel[i].Do)
            Memo1->Lines->Add("Перерыв: " + IntToStr(RestChannel[i].Begin) + " - " + IntToStr(RestChannel[i].Begin + RestChannel[i].Duration));
         else
            Memo1->Lines->Add("Перерыв отсутствует");
         Memo1->Lines->Add("==================================================");
         Memo1->Lines->Add("Номер такта" + AnsiString(Help[0]) + "Номер заявки" + AnsiString(Help[0]) + "Длительность");
         for (size_t j = 0; j < Channel[i].GetCount(); j++)
            {
               Memo1->Lines->Add(IntToStr(Channel[i].GetValue(j).Step) + Help[0] + Help[0] + IntToStr(Channel[i].GetValue(j).Number) + Help[0] + Help[0]
               + IntToStr(Channel[i].GetValue(j).Time) + " (" + IntToStr(Channel[i].GetValue(j).RandomValue) + ")");
            }
         Memo1->Lines->Add("==================================================");
      }
   for (size_t i = 0; i < StrToInt(MCount); i++)
      {
         Memo1->Lines->Add("Место ожидания №" + IntToStr(i + 1));
         Memo1->Lines->Add("==================================================");
         Memo1->Lines->Add("Номер такта" + AnsiString(Help[0]) + "Номер заявки");
         for (size_t j = 0; j < Sit[i].GetCount(); j++)
            {
               Memo1->Lines->Add(IntToStr(Sit[i].GetValue(j).Step) + Help[0] + Help[0] + IntToStr(Sit[i].GetValue(j).Number) + " (" + IntToStr(Sit[i].GetValue(j).RandomValue) + ")");
            }
         Memo1->Lines->Add("==================================================");
         Memo1->Lines->Add("Покинули систему при ожидании свыше 15 - минутного интервала");
         Memo1->Lines->Add("==================================================");
         Memo1->Lines->Add("Номер такта" + AnsiString(Help[0]) + "Номер заявки");
         for (size_t j = 0; j < Fifteen[i].GetCount(); j++)
            {
               Memo1->Lines->Add(IntToStr(Fifteen[i].GetValue(j).Step) + Help[0] + Help[0] + IntToStr(Fifteen[i].GetValue(j).Number) + " (" + IntToStr(Fifteen[i].GetValue(j).RandomValue) + ")");
            }
         Memo1->Lines->Add("==================================================");
      }
   for (size_t i = 0; i < StrToInt(MCount); i++)
      {
         Memo1->Lines->Add("Покинули систему при условии R" + IntToStr(i + 1));
         Memo1->Lines->Add("==================================================");
         Memo1->Lines->Add("Номер такта" + AnsiString(Help[0]) + "Номер заявки");
         for (size_t j = 0; j < LeaveSystem[i].GetCount(); j++)
            {
               Memo1->Lines->Add(IntToStr(LeaveSystem[i].GetValue(j).Step) + Help[0] + Help[0] + IntToStr(LeaveSystem[i].GetValue(j).Number) + " (" + IntToStr(LeaveSystem[i].GetValue(j).RandomValue) + ")");
            }
         Memo1->Lines->Add("==================================================");

      }
   //-----------------------------------------------
   //Немедленные отказы
   Memo1->Lines->Add("Отказы (отсутствие свободных каналов и мест ожидания)");
   Memo1->Lines->Add("==================================================");
   Memo1->Lines->Add("Номер такта" + AnsiString(Help[0]) + "Номер заявки");
   Memo1->Lines->Add("==================================================");
   for (size_t i = 0; i < (Reject->GetCount()); i++)
      {
         Memo1->Lines->Add(IntToStr(Reject->GetValue(i).Step) + Help[0] + Help[0] + IntToStr(Reject->GetValue(i).Number));
      }
   delete []Help;
   Help = NULL;
}
//---------------------------------------------------------------------------
//Gorizontal Change of the Status Scroll Bar
void __fastcall TMainForm::GorizontalStatusChange(TObject *Sender)
{
   if (StatusBuffer != NULL)
      {
         JSt = GorizontalStatus->Position;
         RenderStatus->RePaint(ISt, JSt);
      }
}
//---------------------------------------------------------------------------
//Vertical Change of the Status Scroll Bar
void __fastcall TMainForm::VerticalStatusChange(TObject *Sender)
{
   if (StatusBuffer != NULL)
      {
         ISt = VerticalStatus->Position;
         RenderStatus->RePaint(ISt, JSt);
      }
}
//---------------------------------------------------------------------------
//Menu
void __fastcall TMainForm::TreeView1Changing(TObject *Sender,
      TTreeNode *Node, bool &AllowChange)
{
   if (Node->Text == "Логотип") {PageControl1->ActivePageIndex = 0;}
   if (Node->Text == "Настройки") {PageControl1->ActivePageIndex = 1;}
   if ((Node->Text == "Циклограмма") && (Node->Index == 2)) {PageControl1->ActivePageIndex = 2;}
   if ((Node->Text == "Статистика") && (Node->Index == 3)) {PageControl1->ActivePageIndex = 3;}
   if ((Node->Text == "График") && (Node->Index == 4)) {PageControl1->ActivePageIndex = 4;}
   if (Node->Text == "О программе") {PageControl1->ActivePageIndex = 5;}
   if (Node->Text == "Об авторе")
      {
         if (!Splash)
         {
            Application->CreateForm(__classid(TSplash), &Splash);
         }
         Splash->ShowModal();
      }
   //-----------------------------------------------------
   if ((Node->Text == "Циклограмма") && (Node->Index == 0))
      {
         if (!SaveCircle())
            {
               MessageDlg("Невозможно сохранить файл на диске!!!", mtError, TMsgDlgButtons() << mbOK, 0);
            }
      }
   //-----------------------------------------------------
   if ((Node->Text == "Статистика") && (Node->Index == 1))
      {
         if (!SaveStatistic())
            {
               MessageDlg("Невозможно сохранить файл на диске!!!", mtError, TMsgDlgButtons() << mbOK, 0);
            }
      }
   //-----------------------------------------------------
   if ((Node->Text == "График") && (Node->Index == 2))
      {
         if (!SaveStatus())
            {
               MessageDlg("Невозможно сохранить файл на диске!!!", mtError, TMsgDlgButtons() << mbOK, 0);
            }
      }
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm :: SaveStatistic()
{
   if (Render)
      {
         if (SaveDialog1->Execute())
            {
               if (FileExists(SaveDialog1->FileName))
                  {
                     if (MessageDlg("Файл с указанным именем уже существует. Желаете заменить его?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                        {
                           return true;
                        }
                  }
               try
                  {
                     Memo1->Lines->SaveToFile(SaveDialog1->FileName);
                  }
               catch(...)
                  {
                     return false;
                  }
               return true;
            }
         else
            {
               return true;
            }
      }
   else
      {
         MessageDlg("Моделирование не произведено!!!", mtWarning, TMsgDlgButtons() << mbOK, 0);
         return true;
      }
}
//--------------------------------------------------------------------------
bool __fastcall TMainForm :: SaveCircle()
{
   if (Render)
      {
         SavePictureDialog1->FileName = "Circle";
         if (SavePictureDialog1->Execute())
            {
               if (FileExists(SavePictureDialog1->FileName))
                  {
                     if (MessageDlg("Файл с указанным именем уже существует. Желаете заменить его?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                        {
                           return true;
                        }
                  }
               return (Render->SaveToFile(SavePictureDialog1->FileName));
            }
         else
            {
               return true;
            }
      }
   else
      {
         MessageDlg("Моделирование не произведено!!!", mtWarning, TMsgDlgButtons() << mbOK, 0);
         return true;
      }
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm :: SaveStatus()
{
   if (RenderStatus)
      {
         SavePictureDialog1->FileName = "Status";
         if (SavePictureDialog1->Execute())
            {
               if (FileExists(SavePictureDialog1->FileName))
                  {
                     if (MessageDlg("Файл с указанным именем уже существует. Желаете заменить его?", mtWarning, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                        {
                           return true;
                        }
                  }
               return (RenderStatus->SaveToFile(SavePictureDialog1->FileName));
            }
         else
            {
               return true;
            }
      }
   else
      {
         MessageDlg("Моделирование не произведено!!!", mtWarning, TMsgDlgButtons() << mbOK, 0);
         return true;
      }
}
//--------------------------------------------------------------------------



