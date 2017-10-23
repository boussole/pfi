#ifndef PictureBuffer_H
#define PictureBuffer_H
//---------------------
#include "ValueBuffer.h"
#include "StringBuffer.h"
#include "ArrayBuffer.h"
//----------------------------------------------------------------------
//   0      000   00       00
//   |      |||   ||       ||
//  Kind    Type  Status   Leave
//----------------------------------------------------------------------
//Type Key
enum Kind {Table, Graphic};
enum type {Table_Menu, Table_N, Table_R, Table_l, Graphic_n, Graphic_m, Table_S, TimeOut};
enum Status {Empty, Start, Continue, Finish};
enum Leave {NoLeave, Desire, Rejection, DesAndRej};
//----------------------------------------------------------------------
class TPictureBuffer
{
   public:
      TPictureBuffer();
      ~TPictureBuffer();
      bool Add();
      bool SetKind(size_t, Kind);
      bool SetType(size_t, type);
      bool SetStatus(size_t, Status);
      bool SetLeave(size_t, Leave);
      Kind GetKind (size_t);
      type GetType (size_t);
      Status GetStatus (size_t);
      Leave GetLeave (size_t);
      unsigned char Convert(Kind, type, Status, Leave);
      size_t GetCount() {return Count;}
   private:
      unsigned char *pPointer;
      size_t size;
      size_t Count;
      unsigned char KindMask, TypeMask, StatusMask, LeaveMask;
};
//----------------------------------------------------------------------
//Constructor
TPictureBuffer :: TPictureBuffer()
{
   pPointer = NULL;
   size = 0;
   Count = 0;
   KindMask = 128;
   TypeMask = 112;
   StatusMask = 12;
   LeaveMask = 3;
}
//----------------------------------------------------------------------
//Destructor
TPictureBuffer :: ~TPictureBuffer()
{
   free(pPointer);
   pPointer = NULL;
   Count = 0;
   size = 0;
}
//----------------------------------------------------------------------
//Add
bool TPictureBuffer :: Add()
{
   //First
   if (pPointer == NULL)
      {
         if ( (pPointer = (char *) malloc(sizeof(pPointer))) != NULL )
            {
               size = sizeof(pPointer);
               ZeroMemory(pPointer, 1);
               Count++;
               return true;
            }
         else
            {
               MessageDlg("Ќевозможно выделить пам€ть", mtError, TMsgDlgButtons() << mbOK, 0);
               return false;
            }
      }
   //Other
   else
      {
         if ( (pPointer = (char *) realloc(pPointer, (size + sizeof(pPointer)))) != NULL )
            {
               size += sizeof(pPointer);
               ZeroMemory(pPointer + Count, 1);
               Count++;
               return true;
            }
         else
            {
               MessageDlg("Ќевозможно выделить пам€ть", mtError, TMsgDlgButtons() << mbOK, 0);
               return false;
            }
      }
}
//----------------------------------------------------------------------
//Make the structure
unsigned char TPictureBuffer :: Convert(Kind _K, type _t, Status _S, Leave _L)
{
   unsigned char Byte, Help;
   Byte = 0;
   Help = _K;
   Help <<= 7;
   Byte |= Help;
   Help = _t;
   Help <<= 4;
   Byte |= Help;
   Help = _S;
   Help <<= 2;
   Byte |= Help;
   Byte |= _L;
   return Byte;
}
//----------------------------------------------------------------------
//Set Kind Key
bool TPictureBuffer :: SetKind(size_t Index, Kind _Kind)
{
   if (Index >= Count)
      {
         MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return false;
      }
   pPointer[Index] &= ~KindMask;
   unsigned char Help;
   Help = _Kind;
   Help <<= 7;
   pPointer[Index] |= Help;
   return true;
}
//----------------------------------------------------------------------
//Set Type Key
bool TPictureBuffer :: SetType(size_t Index, type _Type)
{
   if (Index >= Count)
      {
         MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return false;
      }
   pPointer[Index] &= ~TypeMask;
   unsigned char Help;
   Help = _Type;
   Help <<= 4;
   pPointer[Index] |= Help;
   return true;
}
//----------------------------------------------------------------------
//Set Status Key
bool TPictureBuffer :: SetStatus(size_t Index, Status _Status)
{
   if (Index >= Count)
      {
         MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return false;
      }
   pPointer[Index] &= ~StatusMask;
   unsigned char Help;
   Help = _Status;
   Help <<= 2;
   pPointer[Index] |= Help;
   return true;
}
//----------------------------------------------------------------------
//Set Leave Key
bool TPictureBuffer :: SetLeave(size_t Index, Leave _Leave)
{
   if (Index >= Count)
      {
         MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return false;
      }
   pPointer[Index] &= ~LeaveMask;
   pPointer[Index] |= _Leave;
   return true;
}
//----------------------------------------------------------------------
//Get Kind
Kind TPictureBuffer :: GetKind(size_t Index)
{
   if (Index >= Count)
      {
//         MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return 255;
      }
         unsigned char Help;
         Help = pPointer[Index];
         Help &= KindMask;
         Help >>= 7;
         return Help;
}
//----------------------------------------------------------------------
//Get Type
type TPictureBuffer :: GetType(size_t Index)
{
   if (Index >= Count)
      {
         //MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return 255;
      }
         unsigned char Help;
         Help = pPointer[Index];
         Help &= TypeMask;
         Help >>= 4;
         return Help;
}
//----------------------------------------------------------------------
//Get Status
Status TPictureBuffer :: GetStatus(size_t Index)
{
   if (Index >= Count)
      {
         //MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return 255;
      }
         unsigned char Help;
         Help = pPointer[Index];
         Help &= StatusMask;
         Help >>= 2;
         return Help;
}
//----------------------------------------------------------------------
//Get Leave
Leave TPictureBuffer :: GetLeave(size_t Index)
{
   if (Index >= Count)
      {
         //MessageDlg("Ёлемент структуры не создан", mtError, TMsgDlgButtons() << mbOK, 0);
         return 255;
      }
         unsigned char Help;
         Help = pPointer[Index];
         Help &= LeaveMask;
         return Help;
}
//----------------------------------------------------------------------
#endif