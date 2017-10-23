#ifndef ArrayBuffer_h
#define ArrayBuffer_h
//----------------------------------------------------------------------
//Structure of n - Channel's Array
struct TChannel
{
   TChannel() {Step = 0; Number = 0; Time = 0; RandomValue = 0;};
   unsigned int Step;
   unsigned int Number;
   unsigned char RandomValue;
   unsigned char Time;
};
//----------------------------------------------------------------------
//Structure of m - Sit's Array
struct TSit
{
   TSit() {Step = 0; Number = 0; RandomValue = 0;};
   unsigned int Step;
   unsigned int Number;
   unsigned char RandomValue;
};                                                                     
//----------------------------------------------------------------------
//Structure of the left transacts
struct TLeave
{
   TLeave() {Step = 0; Number = 0;};
   unsigned int Step;
   unsigned int Number;
};
//----------------------------------------------------------------------
//Array of Channels Value
template <class Type>
class TArrayChannel
{
   public:
      TArrayChannel();
      ~TArrayChannel();
      bool Add(Type);
      Type operator [] (unsigned int);
      size_t GetCount() {return Count;}
      Type GetValue(size_t i) {return Channel[i];}
   private:
      Type *Channel;
      unsigned int Count;
      size_t size;
};
//----------------------------------------------------------------------
//Constructor
template <class Type>
TArrayChannel<Type> :: TArrayChannel()
{
   Channel = NULL;
   Count = 0;
   size = 0;
}
//----------------------------------------------------------------------
//Destructor
template <class Type>
TArrayChannel<Type> :: ~TArrayChannel()
{
   free(Channel);
   Channel = NULL;
}
//----------------------------------------------------------------------
template <class Type>
bool TArrayChannel<Type> :: Add(Type _Channel)
{
   if (Channel == NULL)
      {
         if ( (Channel = (Type *) malloc(sizeof(Type))) != NULL)
            {
               Channel[Count] = _Channel;
               Count++;
               size = sizeof(Type);
               return true;
            }
         else
            {
               MessageDlg("Невозможно выделить память", mtError, TMsgDlgButtons() << mbOK, 0);
               return false;
            }
      }
   //-----------------
   else
      {
         if ( (Channel = (Type *) realloc(Channel, (size + (sizeof(Type))))) != NULL)
            {
               size += sizeof(Type);
               Channel[Count++] = _Channel;
               return true;
            }
         else
            {
               MessageDlg("Невозможно выделить память", mtError, TMsgDlgButtons() << mbOK, 0);
               return false;
            }
      }
}
//----------------------------------------------------------------------
template <class Type>
Type TArrayChannel<Type> :: operator [] (unsigned int Index)
{
   for (unsigned int i = 0; i <= Count; i++)
      {
         if (Channel[i].Step == Index)
            {
               return (Channel[i]);
            }
      }
   MessageDlg("Элемент найден не был!!!", mtWarning, TMsgDlgButtons() << mbOK, 0);
   Type Help;
   return (Help);
}
//----------------------------------------------------------------------
#endif
