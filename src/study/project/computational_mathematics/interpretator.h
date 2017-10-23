#ifndef interpretator
#define interpretator
#include "element.h"
#include "Math.h"
#include "Math.hpp"
/*/------------------------------------------------------------------/*/
typedef unsigned int UInt;
/*/------------------------------------------------------------------/*/
/*/���������/*/
Set <char, 44, 57> N;
Set <char, 0, 255> F;
Set <char, 42, 47> O;
Set <char, 40, 41> B;
Set <char, 0, 255> V;
Set <char, 0, 255> C;
/*/------------------------------------------------------------------/*/
/*/����������� ������, ����������������� ������ �� ��������/*/
class Interpretator
   {
   public:
         Interpretator(AnsiString);
         ~Interpretator();
         void Clear();
         void SetCount(UInt);
         UInt GetCount();
         Element *GetLeft();
         Element *GetRight();
         void SetLeft(Element *init);
         void SetRight(Element *init);
         bool GetErr();
         void SchNum();
         void CtrlNum();
         void Add(TID);
         void SchFun();
         void LexMenus();
         void CtrlLex();
         bool Get_X();
         bool Get_Y();
         bool Get_Z();
         void CtrlBracket();
         Element *GetElement(UInt);
         void SetVariable(AnsiString, AnsiString, AnsiString);
         void SetNullAfterRight();
         void SetNullBeforeLeft();
         void Delete(Element **_DelEl);
   private:
         AnsiString String, HelpStr;
         bool Error, Var_X, Var_Y, Var_Z;
         Element *Left, *Right;
         UInt Count, Index;
         LDouble x, y, z;
   };
/*/------------------------------------------------------------------/*/
/*/�����������/*/
Interpretator::Interpretator(AnsiString init)
   {
      Error = false;
      Var_X = false;
      Var_Y = false;
      Var_Z = false;
      String = init;
      Count = 0;
      Left = NULL;
      Right  = NULL;
      Index = 1;
      while ((Index <= String.Length()) && (!Error))
         {
            /*/������� �����/*/
            if (N.Contains(String[Index]))
               {
                  SchNum();
                  CtrlNum();
                  if (Error)
                     {
                        Application->MessageBoxA("������ � ��������� �����",
                                                 "������������� ������", MB_OK);
                        break;
                     }
                  else
                     {
                        Add(Num);
                     }
               }
            else
            /*/������� �������������� �����/*/
            if (C.Contains(String[Index]))
               {
                  switch (String[Index])
                     {
                        case 'P':
                                 HelpStr = "3,14159265358979";
                                 break;
                        case 'p':
                                 HelpStr = "3,14159265358979";
                                 break;
                        case 'E':
                                 HelpStr = "2,718281828459";
                                 break;
                        case 'e':
                                 HelpStr = "2,718281828459";
                                 break;
                     }
                  Add(Num);
                  Index++;
               }
            else
            /*/������� ������/*/
            if (B.Contains(String[Index]))
               {
                  HelpStr = String[Index];
                  Add(Br);
                  Index++;
               }
            else
            /*/������� ����������/*/
            if (V.Contains(String[Index]))
               {
                  switch (String[Index])
                     {
                        case 'X':
                                 HelpStr = char(int(String[Index]) + 32);
                                 Var_X = true;
                                 break;
                        case 'Y':
                                 HelpStr = char(int(String[Index]) + 32);
                                 Var_Y = true;
                                 break;
                        case 'Z':
                                 HelpStr = char(int(String[Index]) + 32);
                                 Var_Z = true;
                                 break;
                        default:
                                 HelpStr = String[Index];
                                 switch (String[Index])
                                    {
                                       case 'x':
                                                   Var_X = true;
                                                   break;
                                       case 'y':
                                                   Var_Y = true;
                                                   break;
                                       case 'z':
                                                   Var_Z = true;
                                                   break;
                                    }
                                 break;
                     }
                  Add(Var);
                  Index++;
               }
            else
            /*/������� �������/*/
            if (F.Contains(String[Index]))
               {
                  SchFun();
                  if (Error)
                     {
                        Application->MessageBoxA("������ � ��������� �������",
                                                 "������������� ������   ", MB_OK);
                        break;
                     }
                  else
                     {
                        Add(Func);
                     }
               }
            else
            /*/������� ��������/*/
            if (O.Contains(String[Index]))
               {
                  switch(String[Index])
                     {
                        case '+':
                                 {
                                    HelpStr = String[Index];
                                    Index++;
                                    Add(Op);
                                    break;
                                 }

                        case '*':
                                 {
                                    HelpStr = String[Index];
                                    Index++;
                                    Add(Op);
                                    break;
                                 }

                        case '/':
                                 {
                                    HelpStr = String[Index];
                                    Index++;
                                    Add(Op);
                                    break;
                                 }

                        case '-':
                                 {
                                    LexMenus();
                                    Index++;
                                    break;
                                 }
                     }
               }
            else
            /*/������� ����������� �������/*/
               {
                  Application->MessageBoxA("    ����������� �������", "������������� ������",
                                           MB_OK);
                  Error = true;
                  break;
               }
         }
      if (Error)
         {
            Clear();
            return;
         }
      CtrlLex();
      if (Error)
         {
            Clear();
            return;
         }
      CtrlBracket();
      if (Error)
         {
            Clear();
            return;
         }
   }
/*/------------------------------------------------------------------/*/
/*/����������/*/
Interpretator::~Interpretator()
   {
      Clear();
   }
/*/------------------------------------------------------------------/*/
/*/��������� ������� ����� ������/*/
void Interpretator::Clear()
   {
      if (Left == NULL) return;
      Element *Help;
      while (Left != NULL)
         {
            Help = Left;
            Left = Left->Next;
            delete Help;
            Count--;
         }
      Left = NULL;
      Right = NULL;
   }
/*/------------------------------------------------------------------/*/
UInt Interpretator::GetCount()
   {
      return Count;
   }
/*/------------------------------------------------------------------/*/
/*/����������� ������ ������ ������� ����/*/
Element *Interpretator::GetLeft()
   {
      return Left;
   }
/*/------------------------------------------------------------------/*/
/*/����������� ������ ������� ������� ����/*/
/*/------------------------------------------------------------------/*/
Element *Interpretator::GetRight()
   {
      return Right;
   }
/*/------------------------------------------------------------------/*/
/*/��������� ������ ������ ������� ����/*/
void Interpretator::SetLeft(Element *init)
   {
      Left = init;
   }
/*/------------------------------------------------------------------/*/
/*/��������� ������ ������ ������� ����/*/
void Interpretator::SetRight(Element *init)
   {
      Right = init;
   }
/*/------------------------------------------------------------------/*/
/*/����������� �������� ���������� _Error/*/
bool Interpretator::GetErr()
   {
      return Error;
   }
/*/------------------------------------------------------------------/*/
/*/����������� �����/*/
void Interpretator::SchNum()
   {
      HelpStr = "";
      while ( (Index <= String.Length()) && (N.Contains(String[Index])) )
         {
            HelpStr = HelpStr + String[Index];
            Index++;
         }
   }
/*/------------------------------------------------------------------/*/
/*/�������� ����� �� ���������� ������/*/
void Interpretator::CtrlNum()
   {
      if (HelpStr.Length() == 0)
         {
            Error = true;
         }
      else
      if ( (HelpStr.Length() != 1) && (HelpStr[1] == '0') && (HelpStr[2] != ','))
         {
               Error = true;
         }
      else
         if  ((HelpStr[1] == ',') || (HelpStr[HelpStr.Length()] == ','))
               {
                  Error = true;
               }
      else
         {
            bool First = false;
               for (int i = 1; i <= HelpStr.Length(); i++)
                  {
                     if ( (HelpStr[i] == ',') && (!First) )
                        {
                           First = true;
                           i++;
                        }
                     else
                        if ( (HelpStr[i] == ',') && (First))
                           {
                              Error = true;
                           }
                  }
         }
      for (int i = 2; i <= HelpStr.Length(); i++)
         {
            if (!N.Contains(HelpStr[i]))
               {
                  if ((HelpStr[i] == '-') && (HelpStr[i-1]) == 'E')
                     {
                        continue;
                     }
                  else
                     {
                        Error = true;
                     }
               }
         }
   }
/*/------------------------------------------------------------------/*/
/*/���������� ������� - �������/*/
void Interpretator::Add(TID Key)
   {
      Element *Lex = new Element;
      Lex->SetID(Key);
      switch (Key)
            {
               case Num:
                        Lex->SetNumber(StrToFloat(HelpStr));
                        break;
               case Func:
                        Lex->SetFunction(HelpStr);
                        break;
               case Br:
                        Lex->SetBracket(HelpStr.c_str());
                        break;
               case Op:
                        Lex->SetOperation(HelpStr.c_str());
                        break;
               case Var:
                        Lex->SetVariable(HelpStr.c_str());
                        break;
            }
      if (Left != NULL)
         {
            Right->Next = Lex;
            Lex->Prev = Right;
            Right = Lex;
         }
      else
         {
            Left = Lex;
            Right = Left;
         }
      Count++;
   }
/*/------------------------------------------------------------------/*/
/*/����������� ����� �������/*/
void Interpretator::SchFun()
   {
      HelpStr = "";
      while ( (Index <= String.Length()) && (F.Contains(String[Index])) )
         {
            switch (String[Index])
               {
                  case 'S':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'C':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'I':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'N':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'O':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'T':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'G':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'A':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'R':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'H':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  case 'L':
                           HelpStr = HelpStr + char(int(String[Index]) + 32);
                           break;
                  default:
                           HelpStr = HelpStr + String[Index];
                           break;
               }
            Index++;
            if ( (HelpStr == "cos") || (HelpStr == "sin") || (HelpStr == "tg") ||
               (HelpStr == "ctg") || (HelpStr == "arctg") || (HelpStr == "arcctg")
               || (HelpStr == "!") || (HelpStr == "^") || (HelpStr == "sh") || (HelpStr == "ch")
               || (HelpStr == "th") || (HelpStr == "cth") || (HelpStr == "ln") || (HelpStr == "arcsin")
               || (HelpStr == "arccos") || (HelpStr == "arcch") || (HelpStr == "arcsh") || (HelpStr == "arcth")
               || (HelpStr == "arccth") )
               {
                  break;
               }
         }
      if ( (HelpStr != "cos") && (HelpStr != "sin") && (HelpStr != "tg") &&
           (HelpStr != "ctg") && (HelpStr != "arctg") && (HelpStr != "arcctg")
           && (HelpStr != "!") && (HelpStr != "^") && (HelpStr != "sh") && (HelpStr != "ch")
           && (HelpStr != "th") && (HelpStr != "cth") && (HelpStr != "ln") && (HelpStr != "arcsin")
           && (HelpStr != "arccos") && (HelpStr != "arcch") && (HelpStr != "arcsh") && (HelpStr != "arcth")
           && (HelpStr != "arccth") )
         {
            Error = true;
         }
   }
/*/------------------------------------------------------------------/*/
/*/�������� ������� "-"/*/
void Interpretator::LexMenus()
   {
      if ( Index+1 > String.Length())
         {
            Application->MessageBoxA("������ ����� ����� �����", "�������� ��������� ", MB_OK);
            Error = true;
         }
      else
      if ( ((String[Index + 1] == ')') || (O.Contains(String[Index + 1])) || (String[Index + 1] == '^')
          || (String[Index + 1] == '!') || (String[Index + 1] == ' ') || ( (Index != 1) && (O.Contains(String[Index - 1]) ))
          || ((String[Index + 1] == '(') && ( (Index != 1) && (F.Contains(String[Index - 1]) )))) )
          {
            Application->MessageBoxA("������ ����� ����� �����", "�������� ��������� ", MB_OK);
            Error = true;
          }
      else
      /*/�����������  -1/*/
      if ( (String[Index] == '-') && ( ((Index == 1) && (F.Contains(String[Index+1])))
         || ((Index == 1) && ((N.Contains(String[Index + 1])) || (V.Contains(String[Index+1]))) ) || ((Index == 1)
         && (String[Index + 1] == '(')) || ( (Index != 1) && (String[Index - 1] == '('))
         || ( (Index != 1) && (F.Contains(String[Index-1])) && (String[Index-1] != '!')) ) )
            {
               HelpStr = "-1";
               Add(Num);
               HelpStr = "*";
               Add(Op);
            }
  else
      /*/����������� + -1/*/
      if (
            (String[Index] == '-') && (Index != 1)
            &&
            (
               (N.Contains(String[Index - 1])) || (V.Contains(String[Index-1])
            )
            ||
            (
               (String[Index+1] == '(') && (!F.Contains(String[Index-1]))
            )
               ||
            (String[Index-1] == ')')  || ((F.Contains(String[Index-1])) && (String[Index-1] == '!')))
         )
            {
               HelpStr = "+";
               Add(Op);
               HelpStr = "-1";
               Add(Num);
               HelpStr = "*";
               Add(Op);
            }
   }
/*/------------------------------------------------------------------/*/
/*/�������� ������ �� ������/*/
void Interpretator::CtrlLex()
   {
    Element *Help = Left;
    while (Help != NULL)
      {
      /*/������� ����������� ������/*/
      if ((Help->GetID() == Br) && (Help->GetBracket() == '('))
         {
          if ( ((Help != Left) && (Help->Prev->GetID() == Num)) ||
               ((Help != Left) && (Help->Prev->GetID() == Var)) ||
               ((Help != Right) && (Help->Next->GetID() == Op)) ||
               ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == '!')) ||
               ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == '!')) ||
               ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == '^')) ||
               ((Help != Left) && (Help->Prev->GetID() == Br) && (Help->Prev->GetBracket() != Help->GetBracket())) ||
               ((Help != Right) && (Help->Next->GetID() == Br) && (Help->Next->GetBracket() != Help->GetBracket())) )
            {
              Application->MessageBoxA("������ ����� ����������� ������  ",
                                       "�������� ���������", MB_OK);
              Error = true;
              break;
            }
          }
      else
      /*/������� ����������� ������/*/
      if ( (Help->GetID() == Br) && (Help->GetBracket() == ')') )
         {
          if ( ((Help != Right) && (Help->Next->GetID() == Num)) ||
               ((Help != Right) && (Help->Next->GetID() == Var)) ||
               ((Help != Left) && (Help->Prev->GetID() == Op)) ||
               ((Help != Right) && (Help->Next->GetID() == Func) && ( (Help->Next->GetFunction() != '!')
                                    && (Help->Next->GetFunction() != '^')) ) ||
               ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() != '!')) ||
               ((Help != Left) && (Help->Prev->GetID() == Br) && (Help->Prev->GetBracket() != Help->GetBracket())) ||
               ((Help != Right) && (Help->Next->GetID() == Br) && (Help->Next->GetBracket() != Help->GetBracket())))
            {
               Application->MessageBoxA("������ ����� ����������� ������  ",
                                        "�������� ���������", MB_OK);
               Error = true;
               break;
            }
          }
      else
      /*/������� �����/*/
      if (Help->GetID() == Num)
         {
          if ( ((Help != Right) && (Help->Next->GetID() == Func) && ((Help->Next->GetFunction() != '^') &&
                                                                      (Help->Next->GetFunction() != '!'))) ||
             ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == '!')) ||
             ((Help != Left) && (Help->Prev->GetID() == Var)) ||
             ((Help != Right) && (Help->Next->GetID() == Var)) )
            {
              Application->MessageBoxA("     ������ ����� �����",
                                       "�������� ���������", MB_OK);
              Error = true;
              break;
            }
          }
      else
      /*/������� ������������������ ��� ��������������� ������� /*/
      if ( (Help->GetID() == Func) && ((Help->GetFunction() != '^') && (Help->GetFunction() != '!')))
         {
            if ( ((Help != Right) && (Help->Next->GetID() == Op)) ||
                 ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == '!')) ||
                 ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == '!')) ||
                 ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == '^')) ||
                 ((Help != Right) && (Help->Next->GetID() == Num) && (Help->Next->GetNumber() == -1)) ||
                 ((Help != Right) && (Help->Next->GetID() == Func)) || (Help == Right) )
               {
                  Application->MessageBoxA("������ ����� ������������������ ��� ��������������� �������  ",
                                           "�������� ���������", MB_OK);
                  Error = true;
                  break;
               }
         }
      else
      /*/������ ���������/*/
      if ( (Help->GetID() == Func) && (Help->GetFunction() == '!') )
         {
          if ( ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == '!')) ||
               ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == '!')) ||
               ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == '^')) ||
               (Help == Left) )
            {
               Application->MessageBoxA("������ ����� ������� ���������  ",
                                        "�������� ���������", MB_OK);
               Error = true;
               break;
            }
         }
      else
      /*/������� ���������� � �������/*/
      if ( (Help->GetID() == Func) && (Help->GetFunction() == "^") )
         {
          if ( ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == "^")) ||
               ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == "^")) ||
               ((Help != Right) && (Help->Next->GetID() == Num) && (Help->Next->GetNumber() == -1)) ||
               (Help == Left) || (Help == Right) )
            {
              Application->MessageBoxA("������ ����� ������� <<���������� � �������>>  ",
                                       "�������� ���������", MB_OK);
              Error = true;
              break;
            }
         }
      else
      /*/������� ��������/*/
      if (Help->GetID() == Op)
         {
          if ( ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == "!")) ||
               ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == "^")) ||
               ((Help != Right) && (Help->Next->GetID() == Func) && (Help->Next->GetFunction() == "^")) ||
               ((Help != Left) && (Help->Prev->GetID() == Op)) ||
               ((Help != Right) && (Help->Next->GetID() == Op)) || (Help == Left) || (Help == Right) )
             {
                Application->MessageBoxA("������ ����� ����� ��������   ",
                                         "�������� ���������", MB_OK);
                Error = true;
                break;
             }
         }
      else
      /*/������� ����������/*/
      if (Help->GetID() == Var)
         {
            if ( ((Help != Right) && (Help->Next->GetID() == Func) && ((Help->Next->GetFunction() != '^') &&
                                                                         (Help->Next->GetFunction() != '!'))) ||
               ((Help != Left) && (Help->Prev->GetID() == Func) && (Help->Prev->GetFunction() == '!')) ||
               ((Help != Left) && (Help->Prev->GetID() == Var))
               || ((Help != Right) && (Help->Next->GetID() == Var))
               || ((Help != Left) && (Help->Prev->GetID() == Num)) || ((Help != Right) && (Help->Next->GetID() == Num)))
               {
                  Application->MessageBoxA("������ ����� ���������� ",
                                           "�������� ���������", MB_OK);
                  Error = true;
                  break;
               }
         }
         Help = Help->Next;
      }
   }
/*/------------------------------------------------------------------/*/
/*/�������� ���������� � ������ ���������� �/*/
bool Interpretator::Get_X()
   {
      return Var_X;
   }
/*/------------------------------------------------------------------/*/
/*/�������� ���������� � ������ ���������� y/*/
bool Interpretator::Get_Y()
   {
      return Var_Y;
   }
/*/-----------------------------------------------------------------/*/
/*/�������� ���������� � ������ ���������� z/*/
bool Interpretator::Get_Z()
   {
      return Var_Z;
   }
/*/------------------------------------------------------------------/*/
/*/�������� ������������ ������������ ������/*/
void Interpretator::CtrlBracket()
   {
      Element *First = Left;
      Element *Last;
      bool Find_Open = true, Find_Close = true, Duble;
      UInt Array[255];
      UInt Open, Close = 1, ArraySize = 0;
      while ((Find_Open) && (Find_Close) && (!Error))
         {
            Find_Close = false;
            Find_Open = false;
            Duble = false;
            /*/����� ����������� ������/*/
            while (First != NULL)
               {
                  if ((First->GetID() == Br) && (First->GetBracket() == ')'))
                     {
                        Find_Close = true;
                        break;
                     }
                  Close++;
                  First = First->Next;
               }
            if (!Find_Close)
               {
                  Close--;
                  Last = Right;
                  Open = Close;
               }
            else
               {
                  Last = First;
                  Open = Close;
               }
            /*/����� ����������� ������/*/
            while (Last != NULL)
               {
                  if ((Last->GetID() == Br) && (Last->GetBracket() == '('))
                     {
                        /*/�������� �� ����������� ���� ������/*/
                        for (int i = 0; i < ArraySize; i++)
                           {
                              if (Array[i] == Open)
                                 {
                                    Duble = true;
                                 }
                           }
                        if (!Duble)
                           {
                              Find_Open = true;
                              Array[ArraySize] = Open;
                              ArraySize++;
                              break;
                           }
                        else
                           {
                              Duble = false;
                           }
                     }
                  Open--;
                  Last = Last->Prev;
               }
            if ((Find_Open) && (!Find_Close))
               {
                  Application->MessageBoxA("  �� ������� ����������� ������",
                                           "�������� ����������� ������", MB_OK);
                  Error = true;
               }
            else
            if ((!Find_Open) && (Find_Close))
               {
                  Application->MessageBoxA("  �� ������� ����������� ������",
                                           "�������� ����������� ������", MB_OK);
                  Error = true;
               }
            else
            if (First != NULL)
               {
                  First = First->Next;
                  Close++;
               }
         }
   }
/*/------------------------------------------------------------------/*/
/*/������� ���������� ����� �������� �� ������/*/
Element *Interpretator::GetElement(UInt NumEl)
   {
      if (Left == NULL) return 0;
      Element *HelpNum = Left;
      for (UInt i = 1; i < NumEl; i++)
         {
            HelpNum = HelpNum->Next;
         }
      return HelpNum;
   }
/*/------------------------------------------------------------------/*/
/*/���������� �������� ����������/*/
void Interpretator::SetVariable(AnsiString X, AnsiString Y, AnsiString Z)
   {
      /*/�������� �/*/
      HelpStr = X;
      if ((Var_X) && (HelpStr.Length() == 0))
         {
            Application->MessageBoxA("��������� ���� �� ��������� � ",
                                     "����������", MB_OK);
            Error = true;
            return;
         }
      else
      if (Var_X)
         {
            CtrlNum();
         }
      if (Error)
         {
            Application->MessageBoxA(" ������ � ��������� �����",
                                     "�������� ���������� X", MB_OK);
            Error = true;
            return;
         }
      /*/�������� Y/*/
      HelpStr = Y;
      if ((Var_Y) && (HelpStr.Length() == 0))
         {
            Application->MessageBoxA("��������� ���� �� ��������� Y ",
                                     "����������", MB_OK);
            Error = true;
            return;
         }
      else
      if (Var_Y)
         {
            CtrlNum();
         }
      if (Error)
         {
            Application->MessageBoxA(" ������ � ��������� �����",
                                     "�������� ���������� Y", MB_OK);
            Error = true;
            return;
         }
      /*/�������� Z/*/
      HelpStr = Z;
      if ((Var_Z) && (HelpStr.Length() == 0))
         {
            Application->MessageBoxA("��������� ���� �� ��������� Z ",
                                     "����������", MB_OK);
            Error = true;
            return;
         }
      else
      if (Var_Z)
         {
            CtrlNum();
         }
      if (Error)
         {
            Application->MessageBoxA(" ������ � ��������� �����",
                                     "�������� ���������� Z", MB_OK);
            Error = true;
            return;
         }
      Element *Help = Left;
      while (Help != NULL)
         {
            if (Help->GetID() == Var)
               {
                  switch (Help->GetVariable())
                     {
                        case 'x':
                                    Help->SetNumber(StrToFloat(X));
                                    break;
                        case 'y':
                                    Help->SetNumber(StrToFloat(Y));
                                    break;
                        case 'z':
                                    Help->SetNumber(StrToFloat(Z));
                                    break;
                     }
               }
            Help = Help->Next;
         }
   }
/*/------------------------------------------------------------------/*/
void Interpretator::SetCount(UInt init)
   {
      Count = init;
   }
/*/------------------------------------------------------------------/*/
void Interpretator::SetNullAfterRight()
   {
      Right->Next = NULL;
   }
/*/------------------------------------------------------------------/*/
void Interpretator::SetNullBeforeLeft()
   {
      Left->Prev = NULL;
   }
/*/------------------------------------------------------------------/*/
/*/�������� ������ ������� ������/*/
void Interpretator::Delete(Element **_DelEl)
   {
      /*/�������� �� ������/*/
      if (*_DelEl == Left)
         {
            Left = Left->Next;
            delete *_DelEl;
            *_DelEl = NULL;
            Left->Prev = NULL;
            Count--;
         }
      else
      /*/�������� �� �����/*/
      if (*_DelEl == Right)
         {
            Right = Right->Prev;
            delete *_DelEl;
            *_DelEl = NULL;
            Right->Next = NULL;
            Count--;
         }
      else
      /*/�������� �� ��������/*/
         {
            (*_DelEl)->Next->Prev = (*_DelEl)->Prev;
            (*_DelEl)->Prev->Next = (*_DelEl)->Next;
            delete *_DelEl;
            *_DelEl = NULL;
            Count--;
         }
   }
#endif
/*/------------------------------------------------------------------/*/
