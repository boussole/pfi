//---------------------------------------------------------------------------

#ifndef TemplateClassUnitH
#define TemplateClassUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TManForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TGroupBox *GroupBox3;
   TGroupBox *GroupBox4;
   TGroupBox *GroupBox5;
   TEdit *Edit1;
   TBitBtn *BitBtn1;
   TGroupBox *GroupBox6;
   TEdit *Edit2;
   TBitBtn *BitBtn2;
   TGroupBox *GroupBox7;
   TEdit *Edit3;
   TBitBtn *BitBtn3;
   TGroupBox *GroupBox8;
   TEdit *Edit4;
   TBitBtn *BitBtn4;
   TGroupBox *GroupBox2;
   TGroupBox *GroupBox9;
   TEdit *Edit5;
   TBitBtn *BitBtn5;
   TGroupBox *GroupBox10;
   TEdit *Edit6;
   TBitBtn *BitBtn6;
   TGroupBox *GroupBox11;
   TEdit *Edit7;
   TBitBtn *BitBtn7;
   TGroupBox *GroupBox12;
   TEdit *Edit8;
   TBitBtn *BitBtn8;
   TGroupBox *GroupBox13;
   TGroupBox *GroupBox14;
   TGroupBox *GroupBox15;
   TRadioButton *RadioButton1;
   TEdit *Edit9;
   TEdit *Edit10;
   TEdit *Edit11;
   TBitBtn *BitBtn9;
   TBitBtn *BitBtn10;
   TBitBtn *BitBtn11;
   TBitBtn *BitBtn12;
   TRadioButton *RadioButton2;
   TRadioButton *RadioButton3;
   TBitBtn *BitBtn13;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
   void __fastcall BitBtn4Click(TObject *Sender);
   void __fastcall BitBtn5Click(TObject *Sender);
   void __fastcall BitBtn6Click(TObject *Sender);
   void __fastcall BitBtn7Click(TObject *Sender);
   void __fastcall BitBtn8Click(TObject *Sender);
   void __fastcall BitBtn9Click(TObject *Sender);
   void __fastcall BitBtn10Click(TObject *Sender);
   void __fastcall BitBtn11Click(TObject *Sender);
   void __fastcall BitBtn12Click(TObject *Sender);
   void __fastcall BitBtn13Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TManForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TManForm *ManForm;
//---------------------------------------------------------------------------
#endif
