//---------------------------------------------------------------------------

#ifndef Lab4UnitH
#define Lab4UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TTrackBar *TrackBar1;
   TPanel *Panel2;
   TTrackBar *TrackBar2;
   TTrackBar *TrackBar3;
   TTrackBar *TrackBar4;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   void __fastcall FormCreate(TObject *Sender);
   void __fastcall FormPaint(TObject *Sender);
   void __fastcall FormResize(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall TrackBar1Change(TObject *Sender);
   void __fastcall FormClick(TObject *Sender);
   void __fastcall TrackBar2Change(TObject *Sender);
   void __fastcall TrackBar3Change(TObject *Sender);
   void __fastcall TrackBar4Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
