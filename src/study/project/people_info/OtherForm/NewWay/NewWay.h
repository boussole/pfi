//---------------------------------------------------------------------------

#ifndef NewWayH
#define NewWayH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TNewWayForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TEdit *Edit1;
   TBitBtn *BitBtn1;
   TBitBtn *BitBtn2;
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TNewWayForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewWayForm *NewWayForm;
//---------------------------------------------------------------------------
#endif
