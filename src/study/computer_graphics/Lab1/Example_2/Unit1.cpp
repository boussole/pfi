//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
   Canvas->Brush->Style = bsClear;  //������ �����,  �� ��� ������� �� ��������
   Canvas->Font->Color = clBlue;	   //����� ������ �����
   Canvas->Font->Size = 144;		   //������ ���� - 144 ������
   Canvas->Font->Name = "Webdings";	//�������� ������
   Canvas->TextOutA(50,5,'�');       //����� ����� ������

}
//---------------------------------------------------------------------------
 