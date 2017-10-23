//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "NewWay.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewWayForm *NewWayForm;
//---------------------------------------------------------------------------
__fastcall TNewWayForm::TNewWayForm(TComponent* Owner)
   : TForm(Owner)
{
}
/*/-----------------------------------------------------------------------/*/
AnsiString NewWay;
//---------------------------------------------------------------------------
void __fastcall TNewWayForm::BitBtn1Click(TObject *Sender)
{
   NewWay = "";
   NewWay = Edit1->Text;
   NewWayForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TNewWayForm::BitBtn2Click(TObject *Sender)
{
   NewWay = "";
   NewWayForm->Close();   
}
//---------------------------------------------------------------------------
