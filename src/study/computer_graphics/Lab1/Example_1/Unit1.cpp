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
   //Нарисуем левый круг, используя стандартный стиль закраски
   Canvas->Pen->Color = clLime; //зеленый цвет для пера
   Canvas->Pen->Width = 3; //перо толщиной 3 точки
   Canvas->Brush->Color = clRed; //красный цвет для кисти
   Canvas->Brush->Style = bsBDiagonal; //закраска наклонными линиями
   //рисуется первый круг
   Canvas->Ellipse(10,10,160,160);
   //Нарисуем правый круг, используя собственный шаблон для кисти
   //создадим изображение-шаблон
   bmp->PixelFormat = pf24bit; //формат изображения - TrueColor
   bmp->Width = 8; bmp->Height = 8; //размер 8x8 точек
   //нарисуем на изображении красный кружок
   bmp->Canvas->Pen->Color = clRed;
   bmp->Canvas->Brush->Color = clRed;
   bmp->Canvas->Ellipse(0, 0, 5, 5) ;
   Canvas->Brush->Bitmap = bmp; //выберем изображение как шаблон для кисти
   //рисуется второй круг
   Canvas->Ellipse(170,10,320,160);
   //удалим изображение
   Canvas->Brush->Bitmap = NULL;
   delete bmp;
}
//---------------------------------------------------------------------------
 