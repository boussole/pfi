//---------------------------------------------------------------------------

#ifndef TurnpikeUnitH
#define TurnpikeUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
   TTimer *Timer1;
   TTimer *Timer2;
   void __fastcall FormPaint(TObject *Sender);
   void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall Timer1Timer(TObject *Sender);
   void __fastcall Timer2Timer(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
