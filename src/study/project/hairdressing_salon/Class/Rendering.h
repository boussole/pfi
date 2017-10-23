#ifndef Rendering_H
#define Rendering_H
#include "PictureBuffer.h"
//-----------------------------------------------------------
class TRendering
{
   public:
      TRendering(TImage *, TPictureBuffer *, TStringBuffer *, TValueBuffer *, TValueBuffer *, TValueBuffer *, TArrayChannel<TChannel> *, TArrayChannel<TSit> *, TScrollBar *, TScrollBar *);
      ~TRendering();
      void DoTable(size_t, size_t, size_t);
      void DoGraphic(size_t, size_t, size_t);
      void DoLeave(size_t, size_t, size_t);
      void RePaint(size_t, size_t);
      void DoDesire(size_t, size_t);
      void DoRejection(size_t, size_t);
      size_t GetWidth() {return iSize;}
      bool SaveToFile(AnsiString);
   private:
      TCanvas *Canvas;
//      TScrollBar *Gorizontal, *Vertical;
      TPictureBuffer *Buffer;
      TStringBuffer *StringBuffer;
      TValueBuffer *RBuffer, *LBuffer, *SBuffer;
      TArrayChannel<TChannel> *NBuffer;
      TArrayChannel<TSit> *MBuffer;
      size_t iSize, jSize, NCount, MCount, PaintElement, _i_index, _j_index;
      Graphics :: TBitmap *Bmp;
      TImage *Image;
};
//-----------------------------------------------------------
//Constructor
TRendering :: TRendering(TImage *_Image, TPictureBuffer *_Buffer, TStringBuffer *_StringBuffer,
                         TValueBuffer *_R, TValueBuffer *_L, TValueBuffer *_S, TArrayChannel<TChannel> *_N,
                         TArrayChannel<TSit> *_M, TScrollBar *G, TScrollBar *V)
{
   Image = _Image;
   Canvas = _Image->Canvas;
   Buffer = _Buffer;
   StringBuffer = _StringBuffer;
   RBuffer = _R;
   LBuffer = _L;
   SBuffer = _S;
   NBuffer = _N;
   MBuffer = _M;
   //-------------------------------
   Bmp = NULL;
   Bmp = new Graphics :: TBitmap();
   Bmp->Height = Image->Height;
   Bmp->Width  = Image->Width;
   Bmp->Canvas->Pen->Color = clBlack;
   Bmp->Canvas->Font->Size = 8;
   //-------------------------------
   jSize = StringBuffer->GetCountCol();
   iSize = Buffer->GetCount() / jSize + 1;
   NCount = StringBuffer->GetN();
   MCount = StringBuffer->GetM();
   PaintElement = 0;
   _i_index = 0;
   _j_index = 0;
//   Gorizontal = G;
//   Vertical = V;
   G->Max = iSize - 1;
   V->Max = jSize - 1;
}
//-----------------------------------------------------------
//Destructor
TRendering :: ~TRendering()
{
   delete Bmp;
   Bmp = NULL;
}
//-----------------------------------------------------------
//Paint Menu
void TRendering :: DoTable(size_t _i, size_t _j, size_t Index)
{
   size_t Offset = 0;
   switch (Index)
      {
         case (0) : Offset = 45;
         break;
         //----
         case (1) : Offset = 60;
         break;
         //----
         case (2) : Offset = 75;
         break;
         //----
         default: Offset = 90;
         break;
   };
   //-------------------Graphic_n, Graphic_m,
   //N, r, l
   if (_j_index <= 2)
      {
         Bmp->Canvas->Rectangle(_i * 60, _j * 15, (_i + 1) * 60, (_j + 1) * 15);
         switch (Buffer->GetType(PaintElement))
            {
               case(Table_Menu): Bmp->Canvas->TextOut((_i * 60 + 20), (_j * 15 + 1), (*StringBuffer)[_j_index]);
                                 break;
               //-------------
               case(Table_N):    Bmp->Canvas->TextOut((_i * 60 + 20), (_j * 15 + 1), IntToStr(_i_index));
                                 break;
               //-------------
               case(Table_R):    Bmp->Canvas->TextOut((_i * 60 + 20), (_j * 15 + 1), IntToStr((*RBuffer)[_i_index - 1]));
                                 break;
               //-------------
               case(Table_l):    Bmp->Canvas->TextOut((_i * 60 + 20), (_j * 15 + 1), IntToStr((*LBuffer)[_i_index - 1]));
                                 break;
            };
      }
   //-------------------
   //m, n, S
   if ((_j_index > 2) && (_i_index < 1))
      {
         Bmp->Canvas->Rectangle((_i * 60), (Offset + ((_j - 3) * 30)), ((_i + 1) * 60), (Offset + ((_j - 2) * 30)));
         switch (Buffer->GetType(PaintElement))
            {
               case(Table_Menu): Bmp->Canvas->TextOut((_i * 60 + 20), (Offset + ((_j - 3) * 30) + 16), (*StringBuffer)[_j_index]);
                                 break;
            };
      }
   //------------------
   //S - Not Menu
   if ((_j_index == jSize - 1) && (_i_index > 0) && (Buffer->GetType(PaintElement) == Table_S))
      {
         Bmp->Canvas->MoveTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30) - 1));
         Bmp->Canvas->LineTo( (_i * 60), (Offset + ((_j - 2) * 30) - 1));
         Bmp->Canvas->MoveTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30) - 1));
         Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30) - 5));
         if ((*SBuffer)[_i_index - 1] > (MCount + NCount))
            {Bmp->Canvas->TextOut((_i * 60 + 20), (Offset + ((_j - 3) * 30) + 16), "S" + IntToStr((*SBuffer)[_i_index - 1] - (NCount + MCount)) + '*');}
         else
            {Bmp->Canvas->TextOut((_i * 60 + 20), (Offset + ((_j - 3) * 30) + 16), "S" + IntToStr((*SBuffer)[_i_index - 1]));}
      }
}
//-----------------------------------------------------------
//Paint Graphic
void TRendering :: DoGraphic(size_t _i, size_t _j, size_t Index)
{  
   if ((_i_index > 0) && (_j_index > 2) && (_j_index < jSize - 1))
      {
         size_t Offset = 0;
         switch (Index)
            {
               case (0) : Offset = 45;
                          break;
               //----
               case (1) : Offset = 60;
                          break;
               //----
               case (2) : Offset = 75;
                          break;
               //----
               default: Offset = 90;
                          break;
            };
      //--------------------------------
      //TimeOut
      if (Buffer->GetType(PaintElement) == TimeOut)
      {
         Bmp->Canvas->Brush->Color = clRed;
         Bmp->Canvas->Font->Size = 10;
         Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
         Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30)) );
         Bmp->Canvas->TextOutA( (_i * 60), (Offset + (_j - 2) * 30 - 16), "Перерыв");
         Bmp->Canvas->Brush->Color = clWhite;
         Bmp->Canvas->Font->Size = 8;
         goto CheckLeave;
      }
      //--------------------------------
      //Other
      switch (Buffer->GetStatus(PaintElement))
         {
            //Empty
            case(Empty) :  Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
                           Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30)) );
                           break;
            //-----
            //Start
            case(Start) :  Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
                           Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30)) );
                           Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
                           Bmp->Canvas->LineTo( (_i * 60), (Offset + (_j - 2) * 30) - 15);
                           Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + (_j - 2) * 30) - 15);
                           //-------------------------------------------------------------------
                           if ((_j_index <= 2 + NCount) && (NBuffer != NULL))
                              {
                                 Bmp->Canvas->Font->Color = clBlue;
                                 Bmp->Canvas->TextOut((_i * 60 + 6), (Offset + (_j - 3) * 30 + 2), IntToStr((NBuffer[_j_index - 3][_i_index]).Number));
                                 Bmp->Canvas->Font->Color = clBlack;
                                 Bmp->Canvas->TextOut((_i * 60 + 2), (Offset + (_j - 2) * 30 - 13), IntToStr((NBuffer[_j_index - 3][_i_index]).RandomValue) + "/" + IntToStr((NBuffer[_j_index - 3][_i_index]).Time));
                              }
                           else
                              {
                                 if (MBuffer != NULL)
                                 {
                                 Bmp->Canvas->Font->Color = clBlue;
                                 Bmp->Canvas->TextOut((_i * 60 + 6), (Offset + (_j - 3) * 30 + 2), IntToStr((MBuffer[_j_index - 3 - NCount][_i_index]).Number));
                                 Bmp->Canvas->Font->Color = clBlack;
                                 Bmp->Canvas->TextOut((_i * 60 + 2), (Offset + (_j - 2) * 30 - 13), IntToStr((MBuffer[_j_index - 3 - NCount][_i_index]).RandomValue));
                                 }
                              }
                           break;
            //-----
            //Continue
            case(Continue) :  Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
                              Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30)) );
                              Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30) - 15);
                              Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + (_j - 2) * 30) - 15);
                              break;
            //-----
            //Finish
            case(Finish) : Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
                           Bmp->Canvas->LineTo( ((_i + 1) * 60), (Offset + ((_j - 2) * 30)) );
                           Bmp->Canvas->MoveTo( (_i * 60), (Offset + (_j - 2) * 30));
                           Bmp->Canvas->LineTo( (_i * 60), (Offset + (_j - 2) * 30) - 15);
                           break;
         };
      //-------------------------------
      CheckLeave:
      switch (Buffer->GetLeave(PaintElement))
         {
            //Desire
            case(Desire):     DoDesire((_i * 60), (Offset + (_j - 2) * 30));
                              break;
            //-----
            //Rejection
            case(Rejection):  DoRejection((_i * 60), (Offset + (_j - 2) * 30));
                              break;
            //-----
            //DesAndRej
            case(DesAndRej):  DoDesire((_i * 60), (Offset + (_j - 2) * 30));
                              DoRejection((_i * 60), (Offset + (_j - 2) * 30));
                              break;
         };
      }
}
//-----------------------------------------------------------
//Paint left transakts
void TRendering :: DoLeave(size_t _i, size_t _j, size_t Index)
{
   if ((_i_index > 0) && (_j_index > 2) && (_j_index < jSize - 1))
      {
         size_t Offset = 0;
         switch (Index)
            {
               case (0) : Offset = 45;
                          break;
               //----
               case (1) : Offset = 60;
                          break;
               //----
               case (2) : Offset = 75;
                          break;
               //----
               default: Offset = 90;
                          break;
            };
   //Desire, Rejection, DesAndRej
   //Leave
      switch (Buffer->GetLeave(PaintElement))
         {
            //Desire
            case(Desire):     DoDesire((_i * 60), (Offset + (_j - 2) * 30));
                              break;
            //-----
            //Rejection
            case(Rejection):  DoRejection((_i * 60), (Offset + (_j - 2) * 30));
                              break;
            //-----
            //DesAndRej
            case(DesAndRej):  DoDesire((_i * 60), (Offset + (_j - 2) * 30));
                              DoRejection((_i * 60), (Offset + (_j - 2) * 30));
                              break;
         };
      }
}
//-----------------------------------------------------------
//Paint Arrow Desire
void TRendering :: DoDesire(size_t X, size_t Y)
{
   Bmp->Canvas->Brush->Color = clBlack;
   Bmp->Canvas->MoveTo(X, Y);
   Bmp->Canvas->LineTo(X, Y - 20);
   Bmp->Canvas->MoveTo(X, Y - 30);
   Bmp->Canvas->LineTo(X + 5, Y - 20);
   Bmp->Canvas->LineTo(X - 5, Y - 20);
   Bmp->Canvas->LineTo(X, Y - 30);
   Bmp->Canvas->FloodFill(X, Y - 21, clBlack, fsBorder);
   Bmp->Canvas->FloodFill(X - 2, Y - 21, clBlack, fsBorder);
   Bmp->Canvas->Brush->Color = clWhite;
}
//-----------------------------------------------------------
//Paint Arrow Rejection
void TRendering :: DoRejection(size_t X, size_t Y)
{
   Bmp->Canvas->Pen->Color = clRed;
   Bmp->Canvas->Brush->Color = clRed;
   Bmp->Canvas->MoveTo(X, Y);
   Bmp->Canvas->LineTo(X, Y + 20);
   Bmp->Canvas->MoveTo(X, Y + 30);
   Bmp->Canvas->LineTo(X + 5, Y + 20);
   Bmp->Canvas->LineTo(X - 5, Y + 20);
   Bmp->Canvas->LineTo(X, Y + 30);
   Bmp->Canvas->FloodFill(X, Y + 21, clRed, fsBorder);
   Bmp->Canvas->Pen->Color = clBlack;
   Bmp->Canvas->Brush->Color = clWhite;
}
//-----------------------------------------------------------
//Paint
void TRendering :: RePaint(size_t i_index, size_t j_index)
{
   //Clear Canvas
   Bmp->Canvas->Brush->Color = clWhite;
   Bmp->Canvas->Pen->Color = clWhite;
   Bmp->Canvas->FillRect(Rect(0, 0, Image->ClientWidth, Image->ClientHeight));
   Bmp->Canvas->Pen->Color = clBlack;
   _i_index = i_index;
   _j_index = j_index;
   for (size_t i = 0; i <= size_t((Image->Width / 60) + 1); i++)
   for (size_t j = 0; j <= size_t((Image->Height / 30) + 1); j++)
      {
         if ((jSize - j_index <= jSize) && (iSize - i_index <= iSize) && (j < jSize - j_index) && (i < iSize - i_index))
         {
         //Paint Kind
         switch  (Buffer->GetKind((i_index + i)* jSize + (j_index + j)))
            {
               //Table
               case(Table):   {
                                 PaintElement = (i_index + i)* jSize + (j_index + j);
                                 _j_index = j_index + j;
                                 _i_index = i_index + i;
                                 DoTable(i, j, j_index);
                                 break;
                              }
               //------------
               //Graphic
               case(Graphic): {
                                 PaintElement = (i_index + i)* jSize + (j_index + j);
                                 _j_index = j_index + j;
                                 _i_index = i_index + i;
                                 DoGraphic(i, j, j_index);
                                 break;
                              }
               //------------
               //No Picture
               default:
                              {
                                 PaintElement = -1;
                                 continue;
                              }
            };
         }
      }
   Canvas->Draw(0, 0, Bmp);
}
//-----------------------------------------------------------
bool TRendering :: SaveToFile(AnsiString FileName)
{
   //Clear Canvas
   Bmp->Canvas->Brush->Color = clWhite;
   Bmp->Canvas->Pen->Color = clWhite;
   Bmp->Width = (iSize - 1)* 60;
   Bmp->Height = (jSize - 1)* 30 - 15;
   Bmp->Canvas->FillRect(Rect(0, 0, (iSize - 1) * 60, (jSize - 1) * 30));
   Bmp->Canvas->Pen->Color = clBlack;
   for (size_t i = 0; i < iSize; i++)
   for (size_t j = 0; j < jSize; j++)
      {
         //Paint Kind
         switch  (Buffer->GetKind(i * jSize + j))
            {
               //Table
               case(Table):   {
                                 PaintElement = i * jSize + j;
                                 _j_index = j;
                                 _i_index = i;
                                 DoTable(i, j, 0);
                                 break;
                              }
               //------------
               //Graphic
               case(Graphic): {
                                 PaintElement = i * jSize + j;
                                 _j_index = j;
                                 _i_index = i;
                                 DoGraphic(i, j, 0);
                                 break;
                              }
               //------------
               //No Picture
               default:
                              {
                                 PaintElement = -1;
                                 continue;
                              }
            };
      }
   try
      {
         Bmp->SaveToFile(FileName);
      }
   catch (...)
      {
         Bmp->Height = Image->Height;
         Bmp->Width  = Image->Width;
         return false;
      }
   Bmp->Height = Image->Height;
   Bmp->Width  = Image->Width;
   return true;
}
//----------------------------------------------------------
#endif
