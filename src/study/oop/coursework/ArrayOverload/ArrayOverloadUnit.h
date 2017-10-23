//---------------------------------------------------------------------------

#ifndef ArrayOverloadUnitH
#define ArrayOverloadUnitH
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
   TGroupBox *Source;
   TGroupBox *Final;
   TStringGrid *StringGrid1;
   TStringGrid *StringGrid2;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TBitBtn *BitBtn3;
   TBitBtn *BitBtn4;
   TLabeledEdit *LabeledEdit1;
   TLabeledEdit *LabeledEdit2;
   TButton *Button1;
   TButton *Button2;
   TButton *Button3;
   TButton *Button4;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   void __fastcall BitBtn4Click(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Button3Click(TObject *Sender);
   void __fastcall Button4Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
