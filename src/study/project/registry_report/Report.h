//---------------------------------------------------------------------------

#ifndef fReportH
#define fReportH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TfRep : public TForm
{
__published:	// IDE-managed Components
        TQuickRep *QuickRep1;
        TQRLabel *QRLabel1;
        TQRLabel *QRLabel2;
        TQRBand *TitleBand1;
        TQRImage *QRImage1;
        TQRLabel *QRLabel3;
        TQRLabel *QRLabel4;
        TQRLabel *QRLabel5;
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfRep(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfRep *fRep;
//---------------------------------------------------------------------------
#endif
