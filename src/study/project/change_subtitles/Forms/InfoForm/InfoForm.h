//---------------------------------------------------------------------------

#ifndef InfoFormH
#define InfoFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TChangeSubTitlesInfoForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TMemo *Memo1;
private:	// User declarations
public:		// User declarations
   __fastcall TChangeSubTitlesInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChangeSubTitlesInfoForm *ChangeSubTitlesInfoForm;
//---------------------------------------------------------------------------
#endif
