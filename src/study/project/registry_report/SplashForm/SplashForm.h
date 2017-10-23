//---------------------------------------------------------------------------

#ifndef SplashFormH
#define SplashFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TSplash : public TForm
{
__published:	// IDE-managed Components
   TImage *Image1;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TLabel *Label6;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TLabel *Label10;
   void __fastcall Label6MouseEnter(TObject *Sender);
   void __fastcall Label6MouseLeave(TObject *Sender);
   void __fastcall Label6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TSplash(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSplash *Splash;
//---------------------------------------------------------------------------
#endif
