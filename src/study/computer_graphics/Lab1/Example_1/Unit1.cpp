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
   Graphics :: TBitmap *bmp = new Graphics :: TBitmap;
   //�������� ����� ����, ��������� ����������� ����� ��������
   Canvas->Pen->Color = clLime; //������� ���� ��� ����
   Canvas->Pen->Width = 3; //���� �������� 3 �����
   Canvas->Brush->Color = clRed; //������� ���� ��� �����
   Canvas->Brush->Style = bsBDiagonal; //�������� ���������� �������
   //�������� ������ ����
   Canvas->Ellipse(10,10,160,160);
   //�������� ������ ����, ��������� ����������� ������ ��� �����
   //�������� �����������-������
   bmp->PixelFormat = pf24bit; //������ ����������� - TrueColor
   bmp->Width = 8; bmp->Height = 8; //������ 8x8 �����
   //�������� �� ����������� ������� ������
   bmp->Canvas->Pen->Color = clRed;
   bmp->Canvas->Brush->Color = clRed;
   bmp->Canvas->Ellipse(0, 0, 5, 5) ;
   Canvas->Brush->Bitmap = bmp; //������� ����������� ��� ������ ��� �����
   //�������� ������ ����
   Canvas->Ellipse(170,10,320,160);
   //������ �����������
   Canvas->Brush->Bitmap = NULL;
   delete bmp;
}
//---------------------------------------------------------------------------
 