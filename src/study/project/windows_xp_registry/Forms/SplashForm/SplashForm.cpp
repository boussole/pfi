//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SplashForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSplash *Splash;
//---------------------------------------------------------------------------
__fastcall TSplash::TSplash(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSplash::Label6MouseEnter(TObject *Sender)
{
   Label6->Font->Style = TFontStyles() << fsBold << fsUnderline;
   Label6->Font->Color = clRed;
}
//---------------------------------------------------------------------------

void __fastcall TSplash::Label6MouseLeave(TObject *Sender)
{
   Label6->Font->Style = TFontStyles() << fsBold >> fsUnderline;
   Label6->Font->Color = clBlue;
}
//---------------------------------------------------------------------------
void __fastcall TSplash::Label6Click(TObject *Sender)
{
   ShellExecute(Handle, "open", "mailto:Null56@mail.ru", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

