//---------------------------------------------------------------------------

#ifndef ArrayCodeH
#define ArrayCodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox2;
   TGroupBox *ControlPanel;
   TStringGrid *SourceArray;
   TStringGrid *FinalArray;
   TGroupBox *SizeOfMatrix;
   TLabeledEdit *LabeledEdit1;
   TLabeledEdit *LabeledEdit2;
   TBitBtn *ButtonDo;
   TBitBtn *ButtonExit;
   TGroupBox *Action;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   TBitBtn *BitBtn1;
   void __fastcall ButtonExitClick(TObject *Sender);
   void __fastcall RadioButton1Click(TObject *Sender);
   void __fastcall RadioButton2Click(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall ButtonDoClick(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall LabeledEdit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall LabeledEdit2KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
