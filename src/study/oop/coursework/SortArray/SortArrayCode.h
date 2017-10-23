//---------------------------------------------------------------------------

#ifndef SortArrayCodeH
#define SortArrayCodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *Source;
   TStringGrid *StringGrid1;
   TGroupBox *SortOut;
   TStringGrid *StringGrid2;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TBitBtn *ClearStringGrid;
   TLabeledEdit *LabeledEdit1;
   TBitBtn *Exit;
   TButton *AddTable;
   TButton *DeleteTable;
   void __fastcall ExitClick(TObject *Sender);
   void __fastcall ClearStringGridClick(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall AddTableClick(TObject *Sender);
   void __fastcall DeleteTableClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
