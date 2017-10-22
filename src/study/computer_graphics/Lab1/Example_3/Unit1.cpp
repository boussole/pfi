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

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
   Canvas->Brush->Color = Color;		//���� ���������� - ��� � �����
   Canvas->Font->Color = clBlue;		//���� ������ -- �����
   Canvas->Font->Size = 10; 			//������ ������
   Canvas->Font->Name = "Times New Roman";	//�����
   //����� ���������� = ������� + ��������� + ������������
   Canvas->Font->Style = TFontStyles()<< fsBold << fsUnderline;
   //������� ����� � �������� ���� ��� ����������
   Canvas->TextOut(X, Y, "(" + IntToStr(X) + "," + IntToStr(Y) + ")");
   //�������� ��� �������� ������� ������ �����
   Canvas->Brush->Color = clBlack;			//���� ����� - ������
   Canvas->Pen->Color = clBlack;			//���� ���� - ������
   Canvas->Ellipse(X - 3, Y - 3, X + 3, Y + 3); 	//��������� ������
}
//---------------------------------------------------------------------------
 