//---------------------------------------------------------------------------

#ifndef AuthorH
#define AuthorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
   TImage *Image1;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label5;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   TLabel *Label11;
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall Label11MouseEnter(TObject *Sender);
   void __fastcall Label11MouseLeave(TObject *Sender);
   void __fastcall Label11Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
