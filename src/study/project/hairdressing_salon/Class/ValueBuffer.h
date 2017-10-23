#ifndef ValueBuffer_H
#define ValueBuffer_H
//----------------------------------------------------------------------
class TValueBuffer
{
   public:
      TValueBuffer();
      ~TValueBuffer();
      bool Add(unsigned int);
      unsigned int operator[](unsigned int);
      size_t GetCount() {return Index;}
   private:
      char *pPointer;
      unsigned int Index;
      size_t size;
};
//----------------------------------------------------------------------
//Constructor
TValueBuffer :: TValueBuffer()
{
   pPointer = NULL;
   Index = 0;
   size = 0;
}
//----------------------------------------------------------------------
//Destructor
TValueBuffer :: ~TValueBuffer()
{
   free(pPointer);
   pPointer = NULL;
}
//----------------------------------------------------------------------
//Add value to array
bool TValueBuffer :: Add(unsigned int Value)
{
   if (pPointer == NULL)
      {
         if ( (pPointer = (char *) malloc(sizeof(char))) == NULL)
            {
               MessageDlg("Невозможно выделить память!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return false;
            }
         else
            {
               pPointer[Index] = Value;
               size = sizeof(char);
               return true;
            }
      }
   //------------------
   else
      {
         if ( (pPointer = (char *) realloc(pPointer, (size + sizeof(char)) )) == NULL)
            {
               MessageDlg("Невозможно выделить память!!!", mtError, TMsgDlgButtons() << mbOK, 0);
               return false;
            }
         else
            {
               pPointer[++Index] = Value;
               size += sizeof(char);
               return true;
            }
      }
}
//----------------------------------------------------------------------
//Index
unsigned int TValueBuffer :: operator[](unsigned int _Index)
{
   if ((_Index > Index) || (pPointer == NULL))
      {
         //MessageDlg("Выход за пределы массива", mtError, TMsgDlgButtons() << mbOK, 0);
         return 0;
      }
   else
      {
         return (pPointer[_Index]);
      }
}
//----------------------------------------------------------------------
#endif
