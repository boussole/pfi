//---------------------------------------------------------------------------

#ifndef RotationUnitH
#define RotationUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TMainPanel : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TPanel *Panel2;
   TPanel *Panel3;
   TImage *Image1;
   TImage *Image2;
   TImage *Image3;
   TBitBtn *PaintPolygon;
   TPanel *Panel4;
   TGroupBox *GroupBox1;
   TEdit *Edit1;
   TPanel *Panel5;
   TBitBtn *ClearAll;
   TRadioButton *RadioButton1;
   TRadioButton *RadioButton2;
   TBitBtn *TurnUp;
   TBitBtn *TurnLeft;
   TBitBtn *TurnRight;
   TBitBtn *TurnDown;
   TBitBtn *TurnAround;
   TMainMenu *MainMenu1;
   TMenuItem *Open1;
   TMenuItem *Save1;
   TMenuItem *Savetemplate1;
   TMenuItem *SaveBitMap1;
   TMenuItem *N1;
   TMenuItem *Exit1;
   TMenuItem *Loadtemplate1;
   TMenuItem *LoadBitMap1;
   TOpenPictureDialog *OpenPictureDialog1;
   TOpenDialog *OpenDialog1;
   TSavePictureDialog *SavePictureDialog1;
   TSaveDialog *SaveDialog1;
   TMenuItem *SaveVertexEdge1;
   TSaveDialog *SaveDialog2;
   TMenuItem *LoadFigure;
   TOpenDialog *OpenDialog2;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall Image3Click(TObject *Sender);
   void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall PaintPolygonClick(TObject *Sender);
   void __fastcall FormPaint(TObject *Sender);
   void __fastcall ClearAllClick(TObject *Sender);
   void __fastcall FormDestroy(TObject *Sender);
   void __fastcall TurnUpClick(TObject *Sender);
   void __fastcall TurnDownClick(TObject *Sender);
   void __fastcall TurnLeftClick(TObject *Sender);
   void __fastcall TurnRightClick(TObject *Sender);
   void __fastcall TurnAroundClick(TObject *Sender);
   void __fastcall Exit1Click(TObject *Sender);
   void __fastcall SaveBitMap1Click(TObject *Sender);
   void __fastcall LoadBitMap1Click(TObject *Sender);
   void __fastcall Savetemplate1Click(TObject *Sender);
   void __fastcall SaveVertexEdge1Click(TObject *Sender);
   void __fastcall Loadtemplate1Click(TObject *Sender);
   void __fastcall LoadFigureClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TMainPanel(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainPanel *MainPanel;
//---------------------------------------------------------------------------
#endif
