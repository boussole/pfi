#ifndef element
#define element
/*/------------------------------------------------------------------------/*/
/*/Тип идентификатор/*/
enum TID {Num, Op, Br, Func, Var};
/*/------------------------------------------------------------------------/*/
/*/Типы данных/*/
typedef long double LDouble;
/*/------------------------------------------------------------------------/*/
/*/Определение класса, представляющего структуру данных/*/
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
/*/Конструктор/*/
Element::Element()
   {
      Prev = NULL;
      Next = NULL;
   }
/*/------------------------------------------------------------------------/*/
/*/Деструктор/*/
Element::~Element()
   {
      Prev = NULL;
      Next = NULL;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция, устанавливает значение поля ID/*/
void Element::SetID(TID init)
   {
      ID = init;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция, возвращает значение поля ID/*/
TID Element::GetID()
   {
      return ID;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция, устанавливает значение поля Number/*/
void Element::SetNumber(LDouble init)
   {
      Number = init;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция, возвращает значение поля Number/*/
LDouble Element::GetNumber()
   {
      return Number;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция устанавливает значение поля Operation/*/
void Element::SetOperation(Char init[1])
   {
      Operation[0] = init[0];
   }
/*/------------------------------------------------------------------------/*/
/*/Функция возвращает значение поля Operation/*/
Char Element::GetOperation()
   {
      return Operation[0];
   }
/*/------------------------------------------------------------------------/*/
/*/Функция устанавливает значение поля Bracket/*/
void Element::SetBracket(Char init[1])
   {
      Bracket[0] = init[0];
   }
/*/------------------------------------------------------------------------/*/
/*/Функция возвращает значение поля Bracket/*/
Char Element::GetBracket()
   {
      return Bracket[0];
   }
/*/------------------------------------------------------------------------/*/
/*/Функция устанавливает значение поля Func/*/
void Element::SetFunction(AnsiString init)
   {
      Func = init;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция, возвращает значение поля Func/*/
AnsiString Element::GetFunction()
   {
      return Func;
   }
/*/------------------------------------------------------------------------/*/
/*/Функция устанавливает значение поля Variable/*/
void Element::SetVariable(Char init[1])
   {
      Variable[0] = init[0];
   }
/*/------------------------------------------------------------------------/*/
/*/Функция возвращает значение поля Variables/*/
Char Element::GetVariable()
   {
      return Variable[0];
   }
/*/------------------------------------------------------------------------/*/
/*/Установка адреса на предыдущий элемент/*/
void Element::SetPrevious(Element *init)
   {
     Prev = init;
   }
/*/------------------------------------------------------------------------/*/
/*/Возвращение адреса предыдущего элемента/*/
Element *Element::GetPrevious()
   {
      return Prev;
   }
/*/------------------------------------------------------------------------/*/
/*/Установка адреса на следующий элемент/*/
void Element::SetNext(Element *init)
   {
      Next = init;
   }
/*/------------------------------------------------------------------------/*/
/*/Возвращение адреса следующего элемента/*/
Element *Element::GetNext()
   {
      return Next;
   }
/*/------------------------------------------------------------------------/*/
#endif
/*/------------------------------------------------------------------------/*/