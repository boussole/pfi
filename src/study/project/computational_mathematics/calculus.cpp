//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "calculus.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
/*/-----------------------------------------------------------------------/*/
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
/*/-----------------------------------------------------------------------/*/
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   N << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7'
     << '8' << '9' << ',';
   O << '+' << '-' << '*' << '/';
   F << 'S' << 's' << 'C' << 'c' << 'I' << 'i' << 'N' << 'n' << 'O'
     << 'o' << 'T' << 't' << 'G' << 'g' << 'A' << 'a' << 'R' << 'r'
     << '!' << '^' << 'H' << 'h' << 'L' << 'l';
   B << '(' << ')';
   V << 'X' << 'x' << 'Y' << 'y' << 'Z' << 'z';
   C << 'P' << 'p' << 'E' << 'e';
   /*/Заполнение фиксированных столбцов таблицы/*/
/*/Нелинейные уравнения - Метод биссекции/*/
StringGrid1->Cells[0][0] = "            a";
StringGrid1->Cells[1][0] = "          f (a)";
StringGrid1->Cells[2][0] = "            b";
StringGrid1->Cells[3][0] = "          f (b)";
StringGrid1->Cells[4][0] = "            c";
StringGrid1->Cells[5][0] = "          f (c)";
/*/-----------/*/
/*/Нелинейные уравнения - Метод хорд/*/
StringGrid2->Cells[0][0] = "            a";
StringGrid2->Cells[1][0] = "          f (a)";
StringGrid2->Cells[2][0] = "            b";
StringGrid2->Cells[3][0] = "          f (b)";
StringGrid2->Cells[4][0] = "            c";
StringGrid2->Cells[5][0] = "          f (c)";
/*/-----------/*/
/*/Нелинейные уравнения - Метод каcательных/*/
StringGrid3->Cells[0][0] = "             X";
StringGrid3->Cells[1][0] = "             Y (x)";
StringGrid3->Cells[2][0] = "             Y' (x)";
StringGrid3->Cells[3][0] = "        ^X = - (Y(x) / Y'(x))";
/*/-----------/*/
/*/Одномерная оптимизация - Метод биссекции/*/
StringGrid4->Cells[0][0] = "            a";
StringGrid4->Cells[1][0] = "         F ' (a)";
StringGrid4->Cells[2][0] = "            b";
StringGrid4->Cells[3][0] = "         F ' (b)";
StringGrid4->Cells[4][0] = "            c";
StringGrid4->Cells[5][0] = "         F ' (c)";
/*/-----------/*/
/*/Одномерная оптимизация - Метод золотого сечения/*/
StringGrid5->Cells[0][0] = "             a";
StringGrid5->Cells[1][0] = "           f (a)";
StringGrid5->Cells[2][0] = "             X1";
StringGrid5->Cells[3][0] = "           f (X1)";
StringGrid5->Cells[4][0] = "             X2";
StringGrid5->Cells[5][0] = "           f (X2)";
StringGrid5->Cells[6][0] = "            b";
StringGrid5->Cells[7][0] = "           f (b)";
StringGrid5->Cells[8][0] = "           Lo";
StringGrid5->Cells[9][0] = "           L1";
StringGrid5->Cells[10][0] = "          L2";
/*/-----------/*/
/*/Одномерная оптимизация - Метод Ньютона - Рафсона/*/
StringGrid6->Cells[0][0] = "               X";
StringGrid6->Cells[1][0] = "             Y (x)";
StringGrid6->Cells[2][0] = "            Y ' (x)";
StringGrid6->Cells[3][0] = "           Y '' (x)";
StringGrid6->Cells[4][0] = "^X = - (Y'(x) / Y '' (x))";
/*/-----------/*/
/*/Задача Коши - Метод Эйлера/*/
StringGrid7->Cells[0][0] = "                         X";
StringGrid7->Cells[1][0] = "                         Y ";
StringGrid7->Cells[2][0] = "                         Y ' ";
/*/-----------/*/
/*/Исправленый метод Эйлера/*/
StringGrid8->Cells[0][0] = "             X";
StringGrid8->Cells[1][0] = "             Y ";
StringGrid8->Cells[2][0] = "            Y '";
StringGrid8->Cells[3][0] = "           ~X";
StringGrid8->Cells[4][0] = "           ~Y ";
StringGrid8->Cells[5][0] = "           ~Y ' ";
/*/-----------/*/
/*/Метод Рунге - Кутта IV порядка/*/
StringGrid9->Cells[0][0] = "               X";
StringGrid9->Cells[1][0] = "               Y ";
StringGrid9->Cells[2][0] = "           Y ' = T1";
StringGrid9->Cells[3][0] = "            ~X";
StringGrid9->Cells[4][0] = "            ~Y";
StringGrid9->Cells[5][0] = "        ~Y ' = T2";
StringGrid9->Cells[6][0] = "            ^X";
StringGrid9->Cells[7][0] = "            ^Y";
StringGrid9->Cells[8][0] = "        ^Y ' = T3";
StringGrid9->Cells[9][0] = "            <X";
StringGrid9->Cells[10][0] = "           <Y";
StringGrid9->Cells[11][0] = "       <Y ' = T4";
StringGrid9->Cells[12][0] = "              T";
}
/*/-----------------------------------------------------------------------/*/
/*/Глобальные переменные/*/
enum El{Up, Mid, Low};
/*/-----------------------------------------------------------------------/*/
/*/Прототипы функций/*/
void CrtlMenus(Interpretator **List);
void Result(Interpretator *, bool &, LDouble &, bool, bool);
bool Drobnoe(LDouble);
LDouble Factorial(LDouble, bool &);
bool CtrlNum(AnsiString);
LDouble Eps(AnsiString);
void ClearStrGrd(TStringGrid *);
LDouble Modul(LDouble);
void AnsFun(AnsiString, bool &, LDouble, LDouble &, bool, bool);
void AnsDFun(AnsiString, bool &, LDouble, LDouble &, bool, bool);
void PrintBissekcy(TStringGrid *, int, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString);
void StrGrdRow(TStringGrid *);
void PrintNew(TStringGrid *, int, AnsiString, AnsiString, AnsiString, AnsiString);
void PrintGold(TStringGrid *, int, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString,
                     AnsiString, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString);
void PrintOO(TStringGrid *, int, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString);
bool Kratnost(LDouble, LDouble, LDouble);
void AnsKoshi(AnsiString, bool &, LDouble, LDouble, LDouble &, bool, bool);
void PrintEiler(TStringGrid *, int, AnsiString, AnsiString, AnsiString);
void PrintEiler(TStringGrid *, int, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString);
void PrintEiler(TStringGrid *, int, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString,
AnsiString, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString, AnsiString);
/*/-----------------------------------------------------------------------/*/
/*/------------------------------Функции----------------------------------/*/
/*/-----------------------------------------------------------------------/*/
/*/Умножение "лишней" -1/*/
void CtrlMenus(Interpretator **List)
   {
      Element *Pointer = (*List)->GetLeft();
      Element *DelEl_1, *DelEl_2;
      while (Pointer != NULL)
         {
            if ( (Pointer->Next != NULL) && (Pointer->Next->Next != NULL) &&
                 (((Pointer->GetID() == Num) || (Pointer->GetID() == Var)) && (Pointer->GetNumber() == -1)) &&
                 ((Pointer->Next->GetID() == Op) && (Pointer->Next->GetOperation() == '*')) &&
                 (Pointer->Next->Next->GetID() == Num) )
               {
                  Pointer->SetNumber((Pointer->GetNumber()) * (Pointer->Next->Next->GetNumber()));
                  DelEl_1 = Pointer->Next;
                  DelEl_2 = Pointer->Next->Next;
                  (*List)->Delete(&DelEl_1);
                  (*List)->Delete(&DelEl_2);
                  Pointer = (*List)->GetLeft();
               }
            else
               {
                  Pointer = Pointer->Next;
               }
         }
   }
/*/-----------------------------------------------------------------------/*/
/*/Подсчёт результата/*/
void Result(Interpretator *_List, bool &_ErrAns, LDouble &_Answer, bool _Deg, bool _Grad)
   { /*/начало/*/
      Element *Begin, *End, *Del_El1, *Del_El2, *Memory;
      bool BracketFound = false;
      LDouble Help;
/*/<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>/*/
      while ((_List->GetLeft()->Next != NULL) && (!_ErrAns))
         {  /*/начало цикла/*/
            Begin = _List->GetLeft();
            End = _List->GetRight();
/*/-----------------------------------------------------------------------/*/
            /*/Поиск открывающей скобки/*/
            while (Begin != NULL)
               {
                  if ((Begin->GetID() == Br) && (Begin->GetBracket() == ')'))
                     {
                        End = Begin;
                        BracketFound = true;
                        break;
                     }
                  Begin = Begin->Next;
               }
/*/----------------------------------------------------------------------/*/
            /*/Поиск закрывающей/*/
            if (BracketFound)
               {
                  while (Begin != NULL)
                     {
                        if ((Begin->GetID() == Br) && (Begin->GetBracket() == '('))
                           {
                              BracketFound = false;
                              break;
                           }
                        Begin = Begin->Prev;
                     }
                  /*/-----------------------------------------------------/*/
                  /*/число между двумя скобками/*/
                  if ( (Begin == End->Prev->Prev) && ((Begin->Next->GetID() == Num) || (Begin->Next->GetID() == Var)) )
                     {
                        Begin->SetID(Num);
                        Begin->SetNumber(Begin->Next->GetNumber());
                        Del_El1 = Begin->Next;
                        Del_El2 = Begin->Next->Next;
                        _List->Delete(&Del_El1);
                        _List->Delete(&Del_El2);
                        goto EndOfWhile;
                     }
                  /*/----------------------------------------------------/*/
               }
/*/----------------------------------------------------------------------/*/
            /*/Дальнейший поиск/*/
            if (Begin == NULL)
               {
                  Begin = _List->GetLeft();
                  End = _List->GetRight();
               }
            Memory = Begin;
/*/----------------------------------------------------------------------/*/
        /*/Подсчёт тригонометрических и логарифмической функций/*/
/*/----------------------------------------------------------------------/*/
        while (Begin != End->Next)
           {
            /*/Найдена функция (не факториал и не возведение в степень)/*/
            if ( (Begin->Next != NULL) && (Begin->GetID() == Func) && ((Begin->GetFunction() != '!') && (Begin->GetFunction() != '^'))
               && ((Begin->Next->GetID() == Num) || (Begin->Next->GetID() == Var)) )
               {
                  Begin->SetID(Num);
                  /*/Функция косинус/*/
                  if (Begin->GetFunction() == "cos")
                     {
                        if (_Deg)
                           {
                              Begin->SetNumber(cos(DegToRad(Begin->Next->GetNumber())));
                           }
                        else
                        if (_Grad)
                           {
                              Begin->SetNumber(cos(GradToRad(Begin->Next->GetNumber())));
                           }
                        else
                           {
                              Begin->SetNumber(cos(Begin->Next->GetNumber()));
                           }
                     }
                  else
                  /*/Функция синус/*/
                  if (Begin->GetFunction() == "sin")
                     {
                        if (_Deg)
                           {
                              Begin->SetNumber(sin(DegToRad(Begin->Next->GetNumber())));
                           }
                        else
                        if (_Grad)
                           {
                              Begin->SetNumber(sin(GradToRad(Begin->Next->GetNumber())));
                           }
                        else
                           {
                              Begin->SetNumber(sin(Begin->Next->GetNumber()));
                           }
                     }
                  else
                  /*/Функция тангенс/*/
                  if (Begin->GetFunction() == "tg")
                     {
                        if (_Deg)
                           {
                              if (
                                    (Begin->Next->GetNumber() == 90)
                                 ||
                                    (Begin->Next->GetNumber() == 270)
                                 )
                                 {
                                    Application->MessageBoxA("Недопустимый аргумент функции",
                                                             "Вычисление тангенса");
                                    _ErrAns = true;
                                    break;
                                 }
                              else
                                 {
                                    Begin->SetNumber(Tan(DegToRad(Begin->Next->GetNumber())));
                                 }
                           }
                        else
                        if (_Grad)
                           {
                              Begin->SetNumber(Tan(GradToRad(Begin->Next->GetNumber())));
                           }
                        else
                           {
                              if (
                                 (Begin->Next->GetNumber() == StrToFloat("1,5707963267949"))
                                 ||
                                 (Begin->Next->GetNumber() == StrToFloat("4,7123889803847"))
                                 )
                                 {
                                    Application->MessageBoxA("Недопустимый аргумент функции",
                                                             "Вычисление тангенса");
                                    _ErrAns = true;
                                    break;
                                 }
                              else
                                 {
                                    Begin->SetNumber(Tan(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  else
                  /*/Функция контангенс/*/
                  if (Begin->GetFunction() == "ctg")
                     {
                        if (_Deg)
                           {
                              if (
                                    (Begin->Next->GetNumber() == 180)
                                 ||
                                    (Begin->Next->GetNumber() == 0)
                                 )
                                 {
                                    Application->MessageBoxA("Недопустимый аргумент функции",
                                                                  "Вычисление котангенса");
                                    _ErrAns = true;
                                    break;
                                 }
                              else
                                 {
                                    Begin->SetNumber(Cot(DegToRad(Begin->Next->GetNumber())));
                                 }
                           }
                        else
                        if (_Grad)
                           {
                              Begin->SetNumber(Cot(GradToRad(Begin->Next->GetNumber())));
                           }
                        else
                           {
                              if (
                                    (Begin->Next->GetNumber() == StrToFloat("3,1415926535897"))
                                 ||
                                    (Begin->Next->GetNumber() == StrToFloat("0"))
                                 )
                                    {
                                       Application->MessageBoxA("Недопустимый аргумент функции",
                                                                  "Вычисление котангенса");
                                       _ErrAns = true;
                                       break;
                                    }
                              else
                                 {
                                    Begin->SetNumber(Cot(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  else
                  /*/Функция арктангенс/*/
                  if (Begin->GetFunction() == "arctg")
                     {
                        Application->MessageBoxA("Данная функция не описана в этой программе", "Предупреждение!!!", MB_OK);
                        _ErrAns = true;
                        break;
                     }
                  else
                  /*/Функция арккотангенс/*/
                  if (Begin->GetFunction() == "arcctg")
                     {
                        if (Begin->Next->GetNumber() == 0)
                           {
                              Application->MessageBoxA("Недопустимый аргумент функции",
                                                       "Вычисление арккотангенса", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                        if (_Deg)
                              {
                                 Begin->SetNumber(RadToDeg(ArcCot(Begin->Next->GetNumber())));
                              }
                           else
                           if (_Grad)
                              {
                                 Begin->SetNumber(RadToGrad(ArcCot(Begin->Next->GetNumber())));
                              }
                           else
                              {
                                 Begin->SetNumber(ArcCot(Begin->Next->GetNumber()));
                              }
                           }
                     }
                  else
                  /*/Функция гиперболический синус - несовпадение с калькулятором/*/
                  if (Begin->GetFunction() == "sh")
                     {
                        if (_Deg)
                           {
                              Begin->SetNumber(Sinh(DegToRad(Begin->Next->GetNumber())));
                           }
                        else
                        if (_Grad)
                           {
                              Begin->SetNumber(Sinh(GradToRad(Begin->Next->GetNumber())));
                           }
                        else
                           {
                              Begin->SetNumber(Sinh(Begin->Next->GetNumber()));
                           }
                     }
                  else
                  /*/Функция гиперболический косинус - несовпадение с калькулятором/*/
                  if (Begin->GetFunction() == "ch")
                     {
                        if (_Deg)
                              {
                                 Begin->SetNumber(Cosh(DegToRad(Begin->Next->GetNumber())));
                              }
                          else
                           if (_Grad)
                              {
                                 Begin->SetNumber(Cosh(GradToRad(Begin->Next->GetNumber())));
                              }
                           else
                              {
                                 Begin->SetNumber(Cosh(Begin->Next->GetNumber()));
                              }
                     }
                  else
                  /*/Функция гиперболический тангенс/*/
                  if (Begin->GetFunction() == "th")
                     {
                        if (_Deg)
                              {
                                 Begin->SetNumber(Tanh(DegToRad(Begin->Next->GetNumber())));
                              }
                          else
                           if (_Grad)
                              {
                                 Begin->SetNumber(Tanh(GradToRad(Begin->Next->GetNumber())));
                              }
                           else
                              {
                                 Begin->SetNumber(Tanh(Begin->Next->GetNumber()));
                              }
                     }
                  else
                  /*/Функция гиперболический котангенс/*/
                  if (Begin->GetFunction() == "cth")
                     {
                        if (Begin->Next->GetNumber() == 0)
                           {
                              Application->MessageBoxA("               Недопустимый аргумент функции",
                                                       "Вычисление гиперболического котангенса", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                        if (_Deg)
                              {
                                 Begin->SetNumber(CotH(DegToRad(Begin->Next->GetNumber())));
                              }
                          else
                           if (_Grad)
                              {
                                 Begin->SetNumber(CotH(GradToRad(Begin->Next->GetNumber())));
                              }
                           else
                              {
                                 Begin->SetNumber(CotH(Begin->Next->GetNumber()));
                              }
                           }
                     }
                  else
                  /*/Натуральный логарифм/*/
                  if (Begin->GetFunction() == "ln")
                     {
                        if (Begin->Next->GetNumber() == 0)
                           {
                              Application->MessageBoxA("           Недопустимый аргумент функции",
                                                       "Вычисление натурального логарифма", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                              Begin->SetNumber(LnXP1(Begin->Next->GetNumber() - 1));
                           }
                     }
                  else
                  /*/Арксинус/*/
                  if (Begin->GetFunction() == "arcsin")
                     {
                        if ((Begin->Next->GetNumber() > 1) || (Begin->Next->GetNumber() < -1))
                           {
                              Application->MessageBoxA("Значение аргумента должно лежать в интервале [-1;1]",
                                                       "Вычисление арксинуса", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                              if (_Deg)
                                 {
                                    Begin->SetNumber(RadToDeg(ArcSin(Begin->Next->GetNumber())));
                                 }
                              else
                              if (_Grad)
                                 {
                                    Begin->SetNumber(RadToGrad(ArcSin(Begin->Next->GetNumber())));
                                 }
                              else
                                 {
                                    Begin->SetNumber(ArcSin(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  else
                  /*/Арккосинус/*/
                  if (Begin->GetFunction() == "arccos")
                     {
                        if ((Begin->Next->GetNumber() > 1) || (Begin->Next->GetNumber() < -1))
                           {
                              Application->MessageBoxA("Значение аргумента должно лежать в интервале [-1;1]",
                                                       "Вычисление арккосинуса", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                              if (_Deg)
                                 {
                                    Begin->SetNumber(RadToDeg(ArcCos(Begin->Next->GetNumber())));
                                 }
                              else
                              if (_Grad)
                                 {
                                    Begin->SetNumber(RadToGrad(ArcCos(Begin->Next->GetNumber())));
                                 }
                              else
                                 {
                                    Begin->SetNumber(ArcCos(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  else
                  /*/Арккосинус гиперболической функции - не совпадает с калькулятором/*/
                  if (Begin->GetFunction() == "arcch")
                     {
                        if (!(Begin->Next->GetNumber() >= 1))
                           {
                              Application->MessageBoxA("Значение аргумента должно быть больше или равно 1",
                                                       "Вычисление гиперболического арккосинуса", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                              if (_Deg)
                                 {
                                    Begin->SetNumber(RadToDeg(ArcCosh(Begin->Next->GetNumber())));
                                 }
                              else
                              if (_Grad)
                                 {
                                    Begin->SetNumber(RadToGrad(ArcCosh(Begin->Next->GetNumber())));
                                 }
                              else
                                 {
                                    Begin->SetNumber(ArcCosh(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  else
                  /*/Арксинус гиперболической функции - не совпадает/*/
                  if (Begin->GetFunction() == "arcsh")
                     {
                        if (_Deg)
                                 {
                                    Begin->SetNumber(RadToDeg(ArcSinh(Begin->Next->GetNumber())));
                                 }
                              else
                              if (_Grad)
                                 {
                                    Begin->SetNumber(RadToGrad(ArcSinh(Begin->Next->GetNumber())));
                                 }
                              else
                                 {
                                    Begin->SetNumber(ArcSinh(Begin->Next->GetNumber()));
                                 }
                     }
                  else
                  /*/Арктангенс гиперболической функции - не совпадает с калькулятором/*/
                  if (Begin->GetFunction() == "arcth")
                     {
                        if ((Begin->Next->GetNumber() >= 1) || (Begin->Next->GetNumber() <= -1))
                              {
                                 Application->MessageBoxA("Значение аргумента должно лежать в интервале (-1;1)",
                                                          "Вычисление арксинуса", MB_OK);
                                 _ErrAns = true;
                                 break;
                              }
                        else
                           {
                              if (_Deg)
                                 {
                                    Begin->SetNumber(RadToDeg(ArcTanh(Begin->Next->GetNumber())));
                                 }
                              else
                              if (_Grad)
                                 {
                                    Begin->SetNumber(RadToGrad(ArcTanh(Begin->Next->GetNumber())));
                                 }
                              else
                                 {
                                    Begin->SetNumber(ArcTanh(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  else
                  /*/Арккотангенс гиперболической функции/*/
                  if (Begin->GetFunction() == "arccth")
                     {
                        if ((Begin->Next->GetNumber() >= -1) && (Begin->Next->GetNumber() <= 1))
                           {
                              Application->MessageBoxA("Аргумент функции должен лежать за пределами интервала (-1;1)",
                                                       "Вычисление гиперболического арккотангенса", MB_OK);
                              _ErrAns = true;
                              break;
                           }
                        else
                           {
                        if (_Deg)
                                 {
                                    Begin->SetNumber(RadToDeg(ArcCot(Begin->Next->GetNumber())));
                                 }
                              else
                              if (_Grad)
                                 {
                                    Begin->SetNumber(RadToGrad(ArcCot(Begin->Next->GetNumber())));
                                 }
                              else
                                 {
                                    Begin->SetNumber(ArcCot(Begin->Next->GetNumber()));
                                 }
                           }
                     }
                  Del_El1 = Begin->Next;
                  _List->Delete(&Del_El1);
                  goto EndOfWhile;
               }
            else
               {
                  Begin = Begin->Next;
               }
           }
/*/-----------------------------------------------------------------------/*/
            /*/Подсчёт факториала или возведения в степень/*/
/*/-----------------------------------------------------------------------/*/
         Begin = Memory;
         while (Begin != End->Next)
            {
               if (
                     (
                        ((Begin->Prev != NULL) && (Begin->Next != NULL))
                        &&
                        ((Begin->GetID() == Func) && (Begin->GetFunction() == '^'))
                        &&
                        (
                           ((Begin->Prev->GetID() == Num) || (Begin->Prev->GetID() == Var))
                           &&
                           ((Begin->Next->GetID() == Num) || (Begin->Next->GetID() == Var))
                        )
                     )
                  ||
                     (
                        (Begin->Prev != NULL)
                        &&
                        ((Begin->GetID() == Func) && (Begin->GetFunction() == '!'))
                        &&
                        ((Begin->Prev->GetID() == Num) || (Begin->Prev->GetID() == Var))
                     )
                  )
                  {
                     if (Begin->GetFunction() == '^')
                        {
                           if ((Begin->Prev->GetNumber() < 0) && ((Drobnoe(Begin->Next->GetNumber()))))
                              {
                                 Application->MessageBoxA("Разрешена работа только с действительними числами  ",
                                                          "Возведение в степень", MB_OK);
                                 _ErrAns = true;
                                 goto EndOfWhile;
                              }
                           Del_El1 = Begin;
                           Del_El2 = Begin->Next;
                           Begin->Prev->SetNumber(Power(Begin->Prev->GetNumber(), Begin->Next->GetNumber()));
                           _List->Delete(&Del_El1);
                           _List->Delete(&Del_El2);
                           goto EndOfWhile;
                        }
                     if (Begin->GetFunction() == '!')
                        {
                           Del_El1 = Begin;
                           Help = Factorial(Begin->Prev->GetNumber(), _ErrAns);
                           if (!_ErrAns)
                              {
                                 Begin->Prev->SetNumber(Help);
                                 _List->Delete(&Del_El1);
                                 goto EndOfWhile;
                              }
                           else
                              {
                                 goto EndOfWhile;
                              }
                        }
                  }
               else
               {
                  Begin = Begin->Next;
               }
            }
/*/------------------------------------------------------------------------/*/
            /*/Подсчёт умножения / деления/*/
/*/------------------------------------------------------------------------/*/
         Begin = Memory;
         while (Begin != End->Next)
            {
               if (
                     ((Begin->Prev != NULL) && (Begin->Next != NULL))
                     &&
                     (
                        (Begin->GetID() == Op)
                        &&
                        ((Begin->GetOperation() == '*') || (Begin->GetOperation() == '/'))
                     )
                     &&
                     (
                        ((Begin->Prev->GetID() == Num) || (Begin->Prev->GetID() ==  Var))
                        &&
                        ((Begin->Next->GetID() == Num) || (Begin->Next->GetID() == Var))
                     )
                  )
                  {
                     if (Begin->GetOperation() == '*')
                        {
                           Del_El1 = Begin;
                           Del_El2 = Begin->Next;
                           Begin->Prev->SetNumber(Begin->Prev->GetNumber() * Begin->Next->GetNumber());
                           _List->Delete(&Del_El1);
                           _List->Delete(&Del_El2);
                           goto EndOfWhile;
                        }
                     if (Begin->GetOperation() == '/')
                        {
                           Del_El1 = Begin;
                           Del_El2 = Begin->Next;
                           if (Begin->Next->GetNumber() == 0)
                              {
                                 Application->MessageBoxA("      Деление на ноль запрещено!!!",
                                                          "Ошибка в процессе вычисления", MB_OK);
                                 _ErrAns = true;
                                 goto EndOfWhile;
                              }
                           else
                              {
                                 Begin->Prev->SetNumber(Begin->Prev->GetNumber() / Begin->Next->GetNumber());
                                 _List->Delete(&Del_El1);
                                 _List->Delete(&Del_El2);
                                 goto EndOfWhile;
                              }
                        }
                  }
               else
                  {
                     Begin = Begin->Next;
                  }
            }
/*/------------------------------------------------------------------------/*/
               /*/Подсчёт суммы двух чисел/*/
/*/------------------------------------------------------------------------/*/
            Begin = Memory;
            while (Begin != End->Next)
               {
                  if (  ((Begin->Prev != NULL) && (Begin->Next != NULL))
                        &&
                        ((Begin->GetID() == Op) && (Begin->GetOperation() == '+'))
                        &&
                        (
                           ((Begin->Prev->GetID() == Num) || (Begin->Prev->GetID() == Var))
                           &&
                           ((Begin->Next->GetID() == Num) || (Begin->Next->GetID() == Var))
                        )
                     )
                     {
                        Del_El1 = Begin;
                        Del_El2 = Begin->Next;
                        Begin->Prev->SetNumber(Begin->Prev->GetNumber() + Begin->Next->GetNumber());
                        _List->Delete(&Del_El1);
                        _List->Delete(&Del_El2);
                        goto EndOfWhile;
                     }
                  else
                     {
                        Begin = Begin->Next;
                     }
               }
/*/------------------------------------------------------------------------/*/
            EndOfWhile:
         }  /*/конец цикла/*/
/*/<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>/*/
   if (!_ErrAns)
         {
            _Answer = _List->GetLeft()->GetNumber();
         }
   } /*/конец/*/
/*/-----------------------------------------------------------------------/*/
bool Drobnoe(LDouble init)
   {
      bool Yes = false;
      AnsiString Str = FloatToStr(init);
      for (int i = 1; i <= Str.Length(); i++)
         {
            if (Str[i] == ',')
               {
                  Yes = true;
                  break;
               }
         }
      return (Yes);
   }
/*/-----------------------------------------------------------------------/*/
/*/Подсчёт факториала/*/
LDouble Factorial(LDouble Numb, bool &_Err)
   {
      if (Numb < 0)
         {
            Application->MessageBoxA("Факториал не существует для отрицательного числа!!!",
                                     "Вычисление факториала", MB_OK);
            _Err = true;
            return 0;
         }
      else
      if (Drobnoe(Numb))
         {
            Application->MessageBoxA("Факториал не существует для вещественного числа!!!",
                                     "Вычисление факториала", MB_OK);
            _Err = true;
            return 0;
         }
      else
      if (Numb == 0)
         {
            Numb = 1;
            return 1;
         }
      else
         {
            int NumRet = 1;
            for (int i = 1; i < Numb; i++)
               {
                  NumRet = NumRet * (i+1);
               }
            Numb = NumRet;
            return (Numb);
         }
   }
/*/-----------------------------------------------------------------------/*/
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
   bool Deg = false, Grad = false;
   if (Edit1->Text == "")
      {
         Application->MessageBoxA("            Заполните строку!",
                                  "Конроль вводимых данных", MB_OK);
         return;
      }
   Edit5->Text = "";
   Interpretator *Calculator = new Interpretator(Edit1->Text);
if (!Calculator->GetErr())
   {
      LDouble Answer;
      bool ErrAns = false;
 /*/-----------------------------------------------------------------------/*/
   /*/Работа над списком/*/
   if ((Calculator->Get_X()) || (Calculator->Get_Y()) || (Calculator->Get_Z()))
      {
         Calculator->SetVariable(Edit2->Text, Edit3->Text, Edit4->Text);
      }
   if (!Calculator->GetErr())
      {
         CtrlMenus(&Calculator);
         if (RadioButton1->Checked)
            {
               Deg = true;
            }
         else
         if (RadioButton3->Checked)
            {
               Grad = true;
            }
         Result(Calculator, ErrAns, Answer, Deg, Grad);
         if (!ErrAns)
            {
               Edit5->Text = FloatToStr(Answer);
            }
         else
            {
               Edit5->Text = "Ошибка в процессе вычисления";
            }
      }
/*/-----------------------------------------------------------------------/*/
   }
   delete Calculator;
}
/*/-----------------------------------------------------------------------/*/
bool CtrlNum(AnsiString HelpStr)
   {
      if (HelpStr.Length() == 0)
         {
            return (true);
         }
      else
      if ( (HelpStr.Length() != 1) && (HelpStr[1] == '0') && (HelpStr[2] != ','))
         {
               return (true);
         }
      else
         if  ((HelpStr[1] == ',') || (HelpStr[HelpStr.Length()] == ','))
               {
                  return (true);
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
                              return (true);
                           }
                  }
         }
      for (int i = 1; i <= HelpStr.Length(); i++)
         {
            if ((!N.Contains(HelpStr[i])) && (HelpStr[i] != '-'))
               {
                  return (true);
               }
         }
      for (int i = 2; i <= HelpStr.Length(); i++)
         {
            if (!N.Contains(HelpStr[i]))
               {
                  return (true);
               }
         }
      return (false);
   }
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit5KeyPress(TObject *Sender, char &Key)
{
   Application->MessageBoxA("Данное поле редактировать нельзя",
                            "Предупрежедение", MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
   switch (int(Key))
      {
         case 13: BitBtn1->Click();
                  break;
         case 46: Key = ',';
                  break;
         case 3:  break;
         case 22: break;
         case 44: break;
         case 24: break;
         case 8 : break;
         default: {
                     if ((!N.Contains(Key)) && (!F.Contains(Key)) &&
                         (!V.Contains(Key)) && (!O.Contains(Key)) &&
                         (!B.Contains(Key)) && (!C.Contains(Key)))
                        {
                           Application->MessageBoxA("         Недопустимые символы",
                                                    "Контроль вводимых данных", MB_OK);
                           Key = char(0);
                        }
                        break;
                  }
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2KeyPress(TObject *Sender, char &Key)
{
 switch (int(Key))
      {
         case 46: Key = ',';
                  break;
         case 3:  break;
         case 44: break;
         case 45: break;
         case 22: break;
         case 24: break;
         case 8 : break;
         default: {
                     if (!N.Contains(Key))
                        {
                           Application->MessageBoxA("         Недопустимые символы",
                                                    "Контроль вводимых данных", MB_OK);
                           Key = char(0);
                        }
                        break;
                  }
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
   Form1->Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
   bool Error = false, Deg = false, Grad = false;
   LDouble a, b, c, fa, fb, fc, eps;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid1);
   Edit11->Clear();
/*/----------------------/*/
   if (Edit10->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Функция>>",
                                  "Нелинейные уравления", MB_OK);
         return;
      }
    if ((Edit6->Text == "") || (Edit7->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала поиска",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit6->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа а",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit7->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (StrToFloat(Edit6->Text) >= StrToFloat(Edit7->Text))
      {
         Application->MessageBoxA("Значение А должно быть < B",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (Edit8->Text == "")
      {
         Application->MessageBoxA("       Заполните поле eps",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit8->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа eps",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (StrToFloat(Edit8->Text) <= 0)
      {
         Application->MessageBoxA("Точность должна быть больше нуля",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (RadioButton4->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton6->Checked)
      {
         Grad = true;
      }
    String = Edit10->Text;
    eps = Eps(Edit8->Text);
    Edit9->Text = FloatToStr(eps);
    a = StrToFloat(Edit6->Text);
    b = StrToFloat(Edit7->Text);
    while ((Modul(b-a) > eps) && (!Error))
      {
         c = (a + b) / 2;
         AnsFun(String, Error, a, fa, Deg, Grad);
            if (Error)
               {
                  break;
               }
             if (fa == 0)
               {
                  Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
                  PrintBissekcy(StringGrid1, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), "",
                        FloatToStr(c), "");
                  Edit11->Text = FloatToStr(a);
                  goto EndOfProcedure;
               }
         AnsFun(String, Error, b, fb, Deg, Grad);
            if (Error)
               {
                  break;
               }
             if (fb == 0)
               {
                  Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
                  PrintBissekcy(StringGrid1, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                        FloatToStr(c), "");
                  Edit11->Text = FloatToStr(fb);
                  goto EndOfProcedure;
               }
         if (
               ((fa < 0) && (fb < 0))
            ||
               ((fa > 0) && (fb > 0))
            )
            {
               Application->MessageBoxA("На данном интервале ноль отсутствует",
                                        "Внимание", MB_OK);
               Edit11->Text = "Ошибка - ноль отсутствует";
               Error = true;
               break;
            }
         AnsFun(String, Error, c, fc, Deg, Grad);
            if (Error)
               {
                  break;
               }
          if (fc == 0)
            {
               Application->MessageBoxA("Приближения закончены, ноль найден",
                                        "Нелинейные уравнения", MB_OK);
               PrintBissekcy(StringGrid1, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                        FloatToStr(c), FloatToStr(fc));
               Edit11->Text = FloatToStr(fc);
               goto EndOfProcedure;
            }
          PrintBissekcy(StringGrid1, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                        FloatToStr(c), FloatToStr(fc));
          Index++;
          if (((fa < 0) && (fc < 0)) || ((fa > 0) && (fc > 0)))
            {
               a = c;
               fa = fc;
            }
          else
          if (((fb < 0) && (fc < 0)) || ((fb > 0) && (fc > 0)))
            {
               b = c;
               fb = fc;
            }
      }
      if (!Error)
         {
            PrintBissekcy(StringGrid1, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb), "", "");
            Edit11->Text = FloatToStr((a + b) / 2);
            Edit11->Text = Edit11->Text + " +- ";
            Edit11->Text = Edit11->Text + FloatToStr((b - a) / 2);
         }
   EndOfProcedure:
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit9KeyPress(TObject *Sender, char &Key)
{
   Application->MessageBoxA("Редактирование данного поля запрещено",
                            "Предупреждение", MB_OK);
}
//---------------------------------------------------------------------------
/*/Функция определения Eps/*/
LDouble Eps(AnsiString _Eps)
   {
      AnsiString Help = "";
      bool Was = false;
      for (int i = 1; i <= _Eps.Length(); i++)
         {
            if (_Eps[i] == ',')
               {
                  Help = Help + _Eps[i];
                  Was = true;
               }
            else
            if ((i+1 <= _Eps.Length()) && (!Was) && (_Eps[i+1] == ',') || (Was))
               {
                  Help = Help + '0';
               }
         }
      if (Was)
         {
            Help = Help + '5';
         }
      else
         {
            Help = "0,5";
         }
      return (StrToFloat(Help));
   }
/*/-----------------------------------------------------------------------/*/
/*/Очистка компонента StringGrid/*/
void ClearStrGrd(TStringGrid *Table)
   {
      for (int i = 1; i <= Table->RowCount; i++)
         for (int j = 0; j <= Table->ColCount; j++)
            {
               Table->Cells[j][i] = "";
            }
     Table->RowCount = 2;
   }
/*/-----------------------------------------------------------------------/*/
/*/Функция возвращает модуль числа, положительное его значение/*/
LDouble Modul(LDouble _Help)
   {
      if (_Help >= 0)
         {
            return (_Help);
         }
      else
         {
            return (_Help * -1);
         }
   }
/*/-----------------------------------------------------------------------/*/
void AnsFun(AnsiString _Str, bool &_Error, LDouble _X, LDouble &_FX, bool _Dg, bool _Grd)
   {
      Interpretator *Class = new Interpretator(_Str);
      if (Class->GetErr())
         {
            Application->MessageBoxA("     Поиск остановлен", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      if (!Class->Get_X())
         {
            Application->MessageBoxA("     Функция постоянна", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      if ((Class->Get_Y()) || (Class->Get_Z()))
         {
            Application->MessageBoxA("     Функция должна быть одной переменной", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      Class->SetVariable(FloatToStr(_X), "", "");
      CtrlMenus(&Class);
      Result(Class, _Error, _FX, _Dg, _Grd);
      Exit:
      delete Class;
   }
/*/-----------------------------------------------------------------------/*/
/*/Вывод на экран приближений - метод биссекции/*/
void PrintBissekcy(TStringGrid *Table, int _i, AnsiString _a, AnsiString _fa, AnsiString _b, AnsiString _fb,
                                               AnsiString _c, AnsiString _fc)
   {
      Table->Cells[0][_i] = _a;
      Table->Cells[1][_i] = _fa;
      Table->Cells[2][_i] = _b;
      Table->Cells[3][_i] = _fb;
      Table->Cells[4][_i] = _c;
      Table->Cells[5][_i] = _fc;
      Table->RowCount = Table->RowCount + 1;
   }
/*/-----------------------------------------------------------------------/*/
/*/Добавление одной строки к компоненту StringGrid/*/
void StrGrdRow(TStringGrid *Table)
   {
      Table->RowCount = Table->RowCount + 1;
   }
/*/-----------------------------------------------------------------------/*/
void __fastcall TForm1::Edit10KeyPress(TObject *Sender, char &Key)
{
switch (int(Key))
      {
         case 46: Key = ',';
                  break;
         case 3:  break;
         case 44: break;
         case 45: break;
         case 22: break;
         case 24: break;
         case 88: break;
         case 120: break;
         case 8 : break;
         default: {
                     if ((!N.Contains(Key)) && (!F.Contains(Key)) && (!O.Contains(Key)) &&
                         (!B.Contains(Key)) && (!C.Contains(Key)))
                        {
                           Application->MessageBoxA("         Недопустимые символы",
                                                    "Контроль вводимых данных", MB_OK);
                           Key = char(0);
                        }
                        break;
                  }
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false, ChangeA = false, ChangeB = false;
   LDouble a, b, c, fa, fb, fc, eps, Da, Db, Change;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid1);
   Edit15->Clear();
/*/----------------------/*/
   if (Edit12->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Функция>>",
                                  "Нелинейные уравления", MB_OK);
         return;
      }
    if ((Edit16->Text == "") || (Edit17->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала поиска",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit16->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа а",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit17->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (StrToFloat(Edit16->Text) >= StrToFloat(Edit17->Text))
      {
         Application->MessageBoxA("Значение А должно быть < B",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (Edit13->Text == "")
      {
         Application->MessageBoxA("       Заполните поле eps",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit13->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа eps",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (StrToFloat(Edit13->Text) <= 0)
      {
         Application->MessageBoxA("Точность должна быть больше нуля",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (RadioButton7->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton9->Checked)
      {
         Grad = true;
      }
    String = Edit12->Text;
    eps = Eps(Edit13->Text);
    Edit14->Text = FloatToStr(eps);
    a = StrToFloat(Edit16->Text);
    b = StrToFloat(Edit17->Text);
    AnsFun(String, Error, a, fa, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (fa == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), "",
                          "", "");
            Edit15->Text = FloatToStr(a);
            goto EndOfProcedure;
         }
    AnsFun(String, Error, b, fb, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (fb == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                          "", "");
            Edit15->Text = FloatToStr(b);
            goto EndOfProcedure;
         }
    c = a - ( (b - a) / (fb - fa) ) * fa;
    AnsFun(String, Error, c, fc, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (fc == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                          FloatToStr(c), FloatToStr(fc));
            Edit15->Text = FloatToStr(c);
            goto EndOfProcedure;
         }
    PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                  FloatToStr(c), FloatToStr(fc));
    Index++;
          if (((fa < 0) && (fc < 0)) || ((fa > 0) && (fc > 0)))
            {
               Da = a;
               ChangeA = true;
               a = c;
               fa = fc;
            }
          else
          if (((fb < 0) && (fc < 0)) || ((fb > 0) && (fc > 0)))
            {
               Db = b;
               ChangeB = true;
               b = c;
               fb = fc;
            }
          if (ChangeA)
            {
               Change = Modul(Da - a);
            }
          if (ChangeB)
            {
               Change = Modul(Db - b);
            }
    while (Change > eps)
      {
      AnsFun(String, Error, a, fa, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (fa == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), "",
                          "", "");
            Edit15->Text = FloatToStr(a);
            goto EndOfProcedure;
         }
    AnsFun(String, Error, b, fb, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (fb == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                          "", "");
            Edit15->Text = FloatToStr(b);
            goto EndOfProcedure;
         }
    c = a - ( (b - a) / (fb - fa) ) * fa;
    AnsFun(String, Error, c, fc, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (fc == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                          FloatToStr(c), FloatToStr(fc));
            Edit15->Text = FloatToStr(c);
            goto EndOfProcedure;
         }
    PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                  FloatToStr(c), FloatToStr(fc));
    Index++;
          if (((fa < 0) && (fc < 0)) || ((fa > 0) && (fc > 0)))
            {
               Da = a;
               ChangeA = true;
               a = c;
               fa = fc;
            }
          else
          if (((fb < 0) && (fc < 0)) || ((fb > 0) && (fc > 0)))
            {
               Db = b;
               ChangeB = true;
               b = c;
               fb = fc;
            }
          if (ChangeA)
            {
               Change = Modul(Da - a);
            }
          if (ChangeB)
            {
               Change = Modul(Db - b);
            }
      }
    if (!Error)
    {
    PrintBissekcy(StringGrid2, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                  "", "");
    if (ChangeA)
      {
         Edit15->Text = FloatToStr(a) + " +- " + FloatToStr(Change);
      }
    if (ChangeB)
      {
          Edit15->Text = FloatToStr(b) + " +- " + FloatToStr(Change);
      }
    }
    EndOfProcedure:
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn7Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false;
   LDouble x, dx, y, dy, eps;
   int Index = 1;
   AnsiString String, String1;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid3);
   Edit24->Clear();
/*/----------------------/*/
   if (Edit18->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Функция>>",
                                  "Нелинейные уравления", MB_OK);
         return;
      }
   if (Edit19->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Первая производная функции>>",
                                  "Нелинейные уравления", MB_OK);
         return;
      }
    if (Edit22->Text == "")
      {
         Application->MessageBoxA("Заполните поле начальное значение X",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit22->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа X",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (Edit20->Text == "")
      {
         Application->MessageBoxA("       Заполните поле eps",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    Error = CtrlNum(Edit20->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа eps",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (StrToFloat(Edit20->Text) <= 0)
      {
         Application->MessageBoxA("Точность должна быть больше нуля",
                                  "Нелинейные уравнения", MB_OK);
         return;
      }
    if (RadioButton10->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton12->Checked)
      {
         Grad = true;
      }
    String = Edit18->Text;
    String1 = Edit19->Text;
    eps = Eps(Edit20->Text);
    Edit21->Text = FloatToStr(eps);
    x = StrToFloat(Edit22->Text);
    AnsFun(String, Error, x, y, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (y == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintNew(StringGrid3, Index, FloatToStr(x), FloatToStr(y), "", "");
            Edit24->Text = FloatToStr(x);
            goto EndOfProcedure;
         }
    AnsDFun(String1, Error, x, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
   dx = -1 * (y / dy);
   PrintNew(StringGrid3, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(dx));
   Index++;
   while (Modul(dx) > eps)
      {
      x = x + dx;
      AnsFun(String, Error, x, y, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if (y == 0)
         {
            Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Нелинейные уравнения", MB_OK);
            PrintNew(StringGrid3, Index, FloatToStr(x), FloatToStr(y), "", "");
            Edit24->Text = FloatToStr(x);
            goto EndOfProcedure;
         }
      AnsDFun(String1, Error, x, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
   dx = -1 * (y / dy);
   PrintNew(StringGrid3, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(dx));
   Index++;
      }
   if (!Error)
      {
         x = x + dx;
         PrintNew(StringGrid3, Index, FloatToStr(x), "", "", "");
         Edit24->Text = FloatToStr(x) + " +- " + FloatToStr(Modul(dx));
      }
   EndOfProcedure:
}
//---------------------------------------------------------------------------
void PrintNew(TStringGrid *Table, int _i, AnsiString _x, AnsiString _y, AnsiString _dy, AnsiString _dx)
   {
      Table->Cells[0][_i] = _x;
      Table->Cells[1][_i] = _y;
      Table->Cells[2][_i] = _dy;
      Table->Cells[3][_i] = _dx;
      Table->RowCount++;
   }
/*/------------------------------------------------------------------------/*/
/*/Подсчёт значения производной/*/
void AnsDFun(AnsiString _Str, bool &_Error, LDouble _X, LDouble &_FX, bool _Dg, bool _Grd)
   {
      Interpretator *Class = new Interpretator(_Str);
      if (Class->GetErr())
         {
            Application->MessageBoxA("     Поиск остановлен", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      if ((Class->Get_Y()) || (Class->Get_Z()))
         {
            Application->MessageBoxA("     Функция должна быть одной переменной", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      Class->SetVariable(FloatToStr(_X), "", "");
      CtrlMenus(&Class);
      Result(Class, _Error, _FX, _Dg, _Grd);
      Exit:
      delete Class;
   }
/*/------------------------------------------------------------------------/*/

void __fastcall TForm1::BitBtn9Click(TObject *Sender)
{
   bool Error = false, Deg = false, Grad = false;
   LDouble a, b, c, fa, fb, fc, eps;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid4);
   Edit29->Clear();
/*/----------------------/*/
   if (Edit23->Text == "")
      {
         Application->MessageBoxA("Заполните поле Первая производная функции",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if ((Edit25->Text == "") || (Edit26->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала поиска",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit25->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа а",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit26->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (StrToFloat(Edit25->Text) >= StrToFloat(Edit26->Text))
      {
         Application->MessageBoxA("Значение А должно быть < B",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (Edit27->Text == "")
      {
         Application->MessageBoxA("       Заполните поле eps",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit27->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа eps",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (StrToFloat(Edit27->Text) <= 0)
      {
         Application->MessageBoxA("Точность должна быть больше нуля",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (RadioButton13->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton15->Checked)
      {
         Grad = true;
      }
    String = Edit23->Text;
    eps = Eps(Edit27->Text);
    Edit28->Text = FloatToStr(eps);
    a = StrToFloat(Edit25->Text);
    b = StrToFloat(Edit26->Text);
    while ((Modul(b-a) > eps) && (!Error))
      {
         c = (a + b) / 2;
         AnsFun(String, Error, a, fa, Deg, Grad);
            if (Error)
               {
                  break;
               }
             if (fa == 0)
               {
                  Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Одномерная оптимизация", MB_OK);
                  PrintBissekcy(StringGrid4, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), "",
                        FloatToStr(c), "");
                  Edit11->Text = FloatToStr(a);
                  goto EndOfProcedure;
               }
         AnsFun(String, Error, b, fb, Deg, Grad);
            if (Error)
               {
                  break;
               }
             if (fb == 0)
               {
                  Application->MessageBoxA("Приближения закончены, ноль найден",
                                           "Одномерная оптимизация", MB_OK);
                  PrintBissekcy(StringGrid4, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                        FloatToStr(c), "");
                  Edit11->Text = FloatToStr(fb);
                  goto EndOfProcedure;
               }
         if (
               ((fa < 0) && (fb < 0))
            ||
               ((fa > 0) && (fb > 0))
            )
            {
               Application->MessageBoxA("На данном интервале ноль отсутствует",
                                        "Внимание", MB_OK);
               Edit11->Text = "Ошибка - ноль отсутствует";
               Error = true;
               break;
            }
         AnsFun(String, Error, c, fc, Deg, Grad);
            if (Error)
               {
                  break;
               }
          if (fc == 0)
            {
               Application->MessageBoxA("Приближения закончены, ноль найден",
                                        "Одномерная оптимизация", MB_OK);
               PrintBissekcy(StringGrid4, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                        FloatToStr(c), FloatToStr(fc));
               Edit11->Text = FloatToStr(fc);
               goto EndOfProcedure;
            }
          PrintBissekcy(StringGrid4, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb),
                        FloatToStr(c), FloatToStr(fc));
          Index++;
          if (((fa < 0) && (fc < 0)) || ((fa > 0) && (fc > 0)))
            {
               a = c;
               fa = fc;
            }
          else
          if (((fb < 0) && (fc < 0)) || ((fb > 0) && (fc > 0)))
            {
               b = c;
               fb = fc;
            }
      }
      if (!Error)
         {
            PrintBissekcy(StringGrid4, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(b), FloatToStr(fb), "", "");
            Edit29->Text = FloatToStr((a + b) / 2);
            Edit29->Text = Edit29->Text + " +- ";
            Edit29->Text = Edit29->Text + FloatToStr((b - a) / 2);
         }
   EndOfProcedure:
}
//---------------------------------------------------------------------------
/*/Метод золотого сечения - Вывод на экран/*/
void PrintGold(TStringGrid *Table, int _i, AnsiString _a, AnsiString _fa, AnsiString _x1, AnsiString _fx1, AnsiString _x2,
                     AnsiString _fx2, AnsiString _b, AnsiString _fb, AnsiString _Lo, AnsiString _L1, AnsiString _L2)
   {
      Table->Cells[0][_i] = _a;
      Table->Cells[1][_i] = _fa;
      Table->Cells[2][_i] = _x1;
      Table->Cells[3][_i] = _fx1;
      Table->Cells[4][_i] = _x2;
      Table->Cells[5][_i] = _fx2;
      Table->Cells[6][_i] = _b;
      Table->Cells[7][_i] = _fb;
      Table->Cells[8][_i] = _Lo;
      Table->Cells[9][_i] = _L1;
      Table->Cells[10][_i] = _L2;
      Table->RowCount++;
   }
/*/-----------------------------------------------------------------------/*/


void __fastcall TForm1::BitBtn11Click(TObject *Sender)
{
   bool Error = false, Deg = false, Grad = false, ChangeX1 = false, ChangeX2 = false, First = false, Second = false;
   LDouble a, b, fa, fb, eps, x1, x2, fx1, fx2, L0, L1, L2;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid5);
   Edit34->Clear();
/*/----------------------/*/
if (Edit35->Text == "")
      {
         Application->MessageBoxA("    Заполните поле Функция",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if ((Edit30->Text == "") || (Edit31->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала поиска",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit30->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа а",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit31->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (StrToFloat(Edit30->Text) >= StrToFloat(Edit31->Text))
      {
         Application->MessageBoxA("Значение А должно быть < B",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (Edit32->Text == "")
      {
         Application->MessageBoxA("       Заполните поле eps",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit32->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа eps",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (StrToFloat(Edit32->Text) <= 0)
      {
         Application->MessageBoxA("Точность должна быть больше нуля",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (RadioButton16->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton18->Checked)
      {
         Grad = true;
      }
    String = Edit35->Text;
    eps = Eps(Edit32->Text);
    Edit33->Text = FloatToStr(eps);
    a = StrToFloat(Edit30->Text);
    b = StrToFloat(Edit31->Text);
    L0 = Modul(b - a);
    L1 = L0 * 0.618;
    L2 = L0 - L1;
    x1 = b - L1;
    x2 = a + L1;
    while ((Modul(b - a) > eps) && (!Error))
      {
         First = false;
         Second = false;
         AnsFun(String, Error, a, fa, Deg, Grad);
            if (Error)
               {
                  break;
               }
         AnsFun(String, Error, x1, fx1, Deg, Grad);
            if (Error)
               {
                  break;
               }
         AnsFun(String, Error, x2, fx2, Deg, Grad);
            if (Error)
               {
                  break;
               }
         AnsFun(String, Error, b, fb, Deg, Grad);
            if (Error)
               {
                  break;
               }
PrintGold(StringGrid5, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(x1),
         FloatToStr(fx1), FloatToStr(x2), FloatToStr(fx2), FloatToStr(b),
         FloatToStr(fb), FloatToStr(L0), FloatToStr(L1), FloatToStr(L2));
         if (fx1 < fx2)
            {
               b = x2;
               fb = fx2;
               x2 = x1;
               fx2 = fx1;
               ChangeX1 = true;
               First = true;
            }
         else
         if (fx1 > fx2)
            {
               a = x1;
               fa = fx1;
               x1 = x2;
               fx1 = fx2;
               ChangeX2 = true;
               Second = true;
            }
         Index++;
      L0 = Modul(b - a);
      L1 = L0 * 0.618;
      L2 = L0 - L1;
      if (ChangeX1)
         {
            x1 = b - L1;
            ChangeX1 = false;
         }
      else
      if (ChangeX2)
         {
            x2 = a + L1;
            ChangeX2 = false;
         }
      }
    if (!Error)
      {
         AnsFun(String, Error, x1, fx1, Deg, Grad);
            if (Error)
               {
                  goto EndOfProcedure;
               }
         AnsFun(String, Error, x2, fx2, Deg, Grad);
            if (Error)
               {
                  goto EndOfProcedure;
               }
PrintGold(StringGrid5, Index, FloatToStr(a), FloatToStr(fa), FloatToStr(x1),
         FloatToStr(fx1), FloatToStr(x2), FloatToStr(fx2), FloatToStr(b),
         FloatToStr(fb), FloatToStr(L0), FloatToStr(L1), FloatToStr(L2));
         if (fx1 < fx2)
            {
               Edit34->Text = FloatToStr(x1) + " +- " + FloatToStr(Modul(b - a));
            }
         else
         if (fx1 > fx2)
            {
               Edit34->Text = FloatToStr(x2) + " +- " + FloatToStr(Modul(b - a));
            }
      }
    EndOfProcedure:
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn13Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false;
   LDouble x, dx, y, dy, dy2, eps;
   int Index = 1;
   AnsiString String, String1, String2;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid6);
   Edit41->Clear();
/*/----------------------/*/
   if (Edit36->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Функция>>",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
   if (Edit37->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Первая производная функции>>",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
   if (Edit38->Text == "")
      {
         Application->MessageBoxA("Заполните поле <<Вторая производная функции>>",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (Edit42->Text == "")
      {
         Application->MessageBoxA("Заполните поле начальное значение X",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit42->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа X",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (Edit39->Text == "")
      {
         Application->MessageBoxA("       Заполните поле eps",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    Error = CtrlNum(Edit39->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа eps",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (StrToFloat(Edit39->Text) <= 0)
      {
         Application->MessageBoxA("Точность должна быть больше нуля",
                                  "Одномерная оптимизация", MB_OK);
         return;
      }
    if (RadioButton19->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton21->Checked)
      {
         Grad = true;
      }
    String = Edit36->Text;
    String1 = Edit37->Text;
    String2 = Edit38->Text;
    eps = Eps(Edit39->Text);
    Edit40->Text = FloatToStr(eps);
    x = StrToFloat(Edit42->Text);
    AnsFun(String, Error, x, y, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
    AnsDFun(String1, Error, x, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
    AnsDFun(String2, Error, x, dy2, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
   if ((dy == 0) && (dy2 == 0))
         {
            Application->MessageBoxA("Приближения закончены, Найдёна точка перегиба",
                                           "Одномерная оптимизация", MB_OK);
            PrintOO(StringGrid6, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(dy2), "");
            Edit41->Text = FloatToStr(x);
            goto EndOfProcedure;
         }
   if (dy2 == 0)
      {
       Application->MessageBoxA("Вторая производная равна нулю",
                                           "Одномерная оптимизация", MB_OK);
            goto EndOfProcedure;
      }
   dx = -1 * (dy / dy2);
   PrintOO(StringGrid6, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(dy2), FloatToStr(dx));
   Index++;
   while (Modul(dx) > eps)
      {
      x = x + dx;
      AnsFun(String, Error, x, y, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      AnsFun(String1, Error, x, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      AnsDFun(String2, Error, x, dy2, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      if ((dy == 0) && (dy2 == 0))
         {
            Application->MessageBoxA("Приближения закончены, найдена точка перегиба",
                                           "Одномерная оптимизация", MB_OK);
            PrintOO(StringGrid6, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(dy2), FloatToStr(dx));
            Edit41->Text = FloatToStr(x);
            goto EndOfProcedure;
         }
   if (dy2 == 0)
      {
       Application->MessageBoxA("Вторая производная равна нулю",
                                           "Одномерная оптимизация", MB_OK);
            goto EndOfProcedure;
      }
   dx = -1 * (dy / dy2);
   PrintOO(StringGrid6, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(dy2), FloatToStr(dx));
   Index++;
      }
   if (!Error)
      {
         x = x + dx;
         PrintOO(StringGrid6, Index, FloatToStr(x), "", "", "", "");
         Edit41->Text = FloatToStr(x) + " +- " + FloatToStr(Modul(dx));
      }
   EndOfProcedure:
}
//---------------------------------------------------------------------------
void PrintOO(TStringGrid *Table, int _i, AnsiString _x, AnsiString _y, AnsiString _dy, AnsiString _dy2, AnsiString _dx)
   {
      Table->Cells[0][_i] = _x;
      Table->Cells[1][_i] = _y;
      Table->Cells[2][_i] = _dy;
      Table->Cells[3][_i] = _dy2;
      Table->Cells[4][_i] = _dx;
      Table->RowCount++;
   }
/*/-----------------------------------------------------------------------/*/

void __fastcall TForm1::Edit46KeyPress(TObject *Sender, char &Key)
{
switch (int(Key))
      {
         case 46: Key = ',';
                  break;
         case 3:  break;
         case 44: break;
         case 45: break;
         case 22: break;
         case 24: break;
         case 88: break;
         case 120: break;
         case 8 : break;
         case 89: break;
         case 121: break;
         default: {
                     if ((!N.Contains(Key)) && (!F.Contains(Key)) && (!O.Contains(Key)) &&
                         (!B.Contains(Key)) && (!C.Contains(Key)))
                        {
                           Application->MessageBoxA("         Недопустимые символы",
                                                    "Контроль вводимых данных", MB_OK);
                           Key = char(0);
                        }
                        break;
                  }
      }   
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit44Change(TObject *Sender)
{
   Edit47->Text = Edit44->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn15Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false;
   LDouble x, y, dy, h, a, b;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid7);
/*/----------------------/*/
   if ((Edit48->Text == "") || (Edit46->Text == ""))
      {
         Application->MessageBoxA("Заполните поля начальные условия",
                                  "Задача Коши", MB_OK);
         return;
      }
   Error = CtrlNum(Edit48->Text);
   if (Error)
     {
        Application->MessageBoxA("Ошибка в написании значения функции",
                                 "Задача Коши", MB_OK);
        return;
     }
   if (Edit43->Text == "")
     {
        Application->MessageBoxA("Заполните поле шаг",
                                 "Задача Коши", MB_OK);
        return;
     }
    Error = CtrlNum(Edit43->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа h",
                                  "Задача Коши", MB_OK);
         return;
      }
    if (StrToFloat(Edit43->Text) <= 0)
      {
         Application->MessageBoxA("Шаг должен быть положительный",
                                  "Задача Коши", MB_OK);
         return;
      }
    if ((Edit44->Text == "") || (Edit45->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала",
                                  "Задача Коши                     ", MB_OK);
         return;
      }
    Error = CtrlNum(Edit44->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа a",
                                  "Задача Коши", MB_OK);
         return;
      }
    Error = CtrlNum(Edit45->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Задача Коши", MB_OK);
         return;
      }
    if (StrToFloat(Edit44->Text) >= StrToFloat(Edit45->Text))
      {
         Application->MessageBoxA("Число а должно быть < b", "Задача Коши", MB_OK);
         return;
      }
    if (RadioButton22->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton24->Checked)
      {
         Grad = true;
      }
    String = Edit46->Text;
    a = StrToFloat(Edit44->Text);
    b = StrToFloat(Edit45->Text);
    h = StrToFloat(Edit43->Text);
    y = StrToFloat(Edit48->Text);
    Error = Kratnost(a, b, h);
    if (Error)
      {
         Application->MessageBoxA("Количество шагов должно быть кратно интервалу",
                                  "Задача Коши", MB_OK);
         return;
      }
   x = a;
   while (x -h < b)
      {
      AnsKoshi(String, Error, x, y, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
   PrintEiler(StringGrid7, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy));
   Index++;
   x = x + h;
   y = y + (dy * h);
      }
   EndOfProcedure:
}
//---------------------------------------------------------------------------
/*/Проверка кратности/*/
bool Kratnost(LDouble _a, LDouble _b, LDouble _h)
   {
      LDouble Help;
      Help = Modul(_b - _a);
      Help = Help / _h;
      if (Drobnoe(Help))
         {
            return (true);
         }
      else
         {
            return (false);
         }
   }
/*/-----------------------------------------------------------------------/*/
void AnsKoshi(AnsiString _Str, bool &_Error, LDouble _X, LDouble _Y, LDouble &_FX, bool _Dg, bool _Grd)
   {
      Interpretator *Class = new Interpretator(_Str);
      if (Class->GetErr())
         {
            Application->MessageBoxA("     Вычисление остановлено", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      if (!Class->Get_X())
         {
            Application->MessageBoxA("     Функция постоянна", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      if (Class->Get_Z())
         {
            Application->MessageBoxA("     Функция должна быть максимум двух переменных переменной", "Вычисление выражения", MB_OK);
            _Error = true;
            goto Exit;
         }
      if ((Class->Get_X()) && (Class->Get_Y()))
         {
           Class->SetVariable(FloatToStr(_X), FloatToStr(_Y), "");
         }
      else
      if ((Class->Get_X()) && !(Class->Get_Y()))
         {
           Class->SetVariable(FloatToStr(_X), "", "");
         }
      else
      if (!(Class->Get_X()) && (Class->Get_Y()))
         {
           Class->SetVariable("", FloatToStr(_Y), "");
         }
      CtrlMenus(&Class);
      Result(Class, _Error, _FX, _Dg, _Grd);
      Exit:
      delete Class;
   }
/*/-----------------------------------------------------------------------/*/
/*/Распечатка Метода Эйлера/*/
void PrintEiler(TStringGrid *Table, int _i, AnsiString _x, AnsiString _y, AnsiString _dy)
   {
      Table->Cells[0][_i] = _x;
      Table->Cells[1][_i] = _y;
      Table->Cells[2][_i] = _dy;
      Table->RowCount++;
   }
/*/-----------------------------------------------------------------------/*/

void __fastcall TForm1::BitBtn17Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false;
   LDouble x, y, dy, x1, y1, dy1, h, a, b;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid8);
/*/----------------------/*/
   if ((Edit52->Text == "") || (Edit54->Text == ""))
      {
         Application->MessageBoxA("Заполните поля начальные условия",
                                  "Задача Коши", MB_OK);
         return;
      }
   Error = CtrlNum(Edit54->Text);
   if (Error)
     {
        Application->MessageBoxA("Ошибка в написании значения функции",
                                 "Задача Коши", MB_OK);
        return;
     }
   if (Edit49->Text == "")
     {
        Application->MessageBoxA("Заполните поле шаг",
                                 "Задача Коши", MB_OK);
        return;
     }
    Error = CtrlNum(Edit49->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа h",
                                  "Задача Коши", MB_OK);
         return;
      }
    if (StrToFloat(Edit49->Text) <= 0)
      {
         Application->MessageBoxA("Шаг должен быть положительный",
                                  "Задача Коши", MB_OK);
         return;
      }
    if ((Edit50->Text == "") || (Edit51->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала",
                                  "Задача Коши                     ", MB_OK);
         return;
      }
    Error = CtrlNum(Edit50->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа a",
                                  "Задача Коши", MB_OK);
         return;
      }
    Error = CtrlNum(Edit51->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Задача Коши", MB_OK);
         return;
      }
    if (StrToFloat(Edit50->Text) >= StrToFloat(Edit51->Text))
      {
         Application->MessageBoxA("Число а должно быть < b", "Задача Коши", MB_OK);
         return;
      }
    if (RadioButton25->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton27->Checked)
      {
         Grad = true;
      }
    String = Edit52->Text;
    a = StrToFloat(Edit50->Text);
    b = StrToFloat(Edit51->Text);
    h = StrToFloat(Edit49->Text);
    y = StrToFloat(Edit54->Text);
    Error = Kratnost(a, b, h);
    if (Error)
      {
         Application->MessageBoxA("Количество шагов должно быть кратно интервалу",
                                  "Задача Коши", MB_OK);
         return;
      }
   x = a;
while (x - h < b)
      {
      AnsKoshi(String, Error, x, y, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      x1 = x + (h / 2);
      y1 = y + dy * (h / 2);
      AnsKoshi(String, Error, x1, y1, dy1, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
   PrintEiler(StringGrid8, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(x1), FloatToStr(y1), FloatToStr(dy1));
   Index++;
   x = x + h;
   y = y + (dy1 * h);
      }
   EndOfProcedure:
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Edit50Change(TObject *Sender)
{
   Edit53->Text = Edit50->Text;
}
/*/-----------------------------------------------------------------------/*/
/*/Распечатка Исправленного метода Эйлера/*/
void PrintEiler(TStringGrid *Table, int _i, AnsiString _x, AnsiString _y, AnsiString _dy, AnsiString _x1, AnsiString _y1, AnsiString _dy1)
   {
      Table->Cells[0][_i] = _x;
      Table->Cells[1][_i] = _y;
      Table->Cells[2][_i] = _dy;
      Table->Cells[3][_i] = _x1;
      Table->Cells[4][_i] = _y1;
      Table->Cells[5][_i] = _dy1;
      Table->RowCount++;
   }
/*/-----------------------------------------------------------------------/*/

void __fastcall TForm1::Edit56Change(TObject *Sender)
{
   Edit59->Text = Edit56->Text;   
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn19Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false;
   LDouble x, y, dy, x1, y1, dy1, x2, y2, dy2, x3, y3, dy3, h, a, b, T;
   int Index = 1;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   ClearStrGrd(StringGrid9);
/*/----------------------/*/
   if ((Edit58->Text == "") || (Edit60->Text == ""))
      {
         Application->MessageBoxA("Заполните поля начальные условия",
                                  "Задача Коши", MB_OK);
         return;
      }
   Error = CtrlNum(Edit60->Text);
   if (Error)
     {
        Application->MessageBoxA("Ошибка в написании значения функции",
                                 "Задача Коши", MB_OK);
        return;
     }
   if (Edit55->Text == "")
     {
        Application->MessageBoxA("Заполните поле шаг",
                                 "Задача Коши", MB_OK);
        return;
     }
    Error = CtrlNum(Edit55->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа h",
                                  "Задача Коши", MB_OK);
         return;
      }
    if (StrToFloat(Edit55->Text) <= 0)
      {
         Application->MessageBoxA("Шаг должен быть положительный",
                                  "Задача Коши", MB_OK);
         return;
      }
    if ((Edit56->Text == "") || (Edit57->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала",
                                  "Задача Коши                     ", MB_OK);
         return;
      }
    Error = CtrlNum(Edit56->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа a",
                                  "Задача Коши", MB_OK);
         return;
      }
    Error = CtrlNum(Edit57->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Задача Коши", MB_OK);
         return;
      }
    if (StrToFloat(Edit56->Text) >= StrToFloat(Edit57->Text))
      {
         Application->MessageBoxA("Число а должно быть < b", "Задача Коши", MB_OK);
         return;
      }
    if (RadioButton28->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton30->Checked)
      {
         Grad = true;
      }
    String = Edit58->Text;
    a = StrToFloat(Edit56->Text);
    b = StrToFloat(Edit57->Text);
    h = StrToFloat(Edit55->Text);
    y = StrToFloat(Edit60->Text);
    Error = Kratnost(a, b, h);
    if (Error)
      {
         Application->MessageBoxA("Количество шагов должно быть кратно интервалу",
                                  "Задача Коши", MB_OK);
         return;
      }
   x = a;
while (x - h < b)
      {
      AnsKoshi(String, Error, x, y, dy, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      x1 = x + (h / 2);
      y1 = y + dy * (h / 2);
      AnsKoshi(String, Error, x1, y1, dy1, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      x2 = x1;
      y2 = y + dy1 * (h / 2);
      AnsKoshi(String, Error, x2, y2, dy2, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
      x3 = x + h;
      y3 = y + dy2 * h;
      AnsKoshi(String, Error, x3, y3, dy3, Deg, Grad);
      if (Error)
         {
            goto EndOfProcedure;
         }
   T = (dy + (2 * dy1) + (2 * dy2) + dy3) / 6;
   PrintEiler(StringGrid9, Index, FloatToStr(x), FloatToStr(y), FloatToStr(dy), FloatToStr(x1), FloatToStr(y1), FloatToStr(dy1),
               FloatToStr(x2), FloatToStr(y2), FloatToStr(dy2), FloatToStr(x3), FloatToStr(y3), FloatToStr(dy3), FloatToStr(T));
   Index++;
   x = x + h;
   y = y + (T * h);
      }
   EndOfProcedure:
}
//---------------------------------------------------------------------------
void PrintEiler(TStringGrid *Table, int _i, AnsiString _x, AnsiString _y, AnsiString _dy, AnsiString _x1, AnsiString _y1, AnsiString _dy1,
AnsiString _x2, AnsiString _y2, AnsiString _dy2, AnsiString _x3, AnsiString _y3, AnsiString _dy3, AnsiString _T)
{
      Table->Cells[0][_i] = _x;
      Table->Cells[1][_i] = _y;
      Table->Cells[2][_i] = _dy;
      Table->Cells[3][_i] = _x1;
      Table->Cells[4][_i] = _y1;
      Table->Cells[5][_i] = _dy1;
      Table->Cells[6][_i] = _x2;
      Table->Cells[7][_i] = _y2;
      Table->Cells[8][_i] = _dy2;
      Table->Cells[9][_i] = _x3;
      Table->Cells[10][_i] = _y3;
      Table->Cells[11][_i] = _dy3;
      Table->Cells[12][_i] = _T;
      Table->RowCount++;
}
/*/-----------------------------------------------------------------------/*/

void __fastcall TForm1::BitBtn21Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false, First = false;
   LDouble a, b, h, HCount, Answer, Help, x;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   Edit65->Clear();
   Edit66->Clear();
/*/----------------------/*/
   if (Edit61->Text == "")
      {
         Application->MessageBoxA("    Заполните поле Функция",
                                  "Численное интегрирование", MB_OK);
         return;
      }
   if (Edit64->Text == "")
     {
        Application->MessageBoxA("          Заполните поле шаг",
                                 "Численное интегрирование", MB_OK);
        return;
     }
    Error = CtrlNum(Edit64->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа h",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if (StrToFloat(Edit64->Text) <= 0)
      {
         Application->MessageBoxA("Шаг должен быть положительный",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if ((Edit62->Text == "") || (Edit63->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    Error = CtrlNum(Edit62->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа a",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    Error = CtrlNum(Edit63->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if (StrToFloat(Edit62->Text) >= StrToFloat(Edit63->Text))
      {
         Application->MessageBoxA("Число а должно быть < b", "Численное интегрирование", MB_OK);
         return;
      }
    if (RadioButton31->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton33->Checked)
      {
         Grad = true;
      }
    String = Edit61->Text;
    a = StrToFloat(Edit62->Text);
    b = StrToFloat(Edit63->Text);
    h = StrToFloat(Edit64->Text);
    Error = Kratnost(a, b, h);
    if (Error)
      {
         Application->MessageBoxA("Количество шагов должно быть кратно интервалу",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    HCount = Modul(b - a) / h;
/*/--------------------------------------------------------------------------/*/
/*/Метод левых прямоугольников/*/
/*/--------------------------------------------------------------------------/*/
   if (RadioButton34->Checked)
      {
         x = a;
         for (int i = 0; i <= HCount - 1; i++)
            {
               AnsFun(String, Error, x, Help, Deg, Grad);
               if (Error)
                  {
                     break;
                  }
               if (!First)
                  {
                     Answer = Help * h;
                     First = true;
                  }
               else
                  {
                     Answer = Answer + ( Help * h);
                  }
               x = x + h;
            }
      }
   else
/*/--------------------------------------------------------------------------/*/
/*/Метод центральных прямоугольников/*/
/*/--------------------------------------------------------------------------/*/
   if (RadioButton35->Checked)
      {
         x = a + ( h / 2 );
         for (int i = 0; i <= HCount - 1; i++)
            {
               AnsFun(String, Error, x, Help, Deg, Grad);
               if (Error)
                  {
                     break;
                  }
               if (!First)
                  {
                     Answer = Help * h;
                     First = true;
                  }
               else
                  {
                     Answer = Answer + ( Help * h);
                  }
               x = x + h;
            }
      }
   else
/*/--------------------------------------------------------------------------/*/
/*/Метод правых прямоугольников/*/
/*/--------------------------------------------------------------------------/*/
   if (RadioButton36->Checked)
      {
         x = a + h;
         for (int i = 0; i <= HCount - 1; i++)
            {
               AnsFun(String, Error, x, Help, Deg, Grad);
               if (Error)
                  {
                     break;
                  }
               if (!First)
                  {
                     Answer = Help * h;
                     First = true;
                  }
               else
                  {
                     Answer = Answer + ( Help * h);
                  }
               x = x + h;
            }
      }
/*/--------------------------------------------------------------------------/*/
   if (!Error)
      {
         Edit65->Text = FloatToStr(Answer);
         Edit66->Text = FloatToStr(HCount);
      }
   EndOfProcedure:
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn23Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false, First = false;
   LDouble a, b, h, HCount, Answer, Help, x;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   Edit70->Clear();
   Edit71->Clear();
/*/----------------------/*/
   if (Edit67->Text == "")
      {
         Application->MessageBoxA("    Заполните поле Функция",
                                  "Численное интегрирование", MB_OK);
         return;
      }
   if (Edit72->Text == "")
     {
        Application->MessageBoxA("          Заполните поле шаг",
                                 "Численное интегрирование", MB_OK);
        return;
     }
    Error = CtrlNum(Edit72->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа h",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if (StrToFloat(Edit72->Text) <= 0)
      {
         Application->MessageBoxA("Шаг должен быть положительный",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if ((Edit68->Text == "") || (Edit69->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    Error = CtrlNum(Edit68->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа a",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    Error = CtrlNum(Edit69->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if (StrToFloat(Edit68->Text) >= StrToFloat(Edit69->Text))
      {
         Application->MessageBoxA("Число а должно быть < b", "Численное интегрирование", MB_OK);
         return;
      }
    if (RadioButton37->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton39->Checked)
      {
         Grad = true;
      }
    String = Edit67->Text;
    a = StrToFloat(Edit68->Text);
    b = StrToFloat(Edit69->Text);
    h = StrToFloat(Edit72->Text);
    Error = Kratnost(a, b, h);
    if (Error)
      {
         Application->MessageBoxA("Количество шагов должно быть кратно интервалу",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    HCount = Modul(b - a) / h;
    x = a;
    for (int i = 0; i <= HCount; i++)
      {
         AnsFun(String, Error, x, Help, Deg, Grad);
            if (Error)
               {
                  break;
               }
         if ((i == 0) || (i == HCount))
            {
               Help = Help / 2;
            }
            if (!First)
               {
                  Answer = Help * h;
                  First = true;
               }
            else
               {
                  Answer = Answer + ( Help * h);
               }
         x = x + h;
      }
/*/--------------------------------------------------------------------------/*/
   if (!Error)
      {
         Edit70->Text = FloatToStr(Answer);
         Edit71->Text = FloatToStr(HCount);
      }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn25Click(TObject *Sender)
{
bool Error = false, Deg = false, Grad = false, First = false;
   LDouble a, b, h, HCount, Answer, Help, x;
   AnsiString String;
/*/----------------------/*/
/*/Очистка полей/*/
   Edit76->Clear();
   Edit77->Clear();
/*/----------------------/*/
   if (Edit73->Text == "")
      {
         Application->MessageBoxA("    Заполните поле Функция",
                                  "Численное интегрирование", MB_OK);
         return;
      }
   if (Edit78->Text == "")
     {
        Application->MessageBoxA("          Заполните поле шаг",
                                 "Численное интегрирование", MB_OK);
        return;
     }
    Error = CtrlNum(Edit78->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа h",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if (StrToFloat(Edit78->Text) <= 0)
      {
         Application->MessageBoxA("Шаг должен быть положительный",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if ((Edit74->Text == "") || (Edit75->Text == ""))
      {
         Application->MessageBoxA("Заполните поля интервала",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    Error = CtrlNum(Edit74->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа a",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    Error = CtrlNum(Edit75->Text);
    if (Error)
      {
         Application->MessageBoxA("Ошибка в написании числа b",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    if (StrToFloat(Edit74->Text) >= StrToFloat(Edit75->Text))
      {
         Application->MessageBoxA("Число а должно быть < b", "Численное интегрирование", MB_OK);
         return;
      }
    if (RadioButton40->Checked)
      {
         Deg = true;
      }
    else
    if (RadioButton42->Checked)
      {
         Grad = true;
      }
    String = Edit73->Text;
    a = StrToFloat(Edit74->Text);
    b = StrToFloat(Edit75->Text);
    h = StrToFloat(Edit78->Text);
    Error = Kratnost(a, b, h);
    if (Error)
      {
         Application->MessageBoxA("Количество шагов должно быть кратно интервалу",
                                  "Численное интегрирование", MB_OK);
         return;
      }
    HCount = Modul(b - a) / h;
    Error = Drobnoe(HCount / 2);
    if (Error)
      {
         Application->MessageBoxA("Измените шаг, количество разбиений должно быть четным",
                                 "Метод Симпсона", MB_OK);
         return;
      }
    x = a;
    for (int i = 0; i <= HCount; i++)
      {
         AnsFun(String, Error, x, Help, Deg, Grad);
            if (Error)
               {
                  break;
               }
         if (i%2 == 1)
            {
               if ((i != 0) && (i != HCount))
                  {
                     Help = Help * 4;
                  }
            }
         if (i%2 == 0)
            {
               if ((i != 0) && (i != HCount))
                  {
                     Help = Help * 2;
                  }
            }
            if (!First)
               {
                  Answer = Help * (h / 3);
                  First = true;
               }
            else
               {
                  Answer = Answer + ( Help * (h / 3));
               }
         x = x + h;
      }
    if (!Error)
      {
         Edit76->Text = FloatToStr(Answer);
         Edit77->Text = FloatToStr(HCount);
      }
    EndOfProcedure:
}
/*/-----------------------------------------------------------------------/*/
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
   Edit5->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Information1Click(TObject *Sender)
{
   TForm2 *Form2 = new TForm2(this);
   Form2->ShowModal();
   delete Form2;
   Form2 = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
   TForm3 *Form3 = new TForm3(this);
   Form3->ShowModal();
   delete Form3;
   Form3 = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit47Change(TObject *Sender)
{
   Edit44->Text = Edit47->Text;   
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit53Change(TObject *Sender)
{
   Edit50->Text = Edit53->Text;      
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit59Change(TObject *Sender)
{
   Edit56->Text = Edit59->Text;
}
//---------------------------------------------------------------------------

