//---------------------------------------------------------------------------

#ifndef RegistryReportUnitH
#define RegistryReportUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TfMain : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TStringGrid *StringGrid1;
        TGroupBox *GroupBox2;
        TEdit *Edit1;
        TGroupBox *GroupBox3;
        TEdit *Edit2;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TEdit *Edit3;
        TGroupBox *GroupBox6;
        TEdit *Edit4;
        TGroupBox *GroupBox7;
        TStringGrid *StringGrid3;
        TPanel *Panel1;
        TBitBtn *BitBtn1;
   TGroupBox *GroupBox8;
   TEdit *Edit5;
   TGroupBox *GroupBox9;
   TEdit *Edit6;
   TUpDown *UpDown1;
   TUpDown *UpDown2;
   TStringGrid *StringGrid2;
   TGroupBox *GroupBox10;
   TEdit *Edit7;
   TGroupBox *GroupBox11;
   TEdit *Edit8;
   TUpDown *UpDown3;
   TBitBtn *BitBtn2;
        TBitBtn *BitBtn3;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox12;
        TGroupBox *GroupBox13;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
   void __fastcall UpDown2Click(TObject *Sender, TUDBtnType Button);
   void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfMain *fMain;
//---------------------------------------------------------------------------
#endif
