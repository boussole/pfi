//---------------------------------------------------------------------------

#ifndef HairdressingSalonCodeH
#define HairdressingSalonCodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "Class\\Rendering.h"
#include "Class\\TModel.h"
#include "Class\\RendererStatus.h"
#include "SplashForm.cpp"
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
   TTreeView *TreeView1;
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TTabSheet *TabSheet2;
   TTabSheet *TabSheet3;
   TPanel *Panel1;
   TScrollBar *Gorizontal;
   TScrollBar *Vertical;
   TImage *Image1;
   TTabSheet *TabSheet4;
   TGroupBox *GroupBox2;
   TGroupBox *GroupBox4;
   TEdit *Edit2;
   TUpDown *UpDown1;
   TGroupBox *GroupBox5;
   TEdit *Edit3;
   TUpDown *UpDown2;
   TGroupBox *GroupBox6;
   TStringGrid *StringGrid1;
   TGroupBox *GroupBox7;
   TEdit *Edit4;
   TUpDown *UpDown3;
   TBitBtn *ModellingButton;
   TGroupBox *GroupBox8;
   TGroupBox *GroupBox9;
   TGroupBox *GroupBox10;
   TEdit *Edit5;
   TEdit *Edit6;
   TUpDown *UpDown4;
   TUpDown *UpDown5;
   TGroupBox *GroupBox3;
   TGroupBox *GroupBox11;
   TEdit *Edit7;
   TUpDown *UpDown6;
   TGroupBox *GroupBox12;
   TEdit *Edit8;
   TUpDown *UpDown7;
   TTabSheet *TabSheet6;
   TGroupBox *GroupBox13;
   TSavePictureDialog *SavePictureDialog1;
   TTabSheet *TabSheet7;
   TGroupBox *GroupBox14;
   TScrollBar *GorizontalStatus;
   TScrollBar *VerticalStatus;
   TImage *Image2;
   TPanel *Panel2;
   TImage *Image3;
   TSaveDialog *SaveDialog1;
   TMemo *Memo1;
   TPanel *Panel3;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall GorizontalChange(TObject *Sender);
   void __fastcall VerticalChange(TObject *Sender);
   void __fastcall Edit2Change(TObject *Sender);
   void __fastcall StringGrid1KeyPress(TObject *Sender, char &Key);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall ModellingButtonClick(TObject *Sender);
   void __fastcall Edit3Change(TObject *Sender);
   void __fastcall Edit5Change(TObject *Sender);
   void __fastcall Edit6Change(TObject *Sender);
   void __fastcall GorizontalStatusChange(TObject *Sender);
   void __fastcall VerticalStatusChange(TObject *Sender);
   void __fastcall TreeView1Changing(TObject *Sender, TTreeNode *Node,
          bool &AllowChange);
private:	// User declarations
   size_t I, J, ISt, JSt;           //Index
   TRendering *Render;              //Class to print picture
   TStringBuffer *StringBuffer;     //Class contain string menu
   TPictureBuffer *PictureBuffer;   //Class contain the picture
   TArrayChannel<TChannel> *Channel;//Class contain values of the channel work
   TArrayChannel<TSit> *Sit;        //Class contain values of the waiting places
   TArrayChannel<TLeave> *Reject;   //Class contain values of the Rejection request
   TArrayChannel<TSit> *LeaveSystem;
   TArrayChannel<TSit> *Fifteen;
   TValueBuffer *R, *L, *S;         //Class contain values of the R, L, S
   TModel *Model;                   //Class is modelling process
   Set <size_t, 8, 105> SetOfChar;  //Set of char for Timeout
   size_t NCount, MCount;           //Count of the channels and the waiting place
   TRest *RestChannel;              //Rest time of the channel
   TStatusGraphicBuffer *StatusBuffer;
   TRenderer *RenderStatus;
public:		// User declarations
        __fastcall TMainForm(TComponent* Owner);
        void __fastcall ClearMemory();
        size_t __fastcall HoursToMinutes(size_t, size_t);
        size_t __fastcall MinutesToHours(size_t);
        size_t __fastcall MinutesWithoutHours(size_t);
        void __fastcall SetRest();
        void __fastcall PrintStatistic();
        bool __fastcall SaveStatistic();
        bool __fastcall SaveCircle();
        bool __fastcall SaveStatus();
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
