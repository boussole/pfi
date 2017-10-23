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
//��������� �� ������ ���������
TSet *SetOfInt;
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   SetOfInt = NULL;
}
//---------------------------------------------------------------------------
//����������� �����
void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
         delete SetOfInt;
         SetOfInt = NULL;
      }
}
//---------------------------------------------------------------------------
//������ �������� ���������
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������ ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetOfInt;
               SetOfInt = NULL;
            }
         else
            {
               MessageDlg("����� ��������� ������� �� ����", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit1->Text) <= 0)
            {
               MessageDlg("����������� ��������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetOfInt = new TSet(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
//������ "���������� ���������"
void __fastcall TMainForm::BitBtn5Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
         Edit5->Text = SetOfInt->PrintSet();    
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//������ "�������� � ���������"
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
            MessageDlg("������ � ��������� ����� ������������ �  ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//������ "������� �� ���������"
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
            MessageDlg("������ � ��������� ����� ���������� �� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//�������� �� �������������� ���������
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   if (SetOfInt != NULL)
      {
      try
         {
            if (SetOfInt->Check(StrToInt(Edit2->Text)))
               {
                  Application->MessageBoxA("              ����� ����������� ���������", "�������� �� �������������� ���������", MB_OK);
               }
            else
               {
                  Application->MessageBoxA("              ����� �� ����������� ���������", "�������� �� �������������� ���������", MB_OK);
               }
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ �� �������������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
