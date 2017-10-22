//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Lab4Unit.h"
#include "Include\\Faces_3D.cpp"
#include "Math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
unsigned int PX, PY, PZ;
const int N = 50;
const   M = 30;//113;
double  Df = 2*M_PI/N;
double Dt = 226 * 2 / double(M);

//точка наблюдения
double  Xs = 1500;

const int  VertexNum = 2 + (M - 1) * N;
const int  FacesNum = 2 * (M - 1) * N;

//луч света
TVector  Light = {0.577, 0.577, 0.577, 0};
//---------------------------------------------------------------------------
//прототипы
double Func(double);
void Vertex(double, double, TVertex);
void SetRx(double);
void SetRy(double);
void SetRz(double);
int VertIndex(int, int);
double Maximal(double, double);
//---------------------------------------------------------------------------
//переменные
//Глобальный массив вершин
TVertex  V[VertexNum];
//Запись трех вершин в массиве V - грани
TFace F[FacesNum];
//Массив индексов видимых граней, в массиве F
unsigned int FI[FacesNum];
//Массив уравнений плоскостей граней в локальной системе координат
TPlane  PL[FacesNum];
//Массив уравнений плоскостей граней в мировой системе координат
TPlane PLM[FacesNum];
//Точка наблюдения
TVertex  S = {Xs, 0, 0, 1};
//Хранение изображения
Graphics :: TBitmap *Bmp;
  //----------------
  //перспективная проекция - точка наблюдения на оси X = 1500
  TTransform P = {
    {0, 0, 0, -1/Xs},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //экранные координаты
  TTransform C = {
    {0,   0,  -1, 0},
    {1,   0,   0, 0},
    {0,   -1,  0, 0},
    {0,   0,   0, 1}
                  };
  //----------------
  //локальные координаты
  TTransform L = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {-1000, 0,  0, 1}
                  };
  //----------------
  //Обратная транспорированная матрица L
  TTransform tiL;
  //----------------
  //поворот вокруг X
  TTransform Rx = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //поворот вокруг Y
  TTransform Ry = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //поворот вокруг Z
  TTransform Rz = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //транспонировання и инвертированная
   TTransform tiRx, tiRy, tiRz;
//-------------------------------------------------------------------------
//функция ограничения параметра t
double Func(double _t)
{
  if ((_t <= -226) || (_t >= 226))
      {return 0;}
  else
      {return (2.268 * 0.00001 * _t * _t * _t - 1.756 * 0.001 * _t * _t - 1.158 * _t + 165.687);}
}
//--------------------------------------------------------------------------
//функция геометрической фигуры
void Vertex(double fi, double t, TVertex _V)
{
  _V[0] = Func(t) * cos(fi);
  _V[1] = Func(t) * sin(fi);
  _V[2] = t;
  _V[3] = 1;
}
//-------------------------------------------------------------------------
//Изменение матрицы Rx
void SetRx(double Angle)
{
   //Присвоим значение матриц
   Rx[1][1] = cos(Angle);
   Rx[1][2] = sin(Angle);
   Rx[2][1] = -sin(Angle);
   Rx[2][2] = cos(Angle);

   CalcInverseTransform(Rx, tiRx);
   TransposeTransformMatrix(tiRx, tiRx);
   //Вычисление новой матрицы вершин и уравнений плоскости
   ApplyTransform(V, V, Rx, sizeof(V));
   ApplyTransform(PL, PL, tiRx, sizeof(PL));
}
//-------------------------------------------------------------------------
//Изменение матрицы Ry
void SetRy(double Angle)
{
   //Присвоим значение матриц
   Ry[0][0] = cos(Angle);
   Ry[0][2] = -sin(Angle);
   Ry[2][0] = sin(Angle);
   Ry[2][2] = cos(Angle);

   CalcInverseTransform(Ry, tiRy);
   TransposeTransformMatrix(tiRy, tiRy);
   //Вычисление новой матрицы вершин и уравнений плоскостей
   ApplyTransform(V, V, Ry, sizeof(V));
   ApplyTransform(PL, PL, tiRy, sizeof(PL));
}
//-------------------------------------------------------------------------
//Изменение матрицы Rz
void SetRz(double Angle)
{
   //Присвоим значение матриц
   Rz[0][0] = cos(Angle);
   Rz[0][1] = sin(Angle);
   Rz[1][0] = -sin(Angle);
   Rz[1][1] = cos(Angle);

   CalcInverseTransform(Rz, tiRz);
   TransposeTransformMatrix(tiRz, tiRz);
   //Вычисление новой матрицы вершин и уравнений плоскостей
   ApplyTransform(V, V, Rz, sizeof(V));
   ApplyTransform(PL, PL, tiRz, sizeof(PL));
}
//-------------------------------------------------------------------------
int VertIndex(int _i, int _j)
{
   return (1+ N * (_i - 1) + _j);
}
//-------------------------------------------------------------------------
//Сравнение двух чисел, возврат максимального из них
double Maximal(double _A, double _B)
{
  if (_A > _B)
   {return _A;}
  else
   {return _B;}
}
//-------------------------------------------------------------------------
//Создание формы
void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Bmp = new Graphics :: TBitmap;
   Bmp->Width = ClientWidth;
   Bmp->Height = ClientHeight - (Panel1->Height + Panel2->Height);
   PX = 0;
   PY = 0;
   PZ = 0;
   unsigned int k;
   C[3][0] = int (ClientWidth / 2);
   C[3][1] = int ((ClientHeight - Panel1->Height)/ 2);

   //вершины
   Vertex(0, -226, V[0]);
   k = 1;
   for (int i = 1; i <= M; i++)
   for (int j = 0; j < N; j++)
      {
         Vertex(j * Df, i * Dt - 226, V[k]);
         k++;
      }
  k = 0;
  //грани
  //нижняя точка
  for (int j = 0; j < N; j++)
   {
      F[k].VI[0] = 0;
      F[k].VI[1] = VertIndex(1, (j + 1) % N);
      F[k].VI[2] = VertIndex(1, j);
      if ((k % 2) == 0)
         {
            F[k].R = 0;
            F[k].G = 0;
            F[k].B = 1;
         }
      else
         {
            F[k].R = 1;
            F[k].G = 1;
            F[k].B = 0.2;
         }
      k++;
   }
  //остальные грани
  for (int i = 1; i < M - 1; i++)
  for (int j = 0; j < N; j++)
   {
    F[k].VI[0] = VertIndex(i, j);
    F[k].VI[1] = VertIndex(i + 1, (j + 1) % N);
    F[k].VI[2] = VertIndex(i + 1, j);
    F[k].R = 1;
    F[k].G = 1;
    F[k].B = 1;
    k++;
    F[k].VI[0] = VertIndex(i, j);
    F[k].VI[1] = VertIndex(i, (j + 1) % N);
    F[k].VI[2] = VertIndex(i + 1, (j + 1) % N);
    F[k].R = 1;
    F[k].G = 1;
    F[k].B = 1;
    k++;
   }

  //коэффициенты вектора нормали
  for (int i = 0; i < FacesNum; i++)
   {
      GetPlaneEquation(V[F[i].VI[0]], V[F[i].VI[1]], V[F[i].VI[2]], PL[i]);
   }

  //вычисление обратной транспорирванной матрицы локальной с. к.
  CalcInverseTransform(L, tiL);
  TransposeTransformMatrix(tiL, tiL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
  //временный массив вершин
  //-----------------------------------
  TVertex VP[VertexNum];
  //переход в мировую систему координат
  ApplyTransform(VP, V, L, sizeof(V));
  //Преобразование массива уравнений плоскости в мировую систему координат
  ApplyTransform(PLM, PL, tiL, sizeof(PL));
  //Определение видимых - невидимых граней - не используется
  int Num = 0;
  for (int i = 0; i < FacesNum; i++)
   {
//     if (DetectPointSide(S, PLM[i]) > 0)
//       {
            FI[Num] = i;
            Num++;
//       }
   }
  //Сортировка вершин по максимальной координате X в массиве граней
  for (int i = 0; i < Num; i++)
   {
      F[FI[i]].maxX = Maximal(Maximal(VP[F[FI[i]].VI[0]][0], VP[F[FI[i]].VI[1]][0]), VP[F[FI[i]].VI[2]][0]);
   }

  //Сортировка вершин по возрастанию
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

  //переход к экранным координатам
  //перспективное проектирование
  ApplyTransform(VP, VP, P, sizeof(V));
  ApplyTransform(VP, VP, C, sizeof(VP));
  //нормализация координат
  NormalizeCoordinates(VP, sizeof(VP));

  //-----------------------------------
  //вывод вершин
  //for (int i = 0; i < VertexNum; i++)
  //{Canvas->Pixels[Round(VP[i][0])][Round(VP[i][1])] = clBlack;}
  //-----------------------------------
  Bmp->Canvas->Brush->Color = clBlack;
  Bmp->Canvas->FillRect(Rect(0, 0, ClientWidth, ClientHeight));
  //----------------------------------
  //Вывод на экран полигонов
  for (int i = 0; i < Num; i++)
     {
        DrawFace(Bmp->Canvas, VP, F[FI[i]], PLM[FI[i]], Light);
     }
  Canvas->Draw(0, Panel1->Height, Bmp);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
   C[3][0] = int(ClientWidth / 2);
   C[3][1] = int( (ClientHeight - (Panel1->Height + Panel2->Height)) / 2);
   Bmp->Width = ClientWidth;
   Bmp->Height = ClientHeight - Panel1->Height;
   Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete Bmp;
   Bmp = NULL;
}
//---------------------------------------------------------------------------
//Расчёт новой освещенности
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
   Light[1] = (TrackBar1->Position - 10) * 0.0577;
   OnPaint(this);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClick(TObject *Sender)
{
   TrackBar1->TabStop = false;
}
//---------------------------------------------------------------------------
//Поворот по оси Х
void __fastcall TForm1::TrackBar2Change(TObject *Sender)
{
   if (TrackBar2->Position > PX)
      {SetRx(DegToRad(TrackBar2->Position - PX));}
   if (TrackBar2->Position < PX)
      {SetRx(DegToRad(360 - 1*(PX - TrackBar2->Position)));}
   PX = TrackBar2->Position;
   OnPaint(this);
}
//---------------------------------------------------------------------------
//Поворот по оси Y
void __fastcall TForm1::TrackBar3Change(TObject *Sender)
{
   if (TrackBar3->Position > PY)
      {SetRy(DegToRad(TrackBar3->Position - PY));}
   if (TrackBar3->Position < PY)
      {SetRy(DegToRad(360 - 1*(PY - TrackBar3->Position)));}
   PY = TrackBar3->Position;
   OnPaint(this);
}
//---------------------------------------------------------------------------
//Поворот по оси Z
void __fastcall TForm1::TrackBar4Change(TObject *Sender)
{
   if (TrackBar4->Position > PZ)
      {SetRz(DegToRad(TrackBar4->Position - PZ));}
   if (TrackBar4->Position < PZ)
      {SetRz(DegToRad(360 - 1*(PZ - TrackBar4->Position)));}
   PZ = TrackBar4->Position;
   OnPaint(this);
}
//---------------------------------------------------------------------------

