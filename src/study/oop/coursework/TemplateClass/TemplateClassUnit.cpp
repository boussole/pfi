//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "TemplateClassUnit.h"
#include "Class\\Set.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TManForm *ManForm;
//---------------------------------------------------------------------------
__fastcall TManForm::TManForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//���������� ����������
   TSet<unsigned int> *SetInt_1, *SetInt_2, *SetInt_3;
   TSet<unsigned short> *SetShort_1, *SetShort_2, *SetShort_3;
   TSet<char> *SetChar_1, *SetChar_2, *SetChar_3;
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TManForm::FormCreate(TObject *Sender)
{
   SetInt_1 = NULL; SetInt_2 = NULL; SetInt_3 = NULL;
   SetShort_1 = NULL; SetShort_2 = NULL; SetShort_3 = NULL;
   SetChar_1 = NULL; SetChar_2 = NULL; SetChar_3 = NULL;
}
//---------------------------------------------------------------------------
//����������� �����
void __fastcall TManForm::FormDestroy(TObject *Sender)
{
if (SetInt_1 != NULL) {delete SetInt_1;SetInt_1 = NULL;}
//-------------------
if (SetInt_2 != NULL) {delete SetInt_2;SetInt_2 = NULL;}
//-------------------
if (SetInt_3 != NULL) {delete SetInt_3;SetInt_3 = NULL;}
//-------------------
if (SetShort_1 != NULL) {delete SetShort_1;SetShort_1 = NULL;}
//-------------------
if (SetShort_2 != NULL) {delete SetShort_2;SetShort_2 = NULL;}
//-------------------
if (SetShort_3 != NULL) {delete SetShort_3;SetShort_3 = NULL;}
//-------------------
if (SetChar_1 != NULL)  {delete SetChar_1;SetChar_1 = NULL;}
//-------------------
if (SetChar_2 != NULL)  {delete SetChar_2;SetChar_2 = NULL;}
//-------------------
if (SetChar_3 != NULL)  {delete SetChar_3; SetChar_3 = NULL;}
}
//---------------------------------------------------------------------------
//�������� ��������� 1
void __fastcall TManForm::BitBtn1Click(TObject *Sender)
{
//---------------------------
//�������� ��������� ���� int
if (RadioButton1->Checked)
{
if (SetInt_1 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ������� ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetInt_1;
               SetInt_1 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit1->Text) <= 0)
            {
               MessageDlg("����������� ������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetInt_1 = new TSet<unsigned int>(StrToInt(Edit1->Text));
      GroupBox4->Enabled = false;
}
//-----------------------------
//�������� ��������� ���� Short
if (RadioButton2->Checked)
{
if (SetShort_1 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ������� ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetShort_1;
               SetShort_1 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit1->Text) <= 0)
            {
               MessageDlg("����������� ������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetShort_1 = new TSet<unsigned short>(StrToInt(Edit1->Text));
      GroupBox4->Enabled = false;
}
//------------------------------
//�������� ��������� ���� Short
if (RadioButton3->Checked)
{
if (SetChar_1 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ������� ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetChar_1;
               SetChar_1 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit1->Text) <= 0)
            {
               MessageDlg("����������� ������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetChar_1 = new TSet<char>(StrToInt(Edit1->Text));
      GroupBox4->Enabled = false;
}
}
//---------------------------------------------------------------------------
//�������� ������� � ��������� 1
void __fastcall TManForm::BitBtn2Click(TObject *Sender)
{
//���������� � ��������� ���� Int
if (RadioButton1->Checked)
{
   if (SetInt_1 != NULL)
      {
      try
         {
            (*SetInt_1) + StrToInt(Edit2->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//���������� � ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_1 != NULL)
      {
      try
         {
            (*SetShort_1) + StrToInt(Edit2->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//���������� � ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_1 != NULL)
      {
         if (Edit2->Text == "")
         {
            MessageDlg("������ ������������ �������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            return;
         }
         (*SetChar_1) + Edit2->Text[1];
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
}
//---------------------------------------------------------------------------
//�������� �� ��������� 1
void __fastcall TManForm::BitBtn3Click(TObject *Sender)
{
//�������� � ��������� ���� Int
if (RadioButton1->Checked)
{
   if (SetInt_1 != NULL)
      {
      try
         {
            (*SetInt_1) - StrToInt(Edit3->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_1 != NULL)
      {
      try
         {
            (*SetShort_1) - StrToInt(Edit3->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_1 != NULL)
      {
         if (Edit3->Text == "")
         {
            MessageDlg("������ ���������� �������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            return;
         }
         (*SetChar_1) - Edit3->Text[1];
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
}
//---------------------------------------------------------------------------
//���������� ��������� 1
void __fastcall TManForm::BitBtn4Click(TObject *Sender)
{
//�������� � ��������� ���� Int
if (RadioButton1->Checked)
{
   if (SetInt_1 != NULL)
      {
         Edit4->Text = SetInt_1->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_1 != NULL)
      {
         Edit4->Text = SetShort_1->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_1 != NULL)
      {
         Edit4->Text = SetChar_1->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
}
//---------------------------------------------------------------------------
//�������� ��������� 2
void __fastcall TManForm::BitBtn5Click(TObject *Sender)
{
//---------------------------
//�������� ��������� ���� int
if (RadioButton1->Checked)
{
   if (SetInt_2 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ������� ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetInt_2;
               SetInt_2 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit5->Text) <= 0)
            {
               MessageDlg("����������� ������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetInt_2 = new TSet<unsigned int>(StrToInt(Edit5->Text));
      GroupBox4->Enabled = false;
}
//-----------------------------
//�������� ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_2 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ������� ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetShort_2;
               SetShort_2 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit5->Text) <= 0)
            {
               MessageDlg("����������� ������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetShort_2 = new TSet<unsigned short>(StrToInt(Edit5->Text));
      GroupBox4->Enabled = false;
}
//------------------------------
//�������� ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_2 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ������� ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetChar_2;
               SetChar_2 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   try
      {
         if (StrToInt(Edit5->Text) <= 0)
            {
               MessageDlg("����������� ������� ������ ���� �������������!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   catch (EConvertError &)
      {
         MessageDlg("������ � ��������� ����������� ���������", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
      SetChar_2 = new TSet<char>(StrToInt(Edit5->Text));
      GroupBox4->Enabled = false;
}
}
//---------------------------------------------------------------------------
//���������� � ��������� 2
void __fastcall TManForm::BitBtn6Click(TObject *Sender)
{
//���������� � ��������� ���� Int
if (RadioButton1->Checked)
{
   if (SetInt_2 != NULL)
      {
      try
         {
            (*SetInt_2) + StrToInt(Edit6->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//���������� � ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_2 != NULL)
      {
      try
         {
            (*SetShort_2) + StrToInt(Edit6->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//���������� � ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_2 != NULL)
      {
      if (Edit6->Text == "")
         {
            MessageDlg("������ ������������ �������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            return;
         }
         (*SetChar_2) + Edit6->Text[1];
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
}
//---------------------------------------------------------------------------
//�������� �������� �� ��������� 2
void __fastcall TManForm::BitBtn7Click(TObject *Sender)
{
//�������� � ��������� ���� Int
if (RadioButton1->Checked)
{
   if (SetInt_2 != NULL)
      {
      try
         {
            (*SetInt_2) - StrToInt(Edit7->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_2 != NULL)
      {
      try
         {
            (*SetShort_2) - StrToInt(Edit7->Text);
         }
      catch (EConvertError &)
         {
            MessageDlg("������ � ��������� ����� ������������ � ���������", mtError, TMsgDlgButtons() << mbOK, 0);
            return;
         }
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_2 != NULL)
      {
      if (Edit7->Text == "")
         {
            MessageDlg("������ ���������� �������� �� ���������!!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            return;
         }
         (*SetChar_2) - Edit7->Text[1];
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
}
//---------------------------------------------------------------------------
//���������� ��������� 2
void __fastcall TManForm::BitBtn8Click(TObject *Sender)
{
//�������� � ��������� ���� Int
if (RadioButton1->Checked)
{
   if (SetInt_2 != NULL)
      {
         Edit8->Text = SetInt_2->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Short
if (RadioButton2->Checked)
{
   if (SetShort_2 != NULL)
      {
         Edit8->Text = SetShort_2->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//�������� � ��������� ���� Char
if (RadioButton3->Checked)
{
   if (SetChar_2 != NULL)
      {
         Edit8->Text = SetChar_2->PrintSet();
      }
   else
      {
         MessageDlg("��������� �� �������", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
}
//---------------------------------------------------------------------------
//���������� ��������� 3 = ��������� 1
void __fastcall TManForm::BitBtn9Click(TObject *Sender)
{
//����������� ��������� Int
if (RadioButton1->Checked)
{
   if (SetInt_3 != NULL)
      {
         if (MessageDlg("������� ������ ��������� ������ ����������. ������� ���������� ���������", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete SetInt_3;
               SetInt_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetInt_3 = new TSet<unsigned int>(SetInt_1->GetMax());
   *SetInt_3 = *SetInt_1;
   Edit9->Text = SetInt_3->PrintSet();
}
//����������� ��������� Short
if (RadioButton2->Checked)
{
   if (SetShort_3 != NULL)
      {
         if (MessageDlg("������� ������ ��������� ������ ����������. ������� ���������� ���������", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete SetShort_3;
               SetShort_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetShort_3 = new TSet<unsigned short>(SetShort_1->GetMax());
   *SetShort_3 = *SetShort_1;
   Edit9->Text = SetShort_3->PrintSet();
}
//����������� ��������� Char
if (RadioButton3->Checked)
{
   if (SetChar_3 != NULL)
      {
         if (MessageDlg("������� ������ ��������� ������ ����������. ������� ���������� ���������", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete SetChar_3;
               SetChar_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetChar_3 = new TSet<char>(SetChar_1->GetMax());
   *SetChar_3 = *SetChar_1;
   Edit9->Text = SetChar_3->PrintSet();
}
}
//---------------------------------------------------------------------------
//���������� ��������� 3 = ��������� 2 
void __fastcall TManForm::BitBtn10Click(TObject *Sender)
{
//����������� ��������� Int
if (RadioButton1->Checked)
{
   if (SetInt_3 != NULL)
      {
         if (MessageDlg("������� ������ ��������� ������ ����������. ������� ���������� ���������", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete SetInt_3;
               SetInt_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetInt_3 = new TSet<unsigned int>(SetInt_2->GetMax());
   *SetInt_3 = *SetInt_2;
   Edit9->Text = SetInt_3->PrintSet();
}
//����������� ��������� Short
if (RadioButton2->Checked)
{
   if (SetShort_3 != NULL)
      {
         if (MessageDlg("������� ������ ��������� ������ ����������. ������� ���������� ���������", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete SetShort_3;
               SetShort_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetShort_3 = new TSet<unsigned short>(SetShort_2->GetMax());
   *SetShort_3 = *SetShort_2;
   Edit9->Text = SetShort_3->PrintSet();
}
//����������� ��������� Char
if (RadioButton3->Checked)
{
   if (SetChar_3 != NULL)
      {
         if (MessageDlg("������� ������ ��������� ������ ����������. ������� ���������� ���������", mtConfirmation, TMsgDlgButtons() << mbYes<< mbNo, 0) == mrYes)
            {
               delete SetChar_3;
               SetChar_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetChar_3 = new TSet<char>(SetChar_2->GetMax());
   *SetChar_3 = *SetChar_2;
   Edit9->Text = SetChar_3->PrintSet();
}
}
//---------------------------------------------------------------------------
//����������� ��������
void __fastcall TManForm::BitBtn11Click(TObject *Sender)
{
//��� Int
if (RadioButton1->Checked)
   {
   if (SetInt_3 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetInt_3;
               SetInt_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetInt_3 = *SetInt_1 + *SetInt_2;
   Edit10->Text = SetInt_3->PrintSet();
   }
//��� Short
if (RadioButton2->Checked)
   {
   if (SetShort_3 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetShort_3;
               SetShort_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetShort_3 = *SetShort_1 + *SetShort_2;
   Edit10->Text = SetShort_3->PrintSet();
   }
//��� Char
if (RadioButton3->Checked)
   {
   if (SetChar_3 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetChar_3;
               SetChar_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetChar_3 = *SetChar_1 + *SetChar_2;
   Edit10->Text = SetChar_3->PrintSet();
   }
}
//---------------------------------------------------------------------------
//����������� ��������
void __fastcall TManForm::BitBtn12Click(TObject *Sender)
{
//��� Int
if (RadioButton1->Checked)
   {
   if (SetInt_3 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetInt_3;
               SetInt_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetInt_3 = *SetInt_1 * *SetInt_2;
   Edit11->Text = SetInt_3->PrintSet();
   }
//��� Short
if (RadioButton2->Checked)
   {
   if (SetShort_3 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetShort_3;
               SetShort_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetShort_3 = *SetShort_1 * *SetShort_2;
   Edit11->Text = SetShort_3->PrintSet();
   }
//��� Char
if (RadioButton3->Checked)
   {
   if (SetChar_3 != NULL)
      {
         if (MessageDlg("������� ������ ������ ������ ����������. ���������� ������?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
            {
               delete SetChar_3;
               SetChar_3 = NULL;
            }
         else
            {
               MessageDlg("��������� �� ������� !!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return;
            }
      }
   SetChar_3 = *SetChar_1 * *SetChar_2;
   Edit11->Text = SetChar_3->PrintSet();
   }
}
//---------------------------------------------------------------------------
//������ �������� ��� ��������� ��� �������� ����� ������
void __fastcall TManForm::BitBtn13Click(TObject *Sender)
{
if (SetInt_1 != NULL) {delete SetInt_1;SetInt_1 = NULL;}
//-------------------
if (SetInt_2 != NULL) {delete SetInt_2;SetInt_2 = NULL;}
//-------------------
if (SetInt_3 != NULL) {delete SetInt_3;SetInt_3 = NULL;}
//-------------------
if (SetShort_1 != NULL) {delete SetShort_1;SetShort_1 = NULL;}
//-------------------
if (SetShort_2 != NULL) {delete SetShort_2;SetShort_2 = NULL;}
//-------------------
if (SetShort_3 != NULL) {delete SetShort_3;SetShort_3 = NULL;}
//-------------------
if (SetChar_1 != NULL)  {delete SetChar_1;SetChar_1 = NULL;}
//-------------------
if (SetChar_2 != NULL)  {delete SetChar_2;SetChar_2 = NULL;}
//-------------------
if (SetChar_3 != NULL)  {delete SetChar_3; SetChar_3 = NULL;}
Edit1->Clear(); Edit2->Clear(); Edit3->Clear(); Edit4->Clear();
Edit5->Clear(); Edit6->Clear(); Edit7->Clear(); Edit8->Clear();
Edit9->Clear(); Edit10->Clear(); Edit11->Clear();
GroupBox4->Enabled = true;
}
//---------------------------------------------------------------------------
