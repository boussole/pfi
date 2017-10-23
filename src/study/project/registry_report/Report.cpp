//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Report.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfRep *fRep;
//---------------------------------------------------------------------------
__fastcall TfRep::TfRep(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TfRep::FormCreate(TObject *Sender)
{
        QRLabel4->Caption = "";
        QRLabel5->Caption = "";
        QRImage1->Canvas->Brush->Color = clWhite;
        QRImage1->Canvas->Rectangle(0, 0, 640, 340);
        QRImage1->Canvas->MoveTo(0, 20);
        QRImage1->Canvas->LineTo(640, 20);
        QRImage1->Canvas->MoveTo(0, 40);
        QRImage1->Canvas->LineTo(640, 40);
        QRImage1->Canvas->MoveTo(0, 60);
        QRImage1->Canvas->LineTo(640, 60);
        QRImage1->Canvas->MoveTo(0, 80);
        QRImage1->Canvas->LineTo(640, 80);
        QRImage1->Canvas->MoveTo(0, 100);
        QRImage1->Canvas->LineTo(640, 100);
        QRImage1->Canvas->MoveTo(0, 120);
        QRImage1->Canvas->LineTo(640, 120);
        QRImage1->Canvas->MoveTo(0, 140);
        QRImage1->Canvas->LineTo(640, 140);
        QRImage1->Canvas->MoveTo(0, 160);
        QRImage1->Canvas->LineTo(640, 160);
        QRImage1->Canvas->MoveTo(0, 180);
        QRImage1->Canvas->LineTo(640, 180);
        QRImage1->Canvas->MoveTo(0, 200);
        QRImage1->Canvas->LineTo(640, 200);
        QRImage1->Canvas->MoveTo(0, 220);
        QRImage1->Canvas->LineTo(640, 220);
        QRImage1->Canvas->MoveTo(0, 240);
        QRImage1->Canvas->LineTo(640, 240);
        QRImage1->Canvas->MoveTo(0, 260);
        QRImage1->Canvas->LineTo(640, 260);
        QRImage1->Canvas->MoveTo(0, 280);
        QRImage1->Canvas->LineTo(640, 280);
        QRImage1->Canvas->MoveTo(0, 300);
        QRImage1->Canvas->LineTo(640, 300);
        QRImage1->Canvas->MoveTo(0, 320);
        QRImage1->Canvas->LineTo(640, 320);
        //---------------------------------
        QRImage1->Canvas->MoveTo(40, 0);
        QRImage1->Canvas->LineTo(40, 360);
        QRImage1->Canvas->MoveTo(200, 0);
        QRImage1->Canvas->LineTo(200, 640);
        QRImage1->Canvas->MoveTo(280, 0);
        QRImage1->Canvas->LineTo(280, 640);
        QRImage1->Canvas->MoveTo(360, 0);
        QRImage1->Canvas->LineTo(360, 640);
        QRImage1->Canvas->MoveTo(500, 0);
        QRImage1->Canvas->LineTo(500, 640);
        //---------------------------------
        QRImage1->Canvas->TextOutA(5, 5, "№№");
        QRImage1->Canvas->TextOutA(5, 25, "1.");
        QRImage1->Canvas->TextOutA(5, 145, "2.");
        QRImage1->Canvas->TextOutA(5, 205, "3.");
        //---------------------------------
        QRImage1->Canvas->TextOutA(45, 5, "Пользователи");
        QRImage1->Canvas->Font->Style = TFontStyles() << fsBold;
        QRImage1->Canvas->TextOutA(45, 25, "Арендаторы всего:");
        QRImage1->Canvas->Font->Style = TFontStyles() >> fsBold;
        QRImage1->Canvas->TextOutA(45, 45, "арендаторы");
        QRImage1->Canvas->TextOutA(45, 65, "гаражи");
        QRImage1->Canvas->TextOutA(45, 85, "подсветка");
        QRImage1->Canvas->TextOutA(45, 105, "арендатор");
        QRImage1->Canvas->Font->Style = TFontStyles() << fsBold;
        QRImage1->Canvas->TextOutA(45, 145, "Домохозяйство");
        QRImage1->Canvas->TextOutA(45, 205, "Силовая электроэнергия");
        QRImage1->Canvas->Font->Style = TFontStyles() >> fsBold;
        QRImage1->Canvas->TextOutA(45, 225, "(в топл. смету)");
        QRImage1->Canvas->TextOutA(45, 265, "жильцы");
        QRImage1->Canvas->TextOutA(45, 285, "арендаторы");
        QRImage1->Canvas->Font->Style = TFontStyles() << fsBold << fsItalic;
        QRImage1->Canvas->TextOutA(145, 325, "ИТОГО:");
        QRImage1->Canvas->Font->Style = TFontStyles() >> fsBold >> fsItalic;
        //---------------------------------
        QRImage1->Canvas->TextOutA(222, 5, "Группа");
        QRImage1->Canvas->TextOutA(302, 5, "Тариф");
        QRImage1->Canvas->TextOutA(375, 5, "Количество кВт, факт");
        QRImage1->Canvas->TextOutA(510, 5, "По счету: сумма с НДС");
}
//---------------------------------------------------------------------------


