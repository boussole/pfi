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
   Canvas->Brush->Style = bsClear;  //чистая кисть,  он под текстом не рисуется
   Canvas->Font->Color = clBlue;	   //буквы синего цвета
   Canvas->Font->Size = 144;		   //размер букв - 144 пункта
   Canvas->Font->Name = "Webdings";	//название шрифта
   Canvas->TextOutA(50,5,'я');       //вывод буквы голубь

}
//---------------------------------------------------------------------------
 