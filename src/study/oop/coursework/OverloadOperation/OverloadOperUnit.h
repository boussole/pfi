//---------------------------------------------------------------------------

#ifndef OverloadOperUnitH
#define OverloadOperUnitH
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
   TGroupBox *Set1;
   TGroupBox *Set3;
   TGroupBox *GroupBox1;
   TEdit *Edit1;
   TBitBtn *BitBtn1;
   TGroupBox *GroupBox2;
   TEdit *Edit2;
   TBitBtn *BitBtn2;
   TGroupBox *GroupBox3;
   TEdit *Edit3;
   TBitBtn *BitBtn3;
   TGroupBox *GroupBox4;
   TEdit *Edit4;
   TBitBtn *BitBtn4;
   TGroupBox *GroupBox5;
   TEdit *Edit5;
   TBitBtn *BitBtn5;
   TGroupBox *GroupBox6;
   TGroupBox *GroupBox7;
   TEdit *Edit6;
   TBitBtn *BitBtn6;
   TGroupBox *GroupBox8;
   TEdit *Edit7;
   TBitBtn *BitBtn7;
   TGroupBox *GroupBox9;
   TEdit *Edit8;
   TBitBtn *BitBtn8;
   TGroupBox *GroupBox10;
   TEdit *Edit9;
   TBitBtn *BitBtn9;
   TGroupBox *GroupBox11;
   TEdit *Edit10;
   TBitBtn *BitBtn10;
   TGroupBox *GroupBox12;
   TEdit *Edit11;
   TButton *Button1;
   TButton *Button2;
   TGroupBox *GroupBox13;
   TGroupBox *GroupBox14;
   TEdit *Edit12;
   TEdit *Edit13;
   TButton *Button3;
   TButton *Button4;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn5Click(TObject *Sender);
   void __fastcall BitBtn3Click(TObject *Sender);
   void __fastcall BitBtn6Click(TObject *Sender);
   void __fastcall BitBtn10Click(TObject *Sender);
   void __fastcall BitBtn8Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
   void __fastcall BitBtn4Click(TObject *Sender);
   void __fastcall BitBtn7Click(TObject *Sender);
   void __fastcall BitBtn9Click(TObject *Sender);
   void __fastcall Button1Click(TObject *Sender);
   void __fastcall Button2Click(TObject *Sender);
   void __fastcall Button3Click(TObject *Sender);
   void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
