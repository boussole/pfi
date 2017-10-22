//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "YachtUnit.h"
#include "math.h"
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
/*/Флаги управления/*/
   bool Around = false, AroundX = false, AroundY = false, AroundZ;
/*/-----------------------------------------------------------------------/*/
/*/Используемые типы данных/*/
  //Тип для описания одной вершины
   typedef double TVertex[4];

  //Массив ребер
   typedef unsigned short TEdge[2];

  //Матрицы преобразования
   typedef double TTransform[4][4];
/*/-----------------------------------------------------------------------/*/
/*/Прототипы/*/
void Copy(TVertex *,TVertex *, unsigned short int);
void Copy(TTransform CopyMatrix,TTransform OrigMatrix);
void CombineTransforms(TTransform , const TTransform, const TTransform);
void ApplyTransform(TVertex *, TVertex *, const TTransform, unsigned short int);
void NormalizeCoordinates(TVertex *V, unsigned short int);
void DrawWire(TCanvas *, TVertex *, TEdge *, unsigned short int, unsigned short int);
double Round(double);
/*/-----------------------------------------------------------------------/*/
/*/Координаты фигуры/*/
   const VCount = 30;
   const ECount = 42;
   TVertex V[VCount] = {
                           //Парус
                           {-20, -20, 30, 1},  //0
                           {-20, -20, 70, 1},  //1
                           {-20, 20, 70, 1},   //2
                           {-20, 20, 30, 1},   //3
                           //Мачта
                           {-20, 0, 10, 1},    //4
                           {-20, 0, 80, 1},    //5
                           //Каюта
                           {10, -10, 10, 1},   //6
                           {10, -10, 20, 1},   //7
                           {60, -10, 20, 1},   //8
                           {60, -10, 10, 1},   //9
                           {10, 10, 10, 1},    //10
                           {10, 10, 20, 1},    //11
                           {60, 10, 20, 1},    //12
                           {60, 10, 10, 1},    //13
                           //Корпус
                           {-60, -20, 0, 1},   //14
                           {-60, -20, 10, 1},  //15
                           {60, -20, 10, 1},   //16
                           {60, -20, 0, 1},    //17

                           {-60, 20, 0, 1},    //18
                           {-60, 20, 10, 1},   //19
                           {60, 20, 10, 1},    //20
                           {60, 20, 0, 1},     //21

                           {-60, -10, -10, 1}, //22
                           {-60, 10, -10, 1},  //23
                           {60, -10, -10, 1},  //24
                           {60, 10, -10, 1},   //25
                           //Нос
                           {90, 0, 20, 1},     //26 - Передняя часть
                           {80, 0, 10, 1},     //27
                           {80, 0, 10, 1},     //28
                           {0, 0, 0, 1}        //29 - центр
                        };
   /*/Ребра фигуры/*/
   TEdge E[ECount] = {
                     {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {6, 7}, {7, 8}, {8, 9}, {9, 6},
                     {10, 11}, {11, 12}, {12, 13}, {13, 10}, {6, 10}, {7, 11}, {8, 12}, {9, 13},
                     {14, 15}, {15, 16}, {16, 17}, {18, 19}, {19, 20}, {20, 21}, {15, 19}, {14, 22},
                     {22, 23}, {23, 18}, {17, 24}, {24, 25}, {25, 21}, {14, 17}, {22, 24}, {23, 25},
                     {18, 21}, {28, 26}, {16, 27}, {20, 27}, {21, 27}, {17, 27}, {24, 27}, {25, 27}};
/*/-----------------------------------------------------------------------/*/
/*/Необходимые матрицы/*/
//----------------------
//Матрица перехода к мировым координатам
   TTransform M= {
                     {    1,    0,    0,  0},
                     {    0,    1,    0,  0},
                     {    0,    0,    1,  0},
                     {   -100, -200, -125, 1}
                  };
//----------------------
//Перспективное проектирование
   const double Xs = 1500; //Точка наблюдения на оси x

//Матрица перспективного проектирования
   TTransform P =   {
                     {0, 0, 0, -1/Xs},
                     {0, 1, 0,     0},
                     {0, 0, 1,     0},
                     {0, 0, 0,     1}
                    };
//----------------------
//Переход к экранной системе координат

//Поворот вокруг оси Y на -90 градусов
  TTransform Cy = {
                     {0, 0, -1, 0},
                     {0, 1,  0, 0},
                     {1, 0,  0, 0},
                     {0, 0,  0, 1}
                  };

//Поворот воруг оси Z на 90 градусов
  TTransform Cz = {
                     {0, -1, 0,  0},
                     {1,  0,  0, 0},
                     {0,  0,  1, 0},
                     {0,  0,  0, 1}
                  };

//Переход в начало координат
  TTransform Ct = {
                     {1,  0, 0,  0},
                     {0,  1,  0, 0},
                     {0,  0,  1, 0},
                     {0,  0,  0, 1}
                  };

//[C] := [Cy]*[Cz]*[Ct]
  TTransform C;
//----------------------
//Масштабирование
   //Коэфициент увеличения
   const double K = 1.1;
   //Увеличение
   TTransform S1 = {
                     {K, 0, 0, 0},
                     {0, K, 0, 0},
                     {0, 0, K, 0},
                     {0, 0, 0, 1}
                   };
   //Уменьшение
   TTransform S2 = {
                     {1/K, 0, 0, 0},
                     {0, 1/K, 0, 0},
                     {0, 0, 1/K, 0},
                     {0, 0, 0,   1}
                   };
//----------------------
//Поворот
   //Количество поворотов
   double CountReturn = 45;
   double Angle = M_PI / 45;
   //Вокруг Х
   TTransform RX = {
                     {1,         0,           0, 0},
                     {0,  cos(Angle), sin(Angle), 0},
                     {0, -sin(Angle), cos(Angle), 0},
                     {0,           0,          0, 1}
                   };
  //Вокруг Y
  TTransform RY = {
                     {cos(Angle), 0, -sin(Angle), 0},
                     {         0, 1,           0, 0},
                     {sin(Angle), 0, cos(Angle), 0},
                     {         0, 0,          0, 1}
                   };
  //Вокруг Z
  TTransform RZ = {
                     { cos(Angle), sin(Angle), 0, 0},
                     {-sin(Angle), cos(Angle), 0, 0},
                     {          0,          0, 1, 0},
                     {          0,          0, 0, 1}
                   };
//----------------------
//Перенос
   //Величина переноса
   const double d = 5;
   //Матрица переноса
   TTransform Transport = {
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}
                   };
/*/-----------------------------------------------------------------------/*/
/*/Вспомогательные функции для работы с матрицами/*/
/*/-----------------------------------------------------------------------/*/
//Приравнивание матриц
void Copy(TVertex *CopyMatrix, TVertex *OrigMatrix, unsigned short int Size)
   {
      for (int i = 0; i < Size/32; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//Для TTransform
void Copy(TTransform CopyMatrix,TTransform OrigMatrix)
   {
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//Сложное преобразование координат
//[T]:=[T1]*[T2]
void CombineTransforms(TTransform T, const TTransform T1, const TTransform T2)
   {
   void Copy(TTransform, TTransform);
      TTransform Tmp;
      //Перемножим [T1] и [T2]
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            Tmp[i][j] = 0;
            for (int k = 0; k < 4; k++)
               Tmp[i][j] = Tmp[i][j] + T1[i][k] * T2[k][j];
         }
      //Присвоить ответ
      Copy(T,Tmp);
   }

//Осуществляет преобразование [T]: [TV] = [V]*[T]
void ApplyTransform(TVertex *VRet, TVertex *_V, const TTransform T, unsigned short int Size)
   {
      TVertex VT;
  //Пройдём по всем вершинам
  for (int i = 0; i < Size/32; i++)
      {
         //Вычислим координаты i - ой вершины
         for (int j = 0; j < 4; j++)
            {
               VT[j] = 0;
               //координаты j - ой вершины
               for (int k = 0; k < 4; k++)
                  VT[j] = VT[j] + _V[i][k] * T[k][j];
            }
         //Переместим координаты вершины в массив
         for (int z = 0; z < 4; z++)
            {VRet[i][z] = VT[z];}
      }
   }

//Нормализация кординат
void NormalizeCoordinates(TVertex *_V, unsigned short int Size)
   {
      double H;
      for (int i = 0; i < Size/32; i++)
         {
            H = _V[i][3];             //Сохраняем значение H
            _V[i][0] = _V[i][0] / H;  //Вычисляем значение X
            _V[i][1] = _V[i][1] / H;  //Вычисляем Y
            _V[i][2] = _V[i][2] / H;  //Вычисляем Z
            _V[i][3] = 1;             //Присваеваем H значение 1
         }
   }

//Рисование каркасного изображения
void DrawWire(TCanvas *Canv, TVertex *_V, TEdge *E, unsigned short int SizeV, unsigned short int SizeE)
   {
      //Нарисуем все рёбра
      for (int i = 0; i < SizeE/4; i++)
         {
         //Проверка
         if ((E[i][0] > SizeV/32) || (E[i][1] > SizeV/32))
            {
               ShowMessage("Выход за границу массива вершин");
               return;
            }
         Canv->MoveTo(Round(_V[E[i][0]] [0]), Round(_V[E[i][0]] [1]));
         Canv->LineTo(Round(_V[E[i][1]] [0]), Round(_V[E[i][1]] [1]));
         }
   }
/*/-----------------------------------------------------------------------/*/
/*/Функция округления/*/
double Round(double Var)
   {
      int Help = Var;
      double VarHelp = Var - Help;
      if (VarHelp > 0.5) {return(int(Var+1));}
      else {return(int(Var));}
   }
/*/-----------------------------------------------------------------------/*/
void __fastcall TForm1::FormCreate(TObject *Sender)
{
//Это второй способ при котором изображение переходило ещё и из лкальной в мировую
//ApplyTransform(V, V, M, sizeof(V));
  Ct[3][0] = int(ClientWidth/2);
  Ct[3][1] = int(ClientHeight/2);

  CombineTransforms(C, Cy, Cz); //[C]:=[Cy]*[Cz]
  CombineTransforms(C, C, Ct);  //[C]:=[C]*[Ct]
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
  //Вывод текста
  Canvas->Font->Color = clBlue;
  Canvas->Brush->Color = clYellow;
  Canvas->Font->Height = 14;
  Canvas->Font->Name = "Arial";
  Canvas->TextOutA(0, ClientHeight-70, "Управление:");
  Canvas->TextOutA(0, ClientHeight-56, "Стрелки - перенос по осям; '+', '-' масштабирование");
  Canvas->TextOutA(0, ClientHeight-42, "Space - вращение вокруг всех осей/остановка вращения");
  Canvas->TextOutA(0, ClientHeight-28, "X, Y, Z - вращение по одноимённым осям/остановка вращения");
  Canvas->TextOutA(0, ClientHeight-14, "Back Space - изменение угла вращения");


  TVertex VP[VCount];
  //yOz: [VP]:=[V]*[P]
  ApplyTransform(VP, V, P, sizeof(VP));

  //[VP]:=[VP]*[C]
  ApplyTransform(VP, VP, C, sizeof(VP));

  //Нормализация
  NormalizeCoordinates(VP, sizeof(VP));

  Canvas->Pen->Color = clBlack;
  DrawWire(Canvas, VP, E, sizeof(VP), sizeof(E));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   //Увеличение
   if (Key == VK_ADD)
      {
         Transport[3][0] = -V[29][0];
         Transport[3][1] = -V[29][1];
         Transport[3][2] = -V[29][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         ApplyTransform(V, V, S1, sizeof(V));
         Transport[3][0] = -Transport[3][0];
         Transport[3][1] = -Transport[3][1];
         Transport[3][2] = -Transport[3][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
   //Уменьшение
   if (Key == VK_SUBTRACT)
      {
         Transport[3][0] = -V[29][0];
         Transport[3][1] = -V[29][1];
         Transport[3][2] = -V[29][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         ApplyTransform(V, V, S2, sizeof(V));
         Transport[3][0] = -Transport[3][0];
         Transport[3][1] = -Transport[3][1];
         Transport[3][2] = -Transport[3][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
   //Поворот воркуг оси Х
   if (Key == VK_SPACE)
      {
         if (Around)
            {
               Timer1->Enabled = false;
               Around = false;
            }
         else
            {
               Timer1->Enabled = true;
               Around = true;
            }
      }
   //Перенос по оси Y - влево
   if (Key == VK_LEFT)
      {
         Timer1->Enabled = false;
         Transport[3][0] = 0;
         Transport[3][1] = -d;
         Transport[3][2] = 0;
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
         Timer1->Enabled = true;
      }
   //Перенос по оси y - вправо
   if (Key == VK_RIGHT)
      {
         Timer1->Enabled = false;
         Transport[3][0] = 0;
         Transport[3][1] = d;
         Transport[3][2] = 0;
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
         Timer1->Enabled = true;
      }
   //Перенос по оси Z - вниз
   if (Key == VK_DOWN)
      {
         Timer1->Enabled = false;
         Transport[3][0] = 0;
         Transport[3][1] = 0;
         Transport[3][2] = -d;
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
         Timer1->Enabled = true;
      }
   //Перенос по оси Z - вверх
   if (Key == VK_UP)
      {
         Transport[3][0] = 0;
         Transport[3][1] = 0;
         Transport[3][2] = d;
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
   //Изменение направление угла
   if (Key == VK_BACK)
      {
         Angle = - Angle;
         RX[1][1] = cos(Angle); RX[1][2] = sin(Angle);
         RX[2][1] = -sin(Angle); RX[2][2] = cos(Angle);

         RY[0][0] = cos(Angle);  RY[0][2] = -sin(Angle);
         RY[2][0] = sin(Angle); RY[2][2] = cos(Angle);

         RZ[0][0] = cos(Angle); RZ[0][1] = -sin(Angle);
         RZ[1][0] = sin(Angle); RZ[1][1] = cos(Angle);
      }
      
   //Вращательное движение вокруг Х
   if ( (Key == int('X')) || (Key == int('x')) )
      {
      if (AroundX)
            {
               Timer1->Enabled = false;
               AroundX = false;
            }
         else
            {
               Timer1->Enabled = true;
               AroundX = true;
            }
         Around = false;
         AroundY = false;
         AroundZ = false;
      }

   //Вращательное движение вокруг Y
   if ( (Key == int('Y')) || (Key == int('y')) )
      {
      if (AroundY)
            {
               Timer1->Enabled = false;
               AroundY = false;
            }
         else
            {
               Timer1->Enabled = true;
               AroundY = true;
            }
         Around = false;
         AroundX = false;
         AroundZ = false;
      }

   //Вращательное движение вокруг Z
   if ( (Key == int('Z')) || (Key == int('z')) )
      {
      if (AroundZ)
            {
               Timer1->Enabled = false;
               AroundZ = false;
            }
         else
            {
               Timer1->Enabled = true;
               AroundZ = true;
            }
         Around = false;
         AroundX = false;
         AroundY = false;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
   Ct[3][0] = int(ClientWidth/2);
   Ct[3][1] = int(ClientHeight/2);

   CombineTransforms(C, Cy, Cz); //[C]:=[Cy]*[Cz]
   CombineTransforms(C, C, Ct);  //[C]:=[C]*[Ct]
   Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   //Оборот вокруг всех кооринатных осей на один и тот же угол
   if (Around)
      {
         Transport[3][0] = -V[29][0];
         Transport[3][1] = -V[29][1];
         Transport[3][2] = -V[29][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         ApplyTransform(V, V, RX, sizeof(V));
         ApplyTransform(V, V, RY, sizeof(V));
         ApplyTransform(V, V, RZ, sizeof(V));
         Transport[3][0] = -Transport[3][0];
         Transport[3][1] = -Transport[3][1];
         Transport[3][2] = -Transport[3][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
   //Оборот вокруг Х
   if (AroundX)
      {
         Transport[3][0] = -V[29][0];
         Transport[3][1] = -V[29][1];
         Transport[3][2] = -V[29][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         ApplyTransform(V, V, RX, sizeof(V));
         Transport[3][0] = -Transport[3][0];
         Transport[3][1] = -Transport[3][1];
         Transport[3][2] = -Transport[3][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
    //Оборот вокруг Y
   if (AroundY)
      {
         Transport[3][0] = -V[29][0];
         Transport[3][1] = -V[29][1];
         Transport[3][2] = -V[29][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         ApplyTransform(V, V, RY, sizeof(V));
         Transport[3][0] = -Transport[3][0];
         Transport[3][1] = -Transport[3][1];
         Transport[3][2] = -Transport[3][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
    //Оборот вокруг Z
   if (AroundZ)
      {
         Transport[3][0] = -V[29][0];
         Transport[3][1] = -V[29][1];
         Transport[3][2] = -V[29][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         ApplyTransform(V, V, RZ, sizeof(V));
         Transport[3][0] = -Transport[3][0];
         Transport[3][1] = -Transport[3][1];
         Transport[3][2] = -Transport[3][2];
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
}
//---------------------------------------------------------------------------

