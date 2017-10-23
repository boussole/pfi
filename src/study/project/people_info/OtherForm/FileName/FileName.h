//---------------------------------------------------------------------------
#ifndef FileNameH
#define FileNameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFileNameForm : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TBitBtn *Ok;
   TBitBtn *Cancel;
   TEdit *Edit1;
   void __fastcall CancelClick(TObject *Sender);
   void __fastcall OkClick(TObject *Sender);
   void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TFileNameForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFileNameForm *FileNameForm;
//---------------------------------------------------------------------------
#endif
