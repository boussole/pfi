//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FileName.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFileNameForm *FileNameForm;
AnsiString FileNameHelp;
//---------------------------------------------------------------------------
__fastcall TFileNameForm::TFileNameForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFileNameForm::CancelClick(TObject *Sender)
{
   FileNameForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFileNameForm::OkClick(TObject *Sender)
{
   FileNameHelp = Edit1->Text;
   FileNameForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TFileNameForm::FormCreate(TObject *Sender)
{
   FileNameHelp = "";   
}
//---------------------------------------------------------------------------

