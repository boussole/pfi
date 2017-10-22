//---------------------------------------------------------------------------
#pragma hdrstop
#include "Matrix_3d.h"
#include "ClassTMatrix.h"
#include "Include\\TemplateList.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*/-----------------------------------------------------------------------/*/
/*/������ �������� ������������ ��� ������ � ���������/*/
/*/-----------------------------------------------------------------------/*/
/*/������������ ���� ������/*/
//----------------------------
  //��� ������ ��� �������� ����� ������� � ������������
  //� ���������� �����������
  typedef double TVertex[4];
//----------------------------
  //������ ������ ������������� �����������
//  typedef TVertex *TVertices;
//----------------------------
  //��� ������ ��� �������� ������� �������������� ���������
  //� ������������
  typedef double TTransform[4][4];
//----------------------------
  //TMatrix - ����� ������������ �������
/*/-----------------------------------------------------------------------/*/
/*/��������� �����������/*/
void Copy(TVertex *, TVertex *, unsigned int);
void Copy(TTransform, TTransform);
void Copy(TVertex, TVertex);
void Copy(TVertex *, TLIST);
//----------------------------
//��������� ������� �������� �������������� ���������
//[T]:=[T1]*[T2]
void CombineTransforms(TTransform, const TTransform, const TTransform);
//----------------------------
//������������ �������������� ������� [V] �������� ���������
//������ �������, ������� �� �� ������� [T]: [V1] = [V]*[T]
void ApplyTransform(TVertex *, TVertex *, const TTransform, unsigned int);
//----------------------------
//������������ ������������ ���������� ��������� ������
//������ � ������� V, ���� ���������� ������ ������� �� ���������
//���������� H
void NormalizeCoordinates(TVertex *, unsigned int);
//----------------------------
//���������� �������, �������� � T
void CalcInverseTransform(const TTransform, TTransform);
//----------------------------
//���������� ����� �������� � i-� ������ j-�� ������� ���������� ������� T
//TMatrix *GetMinor(const TMatrix *T, unsigned int i, unsigned int j);
void GetMinor(const TMatrix *T, unsigned int i, unsigned int j, TMatrix *);
//----------------------------
//��������� ������������ ���������� ������� T
double CalcDet(const TMatrix *);
//----------------------------
//���������� ����������������� ������� T
void TransposeTransformMatrix(const TTransform, TTransform);
/*/-----------------------------------------------------------------------/*/
/*/�������� �������/*/
/*/-----------------------------------------------------------------------/*/
//����������� ������
void Copy(TVertex *CopyMatrix, TLIST *OrigMatrix)
   {
      for (int i = 0; i < OrigMatrix->GetCount(); i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix->GetValue(i, j);
         }
   }
//����������� ������
void Copy(TVertex *CopyMatrix, TVertex *OrigMatrix, unsigned int Size)
   {
      for (int i = 0; i < Size/32; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//------------------
//����������� ������
void Copy(TVertex CopyMatrix, TVertex OrigMatrix)
   {
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[j] = OrigMatrix[j];
         }
   }
//--------------------------------
//��� TTransform
void Copy(TTransform CopyMatrix,TTransform OrigMatrix)
   {
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//--------------------------------
//��������� ������� �������� �������������� ���������
//[T]:=[T1]*[T2]
void CombineTransforms(TTransform T, const TTransform T1, const TTransform T2)
   {
   void Copy(TTransform, TTransform);
      TTransform Tmp;
      //��������� [T1] �� [T2]
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            Tmp[i][j] = 0;
            for (int k = 0; k < 4; k++)
               Tmp[i][j] = Tmp[i][j] + T1[i][k] * T2[k][j];
         }
      //�������� �����
      Copy(T,Tmp);
   }
//--------------------------------
//������������ �������������� ������� [V] �������� ���������
//������ �������, ������� �� �� ������� [T]: [V1] = [V]*[T]
void ApplyTransform(TVertex *VRet, TVertex *_V, const TTransform T, unsigned int Size)
   {
      TVertex VT;
  //������� �� ���� ��������
  for (int i = 0; i < Size/32; i++)
      {
         //�������� ���������� i-� �������
         for (int j = 0; j < 4; j++)
            {
               VT[j] = 0;
               //�������� j-�� ����������
               for (int k = 0; k < 4; k++)
                  VT[j] = VT[j] + _V[i][k] * T[k][j];
            }
         //���������� ���������� i-�� ������� �� ����������
         //������� VT � ������ V
         for (int z = 0; z < 4; z++)
            {VRet[i][z] = VT[z];}
      }
   }
//--------------------------------
//������������ ������������ ���������� ��������� ������
//������ � ������� V, ���� ���������� ������ ������� �� ���������
//���������� H
void NormalizeCoordinates(TVertex *_V, unsigned int Size)
   {
      double H;
      for (int i = 0; i < Size/32; i++)
         {
            H = _V[i][3];             //���������� H
            _V[i][0] = _V[i][0] / H;  //���������� X
            _V[i][1] = _V[i][1] / H;  //���������� Y
            _V[i][2] = _V[i][2] / H;  //���������� Z
            _V[i][3] = 1;             //���������� H ���������� ������ 1
         }
   }
//--------------------------------/*/
//���������� ����� �������� � i-� ������ j-�� �������
//���������� ������� T
void GetMinor(const TMatrix *T, unsigned int i, unsigned int j, TMatrix *Minor)
{
  unsigned int n;
  //������� ������� T
  n = T->Length();
  //����� M ������� T �� ������� ������
  Minor->SetLength(n-1, n-1);
  //��������� ��� �������� ������ �� ������� T
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
//��������� ������������ ���������� ������� T
double CalcDet(const TMatrix *_T)
{
  unsigned short int m, n;
  TMatrix *_P = new TMatrix;                          //�������� ������� _P
  double Det, s;
  //���������� ����� � �������� ������� T
  m = _T->SizeI(); n = _T->SizeJ();
  //������������ ������� �� ����� ������������
  if (m != n)
   {
      delete _P;
      return 0;
   }

  //������������ ������� ������� 2 ����� ��������� �����
  if (m == 2)
   {
      Det = (_T->GetValue(0, 0) * _T->GetValue(1, 1)) - (_T->GetValue(1, 0) * _T->GetValue(0, 1));
      delete _P;
      return Det;
   }

  //����� ������� ������������ ��� ����� ��������� 1-� ������
  //�������, ���������� �� �� �������������� ����������
//  _P->SetLength(m - 1, n - 1);
  Det = 0; s = 1;
  for (int j = 0; j < n; j++)
   {
      //�������� ����� �������� (0, j)
      GetMinor(_T, 0, j, _P);                         //���������� ������ ������� ��������� P
      Det = Det + s * _T->GetValue(0,j) * CalcDet(_P);
      //���� � ���������� ���������� �������� �� ���������������
      s = -s;
   }
  delete _P;                                          //���������� ������ _P
  return Det;
}
//--------------------------------
//���������� �������, �������� � T
void CalcInverseTransform(const TTransform T, TTransform T_1)
   {
      TMatrix *Help = new TMatrix;  //�������� ������� Help
      TMatrix *M = new TMatrix;     //�������� ������� M
      double detT;
      double A;
  //���������� ������� T ��� ���������� ������������: P <-- T
  Help->SetLength(4, 4);            //�������� ������� � ������������ ������-
  for (int i = 0; i < 4; i++)
  for (int j = 0; j < 4; j++)
   {
      Help->SetValue(i, j) = T[i][j];
   }
  //�������� ������������ ������� T
  detT = CalcDet(Help);
  //�������� ��� �������� �������, �������� � T
  for (int i = 0; i < 4; i++)
  for (int j = 0; j < 4; j++)
   {
    GetMinor(Help, j, i, M); //����� �������� � ������ j ������� i
    //���� ����� ������ ������ � ������� ������, �� A = +M
    if ( ((i+j) % 2) == 0 )
      {A = CalcDet(M);}
    //����� A = -M
    else
      {A = - CalcDet(M);}
    T_1[i][j] = A / detT;
   }
      delete Help;      //����������� ������� Help
      Help = NULL;
      delete M;         //����������� ������� M
      M = NULL;
   }
//--------------------------------------
//���������� ����������������� ������� T
void TransposeTransformMatrix(const TTransform T, TTransform TT)
   {
      TTransform Cpy;
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {Cpy[i][j] = T[j][i];}
      Copy(TT, Cpy);
   }
/*/----------------------------�����---------------------------------------/*/
