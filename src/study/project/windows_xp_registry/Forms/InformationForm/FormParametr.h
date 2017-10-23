//---------------------------------------------------------------------------

#ifndef FormParametrH
#define FormParametrH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TParametrForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TRichEdit *RichEdit1;
private:	// User declarations
public:		// User declarations
   __fastcall TParametrForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TParametrForm *ParametrForm;
//---------------------------------------------------------------------------
#endif
