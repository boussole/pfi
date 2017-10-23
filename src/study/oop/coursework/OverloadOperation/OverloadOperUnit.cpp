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
//���������� ��������� �� ���������
TSet *Set_1, *Set_2, *Set_3;
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   Set_1 = NULL;
   Set_2 = NULL;
   Set_3 = NULL;   
}
//---------------------------------------------------------------------------
//����������� �����
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
//�������� ��������� 1
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������ ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_1;
               Set_1 = NULL;
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
      Set_1 = new TSet(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
//���������� ��������� 1
void __fastcall TMainForm::BitBtn5Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
         Edit5->Text = Set_1->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//�������� ����� �� �������������� ��������� 1
void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
   if (Set_1 != NULL)
      {
      try
         {
            if (Set_1->Check(StrToInt(Edit3->Text)))
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
//�������� ��������� 2
void __fastcall TMainForm::BitBtn6Click(TObject *Sender)
{
if (Set_2 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������ ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_2;
               Set_2 = NULL;
            }
         else
            {
               MessageDlg("����� ��������� ������� �� ����", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit6->Text) <= 0)
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
      Set_2 = new TSet(StrToInt(Edit6->Text));
}
//---------------------------------------------------------------------------
//���������� ��������� 2
void __fastcall TMainForm::BitBtn10Click(TObject *Sender)
{
   if (Set_2 != NULL)
      {
         Edit10->Text = Set_2->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//�������� �� �������������� ����� ��������� 2
void __fastcall TMainForm::BitBtn8Click(TObject *Sender)
{
   if (Set_2 != NULL)
      {
      try
         {
            if (Set_2->Check(StrToInt(Edit8->Text)))
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
//���������� �������� ��������� 1
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
//�������� �������� �� ��������� 1
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
            MessageDlg("������ � ��������� �����, ���������� �� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//�������� ����� �� ��������� 2
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
//�������� �������� �� ���������
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
            MessageDlg("������ � ��������� �����, ���������� �� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------
//���������� ��������� 3 = ��������� 1
void __fastcall TMainForm::Button1Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("��������� 3 ��� �������� ������. ������� �������� ��� ������?", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("��������� ������� �� ���� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = new TSet(Set_1->GetMax());
   *Set_3 = *Set_1;
   Edit11->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------
//���������� ��������� 3 = ��������� 2
void __fastcall TMainForm::Button2Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("��������� 3 ��� �������� ������. ������� �������� ��� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("��������� ������� �� ���� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = new TSet(Set_2->GetMax());
   *Set_3 = *Set_2;
   Edit11->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------
//������������ ��������
void __fastcall TMainForm::Button3Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("��������� 3 ��� �������� ������. ������� �������� ��� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("��������� ������� �� ���� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = *Set_1 + *Set_2;
   Edit12->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------
//�������� ����������� ��������
void __fastcall TMainForm::Button4Click(TObject *Sender)
{
   if (Set_3 != NULL)
      {
         if (MessageDlg("��������� 3 ��� �������� ������. ������� �������� ��� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete Set_3;
               Set_3 = NULL;
            }
         else
            {
               MessageDlg("��������� ������� �� ���� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   Set_3 = *Set_1 * *Set_2;
   Edit13->Text = Set_3->PrintSet();
}
//---------------------------------------------------------------------------

