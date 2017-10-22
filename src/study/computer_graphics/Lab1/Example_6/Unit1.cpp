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
//���� ���� ShowPts ����� true, �� �����, �� �������
  //���������� ������ �����, ����������� ����������� �������
  bool ShowPts = false;

  //��������� �����, ������������ ������ �����

  //����� ����� ������� ����
  TPoint p1[7] = {
    Point(150, 250),
    Point(175, 275),
    Point(175, 300),
    Point(150, 325),
    Point(125, 350),
    Point(125, 400),
    Point(175, 425)
                  };


  //������ ����� ������� ����
  TPoint p2[7] = {
    Point(222, 250),
    Point(200, 275),
    Point(200, 300),
    Point(225, 325),
    Point(250, 350),
    Point(250, 400),
    Point(200, 425)
                 };


  //�������
  TPoint p3[4] = {
    Point(186, 246),
    Point(186, 150),
    Point(160,  50),
    Point(109, 138)
                 };

  //������
  TPoint p4[7] = {
    Point(53, 167),
    Point(70, 170),
    Point(100, 110),
    Point(109, 138),
    Point(138, 135),
    Point(100, 190),
    Point(110, 200)
                  };


  //������� ����� - ������ ����� ������
  TPoint p5[5] = {
    Point(53, 167),
    Point(72, 170),
    Point(81, 183),
    Point(100, 186),
    Point(110, 200)
                  };

  //������ ����
  TPoint p6[7] = {
    Point(186, 225),
    Point(205, 160),
    Point(219, 153),
    Point(262, 175),
    Point(246, 165),
    Point(205, 170),
    Point(186, 225)
                  };


  //����� ���� 
  TPoint p7[7] = {
    Point(186, 225),
    Point(154, 187),
    Point(130, 215),
    Point(112, 252),
    Point(142, 219),
    Point(167, 205),
    Point(186, 225)
                  };
/*/-----------------------------------------------------------------------/*/
//���������� ������� OnPaint. ����������, ����� ���������
//������ �������� �����������
void __fastcall TForm1::FormPaint(TObject *Sender)
{
   unsigned char i;

    //������� �������
    Canvas->Brush->Color = Color; //���� ����� = ����� �����
    Canvas->Font->Size = 12; //������ ������
    Canvas->Font->Name = "Comic Sans MS"; //�������� ������
    //������� �������
    Canvas->TextOut(40,10,"������ - ��������/�������� �����");

    //�������� ������ ����
    //��������� ���� � ������ ����
    Canvas->Pen->Color = clBlue; Canvas->Pen->Width = 4;

    //����� ������
    Canvas->PolyBezier(p1,7-1);

    //������ ������
    Canvas->PolyBezier(p2,7-1);

    //������� �������������� �����, �������������� ����
    Canvas->MoveTo(p1[0].x, p1[0].y); Canvas->LineTo(p2[0].x, p2[0].y);

    //������ �������������� �����, �������������� ����
    Canvas->MoveTo(p1[6].x, p1[6].y);Canvas->LineTo(p2[6].x, p2[6].y);

    //������ ���������� ����� ���� ��� �� ������, ����� �����  �� ������
    Canvas->Brush->Color = clBlue; //��������� ���� �����
    Canvas->FloodFill(p1[3].x+5, p1[3].y, clBlue, fsBorder); //�������� �������

    //�������� �������
    Canvas->Pen->Color = clGreen; //���� - �������� �����
    Canvas->PolyBezier(p3, 4-1);

    //�������� ������
    Canvas->Pen->Color = 0x00C080FF; //���� - ��������� �����
    Canvas->PolyBezier(p4, 7-1); //�������� ������� ����� ������ ������� ������
    Canvas->Polyline(p5, 5-1); //�������� ������ ����� ������ ������ � �������
    Canvas->Brush->Color = 0x00C080FF; //����� - ��������� �����
    //������ ���������� ����� ������ �������� �������
    Canvas->FloodFill(p5[1].x+5, p5[1].y, 0x00C080FF, fsBorder);

    //�������� ������ ����
    Canvas->Pen->Color = clGreen; //���� - �������� �����
    Canvas->Pen->Width = 3; //������ ���� - 3
    Canvas->PolyBezier(p6, 7-1); //�������� ������ �����
    Canvas->Brush->Color = clGreen; //����� - - �������� �����
    //������ ������������ ����� ������� �������
    Canvas->FloodFill(222, 172, clGreen, fsBorder);

    //�������� ����� ����
    Canvas->PolyBezier(p7,7-1); //������ �����
    Canvas->FloodFill(150, 213, clGreen, fsBorder); //�������� ���������� �����

    //���� ���� ShowPts = true, �� �������� �����, ����������� �����, �� ������� ���������� ������ ����� � ������� �� �������� ��������
    if (ShowPts)
      {
      //�������� ������� �����
      Canvas->Pen->Color = clBlack; Canvas->Pen->Style = psDot; Canvas->Brush->Color = Color;
      Canvas->Pen->Width = 1;
      Canvas->Polyline(p1, 7 - 1);
      Canvas->Polyline(p2, 7 - 1);
      Canvas->Polyline(p3, 4 - 1);
      Canvas->Polyline(p4, 7 - 1);
      Canvas->Polyline(p5, 5 - 1);
      Canvas->Polyline(p6, 7 - 1);
      Canvas->Polyline(p7, 7 - 1);

      //������� ����� �������� ��������
      Canvas->Pen->Color = clRed;
      Canvas->Brush->Color = clRed;
      for (i = 0; i < sizeof(p1); i++)
        Canvas->Ellipse(p1[i].x-3, p1[i].y-3, p1[i].x+3, p1[i].y+3);
      for (i = 0; i < sizeof(p2); i++)
        Canvas->Ellipse(p2[i].x-3, p2[i].y-3, p2[i].x+3, p2[i].y+3);
      for (i = 0; i < sizeof(p3); i++)
        Canvas->Ellipse(p3[i].x-3, p3[i].y-3, p3[i].x+3, p3[i].y+3);
      for (i = 0; i < sizeof(p4); i++)
        Canvas->Ellipse(p4[i].x-3, p4[i].y-3, p4[i].x+3, p4[i].y+3);
      for (i = 0; i < sizeof(p5); i++)
        Canvas->Ellipse(p6[i].x-3, p6[i].y-3, p6[i].x+3, p6[i].y+3);
      for (i = 0; i < sizeof(p6); i++)
        Canvas->Ellipse(p7[i].x-3, p7[i].y-3, p7[i].x+3, p7[i].y+3);
}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
//���� ������ ������� ������, �� ���������� ����� �����, ����������� �����, �� ������� ��������� ������ �����}
  if (Key == VK_SPACE)
   {
      if (ShowPts)
         ShowPts = false; //������� �������� ShowPts �� ���������������
      else
         ShowPts = true;
    Refresh(); //������� �������
   }
}
//---------------------------------------------------------------------------

