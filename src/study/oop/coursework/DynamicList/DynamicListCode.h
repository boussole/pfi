//---------------------------------------------------------------------------

#ifndef DynamicListCodeH
#define DynamicListCodeH
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
   TGroupBox *GroupBox2;
   TPanel *Panel1;
   TLabeledEdit *LabeledEdit1;
   TBitBtn *Create;
   TBitBtn *BitBtn2;
   TBitBtn *BitBtn3;
   TBitBtn *BitBtn4;
   TBitBtn *BitBtn5;
   TStringGrid *StringGrid1;
   TStringGrid *StringGrid2;
   TBitBtn *BitBtn1;
   TBitBtn *Exit;
   TStringGrid *StringGrid3;
   TBitBtn *BitBtn6;
   TBitBtn *BitBtn7;
   TBitBtn *BitBtn8;
   TBitBtn *BitBtn9;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall ExitClick(TObject *Sender);
   void __fastcall CreateClick(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn4Click(TObject *Sender);
   void __fastcall BitBtn5Click(TObject *Sender);
   void __fastcall BitBtn6Click(TObject *Sender);
   void __fastcall BitBtn7Click(TObject *Sender);
   void __fastcall BitBtn9Click(TObject *Sender);
   void __fastcall BitBtn8Click(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
