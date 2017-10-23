//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "SplashForm.h"
#include <ShellAPI>
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
   Label6->Font->Color = clRed;
   Label6->Font->Style = TFontStyles() << fsBold << fsUnderline;

}
//---------------------------------------------------------------------------

void __fastcall TSplash::Label6MouseLeave(TObject *Sender)
{
   Label6->Font->Color = clBlue;
   Label6->Font->Style = TFontStyles() >> fsBold >> fsUnderline;
   Label6->Font->Style = TFontStyles() << fsBold;
}
//---------------------------------------------------------------------------

void __fastcall TSplash::Label6Click(TObject *Sender)
{
   ShellExecute(Handle, "open", "mailto:fate13@inbox.ru", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

