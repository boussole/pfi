//---------------------------------------------------------------------------

#ifndef ChangeSubTitlesH
#define ChangeSubTitlesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Grids.hpp>
/*/-----------------------------------------------------------------------/*/
/*/Описание структуры - строк/*/
   struct TClock
      {
         AnsiString Hour;
         AnsiString Minutes;
         AnsiString Secondes;
         AnsiString MilliSec;
      };
/*/-----------------------------------------------------------------------/*/
/*/Описание структуры - цифр/*/
   struct TRealTime
      {
         int Hour;
         int Minutes;
         int Secondes;
         int MilliSec;
      };
//---------------------------------------------------------------------------
class TChangeSubTitlesForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *Change;
   TGroupBox *Operation;
   TRadioButton *Sum;
   TRadioButton *Minus;
   TGroupBox *FileSubTitles;
   TEdit *Edit1;
   TOpenDialog *OpenDialog1;
   TBitBtn *BitBtn1;
   TGroupBox *SaveChangeSubTitles;
   TEdit *Edit2;
   TBitBtn *BitBtn2;
   TSaveDialog *SaveDialog1;
   TPanel *Panel1;
   TGroupBox *ChangeTime;
   TMainMenu *MainMenu1;
   TBitBtn *Run;
   TBitBtn *Exit;
   TStringGrid *StringGrid1;
   TMenuItem *ControlPanel1;
   TMenuItem *ChangeSubTitles1;
   TMenuItem *CloseProgram1;
   TMenuItem *AboutProgram1;
   TMenuItem *AboutProgram2;
   TMenuItem *About1;
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall RunClick(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall ExitClick(TObject *Sender);
   void __fastcall StringGrid1KeyPress(TObject *Sender, char &Key);
   void __fastcall AboutProgram2Click(TObject *Sender);
   void __fastcall About1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TChangeSubTitlesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChangeSubTitlesForm *ChangeSubTitlesForm;
//---------------------------------------------------------------------------
#endif
