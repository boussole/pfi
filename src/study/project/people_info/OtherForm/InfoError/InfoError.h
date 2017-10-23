//---------------------------------------------------------------------------

#ifndef InfoErrorH
#define InfoErrorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TInfoErrorForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TMemo *Memo1;
private:	// User declarations
public:		// User declarations
   __fastcall TInfoErrorForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInfoErrorForm *InfoErrorForm;
//---------------------------------------------------------------------------
#endif
