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
   //создадим объект-изображение
   Graphics::TBitmap *Pic = new Graphics::TBitmap;
    //загрузим изображение из файла tulips.bmp
    Pic->LoadFromFile("tulips.bmp");
    //выведем изображение в центре формы
    Canvas->Draw((ClientWidth - Pic->Width) / 2,
     (ClientHeight - Pic->Height) / 2, Pic) ;
    //освободим память, уничтожив объект-изображение
    Pic->Free();
}
//---------------------------------------------------------------------------
 