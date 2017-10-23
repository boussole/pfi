//---------------------------------------------------------------------------
#ifndef PeopleInfoCodeH
#define PeopleInfoCodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Classes\\Human.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TPeopleInfoForm : public TForm
{
__published:	// IDE-managed Components
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TPanel *Panel1;
   TBitBtn *Save;
   TGroupBox *GroupBox1;
   TEdit *Edit1;
   TGroupBox *GroupBox2;
   TEdit *Edit2;
   TGroupBox *GroupBox3;
   TEdit *Edit3;
   TGroupBox *GroupBox4;
   TGroupBox *GroupBox5;
   TGroupBox *GroupBox6;
   TEdit *Edit4;
   TGroupBox *GroupBox7;
   TEdit *Edit5;
   TEdit *Edit6;
   TGroupBox *GroupBox8;
   TEdit *Edit7;
   TGroupBox *GroupBox9;
   TEdit *Edit8;
   TGroupBox *GroupBox10;
   TGroupBox *GroupBox11;
   TEdit *Edit9;
   TEdit *Edit10;
   TGroupBox *GroupBox12;
   TEdit *Edit11;
   TGroupBox *GroupBox13;
   TEdit *Edit12;
   TTabSheet *TabSheet2;
   TBitBtn *SetNewWay;
   TBitBtn *SetDefaultWay;
   TBitBtn *Exit;
   TBitBtn *ShowCurrentWay;
   TGroupBox *GroupBox14;
   TGroupBox *GroupBox15;
   TGroupBox *GroupBox16;
   TEdit *Edit13;
   TEdit *Edit14;
   TEdit *Edit15;
   TGroupBox *GroupBox17;
   TEdit *Edit16;
   TGroupBox *GroupBox19;
   TEdit *Edit18;
   TGroupBox *GroupBox20;
   TGroupBox *GroupBox18;
   TEdit *Edit17;
   TGroupBox *GroupBox21;
   TEdit *Edit19;
   TGroupBox *GroupBox22;
   TEdit *Edit20;
   TGroupBox *GroupBox23;
   TEdit *Edit21;
   TMainMenu *MainMenu1;
   TMenuItem *ControlPanel1;
   TMenuItem *Save1;
   TMenuItem *SetNewWay1;
   TMenuItem *SetdefaultWay1;
   TMenuItem *ShowCurrentWay1;
   TMenuItem *N1;
   TMenuItem *Exit1;
   TMenuItem *Help1;
   TMenuItem *About1;
   TMenuItem *About2;
   TBitBtn *BitBtn1;
   TSaveDialog *SaveDialog1;
   TMenuItem *SaveAs;
   TBitBtn *ScreenRes;
   TBitBtn *Clear;
   TMenuItem *ScrRes;
   TMenuItem *Clr;
   TGroupBox *GroupBox24;
   TEdit *Edit22;
   void __fastcall SaveClick(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall SetNewWayClick(TObject *Sender);
   void __fastcall SetDefaultWayClick(TObject *Sender);
   void __fastcall ExitClick(TObject *Sender);
   void __fastcall ShowCurrentWayClick(TObject *Sender);
   void __fastcall About1Click(TObject *Sender);
   void __fastcall About2Click(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall ScreenResClick(TObject *Sender);
   void __fastcall ClearClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TPeopleInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPeopleInfoForm *PeopleInfoForm;
//---------------------------------------------------------------------------
#endif
