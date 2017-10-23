#ifndef element
#define element
/*/------------------------------------------------------------------------/*/
/*/��� �������������/*/
enum TID {Num, Op, Br, Func, Var};
/*/------------------------------------------------------------------------/*/
/*/���� ������/*/
typedef long double LDouble;
/*/------------------------------------------------------------------------/*/
/*/����������� ������, ��������������� ��������� ������/*/
class Element
   {
   public:
         Element();
         ~Element();
         void SetID(TID init);
         TID GetID();
         void SetNumber(LDouble);
         LDouble GetNumber();
         void SetOperation(Char[1]);
         Char GetOperation();
         void SetBracket(Char[1]);
         Char GetBracket();
         void SetFunction(AnsiString);
         AnsiString GetFunction();
         void SetVariable(Char[1]);
         Char GetVariable();
         void SetPrevious(Element *init);
         Element *GetPrevious();
         void SetNext(Element *init);
         Element *GetNext();
         Element *Prev;
         Element *Next;
   private:
         TID ID;
         LDouble Number;
         Char Operation[1];
         Char Bracket[1];
         AnsiString Func;
         Char Variable[1];

   };
/*/------------------------------------------------------------------------/*/
/*/�����������/*/
Element::Element()
   {
      Prev = NULL;
      Next = NULL;
   }
/*/------------------------------------------------------------------------/*/
/*/����������/*/
Element::~Element()
   {
      Prev = NULL;
      Next = NULL;
   }
/*/------------------------------------------------------------------------/*/
/*/�������, ������������� �������� ���� ID/*/
void Element::SetID(TID init)
   {
      ID = init;
   }
/*/------------------------------------------------------------------------/*/
/*/�������, ���������� �������� ���� ID/*/
TID Element::GetID()
   {
      return ID;
   }
/*/------------------------------------------------------------------------/*/
/*/�������, ������������� �������� ���� Number/*/
void Element::SetNumber(LDouble init)
   {
      Number = init;
   }
/*/------------------------------------------------------------------------/*/
/*/�������, ���������� �������� ���� Number/*/
LDouble Element::GetNumber()
   {
      return Number;
   }
/*/------------------------------------------------------------------------/*/
/*/������� ������������� �������� ���� Operation/*/
void Element::SetOperation(Char init[1])
   {
      Operation[0] = init[0];
   }
/*/------------------------------------------------------------------------/*/
/*/������� ���������� �������� ���� Operation/*/
Char Element::GetOperation()
   {
      return Operation[0];
   }
/*/------------------------------------------------------------------------/*/
/*/������� ������������� �������� ���� Bracket/*/
void Element::SetBracket(Char init[1])
   {
      Bracket[0] = init[0];
   }
/*/------------------------------------------------------------------------/*/
/*/������� ���������� �������� ���� Bracket/*/
Char Element::GetBracket()
   {
      return Bracket[0];
   }
/*/------------------------------------------------------------------------/*/
/*/������� ������������� �������� ���� Func/*/
void Element::SetFunction(AnsiString init)
   {
      Func = init;
   }
/*/------------------------------------------------------------------------/*/
/*/�������, ���������� �������� ���� Func/*/
AnsiString Element::GetFunction()
   {
      return Func;
   }
/*/------------------------------------------------------------------------/*/
/*/������� ������������� �������� ���� Variable/*/
void Element::SetVariable(Char init[1])
   {
      Variable[0] = init[0];
   }
/*/------------------------------------------------------------------------/*/
/*/������� ���������� �������� ���� Variables/*/
Char Element::GetVariable()
   {
      return Variable[0];
   }
/*/------------------------------------------------------------------------/*/
/*/��������� ������ �� ���������� �������/*/
void Element::SetPrevious(Element *init)
   {
     Prev = init;
   }
/*/------------------------------------------------------------------------/*/
/*/����������� ������ ����������� ��������/*/
Element *Element::GetPrevious()
   {
      return Prev;
   }
/*/------------------------------------------------------------------------/*/
/*/��������� ������ �� ��������� �������/*/
void Element::SetNext(Element *init)
   {
      Next = init;
   }
/*/------------------------------------------------------------------------/*/
/*/����������� ������ ���������� ��������/*/
Element *Element::GetNext()
   {
      return Next;
   }
/*/------------------------------------------------------------------------/*/
#endif
/*/------------------------------------------------------------------------/*/