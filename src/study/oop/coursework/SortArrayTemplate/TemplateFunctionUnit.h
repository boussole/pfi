//---------------------------------------------------------------------------

#ifndef TemplateFunctionUnitH
#define TemplateFunctionUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TPanel *Panel1;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   TBitBtn *BitBtn3;
   TBitBtn *BitBtn4;
   TLabeledEdit *LabeledEdit1;
   TGroupBox *GroupBox2;
   TStringGrid *StringGrid1;
   TStringGrid *StringGrid2;
   TButton *Button1;
   TButton *Button2;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   TRadioButton *RadioButton3;
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall BitBtn4Click(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
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
