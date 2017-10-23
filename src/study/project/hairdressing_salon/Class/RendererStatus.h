#ifndef RendererStatus_H
#define RendererStatus_H
#include "TStatusGraphicBuffer.h"
//------------------------------------------------------------------
class TRenderer
{
   public:
      TRenderer(TImage *, TStatusGraphicBuffer *, TValueBuffer *, TScrollBar *, TScrollBar *, size_t, size_t);
      ~TRenderer();
      void RePaint(size_t, size_t);
      void DoGraphic(TGraph);
      void DoCounterType(size_t, size_t, size_t);
      void DoSMenuType(size_t, size_t);
      void DoMark(size_t, size_t, size_t);
      void DoStay(size_t, size_t, size_t);
      void DoStayNotFirst(size_t, size_t, size_t);
      void DoBackMov(size_t, size_t, size_t);
      void DoMov(size_t, size_t, size_t);
      void DoModel();
      bool SaveToFile(AnsiString);

   private:
      TStatusGraphicBuffer *Buffer;
      TValueBuffer *SBuffer;
//      TScrollBar *Gorizontal, *Vertical;
      TImage *Image; TCanvas *Canvas;
      size_t iIndex, jIndex, jSize, iSize, FirstMark, SecondMark, ThirdMark;
      Graphics :: TBitmap *Bmp;
      bool Mark;
      size_t NCount, MCount;
};
//------------------------------------------------------------------
///Constructor
TRenderer :: TRenderer(TImage *_Image, TStatusGraphicBuffer *_Buffer, TValueBuffer *_SBuffer, TScrollBar *_G, TScrollBar *_V, size_t _NCount, size_t _MCount)
{
   Image = _Image;
   Canvas = Image->Canvas;
   Bmp = NULL;
   Bmp = new Graphics :: TBitmap;
   Bmp->Canvas->Pen->Color = clBlack;
   Buffer = _Buffer;
   SBuffer = _SBuffer;
   NCount = _NCount;
   MCount = _MCount;
   Mark = false;
//   Gorizontal = _G;
//   Vertical = _V;
   iIndex = 0;
   jIndex = 0;
   if (SBuffer != NULL)
      {
         iSize = 2 + SBuffer->GetCount();
         jSize = 3 + NCount + MCount * 2;
         Buffer->SetLength(iSize, (jSize + 1)/ 2);
         FirstMark = 0;
         SecondMark = NCount + MCount + 1;
         ThirdMark = NCount + MCount * 2;
         _V->Max = iSize;
         _G->Max = jSize;
         DoModel();
      }
}
//------------------------------------------------------------------
//Destructor
TRenderer :: ~TRenderer()
{
   delete Bmp;
   Bmp = NULL;
}
//------------------------------------------------------------------
//Re Paint the canvas
void TRenderer :: RePaint(size_t i_Index, size_t j_Index)
{
   //Clear Canvas
   Bmp->Width = Image->Width;
   Bmp->Height = Image->Height;
   Bmp->Canvas->Pen->Color = clWhite;
   Bmp->Canvas->FillRect(Rect(0, 0, Image->ClientWidth, Image->ClientHeight));
   Bmp->Canvas->Pen->Color = clBlack;
   Bmp->Canvas->Pen->Width = 2;
   for (size_t i = 0; i < Image->Height / 5 + 1; i++)
   for (size_t j = 0; j < Image->Width / 40 + 1; j++)
      {
         if ((jSize - j_Index <= jSize) && (iSize - i_Index <= iSize) && (j < jSize - j_Index) && (i < iSize - i_Index))
            {
               iIndex = i + i_Index;
               jIndex = j + j_Index;
               switch ((*Buffer)[iIndex].GetTType(jIndex))
                  {
                     case (CounterType):   DoCounterType(i, j, i_Index);
                                           break;
                     //----------------
                     case (SMenuType):     DoSMenuType(i, j);
                                           break;
                     //----------------
                     default: if ((*Buffer)[iIndex].GetTType(jIndex) == MarkType) {Mark = true; DoMark(i, j, i_Index);}
                              switch ((*Buffer)[iIndex].GetTGraph(jIndex))
                                 {
                                    case (Stay):         if ((*Buffer)[iIndex - 1].GetTGraph(jIndex) != Stay) {DoStay(i, j, i_Index);}
                                                         else {DoStayNotFirst(i, j, i_Index);}
                                                         break;
                                    //-------------------------
                                    case (BackMov):      DoBackMov(i, j, i_Index);
                                                         break;
                                    //-------------------------
                                    case (Mov):          DoMov(i, j, i_Index);
                                                         break;
                                    //-------------------------
                                 };
                              break;
                  };
               if ((iIndex + 1 == iSize) && (jIndex > 0))
                  {
                     size_t Offset = 0;
                     if (i_Index == 0) {Offset = 20;}
                     Bmp->Canvas->MoveTo(j * 40, (Offset + (i + 1) * 5));
                     Bmp->Canvas->LineTo((j + 1) * 40, (Offset + (i + 1)* 5));
                  }
            }
      }
   Canvas->Draw(0, 0, Bmp);
}
//------------------------------------------------------------------
//Paint the table Element
void TRenderer :: DoCounterType(size_t _i, size_t _j, size_t Index)
{
   size_t Offset = 0;
   if (Index == 0) {Offset = 20;}
   if ((jIndex == 0) && (iIndex > 0))
      {
         //Gorizontal line
         if ((iIndex - 1) % 10 == 0)
            {
               Bmp->Canvas->MoveTo(33, Offset + _i * 5);
               Bmp->Canvas->LineTo(40, Offset + _i * 5);
            }
         else
            {
               if ((iIndex - 1) % 5 == 0)
                  {
                     Bmp->Canvas->MoveTo(36, Offset + _i * 5);
                     Bmp->Canvas->LineTo(40, Offset + _i * 5);
                  }
               else
                  {
                     Bmp->Canvas->MoveTo(38, Offset + _i * 5);
                     Bmp->Canvas->LineTo(40, Offset + _i * 5);
                  }
            }
         //if 10 * x then Value
         if (((iIndex - 1) % 10) == 0)
            Bmp->Canvas->TextOut(0, (Offset + _i * 5 - 7), IntToStr(iIndex - 1));
         //Vertical line
         Bmp->Canvas->MoveTo(40, Offset + _i * 5);
         Bmp->Canvas->LineTo(40, Offset + (_i + 1) * 5);
         //Gorizontal line
         if ( ((iIndex) % 10 == 0) || (iIndex + 1 == iSize))
            {
               Bmp->Canvas->LineTo(33, Offset + (_i + 1) * 5);
            }
         else
            {
               if  ((iIndex) % 5 == 0)
                  Bmp->Canvas->LineTo(36, Offset + (_i + 1) * 5);
               else
                  Bmp->Canvas->LineTo(38, Offset + (_i + 1) * 5);
            }
         //TextOut
         if ((iIndex) % 10 == 0)
            {
               Bmp->Canvas->TextOut(0, (Offset +(_i + 1) * 5 - 7), IntToStr(iIndex));
            }
         if (iIndex + 1 == iSize)
            {
               Bmp->Canvas->TextOut(32, (Offset +(_i + 2) * 5), IntToStr(iIndex));
            }
      }
}
//------------------------------------------------------------------
//Paint S menu
void TRenderer :: DoSMenuType(size_t _i, size_t _j)
{
   if ((iIndex == 0) && (jIndex > 0))
      {
         if (jIndex == 1)
            {
               Bmp->Canvas->MoveTo(_j * 40, 25);
               Bmp->Canvas->LineTo((_j + 1) * 40, 25);
            }
         else
            {
               if ((jIndex - 2) > NCount + MCount)
                  Bmp->Canvas->TextOut((_j * 40) - 6, 10, "S" + IntToStr(jIndex - 2 - MCount) + "*");
               else
                  Bmp->Canvas->TextOut((_j * 40) - 6, 10, "S" + IntToStr(jIndex - 2));
               Bmp->Canvas->MoveTo(_j * 40, 23);
               Bmp->Canvas->LineTo(_j * 40, 25);
               Bmp->Canvas->LineTo((_j + 1) * 40, 25);
            }
      }
}
//------------------------------------------------------------------
//Paint Mark
void TRenderer :: DoMark(size_t _i, size_t _j, size_t Index)
{
   if ((iSize > 0) && (jSize > 0))
   {
      size_t Offset = 0;
      if (Index == 0) {Offset = 20;}
      if (Mark)
         {
         Bmp->Canvas->MoveTo(_j * 40, Offset + _i * 5);
         Bmp->Canvas->LineTo(_j * 40, Offset + _i * 5 + 3);
         Mark = false;
         }
      if ((jIndex + 1>= jSize) && (iIndex > 0))
         {
            Bmp->Canvas->MoveTo((_j + 1) * 40, Offset + _i * 5);
            Bmp->Canvas->LineTo((_j + 1) * 40, Offset + _i * 5 + 5);
         }
   }
}
//------------------------------------------------------------------
void TRenderer :: DoStay(size_t _i, size_t _j, size_t Index)
{
   if ((iIndex > 0) && (jIndex > 1))
      {
         size_t Offset = 0;
         if (Index == 0) {Offset = 20;}
         Bmp->Canvas->Pen->Color = clBlue;
         Bmp->Canvas->MoveTo(_j * 40, Offset + _i * 5);
         Bmp->Canvas->LineTo(_j * 40, Offset + _i * 5 + 5);
         Bmp->Canvas->Pen->Color = clBlack;
         if ((jIndex + 1>= jSize) && (iIndex > 0))
            {
               Bmp->Canvas->MoveTo((_j + 1) * 40, Offset + _i * 5);
               Bmp->Canvas->LineTo((_j + 1) * 40, Offset + _i * 5 + 5);
            }
      }
}
//------------------------------------------------------------------
void TRenderer :: DoMov(size_t _i, size_t _j, size_t Index)
{
   if ((iIndex > 0) && (jIndex > 1))
      {
         size_t Offset = 0;
         if (Index == 0) {Offset = 20;}
         Bmp->Canvas->Pen->Color = clBlue;
         Bmp->Canvas->MoveTo(_j * 40, Offset + _i * 5);
         Bmp->Canvas->LineTo((_j + 1) * 40, Offset + _i * 5);
         Bmp->Canvas->Pen->Color = clBlack;
         if ((jIndex + 1>= jSize) && (iIndex > 0))
            {
               Bmp->Canvas->MoveTo((_j + 1) * 40, Offset + _i * 5);
               Bmp->Canvas->LineTo((_j + 1) * 40, Offset + _i * 5 + 5);
            }
      }
}
//------------------------------------------------------------------
void TRenderer :: DoBackMov(size_t _i, size_t _j, size_t Index)
{
   if ((iIndex > 0) && (jIndex > 1))
      {
         size_t Offset = 0;
         if (Index == 0) {Offset = 20;}
         Bmp->Canvas->Pen->Color = clBlue;
         Bmp->Canvas->MoveTo(_j * 40, Offset + _i * 5);
         Bmp->Canvas->LineTo((_j - 1) * 40, Offset + _i * 5);
         Bmp->Canvas->Pen->Color = clBlack;

         if ((jIndex + 1>= jSize) && (iIndex > 0))
            {
               Bmp->Canvas->MoveTo((_j + 1) * 40, Offset + _i * 5);
               Bmp->Canvas->LineTo((_j + 1) * 40, Offset + _i * 5 + 5);
            }
      }
}
//------------------------------------------------------------------
void TRenderer :: DoStayNotFirst(size_t _i, size_t _j, size_t Index)
{
   if ((iIndex > 0) && (jIndex > 1))
      {
         size_t Offset = 0;
         if (Index == 0) {Offset = 20;}
         Bmp->Canvas->Pen->Color = clBlue;
         Bmp->Canvas->MoveTo(_j * 40, Offset + _i * 5);
         Bmp->Canvas->LineTo(_j * 40 - 3, Offset + _i * 5);
         Bmp->Canvas->LineTo(_j * 40 + 3, Offset + _i * 5);
         Bmp->Canvas->MoveTo(_j * 40, Offset + _i * 5);
         Bmp->Canvas->LineTo(_j * 40, Offset + _i * 5 + 5);
         Bmp->Canvas->Pen->Color = clBlack;

    if ((jIndex + 1>= jSize) && (iIndex > 0))
         {
            Bmp->Canvas->MoveTo((_j + 1) * 40, Offset + _i * 5);
            Bmp->Canvas->LineTo((_j + 1) * 40, Offset + _i * 5 + 5);
         }
      }
}
//------------------------------------------------------------------
void TRenderer :: DoModel()
{
   size_t RowTimer = 0, Current = 0, Help = 0;
   //Create S - menu
   for (size_t j = 1; j < jSize; j++)
      {
         (*Buffer)[RowTimer].SetTType(j, SMenuType);
      }
   RowTimer++;
   while (RowTimer < iSize)
      {
         //Set Time
         (*Buffer)[RowTimer].SetTType(0, CounterType);
         //Set MArk Elements
         for (size_t i = 0; i < (NCount + (2 * MCount) + 3); i++)
            {
               if ((i - 2 == FirstMark) || (i - 2 == SecondMark) || (i - 2 == ThirdMark))
                  {(*Buffer)[RowTimer].SetTType(i, MarkType);}
            }
         //---------
         Help = (*SBuffer)[RowTimer - 1];
         if (Help > NCount + MCount){Help -= NCount;}
         //Stay that place
         if (Help == Current)
            {
               (*Buffer)[RowTimer].SetTGraph(Current + 2, Stay);
            }
         //---------
         //Mov Front
         if (Help > Current)
            {
               for (size_t i = Current; i < Help; i++)
                  {
                     (*Buffer)[RowTimer].SetTGraph(i + 2, Mov);
                     Current++;
                  }
               (*Buffer)[RowTimer].SetTGraph(Current + 2, Stay);
            }
         //---------
         //Mov Back
         if (Help < Current)
            {
               for (size_t i = Current; i > Help; i--)
                  {
                     (*Buffer)[RowTimer].SetTGraph(i + 2, BackMov);
                     Current--;
                  }
               (*Buffer)[RowTimer].SetTGraph(Current + 2, Stay);
            }
         RowTimer++;
      }
}
//------------------------------------------------------------------
bool TRenderer :: SaveToFile(AnsiString FileName)
{
   Bmp->Width = jSize * 40;
   Bmp->Height = iSize * 5 + 40;
   Bmp->Canvas->Pen->Color = clWhite;
   Bmp->Canvas->FillRect(Rect(0, 0, Image->ClientWidth, Image->ClientHeight));
   Bmp->Canvas->Pen->Color = clBlack;
   Bmp->Canvas->Pen->Width = 2;
   for (size_t i = 0; i < iSize; i++)
   for (size_t j = 0; j < jSize; j++)
      {
         iIndex = i;
         jIndex = j;
         switch ((*Buffer)[i].GetTType(j))
            {
               case (CounterType):   DoCounterType(i, j, 0);
                                     break;
               //----------------
               case (SMenuType):     DoSMenuType(i, j);
                                     break;
               //----------------
               default: if ((*Buffer)[i].GetTType(j) == MarkType) {Mark = true; DoMark(i, j, 0);}
                        switch ((*Buffer)[i].GetTGraph(j))
                           {
                              case (Stay):         if ((*Buffer)[i - 1].GetTGraph(j) != Stay) {DoStay(i, j, 0);}
                                                   else {DoStayNotFirst(i, j, 0);}
                                                   break;
                              //-------------------------
                              case (BackMov):      DoBackMov(i, j, 0);
                                                   break;
                              //-------------------------
                              case (Mov):          DoMov(i, j, 0);
                                                   break;
                              //-------------------------
                           };
                        break;
            };
               if ((i + 1 == iSize) && (j > 0))
                  {
                     size_t Offset = 20;
                     Bmp->Canvas->MoveTo(j * 40, (Offset + (i + 1) * 5));
                     Bmp->Canvas->LineTo((j + 1) * 40, (Offset + (i + 1)* 5));
                  }
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
//------------------------------------------------------------------
#endif


