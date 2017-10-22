#ifndef TemplateList_H
#define TemplateList_H
//--------------------
typedef double TVertex[4];
//--------------------
struct TElement
{
   TVertex Value;
   TElement *Next;
   TElement *Prev;
};
//--------------------
class TLIST
{
public:
      TLIST();
      ~TLIST();
      void Add(double, double, double, double);
      void SetValue(double, double, double);
      double GetValue(unsigned int, unsigned int);
      unsigned int GetCount() {return Count;};
private:
      unsigned int Count;
      TElement *Left;
      TElement *Right;
};
//--------------------
//Конструктор
TLIST :: TLIST() : Left(NULL), Right(NULL), Count(0)
   {
   }
//--------------------
TLIST :: ~TLIST()
   {
      TElement *Help;
      if (Left != NULL)
         {
            while (Left != NULL)
               {
                  Help = Left;
                  Left = Left->Next;
                  Help->Prev = NULL;
                  Help->Next = NULL;
                  delete Help;
               }
            Help = NULL;
            Left = NULL;
            Right = NULL;
            Count = 0;
         }
   }
//--------------------
void TLIST :: Add(double _X, double _Y, double _Z, double _H)
   {
      if (Left == NULL)
         {
            Left = new TElement;
            Left->Value[0] = _X;
            Left->Value[1] = _Y;
            Left->Value[2] = _Z;
            Left->Value[3] = _H;
            Left->Prev = NULL;
            Left->Next = NULL;
         }
      else
         {
            TElement *Help_1, *Help_2;
            Help_1 = new TElement;
            Help_1->Value[0] = _X;
            Help_1->Value[1] = _Y;
            Help_1->Value[2] = _Z;
            Help_1->Value[3] = _H;
            Help_1->Prev = NULL;
            Help_1->Next = NULL;

            Help_2 = Left;
            while (Help_2->Next != NULL)
               {
                  Help_2 = Help_2->Next;
               }
            Help_2->Next = Help_1;
            Help_1->Prev = Help_2;
            Right = Help_1;
         }
      Count++;
   }
//--------------------
double TLIST :: GetValue(unsigned int _I, unsigned int _J)
   {
      if ((_I >= Count) || (_J >= 4))
         {
            ShowMessage("Выход за границы массива");
            return 0;
         }
      else
         {
            TElement *Help = Left;
            for (unsigned int i = 0; i < _I; i++)
               {
                  Help = Help->Next;
               }
            return (Help->Value[_J]);
         }
   }
//--------------------
#endif
//--------------------
