//---------------------------------------------------------------------------

#ifndef AboutProgramH
#define AboutProgramH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TAboutProgramForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TMemo *Memo1;
private:	// User declarations
public:		// User declarations
   __fastcall TAboutProgramForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutProgramForm *AboutProgramForm;
//---------------------------------------------------------------------------
#endif
