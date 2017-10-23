#ifndef StringBuffer_H
#define StringBuffer_H
//---------------------------------------------------------
class TStringBuffer
{
   public:
         TStringBuffer(unsigned, unsigned);
         ~TStringBuffer();
         AnsiString operator[] (unsigned int);
         size_t GetN() {return n;}
         size_t GetM() {return m;}
         size_t GetCountCol() {return (n + m + 4);}
   private:
         AnsiString *pMenu;
         unsigned int n, m;
};
//---------------------------------------------------------
//Constructor
TStringBuffer :: TStringBuffer(unsigned _n, unsigned _m)
{
   pMenu = NULL;
   n = _n;
   m = _m;
   try
      {
         pMenu = new AnsiString[4 + n + m];
      }
   catch (...)
      {
         MessageDlg("Невозможно выделить память!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return;
      }
         pMenu[0] = "N(t)";
         pMenu[1]  = "r";
         pMenu[2] = "l";
         //Create n - menu
         for (unsigned int i = 3, j = 1; i < 3 + n; i++, j++)
            {
               pMenu[i]  = "n" + IntToStr(j);
          }
         //Create m - menu;
         for (unsigned int i = 3 + n, j = 1; i < 3 + n + m; i++, j++)
            {
               pMenu[i] = "m" + IntToStr(j);
            }
         //Create S - menu
         pMenu[3 + m + n] = "So";
}
//---------------------------------------------------------
//Destructor
TStringBuffer :: ~TStringBuffer()
{
   if (pMenu != NULL)
      {
         delete []pMenu;
         pMenu = NULL;
      }
}
//---------------------------------------------------------
//Index
AnsiString TStringBuffer :: operator[] (unsigned int Index)
{
   if (pMenu != NULL)
      {
         if ( (3 + n + m) >= Index)
            {
               return pMenu[Index];
            }
         else
            {
               MessageDlg("Выход за пределы массива строк!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return ("");
            }
      }
   else
      {
         MessageDlg("Меню не создано!!!", mtError, TMsgDlgButtons() << mbOK, 0);
         return ("");
      }
}
//---------------------------------------------------------
#endif



