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
   Canvas->Brush->Color = Color;		//цвет знакоместа - как у формы
   Canvas->Font->Color = clBlue;		//цвет текста -- синий
   Canvas->Font->Size = 10; 			//размер шрифта
   Canvas->Font->Name = "Times New Roman";	//шрифт
   //стиль начертания = толстый + наклонный + подчеркнутый
   Canvas->Font->Style = TFontStyles()<< fsBold << fsUnderline;
   //выведем рядом с курсором мыши его координаты
   Canvas->TextOut(X, Y, "(" + IntToStr(X) + "," + IntToStr(Y) + ")");
   //нарисуем под курсором толстую черную точку
   Canvas->Brush->Color = clBlack;			//цвет кисти - черный
   Canvas->Pen->Color = clBlack;			//цвет пера - черный
   Canvas->Ellipse(X - 3, Y - 3, X + 3, Y + 3); 	//маленький кружок
}
//---------------------------------------------------------------------------
 