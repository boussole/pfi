//---------------------------------------------------------------------------
#pragma hdrstop
#include "Matrix_3d.h"
#include "ClassTMatrix.h"
#include "Include\\TemplateList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*/-----------------------------------------------------------------------/*/
/*/Модуль содержит подпрограммы для работы с матрицами/*/
/*/-----------------------------------------------------------------------/*/
/*/Используемые типы данных/*/
//----------------------------
  //тип данных для описания одной вершины в пространстве
  //в однородных координатах
  typedef double TVertex[4];
//----------------------------
  //массив вершин полигональной поверхности
//  typedef TVertex *TVertices;
//----------------------------
  //тип данных для описания матрицы преобразования координат
  //в пространстве
  typedef double TTransform[4][4];
//----------------------------
  //TMatrix - класс произвольной матрицы
/*/-----------------------------------------------------------------------/*/
/*/Прототипы подпрограмм/*/
void Copy(TVertex *, TVertex *, unsigned int);
void Copy(TTransform, TTransform);
void Copy(TVertex, TVertex);
void Copy(TVertex *, TLIST);
//----------------------------
//вычисляет матрицу сложного преобразования координат
//[T]:=[T1]*[T2]
void CombineTransforms(TTransform, const TTransform, const TTransform);
//----------------------------
//осуществляет преобразование матрицы [V] исходных координат
//вершин объекта, умножая ее на матрицу [T]: [V1] = [V]*[T]
void ApplyTransform(TVertex *, TVertex *, const TTransform, unsigned int);
//----------------------------
//осуществляет нормализацию однородных координат вершин
//фигуры в матрице V, деля координаты каждой вершины на четвертую
//координату H
void NormalizeCoordinates(TVertex *, unsigned int);
//----------------------------
//возвращает матрицу, обратную к T
void CalcInverseTransform(const TTransform, TTransform);
//----------------------------
//возвращает минор элемента в i-й строке j-ом столбце квадратной матрицы T
//TMatrix *GetMinor(const TMatrix *T, unsigned int i, unsigned int j);
void GetMinor(const TMatrix *T, unsigned int i, unsigned int j, TMatrix *);
//----------------------------
//вычисляет определитель квадратной матрицы T
double CalcDet(const TMatrix *);
//----------------------------
//возвращает транспонированную матрицу T
void TransposeTransformMatrix(const TTransform, TTransform);
/*/-----------------------------------------------------------------------/*/
/*/Описание функций/*/
/*/-----------------------------------------------------------------------/*/
//Копирование матриц
void Copy(TVertex *CopyMatrix, TLIST *OrigMatrix)
   {
      for (int i = 0; i < OrigMatrix->GetCount(); i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix->GetValue(i, j);
         }
   }
//Копирование матриц
void Copy(TVertex *CopyMatrix, TVertex *OrigMatrix, unsigned int Size)
   {
      for (int i = 0; i < Size/32; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//------------------
//Копирование матриц
void Copy(TVertex CopyMatrix, TVertex OrigMatrix)
   {
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[j] = OrigMatrix[j];
         }
   }
//--------------------------------
//Для TTransform
void Copy(TTransform CopyMatrix,TTransform OrigMatrix)
   {
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//--------------------------------
//Вычисляет матрицу сложного преобразования координат
//[T]:=[T1]*[T2]
void CombineTransforms(TTransform T, const TTransform T1, const TTransform T2)
   {
   void Copy(TTransform, TTransform);
      TTransform Tmp;
      //Умножение [T1] на [T2]
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            Tmp[i][j] = 0;
            for (int k = 0; k < 4; k++)
               Tmp[i][j] = Tmp[i][j] + T1[i][k] * T2[k][j];
         }
      //Присвоим ответ
      Copy(T,Tmp);
   }
//--------------------------------
//осуществляет преобразование матрицы [V] исходных координат
//вершин объекта, умножая ее на матрицу [T]: [V1] = [V]*[T]
void ApplyTransform(TVertex *VRet, TVertex *_V, const TTransform T, unsigned int Size)
   {
      TVertex VT;
  //пройдем по всем вершинам
  for (int i = 0; i < Size/32; i++)
      {
         //вычислим координаты i-й вершины
         for (int j = 0; j < 4; j++)
            {
               VT[j] = 0;
               //вычислим j-ую координату
               for (int k = 0; k < 4; k++)
                  VT[j] = VT[j] + _V[i][k] * T[k][j];
            }
         //переместим координаты i-ой вершины из временного
         //массива VT в массив V
         for (int z = 0; z < 4; z++)
            {VRet[i][z] = VT[z];}
      }
   }
//--------------------------------
//осуществляет нормализацию однородных координат вершин
//фигуры в матрице V, деля координаты каждой вершины на четвертую
//координату H
void NormalizeCoordinates(TVertex *_V, unsigned int Size)
   {
      double H;
      for (int i = 0; i < Size/32; i++)
         {
            H = _V[i][3];             //координата H
            _V[i][0] = _V[i][0] / H;  //координата X
            _V[i][1] = _V[i][1] / H;  //координата Y
            _V[i][2] = _V[i][2] / H;  //координата Z
            _V[i][3] = 1;             //координата H становится равной 1
         }
   }
//--------------------------------/*/
//возвращает минор элемента в i-й строке j-ом столбце
//квадратной матрицы T
void GetMinor(const TMatrix *T, unsigned int i, unsigned int j, TMatrix *Minor)
{
  unsigned int n;
  //порядок матрицы T
  n = T->Length();
  //минор M матрицы T на порядок меньше
  Minor->SetLength(n-1, n-1);
  //скопируем все элементы минора из матрицы T
  for (int u = 0; u < n-1; u++)
  for (int v = 0; v < n-1; v++)
   {
    if (u < i)
      {
         if (v < j)
            {Minor->SetValue(u, v) = T->GetValue(u, v);}
         else
            {Minor->SetValue(u, v) = T->GetValue(u, v + 1);}
      }
    else
      {
         if (v < j)
            {Minor->SetValue(u, v) = T->GetValue(u + 1, v);}
         else
            {Minor->SetValue(u, v) = T->GetValue(u + 1, v + 1);}
      }
    }
}
//--------------------------------
//вычисляет определитель квадратной матрицы T
double CalcDet(const TMatrix *_T)
{
  unsigned short int m, n;
  TMatrix *_P = new TMatrix;                          //Создание объекта _P
  double Det, s;
  //количество строк и столбцов матрицы T
  m = _T->SizeI(); n = _T->SizeJ();
  //неквадратная матрица не имеет определителя
  if (m != n)
   {
      delete _P;
      return 0;
   }

  //определитель матрицы порядка 2 можно вычислить сразу
  if (m == 2)
   {
      Det = (_T->GetValue(0, 0) * _T->GetValue(1, 1)) - (_T->GetValue(1, 0) * _T->GetValue(0, 1));
      delete _P;
      return Det;
   }

  //будем считать определитель как сумму элементов 1-й строки
  //матрицы, умноженных на их алгебраические дополнения
//  _P->SetLength(m - 1, n - 1);
  Det = 0; s = 1;
  for (int j = 0; j < n; j++)
   {
      //вычислим минор элемента (0, j)
      GetMinor(_T, 0, j, _P);                         //Присвоение адреса объекта указателю P
      Det = Det + s * _T->GetValue(0,j) * CalcDet(_P);
      //знак у следующего слагаемого меняется на противоположный
      s = -s;
   }
  delete _P;                                          //Уничтожили объект _P
  return Det;
}
//--------------------------------
//возвращает матрицу, обратную к T
void CalcInverseTransform(const TTransform T, TTransform T_1)
   {
      TMatrix *Help = new TMatrix;  //Создание объекта Help
      TMatrix *M = new TMatrix;     //Создание объекта M
      double detT;
      double A;
  //подготовим матрицу T для вычисления определителя: P <-- T
  Help->SetLength(4, 4);            //Создание матрицы в динамической памяти-
  for (int i = 0; i < 4; i++)
  for (int j = 0; j < 4; j++)
   {
      Help->SetValue(i, j) = T[i][j];
   }
  //вычислим определитель матрицы T
  detT = CalcDet(Help);
  //вычислим все элементы матрицы, обратной к T
  for (int i = 0; i < 4; i++)
  for (int j = 0; j < 4; j++)
   {
    GetMinor(Help, j, i, M); //минор элемента в строке j столбце i
    //если сумма номера строки и столбца четная, то A = +M
    if ( ((i+j) % 2) == 0 )
      {A = CalcDet(M);}
    //иначе A = -M
    else
      {A = - CalcDet(M);}
    T_1[i][j] = A / detT;
   }
      delete Help;      //уничтожение объекта Help
      Help = NULL;
      delete M;         //уничтожение объекта M
      M = NULL;
   }
//--------------------------------------
//возвращает транспонированную матрицу T
void TransposeTransformMatrix(const TTransform T, TTransform TT)
   {
      TTransform Cpy;
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {Cpy[i][j] = T[j][i];}
      Copy(TT, Cpy);
   }
/*/----------------------------конец---------------------------------------/*/
