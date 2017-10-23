//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DynamicListCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------
//��������� ������ ����
struct TLIST
   {
      char *Shifr;
      char *FIO;
      double Ball;
      TLIST *Next;
   };
//---------------------------------------------------------------------------
//��������� �� ������� �����
TLIST *Head;
//�����������
unsigned Size;
//---------------------------------------------------------------------------
//��������� �������
bool CreateList(TLIST **, TStringGrid *, unsigned int &, bool);
void DeleteList(TLIST **);
bool AddUp(TLIST *, TStringGrid *);
bool DeleteElement(TLIST **);
void PrintList(TLIST *, TStringGrid *, unsigned int);
void ClearTable(TStringGrid *);
//---------------------------------------------------------------------------
//������� �������
void ClearTable(TStringGrid *Table)
{
   for (int i = 1; i < Table->RowCount; i++)
   for (int j = 0; j < 3; j++)
      {
         Table->Cells[j][i] = "";
      }
   Table->RowCount = 2;
}
//---------------------------------------------------------------------------
//�������� �� �������
bool DeleteElement(TLIST **_Head)
{
   if (*_Head != NULL)
      {
         TLIST *Help = *_Head;
         (*_Head)= (*_Head)->Next;
         delete Help;
         Help = NULL;
         return true;
      }
   else
      {
         return false;
      }
}
//---------------------------------------------------------------------------
//������� ����� ������ �� �����
void PrintList(TLIST *_Head, TStringGrid *Table, unsigned int _Size)
{
   if (_Head == NULL)
      {
         MessageDlg("������ ����", mtInformation, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   TLIST *Help = _Head;
   int i = 1;
   Table->RowCount = Size + 1;
   while (Help != NULL)
      {
         Table->Cells[0][i] = AnsiString(Help->Shifr);
         Table->Cells[1][i] = AnsiString(Help->FIO);
         Table->Cells[2][i++] = Help->Ball;
         Help = Help->Next;
      }
}
//---------------------------------------------------------------------------
//������� ���������� �������� � ������� ������
bool AddUp(TLIST **_Head, TStringGrid *Table)
{
   TLIST *Help = new TLIST;
   Help->Shifr = Table->Cells[0][1].c_str();
   Help->FIO = Table->Cells[1][1].c_str();
   try
      {
      Help->Ball = StrToFloat(Table->Cells[2][1]);
      }
   catch(EConvertError &)
      {
         MessageDlg("������ ���������  �������� ����!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         delete Help;
         return false;
      }
   Help->Next = NULL;
   //�������� ������������� ��������
   if (*_Head == NULL)
      {
         *_Head = Help;
      }
   //������� � ������
   else
      {
         Help->Next = *_Head;
         *_Head = Help;
      }
   return true;
}
//---------------------------------------------------------------------------
//������� ������� ������ �� n - ���������
bool CreateList(TLIST **_Head, TStringGrid *Table, unsigned int &_Size, bool St)
{
   unsigned int H = 0;
   //�������� �� ������� ������
   if (*_Head != NULL)
      {
         if ( (MessageDlg("������� ������ ������. ������� �������� ������?",
              mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0)) == mrYes)
              {
                  DeleteList(_Head);
              }
         else
            {
               MessageDlg("������ ������ �� ���!!!", mtInformation, TMsgDlgButtons() << mbOK, 0);
               return true;
            }
      }
   //�������� ������
   TLIST *Help, *CreateEl;
   for (unsigned int i = 1; i < _Size + 1; i++)
      {
         //�������� ��������
         CreateEl = new TLIST;
         CreateEl->Shifr = Table->Cells[0][i].c_str();
         CreateEl->FIO = Table->Cells[1][i].c_str();
         try
            {
               CreateEl->Ball = StrToFloat(Table->Cells[2][i]);
            }
         catch(EConvertError &)
            {
               delete CreateEl;
               CreateEl = NULL;
               if (MessageDlg("������ ��������� �������� ����. ������� �������� ��� ��������� ������ � �����?", mtError, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes)
                  {
                     DeleteList(_Head);
                     return false;
                  }
               else
                  {
                     continue;
                  }
            }
         CreateEl->Next = NULL;
         H++;
         //--------------------
         //������� � ������ ������
         if (*_Head == NULL)
            {
               *_Head = CreateEl;
            }
         //����� ����� �������
         else
            {
               if (!St)
                  {
                  Help = *_Head;
                  while (Help->Next != NULL)
                     {
                        Help = Help->Next;
                     }
                  //�������
                  Help->Next = CreateEl;
                  }
               else
                  {
                     CreateEl->Next = *_Head;
                     *_Head = CreateEl;   
                  }
            }
      }
   _Size = H;
   return true;
}
//---------------------------------------------------------------------------
//������� �����
void DeleteList(TLIST **_Head)
{
   TLIST *Help;
   while ((*_Head) != NULL)
      {
         Help = *_Head;
         *_Head = (*_Head)->Next;
         delete Help;
         Help = NULL;
      }
   *_Head = NULL;
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
   StringGrid1->Cells[0][0] = "����";
   StringGrid1->Cells[1][0] = "                   ���";
   StringGrid1->Cells[2][0] = "��. ���";
   StringGrid2->Cells[0][0] = "����";
   StringGrid2->Cells[1][0] = "                   ���";
   StringGrid2->Cells[2][0] = "��. ���";
   StringGrid3->Cells[0][0] = "����";
   StringGrid3->Cells[1][0] = "                   ���";
   StringGrid3->Cells[2][0] = "��. ���";
   //"���������" ���������
   Head = NULL;
   Size = 0;
}
//---------------------------------------------------------------------------
//������ "�����"
void __fastcall TMainForm::ExitClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//�������� ����� �� n ���������
void __fastcall TMainForm::CreateClick(TObject *Sender)
{
   try
      {
         Size = StrToInt(LabeledEdit1->Text);
      }
   catch(EConvertError&)
      {
         MessageDlg("������ � ���������� ����������� �����", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
   if (StrToInt(LabeledEdit1->Text) < 1)
      {
         MessageDlg("����������� ������ ������ ���� �������������", mtInformation, TMsgDlgButtons() << mbOK, 0);
         Size = 0;
         return;
      }
   if (!CreateList(&Head, StringGrid1, Size, RadioButton2->Checked))
      Size = 0;
}
//---------------------------------------------------------------------------
//�������� ������
void __fastcall TMainForm::BitBtn3Click(TObject *Sender)
{
   StringGrid1->RowCount += 1;
   LabeledEdit1->Text = StringGrid1->RowCount - 1;
}
//---------------------------------------------------------------------------
//������� ������
void __fastcall TMainForm::BitBtn2Click(TObject *Sender)
{
   if (StringGrid1->RowCount > 2)
      {
         StringGrid1->RowCount -= 1;
         LabeledEdit1->Text = StringGrid1->RowCount - 1;
      }
}
//---------------------------------------------------------------------------
//������ "������� ������"
void __fastcall TMainForm::BitBtn1Click(TObject *Sender)
{
   DeleteList(&Head);
   Size = 0;
}
//---------------------------------------------------------------------------
//������ "������� �� �������"
void __fastcall TMainForm::BitBtn4Click(TObject *Sender)
{
   if (DeleteElement(&Head))
      Size--;
}
//---------------------------------------------------------------------------
//������ "�������� � �������"
void __fastcall TMainForm::BitBtn5Click(TObject *Sender)
{
   if (AddUp(&Head, StringGrid3))
      Size++;
}
//---------------------------------------------------------------------------
//����� ������ �� �����
void __fastcall TMainForm::BitBtn6Click(TObject *Sender)
{
   ClearTable(StringGrid2);
   PrintList(Head, StringGrid2, Size);
}
//---------------------------------------------------------------------------
//���������� ���������
void __fastcall TMainForm::BitBtn7Click(TObject *Sender)
{
   MessageDlg("���������� ��������� � �����:  " + IntToStr(Size), mtInformation, TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------
//�������� �� ������� �����

void __fastcall TMainForm::BitBtn9Click(TObject *Sender)
{
   ClearTable(StringGrid1);
   ClearTable(StringGrid2);
   ClearTable(StringGrid3);
}
//---------------------------------------------------------------------------
//����� �������� �� ������� �����
void __fastcall TMainForm::BitBtn8Click(TObject *Sender)
{
   ClearTable(StringGrid3);
   if (Head != NULL)
      {
         StringGrid3->Cells[0][1] = AnsiString(Head->Shifr);
         StringGrid3->Cells[1][1] = AnsiString(Head->FIO);
         StringGrid3->Cells[2][1] = Head->Ball;
      }
   else
      {
         MessageDlg("������ ����", mtInformation, TMsgDlgButtons() << mbOK, 0);
      }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
   DeleteList(&Head);  
}
//---------------------------------------------------------------------------

