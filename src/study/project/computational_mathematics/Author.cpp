//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Author.h"
#include <ShellAPI>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BitBtn1Click(TObject *Sender)
{
   Form3->Close();   
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Label11MouseEnter(TObject *Sender)
{
   Label11->Font->Color = clRed;
   Label11->Cursor = crHandPoint;
   Label11->Font->Style = TFontStyles() << fsBold << fsUnderline;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Label11MouseLeave(TObject *Sender)
{
   Label11->Font->Color = clBlue;
   Label11->Cursor = crDefault;
   Label11->Font->Style = TFontStyles() >> fsBold >> fsUnderline;
   Label11->Font->Style = TFontStyles() << fsBold;
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Label11Click(TObject *Sender)
{
   ShellExecute(Handle, "open", "mailto:fate13@inbox.ru", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

