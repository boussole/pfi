//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TurnpikeUnit.h"
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
   /*/Используемые типы данных/*/
   //двумерный массив для представления матриц
   //преобразований координат размером 3x3
   typedef double TTransformation[3][3];
   //одномерный массив для представления матрицы
   //однородных координат одной вершины
   typedef double TVertex[3];
/*/-----------------------------------------------------------------------/*/
/*/Прототипы функций/*/
void DrawRedEye(TCanvas *, TVertex *);
void DrawTurnPike(TCanvas *, TVertex *);
void ApplyTransform(TVertex *, const TVertex *,	const TTransformation, const unsigned int);
void CombineTransform(TTransformation, const TTransformation, const TTransformation);
void Copy(TVertex *,TVertex *, unsigned int);
/*/-----------------------------------------------------------------------/*/
   /*/Управляющие флаги/*/
   bool Down = false, Up = false;
   /*/Данные, не изменяющихся объектов/*/
   //Точка вращения светофора
   const SignalDx = 70;
   const SignalDy = 210;
   //Точка вращения
   const TurnpikeDx = 170;
   const TurnpikeDy = 230;

   //Угол поворота шлагбаума
   const double Phi = M_PI/130;
   double CurrentAngle = M_PI/2;
   //Координаты деталей светофора
   TRect SignDown = Rect(60, 260, 80, 340);
   TPoint SignUp[3] = {
                        Point(40, 160),
                        Point(100, 260),
                        Point(40, 20)
                   };
   int Eye[4][2] = {
                     {60, 180},
                     {80, 200},
                     {60, 220},
                     {80, 240}
                  };
   //Координаты деталей шлагбаума
   TPoint TurnDown[4] = {
                           Point(120, 340),
                           Point(160, 260),
                           Point(180, 260),
                           Point(220, 340)
                        };
   TRect TurnUp[2] = {
                        Rect(160, 240, 180, 260),
                        Rect(160, 220, 180, 240)
                     };
   TPoint Cross[4] = {
                        Point(160, 240),
                        Point(180, 260),
                        Point(160, 260),
                        Point(180, 240)
                     };
/*/-----------------------------------------------------------------------/*/
/*/Координаты изменяющихся объектов/*/
/*/Матрица однородных координат, характеризующая красный свет светофора/*/
   TVertex RedEye[2] = {
                           {60, 180, 1},
                           {80, 200, 1}
                       };
/*/Матрица однородных координат, характеризующая шлагбаум/*/
/*/Матрица компенсации по вертикали/*/
   TVertex TurnPikeVert[48] = {
                              {160, 20, 1}, {180, 20, 1}, {180, 40, 1}, {160, 40, 1},      //1 - ый квадрат
                              {160, 40, 1}, {180, 40, 1}, {180, 60, 1}, {160, 60, 1},
                              {160, 60, 1}, {180, 60, 1}, {180, 80, 1}, {160, 80, 1},
                              {160, 80, 1}, {180, 80, 1}, {180, 100, 1}, {160, 100, 1},
                              {160, 100, 1}, {180, 100, 1}, {180, 120, 1}, {160, 120, 1},
                              {160, 120, 1}, {180, 120, 1}, {180, 140, 1}, {160, 140, 1},
                              {160, 140, 1}, {180, 140, 1}, {180, 160, 1}, {160, 160, 1},
                              {160, 160, 1}, {180, 160, 1}, {180, 180, 1}, {160, 180, 1},
                              {160, 180, 1}, {180, 180, 1}, {180, 200, 1}, {160, 200, 1},
                              {160, 200, 1}, {180, 200, 1}, {180, 220, 1}, {160, 220, 1},
                              {160, 220, 1}, {180, 220, 1}, {180, 240, 1}, {160, 240, 1},
                              {160, 240, 1}, {180, 240, 1}, {180, 260, 1}, {160, 260, 1}//12 - ый квадрат
                              };
/*/Матрица компенсации по горизонтали/*/
   TVertex TurnPikeGor[48] = {
                              {360, 220, 1}, {380, 220, 1}, {380, 240, 1}, {360, 240, 1},    //1 - ый квадрат
                              {340, 220, 1}, {360, 220, 1}, {360, 240, 1}, {340, 240, 1},
                              {320, 220, 1}, {340, 220, 1}, {340, 240, 1}, {320, 240, 1},
                              {300, 220, 1}, {320, 220, 1}, {320, 240, 1}, {300, 240, 1},
                              {280, 220, 1}, {300, 220, 1}, {300, 240, 1}, {280, 240, 1},
                              {260, 220, 1}, {280, 220, 1}, {280, 240, 1}, {260, 240, 1},
                              {240, 220, 1}, {260, 220, 1}, {260, 240, 1}, {240, 240, 1},
                              {220, 220, 1}, {240, 220, 1}, {240, 240, 1}, {220, 240, 1},
                              {200, 220, 1}, {220, 220, 1}, {220, 240, 1}, {200, 240, 1},
                              {180, 220, 1}, {200, 220, 1}, {200, 240, 1}, {180, 240, 1},
                              {160, 220, 1}, {180, 220, 1}, {180, 240, 1}, {160, 240, 1},
                              {140, 220, 1}, {160, 220, 1}, {160, 240, 1}, {140, 240, 1}    //12 - ый квадрат
};
/*/-----------------------------------------------------------------------/*/
/*/Матрицы преобразования/*/
//матрица перехода к системе координат с центром в точке (Хо, Yo)
//-------------
//Для светофора
    TTransformation PS = {
                           { 1, 0, 0},
                           { 0, 1, 0},
				               {-SignalDx, -SignalDy, 1}
                        };
//-------------
//Для шлагбаума
   TTransformation PT = {
                           { 1, 0, 0},
                           { 0, 1, 0},
				               {-TurnpikeDx, -TurnpikeDy, 1}
                        };
//-------------
//Отражение светофора
   TTransformation M = {
                           {1,  0, 0},
                           {0, -1, 0},
                           {0,  0, 1}
                       };
//-------------
//матрица преобразования поворота на угол Phi
    TTransformation R = {
                           {cos(Phi), sin(Phi), 0},
				               {-sin(Phi), cos(Phi) ,0},
				               {0, 0, 1}
                        };
//Обратная матрица поворота
   TTransformation Rback = {
                           {cos(Phi), -sin(Phi), 0},
				               {sin(Phi), cos(Phi) ,0},
				               {0, 0, 1}
                        };
//-------------
//матрица перехода к исходной системе координат
//Для светофора
    TTransformation PSback = {
                           { 1, 0, 0},
                           { 0, 1, 0},
				               {SignalDx, SignalDy, 1}
                              };
//-------------
//Для шлагбаума
    TTransformation PTback = {
                           { 1, 0, 0},
                           { 0, 1, 0},
				               {TurnpikeDx, TurnpikeDy, 1}
                              };
//-------------
//Рабочая матрица шлагбаума
   TVertex TurnPike[48];
//-------------
//матрица сложного преобразования для одновременного поворота и
//-------------
//Отражение светофора
   TTransformation TS;
//-------------
//Поворот шлагбаума
   TTransformation TT;
/*/-----------------------------------------------------------------------/*/
/*/Рабочие функции/*/
/*/-----------------------------------------------------------------------/*/
//Рисование красного света с помощью матрицы RedEye
void DrawRedEye(TCanvas *Canv, TVertex *Matrix)
   {
      Canv->Pen->Color = clRed;
      Canv->Brush->Color = clRed;
      Canv->Ellipse(Matrix[0][0], Matrix[0][1], Matrix[1][0], Matrix[1][1]);
   }
/*/-----------------------------------------------------------------------/*/
//Рисование шлагбаума
void DrawTurnPike(TCanvas *Canv, TVertex *Matrix)
   {
      bool white = false;
      TPoint Help[4];
      Canv->Pen->Color = clBlack;
      Canv->Brush->Color = clBlack;
      for (int i = 0; i < 48; i+=4)
         {
            Help[0] = Point(Matrix[i][0],   Matrix[i][1]);
            Help[1] = Point(Matrix[i+1][0], Matrix[i+1][1]);
            Help[2] = Point(Matrix[i+2][0], Matrix[i+2][1]);
            Help[3] = Point(Matrix[i+3][0], Matrix[i+3][1]);
            if (i != 44)
            {
            if (white)
               {
                  Canv->Brush->Color = clWhite;
                  white = false;
               }
            else
               {
                  Canv->Brush->Color = clBlack;
                  white = true;
               }

            Canv->Polygon(Help, 3);
            }
            else
            {
            Canv->Brush->Color = clRed;
            Canv->Polygon(Help, 3);
            }
         }
   }
/*/-----------------------------------------------------------------------/*/
/*/Подпрограммы для работы с матрицами/*/
/*/-----------------------------------------------------------------------/*/
//осуществляет преобразование координат вершин (типа double) фигуры,
//переданных в массиве V, с помощью матрицы Т: [VI]:=[V]*[Т]
void ApplyTransform(TVertex *VI, const TVertex *V, const TTransformation T, const unsigned int Size)
   {
    TVertex P;
    //пройдем по всем вершинам фигуры
    for (int i = 0; i < Size/24; i++)
      {
	   //вычислим и поместим в Р преобразованные координаты i-ой вершины
	   for (int j = 0; j < 3; j++)
         P[j] = V[i][0] * T[0][j] + V[i][1] * T[1][j] + V[i][2] * T[2][j];
	      //сохраним вычисленные координаты 1-й вершины в массиве VI
         VI[i][0] = P[0]; VI[i][1] = P[1]; VI[i][2] = P[2];
      }
   }
//----------
//Вычисляет матрицу общего преобразования Т, перемножая матрицы Т1 и Т2
//составляющих его преобразований
void CombineTransform(TTransformation T, const TTransformation T_, const TTransformation T__)
   {
    //вычислим и поместим в T матрицу общего преобразования
    for (int i = 0; i < 3; i++) 	//пройдем по всем строкам
    for (int j = 0; j < 3; j++) 	//пройдем по всем столбцам
      {
      T[i][j] = T_[i][0] * T__[0][j] + T_[i][1] * T__[1][j] + T_[i][2] * T__[2][j];
      }
   }
/*/-----------------------------------------------------------------------/*/
/*/Копирование матрицы/*/
void Copy(TVertex *CopyMatrix,TVertex *OrigMatrix, unsigned int Size)
   {
      for (int i = 0; i < Size/24; i++)
      for (int j = 0; j < 3; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
/*/-----------------------------------------------------------------------/*/
/*/Обработчик OnPaint - рисование объектов/*/
void __fastcall TForm1::FormPaint(TObject *Sender)
{
   /*/-------------------------------/*/
   /*/Вывод надписи/*/
   Canvas->Font->Color = clBlue;
   Canvas->Brush->Color = clBtnFace;
   Canvas->Font->Name = "TimesNewRoman";
   Canvas->Font->Style = TFontStyles() << fsUnderline;
   Canvas->Font->Size = 14;
   Canvas->TextOutA(10, 350, "Управление");
   Canvas->Font->Style = TFontStyles() >> fsUnderline;
   Canvas->TextOutA(20, 380, "Стрелка вниз/вверх - опустить/поднять");
   Canvas->TextOutA(20, 410, "Space - остановка движения шлагбаума");
   /*/-------------------------------/*/
   /*/Рисование неподвиждных объектов/*/
   Canvas->Pen->Color = clBlack;
   Canvas->Brush->Color = clGray;
   Canvas->Rectangle(SignDown);
   Canvas->RoundRect(SignUp[0].x, SignUp[0].y, SignUp[1].x, SignUp[1].y, SignUp[2].x, SignUp[2].y);
   Canvas->Brush->Color = clBlack;
   Canvas->Ellipse(Eye[0][0], Eye[0][1], Eye[1][0], Eye[1][1]);
   Canvas->Ellipse(Eye[2][0], Eye[2][1], Eye[3][0], Eye[3][1]);
   Canvas->Brush->Color = clGray;
   Canvas->Polygon(TurnDown, 3);
   Canvas->Brush->Color = clWhite;
   Canvas->Rectangle(TurnUp[0]);
   Canvas->MoveTo(Cross[0].x, Cross[0].y);
   Canvas->LineTo(Cross[1].x, Cross[1].y);
   Canvas->MoveTo(Cross[2].x, Cross[2].y);
   Canvas->LineTo(Cross[3].x, Cross[3].y);
   Canvas->Brush->Color = clBlack;
   Canvas->Rectangle(TurnUp[1]);
   /*/Изменяющиеся объекты/*/
   DrawTurnPike(Canvas, TurnPike);
   if (Timer2->Enabled)
   {DrawRedEye(Canvas, RedEye);}
}
//---------------------------------------------------------------------------
/*/Обработчик нажатой клавиши/*/
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key == VK_DOWN)
      {
         if (CurrentAngle > 0)
            {
               Up = false;
               Down = true;
               Timer1->Enabled = true;
               Timer2->Enabled = true;
            }
      }
   if (Key == VK_UP)
      {
         if (CurrentAngle < M_PI/2)
            {
               Down = false;
               Up = true;
               Timer1->Enabled = true;
               Timer2->Enabled = true;
            }
      }
   if (Key == VK_SPACE)
      {
               Up = false;
               Down = false;
               Timer1->Enabled = false;
      }
}
//---------------------------------------------------------------------------
/*/Шлагбаум/*/
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
   if (Down)
      {
         if (CurrentAngle <= 0)
            {
               Timer1->Enabled = false;
               Copy(TurnPike, TurnPikeGor, sizeof(TurnPikeGor));
               CurrentAngle = 0;
               Refresh();
            }
         else
            {
               CombineTransform(TT, PT, R);
               CombineTransform(TT, TT, PTback);
               ApplyTransform(TurnPike, TurnPike, TT, sizeof(TurnPike));
               CurrentAngle -= Phi;
               Refresh();
            }
      }
   if (Up)
      {
        if (CurrentAngle >= M_PI/2)
            {
               Timer1->Enabled = false;
               Copy(TurnPike, TurnPikeVert, sizeof(TurnPikeVert));
               CurrentAngle = M_PI/2;
               Refresh();
            }
        else
            {
               CombineTransform(TT, PT, Rback);
               CombineTransform(TT, TT, PTback);
               ApplyTransform(TurnPike, TurnPike, TT, sizeof(TurnPike));
               CurrentAngle += Phi;
               Refresh();
            }
      }
}
//---------------------------------------------------------------------------
/*/Светофор/*/
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
   if (CurrentAngle != M_PI/2)
      {
         CombineTransform(TS, PS, M);
         CombineTransform(TS, TS, PSback);
         ApplyTransform(RedEye, RedEye, TS, sizeof(RedEye));
         OnPaint(this);
      }
   else
      {
        Timer2->Enabled = false;
        Refresh();
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   Copy(TurnPike, TurnPikeVert, sizeof(TurnPikeVert));
}
//---------------------------------------------------------------------------

