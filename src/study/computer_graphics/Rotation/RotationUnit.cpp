//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "RotationUnit.h"
#include "Include\\Faces_3D.cpp"
#include "fstream.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainPanel *MainPanel;
//---------------------------------------------------------------------------
__fastcall TMainPanel::TMainPanel(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//Прототипы
void ClearScreen(TImage *, TColor);
void PaintAxisMain(TCanvas *);
void PaintAxisHelp(TCanvas *);
void Sort(TVertex *, unsigned int);
double Maximal(double, double);
void SetRx(double Angle);
void SetRy(double Angle);
void SetRz(double Angle);
bool GetVertex(TLIST *, AnsiString);
bool GetFaces(TLIST *, AnsiString);
//---------------------------------------------------------------------------
//Очистка всего экрана
void ClearScreen(TImage *_Screen, TColor _Color)
{
   _Screen->Canvas->Brush->Color = _Color;
   _Screen->Canvas->FillRect(Rect(0, 0, Screen->Width, Screen->Height));
}
//Рисование осей координат
void  PaintAxisMain(TCanvas *_Screen)
{
   _Screen->MoveTo(0, 0);
   _Screen->LineTo(0, 400);
   _Screen->MoveTo(0, 200);
   _Screen->LineTo(200, 200);
   _Screen->MoveTo(0, 0);
   _Screen->TextOutA(190, 205, "X");
}
//Рисование осей координат на вспомогательной оси
void PaintAxisHelp(TCanvas *_Screen)
{
   _Screen->MoveTo(0, 200);
   _Screen->LineTo(200, 200);
   _Screen->TextOutA(190, 205, "O");
   _Screen->TextOutA(5, 205, "-X");
   _Screen->TextOutA(185, 385, "-Z");
   _Screen->TextOutA(185, 0, "Z");
}
//Сортировка точек
void Sort(TVertex *_V, unsigned int _Count)
{
   TVertex Help;
   bool Flag = true;
   while (Flag)
      {
         Flag = false;
         for (int i = 0; i < _Count - 1; i++)
            {
               if (_V[i][2] != _V[i + 1][2])
                  {
                     if (_V[i][2] > _V[i + 1][2])
                        {
                           Copy(Help,  _V[i]);
                           Copy(_V[i], _V[i + 1]);
                           Copy(_V[i + 1], Help);
                           Flag = true;
                        }
                  }
               else
                  {
                     if (_V[i][0] > _V[i + 1][0])
                        {
                           Copy(Help,  _V[i]);
                           Copy(_V[i], _V[i + 1]);
                           Copy(_V[i + 1], Help);
                           Flag = true;
                        }
                  }
            }
      }
}
//-------------------------------------------------------------------------
double Maximal(double _A, double _B)
{
  if (_A > _B)
   {return _A;}
  else
   {return _B;}
}
//---------------------------------------------------------------------------
//Переменные
unsigned int CountVer;  //Количество вершин по вертикали
unsigned int CountGor;  //Количество вершин по горизонтали
unsigned int Count;     //Общее количество вершин
unsigned int FacesNum;   //Количество плоскостей

//Саморасширяющийся массив
TLIST *SameArray;
//Шаблон вершин
TVertex *Template;
//Вершины полигональной фигуры
TVertex *Vertex;
//Вершины полигональной фигуры в мировых координатах
TVertex *ScreenVertex;
//Матрица плоскостей
TPlane *PL;
//Матрица плокостей в мировой системе координат
//TPlane *PLM;
//Запись вершин грани
TFace *F;
//Массив индексов видимых граней в массиве F
unsigned int *FI;
//Точка наблюдения
double Ys = 1500;
//Хранение изображения
Graphics :: TBitmap *Bmp;
//Луч света
TVector  Light = {0.577, 0.577, 0.577, 0};
//точка наблюдения
TVertex  S = {0, Ys, 0, 1};
//Рисование изображения
bool Picture = false;
bool Skeleton = false;
//------------------------
//Семафоры
bool PaintPict = false; //Рисование
bool CreateObj = false; //Признак созданного объекта
bool JustPaint  = false;//Признак занятости массив созданных координат
//---------------------------------------------------------------------------
//Матрицы
//--------
//Переход из экранной в мировую, для Image1
TTransform ScreenToWorld = {
                              {1,  0,   0, 0},
                              {0,  0,  -1, 0},
                              {0,  -1,  0, 0},
                              {0,  0, 200, 1}
                           };
//Переход из мировой в экранную, для Image2
TTransform WorldToScreen = {
                              {1,     0,  0, 0},
                              {0,     0,  -1, 0},
                              {0,     -1,  0, 0},
                              {200, 200,  0, 1}
                           };
TTransform WorldToImage1 = {
                              {1,     0,  0, 0},
                              {0,     0,  -1, 0},
                              {0,     -1,  0, 0},
                              {0,    200,  0, 1}
                           };
//Матрица перспективного преобразования точки Zs
TTransform P             = {
                              {1, 0, 0,     0},
                              {0, 0, 0,     -1/Ys},
                              {0, 0, 1,     0},
                              {0, 0, 0,     1}
                           };
//----------------
//Переход в локальную с. к.
TTransform L             = {
                               {1,     0, 0, 0},
                               {0,     1, 0, 0},
                               {0,     0, 1, 0},
                               {0,     0, 0, 1}
                           };
  //----------------
  //Поворот вокруг X
  TTransform Rx = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //Поворот вокруг Y
  TTransform Ry = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //Поворот вокруг Z
  TTransform Rz = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
//Транспорированная инвертированная матрицы
TTransform tiRx, tiRy, tiRz, tiL;
//------------------------------------------
//Множество
Set <char, 44, 69> SetOfChar;
//---------------------------------------------------------------------------
//Изменение матрицы Rx
void SetRx(double Angle)
{
   Rx[1][1] = cos(Angle);
   Rx[1][2] = sin(Angle);
   Rx[2][1] = -sin(Angle);
   Rx[2][2] = cos(Angle);

   CalcInverseTransform(Rx, tiRx);
   TransposeTransformMatrix(tiRx, tiRx);
   ApplyTransform(Vertex, Vertex, Rx, Count * 32);
   ApplyTransform(PL, PL, tiRx, FacesNum * 32);
}
//-------------------------------------------------------------------------
//Изменение матрицы Ry
void SetRy(double Angle)
{
   Ry[0][0] = cos(Angle);
   Ry[0][2] = -sin(Angle);
   Ry[2][0] = sin(Angle);
   Ry[2][2] = cos(Angle);

   CalcInverseTransform(Ry, tiRy);
   TransposeTransformMatrix(tiRy, tiRy);
   ApplyTransform(Vertex, Vertex, Ry, Count * 32);
   ApplyTransform(PL, PL, tiRy, FacesNum * 32);
}
//-------------------------------------------------------------------------
//Изменение матрицы Rz
void SetRz(double Angle)
{
   Rz[0][0] = cos(Angle);
   Rz[0][1] = sin(Angle);
   Rz[1][0] = -sin(Angle);
   Rz[1][1] = cos(Angle);

   CalcInverseTransform(Rz, tiRz);
   TransposeTransformMatrix(tiRz, tiRz);
   ApplyTransform(Vertex, Vertex, Rz, Count * 32);
   ApplyTransform(PL, PL, tiRz, FacesNum * 32);
}
//---------------------------------------------------------------------------
//Распознование строки
bool GetVertex(TLIST *Help, AnsiString _Buff)
{
   unsigned int i = 1;
   bool First = false, Second = false, Third = false, Fourth = false, OpenBracket = false, CloseBracket = false;
   AnsiString Number;
   double Var;
   TVertex _Vertex;

   //Поиск открывающей скобки
   while (i <= _Buff.Length())
      {
         if (_Buff[i] == '(')
            {
               OpenBracket = true;
               i++;
               break;
            }
         i++;
      }
   if (!OpenBracket)
      {
         Application->MessageBoxA("Не найдена открывающая скобка в строке", "Ошибка анализа строки", MB_OK);
         return false;
      }

   //Поиск координат
   while (i <= _Buff.Length())
      {
         if (_Buff[i] != ' ')
            {
               //Заполнение координат
               while ( (i <= _Buff.Length()) && (_Buff[i] != ' ') && (SetOfChar.Contains(_Buff[i])) )
                  {
                     Number = Number + _Buff[i];
                     i++;
                  }
               try
                  {
                     Var = StrToFloat(Number);
                  }
               catch(...)
                  {
                     Application->MessageBoxA("Ошибка в написании числа, возможно указано менее четырех координат вершины", "Ошибка анализа строки", MB_OK);
                     return false;
                  }
               Number = "";
               //Присвоение первой координаты
               if (!First)
                  {
                      _Vertex[0] = Var;
                      First = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //Присвоение второй координаты
               if ( (First) && (!Second))
                  {
                     _Vertex[1] = Var;
                      Second = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //Присвоение третей координаты
               if ( (First) && (Second) && (!Third) )
                  {
                     _Vertex[2] = Var;
                      Third = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               if ( (First) && (Second) && (Third) && (!Fourth))
                  {
                     _Vertex[3] = Var;
                      Fourth = true;
                      break;
                  }
            }
         i++;
      }
   //Поиск закрывающей скобки
   while (i <= _Buff.Length())
      {
         if (_Buff[i] == ')')
            {
               CloseBracket = true;
               break;
            }
         i++;
      }
   if (!CloseBracket)
      {
         Application->MessageBoxA("Не найдена закрывающая скобка в строке", "Ошибка анализа строки", MB_OK);
         return false;
      }
   if ( (!First) || (!Second) || (!Third) || (!Fourth))
      {
         Application->MessageBoxA("Количество координат вершины должно быть равно четырем", "Ошибка анализа строки", MB_OK);
         return false;
      }
   Help->Add(_Vertex[0], _Vertex[1], _Vertex[2], _Vertex[3]);
   return true;
}
//---------------------------------------------------------------------------
//Распознование строки граней
bool GetFaces(TLIST *Help, AnsiString _Buff)
{
   unsigned int i = 1;
   bool First = false, Second = false, Third = false, OpenBracket = false, CloseBracket = false;
   AnsiString Number;
   double Var;
   TVertex _Vertex;

   //Поиск открывающей скобки
   while (i <= _Buff.Length())
      {
         if (_Buff[i] == '(')
            {
               OpenBracket = true;
               i++;
               break;
            }
         i++;
      }
   if (!OpenBracket)
      {
         Application->MessageBoxA("Не найдена открывающая скобка в строке", "Ошибка анализа строки", MB_OK);
         return false;
      }

   //Поиск координат
   while (i <= _Buff.Length())
      {
         if (_Buff[i] != ' ')
            {
               //Заполнение координат
               while ( (i <= _Buff.Length()) && (_Buff[i] != ' ') && (SetOfChar.Contains(_Buff[i])) )
                  {
                     Number = Number + _Buff[i];
                     i++;
                  }
               try
                  {
                     Var = StrToFloat(Number);
                  }
               catch(...)
                  {
                     Application->MessageBoxA("Ошибка в написании числа, возможно указано менее трех индексов грани", "Ошибка анализа строки", MB_OK);
                     return false;
                  }
               Number = "";
               //Присвоение первой координаты
               if (!First)
                  {
                      _Vertex[0] = Var;
                      First = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //Присвоение второй координаты
               if ( (First) && (!Second))
                  {
                     _Vertex[1] = Var;
                      Second = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //Присвоение третей координаты
               if ( (First) && (Second) && (!Third) )
                  {
                     _Vertex[2] = Var;
                      Third = true;
                      break;
                  }
            }
         i++;
      }

   //Поиск закрывающей скобки
   while (i <= _Buff.Length())
      {
         if (_Buff[i] == ')')
            {
               CloseBracket = true;
               break;
            }
         i++;
      }
   if (!CloseBracket)
      {
         Application->MessageBoxA("Не найдена закрывающая скобка в строке", "Ошибка анализа строки", MB_OK);
         return false;
      }
   if ( (!First) || (!Second) || (!Third) )
      {
         Application->MessageBoxA("Количество индексов вершин должно быть равно трем", "Ошибка анализа строки", MB_OK);
         return false;
      }
   Help->Add(_Vertex[0], _Vertex[1], _Vertex[2], 0);
   return true;
}
//---------------------------------------------------------------------------
//Создание формы
void __fastcall TMainPanel::FormCreate(TObject *Sender)
{
   ClearScreen(Image1, clWhite);
   PaintAxisMain(Image1->Canvas);
   ClearScreen(Image3, clBtnFace);
   PaintAxisHelp(Image3->Canvas);
   ClearScreen(Image2, clBlack);
   CountVer = 0;
   CountGor = 0;
   Count = 0;
   FacesNum = 0;
   Bmp = new Graphics :: TBitmap;
   SameArray = NULL;
   SetOfChar << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9' << '-' << ',' << 'E';
}
//---------------------------------------------------------------------------
void __fastcall TMainPanel::Image3Click(TObject *Sender)
{
   Application->MessageBoxA("Вводить координаты точек только в I и IV квадранты", "Внимание", MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TMainPanel::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (
      (
         ((X > 0) && (X <= Image1->Width))
         &&
         ((Y > 0) && (Y <= Image1->Height))
      )
         &&
         (!JustPaint)
      )
      {
      if (SameArray == NULL) {SameArray = new TLIST();}
         SameArray->Add(double(X), double(Y), 0, 1);
         CountVer++;
         Image1->Canvas->Ellipse(X - 1, Y - 1, X + 1, Y + 1);
         CreateObj = true;
      }
}
//---------------------------------------------------------------------------
void __fastcall TMainPanel::PaintPolygonClick(TObject *Sender)
{
if ((CreateObj) && (!JustPaint)) //Проверка семафора на наличие объекта и уже нарисованных коориднат
{
if (SameArray->GetCount() == 1)
{
   Application->MessageBoxA("Необходимо минимум две точки для постоения поверхности вращения", "Внимание", MB_OK);
   return;
}
   //Переменные
   double Angle;
   unsigned int k;
   //----------
   //Задание угла
   try
      {Angle = StrToFloat(Edit1->Text);}
   catch (...)
      {Application->MessageBoxA("Ошибка в написании угла", "Внимание", MB_OK); return;}
   if (Angle > 10) {Application->MessageBoxA("Угол задан слишком большим, измените значение", "Внимание", MB_OK); return;}
   if (Angle <= 0) {Application->MessageBoxA("Угол должен быть положительным", "Внимание", MB_OK); return;}
   CountGor = 360 / Angle;
   //Массив шаблона
   Template = new TVertex[CountVer];
   //Копирование вершин в массив шаблона
   Copy(Template, SameArray);
   //Массив всех вершин поверхности вращения
   Vertex = new TVertex[CountGor * CountVer];
   //Перевод из экранной в мировую с. к.
   ApplyTransform(Template, Template, ScreenToWorld, (CountVer)*32);
   //Сортировка вершин, начиная с намой нижней
   Sort(Template, CountVer);
   //Вычисление остальных вершин
   k = 0;
   for (int i = 0; i < CountVer; i++)
   for (int j = 0; j < CountGor; j++)
         {
            Vertex[k][0] = Template[i][0] * cos(DegToRad(Angle * j));
            Vertex[k][1] = Template[i][0] * sin(DegToRad(Angle * j));
            Vertex[k][2] = Template[i][2];
            Vertex[k][3] = 1;
            k++;
         }
   Count = k;
   //------------
   //Заполнение массива граней
   //------------
   k = 0;
   FacesNum = 2 * (CountVer - 1) * CountGor;
   F = new TFace[FacesNum];
   for (int i = 0; i < CountVer - 1; i++)
   for (int j = 0; j < CountGor; j++)
      {
         F[k].VI[0] = i*CountGor + j % CountGor;
         F[k].VI[1] = (i + 1) * CountGor + (j + 1) % CountGor;
         F[k].VI[2] = (i + 1) * CountGor + j % CountGor;
         F[k].R = 1;
         F[k].G = 1;
         F[k].B = 1;
         k++;
         F[k].VI[0] = i * CountGor + j % CountGor;
         F[k].VI[1] = i * CountGor + (j + 1) % CountGor;
         F[k].VI[2] = (i + 1) * CountGor + (j + 1) % CountGor;
         F[k].R = 1;
         F[k].G = 1;
         F[k].B = 1;
         k++;
      }
   FacesNum = k;
   //------------
   //Заполение массива уравнений плоскостей
   //------------
   PL = new TPlane[FacesNum];
   for (int i = 0; i < FacesNum; i++)
      {
        GetPlaneEquation(Vertex[F[i].VI[0]], Vertex[F[i].VI[1]], Vertex[F[i].VI[2]], PL[i]);
      }
   //------------
   //Вычисление обратной транспорированной матрицы локальной системы координат
//   CalcInverseTransform(L, tiL);
//   TransposeTransformMatrix(tiL, tiL);
   //------------
   //Тип изображения
   if (RadioButton1->Checked)
      {
         Picture = true;
         Skeleton = false;
      }
   else
      {
         Picture = false;
         Skeleton = true;
      }
   //------------
   //Вызов обработчика
   PaintPict = true;    //Включение семафора рисования
   OnPaint(this);
}
}
//---------------------------------------------------------------------------
//Обработчик события OnPaint
void __fastcall TMainPanel::FormPaint(TObject *Sender)
{
if (PaintPict)    //Проверка семафора на возможность рисовать
{
   //---------------------------------
   Bmp->Width = Image2->Width;
   Bmp->Height = Image2->Height;
   //---------------------------------
   //Массив вершин, выводимых на экран
   TVertex *VP;
   //Массив уравнений плоскостей в мировых координатах
   TPlane *PLM;
   //---------------------------------
   //Создание динамических массивов
   VP = new TVertex[Count];
   PLM = new TPlane[FacesNum];
   FI = new unsigned int[FacesNum];
   //---------------------------------
//   ApplyTransform(VP, Vertex, L, Count*32);
 //  ApplyTransform(PLM, PL, tiL, FacesNum*32);
   Copy(VP, Vertex, Count*32);
   //---------------------------------
   //Определение - видимых (невидимых) граней
   int Num = 0;
   for (int i = 0; i < FacesNum; i++)
      {
//       if (DetectPointSide(S, PL[i]) > 0)
          {
               FI[Num] = i;
               Num++;
          }
      }
   //---------------------------------
   //Сортировка вершин по максимальной координате y
   for (int i = 0; i < Num; i++)
      {
         F[FI[i]].maxX = Maximal(Maximal(VP[F[FI[i]].VI[0]][1], VP[F[FI[i]].VI[1]][1]), VP[F[FI[i]].VI[2]][1]);
      }

   //Сортировка граней по удалению
   int temp;
   for (int i = 0; i < Num - 1; i++)
      {
         for (int j = i + 1; j < Num; j++)
         if (F[FI[i]].maxX > F[FI[j]].maxX)
            {
               temp = FI[j];
               FI[j] = FI[i];
               FI[i] = temp;
            }
      }
   //---------------------------------
   ApplyTransform(VP, VP, P, Count*32);
   ApplyTransform(VP, VP, WorldToScreen, Count*32);
   NormalizeCoordinates(VP, Count*32);
   //---------------------------------
   //Вывод на экран
   Bmp->Canvas->Brush->Color = clBlack;
   Bmp->Canvas->FillRect(Rect(0, 0, Image2->ClientWidth, Image2->ClientHeight));
   if (Picture)
   {
   for (int i = 0; i < Num; i++)
     {
        DrawFace(Bmp->Canvas, VP, F[FI[i]], PL[FI[i]], Light);
     }
   }
   if (Skeleton)
   {
      for (int i = 0; i < Count; i++)
        {Bmp->Canvas->Pixels[Round(VP[i][0])][Round(VP[i][1])] = clWhite;}
   }
   Image2->Canvas->Draw(0, 0, Bmp);
   //---------------------------------
   //Переключение необходимого семафора
   JustPaint = true;
   //---------------------------------
   //Уничтожение динамических массивов
   delete []VP;
   VP = NULL;
   delete []PLM;
   PLM = NULL;
   PaintPict = false;
   delete []FI;
   FI = NULL;
}
}
//---------------------------------------------------------------------------
//Уничтожение объектов
void __fastcall TMainPanel::ClearAllClick(TObject *Sender)
{
   CreateObj = false;   //Семафор создания объекта выключен
   JustPaint = false;   //Семафор нарисованного объекта выключен
   PaintPict = false;    //Семафор на рисование объекта
   //Уничтожение массива вершин шаблона
   delete []Template;
   Template  = NULL;
   //Уничтожение массива вершин всей фигуры
   delete []Vertex;
   Vertex = NULL;
   //Уничтожение массива вершин ребёр
   delete []F;
   F = NULL;
   //Уничтожение массива уравнений плоскоти
   delete []PL;
   PL = NULL;
   //Уничтожение самонаращивающегося массива
   delete SameArray;
   SameArray = NULL;
   //Очистка рисунков
   ClearScreen(Image1, clWhite);
   PaintAxisMain(Image1->Canvas);
   Bmp->Canvas->Brush->Color = clBlack;
   Bmp->Canvas->FillRect(Rect(0, 0, Image2->ClientWidth, Image2->ClientHeight));
   Image2->Canvas->Draw(0, 0, Bmp);
   //Зануление основных переменных
   CountVer = 0;
   CountGor = 0;
   Count = 0;
   FacesNum = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainPanel::FormDestroy(TObject *Sender)
{
   delete Bmp;
   Bmp = NULL;
}
//---------------------------------------------------------------------------
//Поворот по X по часовой
void __fastcall TMainPanel::TurnUpClick(TObject *Sender)
{
   if (CreateObj)
   {
   SetRx(DegToRad(6));
   PaintPict = true;
   OnPaint(this);
   }
}
//---------------------------------------------------------------------------
//Поворот по X против часовой
void __fastcall TMainPanel::TurnDownClick(TObject *Sender)
{
   if (CreateObj)
   {
   SetRx(DegToRad(-6));
   PaintPict = true;
   OnPaint(this);
   }
}
//---------------------------------------------------------------------------
//Поворот по Z против часовой
void __fastcall TMainPanel::TurnLeftClick(TObject *Sender)
{
   if (CreateObj)
   {
   SetRz(DegToRad(5));
   PaintPict = true;
   OnPaint(this);
   }
}
//---------------------------------------------------------------------------
//Поворот по Z по часовой
void __fastcall TMainPanel::TurnRightClick(TObject *Sender)
{
   if (CreateObj)
   {
   SetRz(DegToRad(-5));
   PaintPict = true;
   OnPaint(this);
   }
}
//---------------------------------------------------------------------------
//По поворот вокруг своей оси
void __fastcall TMainPanel::TurnAroundClick(TObject *Sender)
{
   if (CreateObj)
   {
   SetRy(DegToRad(5));
   PaintPict = true;
   OnPaint(this);
   }
}
//---------------------------------------------------------------------------
//Закрыть программу
void __fastcall TMainPanel::Exit1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//Сохранение изображения
void __fastcall TMainPanel::SaveBitMap1Click(TObject *Sender)
{
if (JustPaint)
{
   if (SavePictureDialog1->Execute())
      {
         //Файл не создан
         if (!FileExists(SavePictureDialog1->FileName))
            {
               ofstream OutFile((SavePictureDialog1->FileName).c_str());
               if (OutFile.fail())
                  {
                     Application->MessageBox("Невозможно создать файл на диске", "Ошибка создания файла", MB_OK);
                     return;
                  }
               else
               {OutFile.close();}
            }
         //Файл существует
         else
            {
                  if (MessageDlg("Файл с указанным именем присутствует на диске, хотите заменить существующий файл",
                              mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                     {return;}
            }
         try
            {
               Bmp->SaveToFile(SavePictureDialog1->FileName);
            }
         catch (...)
            {
               Application->MessageBox("Невозможно сохранить файл на диске", "Ошибка записи на диск", MB_OK);
               return;
            }
      }
}
else
{
   Application->MessageBoxA("Рисунок не создан", "Внимание", MB_OK);
}
}
//---------------------------------------------------------------------------
//Загрузить рисунок
void __fastcall TMainPanel::LoadBitMap1Click(TObject *Sender)
{
   if (OpenPictureDialog1->Execute())
      {
         if (FileExists(OpenPictureDialog1->FileName))
            {
               try
                  {Bmp->LoadFromFile(OpenPictureDialog1->FileName);}
               catch(...)
                  {Application->MessageBoxA("Невозможно открыть файл", "Ошибка чтения файла", MB_OK); return;}
               ClearAllClick(Sender);
               Bmp->LoadFromFile(OpenPictureDialog1->FileName);
               Image2->Canvas->Draw(0, 0, Bmp);
            }
         else
            {
               Application->MessageBoxA("Указанный файл отсутствует на диске", "Ошибка чтения файла", MB_OK);
            }
      }
}
//---------------------------------------------------------------------------
//Сохранение вершин шаблона
void __fastcall TMainPanel::Savetemplate1Click(TObject *Sender)
{
if (Template != NULL)
{
   if (SaveDialog1->Execute())
      {
         AnsiString Buffer;
         //Файл существует
         if (FileExists(SaveDialog1->FileName))
            {
               if (MessageDlg("Файл с указанным именем присутствует на диске, хотите заменить существующий файл",
                            mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                           {return;}
            }
         //Открыли файл
         ofstream OutFile((SaveDialog1->FileName).c_str());
         if (OutFile.fail())
            {
               Application->MessageBox("Невозможно создать файл на диске", "Ошибка создания файла", MB_OK);
               return;
            }
         //-------------
         //запись в файл
         //-------------
         //Признак вершин шаблона
         Buffer = "[Template Vertex]\n";
         OutFile.write(Buffer.c_str(), Buffer.Length());
         OutFile.put('{').put('\n');
         for (int i = 0; i < CountVer; i++)
            {
               Buffer = "( " + FloatToStr(Template[i][0]) + " " + FloatToStr(Template[i][1]) + " "
                        + FloatToStr(Template[i][2]) + " " + "1 )\n";
               OutFile.write(Buffer.c_str(), Buffer.Length());
            }
         OutFile.put('}').put('\n');
         //-------------
         //Закрытие файла
         OutFile.close();
      }
}
else
{
   Application->MessageBoxA("Шаблон пуст", "Внимание", MB_OK);
}
}
//---------------------------------------------------------------------------
//Сохранение всех вершин и ребер
void __fastcall TMainPanel::SaveVertexEdge1Click(TObject *Sender)
{
if (Template != NULL)
{
   if (SaveDialog2->Execute())
      {
         AnsiString Buffer;
         //Файл существует
         if (FileExists(SaveDialog2->FileName))
            {
               if (MessageDlg("Файл с указанным именем присутствует на диске, хотите заменить существующий файл",
                            mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                           {return;}
            }
         //Открыли файл
         ofstream OutFile((SaveDialog2->FileName).c_str());
         if (OutFile.fail())
            {
               Application->MessageBox("Невозможно создать файл на диске", "Ошибка создания файла", MB_OK);
               return;
            }
         //-------------
         //запись в файл
         //-------------
         //Признак всех вершин фигуры
         Buffer = "[Vertex]\n";
         OutFile.write(Buffer.c_str(), Buffer.Length());
         OutFile.put('{').put('\n');
         for (int i = 0; i < Count; i++)
            {
               Buffer = "( " + FloatToStr((Vertex[i][0])) + " " + FloatToStr((Vertex[i][1])) + " "
                        + FloatToStr((Vertex[i][2])) + " " + "1 )\n";
               OutFile.write(Buffer.c_str(), Buffer.Length());
            }
         OutFile.put('}').put('\n');
         //-------------
         //Признак ребер фигуры
         Buffer = "\n[Faces]\n";
         OutFile.write(Buffer.c_str(), Buffer.Length());
         OutFile.put('{').put('\n');
         for (int i = 0; i < FacesNum; i++)
            {
               Buffer = "( " + IntToStr(F[i].VI[0]) + ", " + IntToStr(F[i].VI[1]) + ", "
                        + IntToStr(F[i].VI[2]) + " )\n";
               OutFile.write(Buffer.c_str(), Buffer.Length());
            }
         OutFile.put('}').put('\n');
         //-------------
         //Закрытие файла
         OutFile.close();
      }
}
else
{
   Application->MessageBoxA("Фигура не создана", "Внимание", MB_OK);
}
}
//---------------------------------------------------------------------------
//Загрузка из файла шаблона
void __fastcall TMainPanel::Loadtemplate1Click(TObject *Sender)
{
   if (OpenDialog1->Execute())
      {
         ifstream LoadFile;
         char *FileName = (OpenDialog1->FileName).c_str();
         LoadFile.open(FileName);
         if (LoadFile.fail())
            {
               Application->MessageBoxA(("Невозможно открыть файл " + AnsiString(FileName)).c_str(), "Ошибка открытия файла", MB_OK);
               LoadFile.close();
               return;
            }
         if (Vertex != NULL)
            {
               ClearAllClick(Sender);
            }
         //Ввод вершин
         TLIST *HelpArray = new TLIST;
         char Buffer[255];
         bool Found = false;
         //--------------
         //Поиск ключа
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //Признак останова
               if (AnsiString(Buffer) == "[Template Vertex]")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Признак вершин шаблона не найден, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //Поиск начала
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //Признак останова
               if (AnsiString(Buffer) == "{")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Не найдена скобка начала всех вершин, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //Интерпретация с поиском конца
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               if (AnsiString(Buffer) == "}")
                  {
                     Found = true;
                     break;
                  }
               //Распознавание строки
               if (!GetVertex(HelpArray, AnsiString(Buffer)))
                  {
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Не найдена скобка конца всех вершин, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
//---------------------------------------------------------------------
//Вычисление координат
if (HelpArray->GetCount() == 1)
{
   Application->MessageBoxA("Необходимо минимум две точки для постоения поверхности вращения", "Внимание", MB_OK);
   return;
}
   CountVer = HelpArray->GetCount();
   //Переменные
   double Angle;
   unsigned int k;
   //----------
   //Задание угла
   try
      {Angle = StrToFloat(Edit1->Text);}
   catch (...)
      {Application->MessageBoxA("Ошибка в написании угла", "Внимание", MB_OK); return;}
   if (Angle > 10) {Application->MessageBoxA("Угол задан слишком большим, измените значение", "Внимание", MB_OK); goto Exit;}
   if (Angle <= 0) {Application->MessageBoxA("Угол должен быть положительным", "Внимание", MB_OK); goto Exit;}
   CountGor = 360 / Angle;
   //Массив шаблона
   Template = new TVertex[CountVer];
   //Копирование вершин в массив шаблона
   Copy(Template, HelpArray);
   //Массив всех вершин поверхности вращения
   Vertex = new TVertex[CountGor * CountVer];
   //Сортировка вершин, начиная с намой нижней
   Sort(Template, CountVer);
   //Вычисление остальных вершин
   k = 0;
   for (int i = 0; i < CountVer; i++)
   for (int j = 0; j < CountGor; j++)
         {
            Vertex[k][0] = Template[i][0] * cos(DegToRad(Angle * j));
            Vertex[k][1] = Template[i][0] * sin(DegToRad(Angle * j));
            Vertex[k][2] = Template[i][2];
            Vertex[k][3] = 1;
            k++;
         }
   Count = k;
   //------------
   //Вывод на экран шаблона
   ApplyTransform(Template, Template, WorldToImage1, CountVer*32);
   NormalizeCoordinates(Template, CountVer*32);
   for (int i = 0; i < CountVer; i++)
      {
         Image1->Canvas->Ellipse(Template[i][0] - 1, Template[i][1] - 1, Template[i][0] + 1, Template[i][1] + 1);
      }
   //------------
   //Заполнение массива граней
   //------------
   k = 0;
   FacesNum = 2 * (CountVer - 1) * CountGor;
   F = new TFace[FacesNum];
   for (int i = 0; i < CountVer - 1; i++)
   for (int j = 0; j < CountGor; j++)
      {
         F[k].VI[0] = i*CountGor + j % CountGor;
         F[k].VI[1] = (i + 1) * CountGor + (j + 1) % CountGor;
         F[k].VI[2] = (i + 1) * CountGor + j % CountGor;
         F[k].R = 1;
         F[k].G = 1;
         F[k].B = 1;
         k++;
         F[k].VI[0] = i * CountGor + j % CountGor;
         F[k].VI[1] = i * CountGor + (j + 1) % CountGor;
         F[k].VI[2] = (i + 1) * CountGor + (j + 1) % CountGor;
         F[k].R = 1;
         F[k].G = 1;
         F[k].B = 1;
         k++;
      }
   FacesNum = k;
   //------------
   //Заполение массива уравнений плоскостей
   //------------
   PL = new TPlane[FacesNum];
   for (int i = 0; i < FacesNum; i++)
      {
        GetPlaneEquation(Vertex[F[i].VI[0]], Vertex[F[i].VI[1]], Vertex[F[i].VI[2]], PL[i]);
      }
   //------------
   //Вычисление обратной транспорированной матрицы локальной системы координат
//   CalcInverseTransform(L, tiL);
//   TransposeTransformMatrix(tiL, tiL);
   //------------
   //Тип изображения
   if (RadioButton1->Checked)
      {
         Picture = true;
         Skeleton = false;
      }
   else
      {
         Picture = false;
         Skeleton = true;
      }
   //------------
   //Вызов обработчика
   CreateObj = true;
   PaintPict = true;    //Включение семафора рисования
   OnPaint(this);
//---------------------------------------------------------------------
         Exit:
         LoadFile.close();
         //--------------
         delete HelpArray;
         HelpArray = NULL;
      }
}
//---------------------------------------------------------------------------
//Загрузка файла вершин фигуры и граней
void __fastcall TMainPanel::LoadFigureClick(TObject *Sender)
{
if (OpenDialog2->Execute())
      {
         ifstream LoadFile;
         bool Error = false;
         char *FileName = (OpenDialog2->FileName).c_str();
         LoadFile.open(FileName);
         if (LoadFile.fail())
            {
               Application->MessageBoxA(("Невозможно открыть файл " + AnsiString(FileName)).c_str(), "Ошибка открытия файла", MB_OK);
               LoadFile.close();
               return;
            }
         if (Vertex != NULL)
            {
               ClearAllClick(Sender);
            }
      //------------------------------------------------------------------------
         //Массив вершин
         TLIST *HelpArray = new TLIST;
         //Массив граней 
         TLIST *HelpFaces = new TLIST;
         char Buffer[255];
         bool Found = false;
      //------------------------------------------------------------------------
      //Вершины фигуры
         //--------------
         //Поиск ключа
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //Признак останова
               if (AnsiString(Buffer) == "[Vertex]")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Признак вершин фигуры не найден, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //Заполнение массива граней
         //------------
         //Поиск начала
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //Признак останова
               if (AnsiString(Buffer) == "{")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Не найдена скобка начала всех вершин, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //Интерпретация с поиском конца
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               if (AnsiString(Buffer) == "}")
                  {
                     Found = true;
                     break;
                  }
               //Распознавание строки
               if (!GetVertex(HelpArray, AnsiString(Buffer)))
                  {
                     Error = true;
                     break;
                  }
            }
         if (Error)
            {
               Application->MessageBoxA("Файл вершин фигуры не соответствует стандарту, поддерживаемому программой", "Внимание", MB_OK);
               goto Exit;               
            }
         if (!Found)
            {
               Application->MessageBoxA("Не найдена скобка конца всех вершин, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
      //------------------------------------------------------------------------
      LoadFile.close();
      Error = false;
      LoadFile.open(FileName);
      //-------------
      //Грани
        //Поиск ключа
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //Признак останова
               if (AnsiString(Buffer) == "[Faces]")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Признак граней фигуры не найден, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //Заполнение массива граней
         //------------
         //Поиск начала
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //Признак останова
               if (AnsiString(Buffer) == "{")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("Не найдена скобка начала индексов граней, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //Интерпретация с поиском конца
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               if (AnsiString(Buffer) == "}")
                  {
                     Found = true;
                     break;
                  }
               //Распознавание строки
               if (!GetFaces(HelpFaces, AnsiString(Buffer)))
                  {
                     Error = true;
                     break;
                  }
            }
         if (Error)
            {
               Application->MessageBoxA("Файл вершин фигуры не соответствует стандарту, поддерживаемому программой", "Внимание", MB_OK);
               goto Exit;
            }
         if (!Found)
            {
               Application->MessageBoxA("Не найдена скобка конца индексов граней, возможно открыт другой файл",
                                        "Ошибка анализа файла", MB_OK);
               goto Exit;
            }
//---------------------------------------------------------------------
//Вычисление координат
   Count = HelpArray->GetCount();
   FacesNum = HelpFaces->GetCount();
   //------------------------------
   //Массив всех вершин поверхности вращения
   Vertex = new TVertex[Count];
   //Индексы граней
   F = new TFace[FacesNum];
   //Копирование вершин в массив
   Copy(Vertex, HelpArray);
   //Копирование граней
   for (int i = 0; i < FacesNum; i++)
      {
         F[i].VI[0] = HelpFaces->GetValue(i, 0);
         F[i].VI[1] = HelpFaces->GetValue(i, 1);
         F[i].VI[2] = HelpFaces->GetValue(i, 2);
         F[i].R = 1;
         F[i].G = 1;
         F[i].B = 1;
      }
   //Сортировка вершин, начиная с намой нижней
//   Sort(Vertex, CountVer);
   //------------
   //Заполение массива уравнений плоскостей
   //------------
   PL = new TPlane[FacesNum];
   for (int i = 0; i < FacesNum; i++)
      {
        GetPlaneEquation(Vertex[F[i].VI[0]], Vertex[F[i].VI[1]], Vertex[F[i].VI[2]], PL[i]);
      }
   //------------
   //Вычисление обратной транспорированной матрицы локальной системы координат
//   CalcInverseTransform(L, tiL);
//   TransposeTransformMatrix(tiL, tiL);
   //------------
   //Тип изображения
   if (RadioButton1->Checked)
      {
         Picture = true;
         Skeleton = false;
      }
   else
      {
         Picture = false;
         Skeleton = true;
      }
   //------------
   //Вызов обработчика
   CreateObj = true;
   PaintPict = true;    //Включение семафора рисования
   OnPaint(this);
//---------------------------------------------------------------------
         Exit:
         LoadFile.close();
         //--------------
         delete HelpArray;
         HelpArray = NULL;
         //--------------
         delete HelpFaces;
         HelpFaces = NULL;
      }
}
//---------------------------------------------------------------------------
