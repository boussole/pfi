//---------------------------------------------------------------------------

#ifndef SetUnitH
#define SetUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TEdit *Edit1;
   TBitBtn *BitBtn1;
   TGroupBox *GroupBox2;
   TEdit *Edit2;
   TBitBtn *BitBtn2;
   TGroupBox *GroupBox3;
   TGroupBox *GroupBox4;
   TEdit *Edit3;
   TEdit *Edit4;
   TBitBtn *BitBtn3;
   TBitBtn *BitBtn4;
   TGroupBox *GroupBox5;
   TEdit *Edit5;
   TBitBtn *BitBtn5;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn5Click(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
   void __fastcall BitBtn4Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
