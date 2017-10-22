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
/*/����� ����������/*/
   bool Around = false, AroundX = false, AroundY = false, AroundZ;
/*/-----------------------------------------------------------------------/*/
/*/������������ ���� ������/*/
  //��� ��� �������� ����� �������
   typedef double TVertex[4];

  //������ �����
   typedef unsigned short TEdge[2];

  //������� ��������������
   typedef double TTransform[4][4];
/*/-----------------------------------------------------------------------/*/
/*/���������/*/
void Copy(TVertex *,TVertex *, unsigned short int);
void Copy(TTransform CopyMatrix,TTransform OrigMatrix);
void CombineTransforms(TTransform , const TTransform, const TTransform);
void ApplyTransform(TVertex *, TVertex *, const TTransform, unsigned short int);
void NormalizeCoordinates(TVertex *V, unsigned short int);
void DrawWire(TCanvas *, TVertex *, TEdge *, unsigned short int, unsigned short int);
double Round(double);
/*/-----------------------------------------------------------------------/*/
/*/���������� ������/*/
   const VCount = 30;
   const ECount = 42;
   TVertex V[VCount] = {
                           //�����
                           {-20, -20, 30, 1},  //0
                           {-20, -20, 70, 1},  //1
                           {-20, 20, 70, 1},   //2
                           {-20, 20, 30, 1},   //3
                           //�����
                           {-20, 0, 10, 1},    //4
                           {-20, 0, 80, 1},    //5
                           //�����
                           {10, -10, 10, 1},   //6
                           {10, -10, 20, 1},   //7
                           {60, -10, 20, 1},   //8
                           {60, -10, 10, 1},   //9
                           {10, 10, 10, 1},    //10
                           {10, 10, 20, 1},    //11
                           {60, 10, 20, 1},    //12
                           {60, 10, 10, 1},    //13
                           //������
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
                           //���
                           {90, 0, 20, 1},     //26 - �������� �����
                           {80, 0, 10, 1},     //27
                           {80, 0, 10, 1},     //28
                           {0, 0, 0, 1}        //29 - �����
                        };
   /*/����� ������/*/
   TEdge E[ECount] = {
                     {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {6, 7}, {7, 8}, {8, 9}, {9, 6},
                     {10, 11}, {11, 12}, {12, 13}, {13, 10}, {6, 10}, {7, 11}, {8, 12}, {9, 13},
                     {14, 15}, {15, 16}, {16, 17}, {18, 19}, {19, 20}, {20, 21}, {15, 19}, {14, 22},
                     {22, 23}, {23, 18}, {17, 24}, {24, 25}, {25, 21}, {14, 17}, {22, 24}, {23, 25},
                     {18, 21}, {28, 26}, {16, 27}, {20, 27}, {21, 27}, {17, 27}, {24, 27}, {25, 27}};
/*/-----------------------------------------------------------------------/*/
/*/����������� �������/*/
//----------------------
//������� �������� � ������� �����������
   TTransform M= {
                     {    1,    0,    0,  0},
                     {    0,    1,    0,  0},
                     {    0,    0,    1,  0},
                     {   -100, -200, -125, 1}
                  };
//----------------------
//������������� ��������������
   const double Xs = 1500; //����� ���������� �� ��� x

//������� �������������� ��������������
   TTransform P =   {
                     {0, 0, 0, -1/Xs},
                     {0, 1, 0,     0},
                     {0, 0, 1,     0},
                     {0, 0, 0,     1}
                    };
//----------------------
//������� � �������� ������� ���������

//������� ������ ��� Y �� -90 ��������
  TTransform Cy = {
                     {0, 0, -1, 0},
                     {0, 1,  0, 0},
                     {1, 0,  0, 0},
                     {0, 0,  0, 1}
                  };

//������� ����� ��� Z �� 90 ��������
  TTransform Cz = {
                     {0, -1, 0,  0},
                     {1,  0,  0, 0},
                     {0,  0,  1, 0},
                     {0,  0,  0, 1}
                  };

//������� � ������ ���������
  TTransform Ct = {
                     {1,  0, 0,  0},
                     {0,  1,  0, 0},
                     {0,  0,  1, 0},
                     {0,  0,  0, 1}
                  };

//[C] := [Cy]*[Cz]*[Ct]
  TTransform C;
//----------------------
//���������������
   //���������� ����������
   const double K = 1.1;
   //����������
   TTransform S1 = {
                     {K, 0, 0, 0},
                     {0, K, 0, 0},
                     {0, 0, K, 0},
                     {0, 0, 0, 1}
                   };
   //����������
   TTransform S2 = {
                     {1/K, 0, 0, 0},
                     {0, 1/K, 0, 0},
                     {0, 0, 1/K, 0},
                     {0, 0, 0,   1}
                   };
//----------------------
//�������
   //���������� ���������
   double CountReturn = 45;
   double Angle = M_PI / 45;
   //������ �
   TTransform RX = {
                     {1,         0,           0, 0},
                     {0,  cos(Angle), sin(Angle), 0},
                     {0, -sin(Angle), cos(Angle), 0},
                     {0,           0,          0, 1}
                   };
  //������ Y
  TTransform RY = {
                     {cos(Angle), 0, -sin(Angle), 0},
                     {         0, 1,           0, 0},
                     {sin(Angle), 0, cos(Angle), 0},
                     {         0, 0,          0, 1}
                   };
  //������ Z
  TTransform RZ = {
                     { cos(Angle), sin(Angle), 0, 0},
                     {-sin(Angle), cos(Angle), 0, 0},
                     {          0,          0, 1, 0},
                     {          0,          0, 0, 1}
                   };
//----------------------
//�������
   //�������� ��������
   const double d = 5;
   //������� ��������
   TTransform Transport = {
                     {1, 0, 0, 0},
                     {0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1}
                   };
/*/-----------------------------------------------------------------------/*/
/*/��������������� ������� ��� ������ � ���������/*/
/*/-----------------------------------------------------------------------/*/
//������������� ������
void Copy(TVertex *CopyMatrix, TVertex *OrigMatrix, unsigned short int Size)
   {
      for (int i = 0; i < Size/32; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//��� TTransform
void Copy(TTransform CopyMatrix,TTransform OrigMatrix)
   {
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            CopyMatrix[i][j] = OrigMatrix[i][j];
         }
   }
//������� �������������� ���������
//[T]:=[T1]*[T2]
void CombineTransforms(TTransform T, const TTransform T1, const TTransform T2)
   {
   void Copy(TTransform, TTransform);
      TTransform Tmp;
      //���������� [T1] � [T2]
      for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         {
            Tmp[i][j] = 0;
            for (int k = 0; k < 4; k++)
               Tmp[i][j] = Tmp[i][j] + T1[i][k] * T2[k][j];
         }
      //��������� �����
      Copy(T,Tmp);
   }

//������������ �������������� [T]: [TV] = [V]*[T]
void ApplyTransform(TVertex *VRet, TVertex *_V, const TTransform T, unsigned short int Size)
   {
      TVertex VT;
  //������ �� ���� ��������
  for (int i = 0; i < Size/32; i++)
      {
         //�������� ���������� i - �� �������
         for (int j = 0; j < 4; j++)
            {
               VT[j] = 0;
               //���������� j - �� �������
               for (int k = 0; k < 4; k++)
                  VT[j] = VT[j] + _V[i][k] * T[k][j];
            }
         //���������� ���������� ������� � ������
         for (int z = 0; z < 4; z++)
            {VRet[i][z] = VT[z];}
      }
   }

//������������ ��������
void NormalizeCoordinates(TVertex *_V, unsigned short int Size)
   {
      double H;
      for (int i = 0; i < Size/32; i++)
         {
            H = _V[i][3];             //��������� �������� H
            _V[i][0] = _V[i][0] / H;  //��������� �������� X
            _V[i][1] = _V[i][1] / H;  //��������� Y
            _V[i][2] = _V[i][2] / H;  //��������� Z
            _V[i][3] = 1;             //����������� H �������� 1
         }
   }

//��������� ���������� �����������
void DrawWire(TCanvas *Canv, TVertex *_V, TEdge *E, unsigned short int SizeV, unsigned short int SizeE)
   {
      //�������� ��� ����
      for (int i = 0; i < SizeE/4; i++)
         {
         //��������
         if ((E[i][0] > SizeV/32) || (E[i][1] > SizeV/32))
            {
               ShowMessage("����� �� ������� ������� ������");
               return;
            }
         Canv->MoveTo(Round(_V[E[i][0]] [0]), Round(_V[E[i][0]] [1]));
         Canv->LineTo(Round(_V[E[i][1]] [0]), Round(_V[E[i][1]] [1]));
         }
   }
/*/-----------------------------------------------------------------------/*/
/*/������� ����������/*/
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
//��� ������ ������ ��� ������� ����������� ���������� ��� � �� �������� � �������
//ApplyTransform(V, V, M, sizeof(V));
  Ct[3][0] = int(ClientWidth/2);
  Ct[3][1] = int(ClientHeight/2);

  CombineTransforms(C, Cy, Cz); //[C]:=[Cy]*[Cz]
  CombineTransforms(C, C, Ct);  //[C]:=[C]*[Ct]
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormPaint(TObject *Sender)
{
  //����� ������
  Canvas->Font->Color = clBlue;
  Canvas->Brush->Color = clYellow;
  Canvas->Font->Height = 14;
  Canvas->Font->Name = "Arial";
  Canvas->TextOutA(0, ClientHeight-70, "����������:");
  Canvas->TextOutA(0, ClientHeight-56, "������� - ������� �� ����; '+', '-' ���������������");
  Canvas->TextOutA(0, ClientHeight-42, "Space - �������� ������ ���� ����/��������� ��������");
  Canvas->TextOutA(0, ClientHeight-28, "X, Y, Z - �������� �� ���������� ����/��������� ��������");
  Canvas->TextOutA(0, ClientHeight-14, "Back Space - ��������� ���� ��������");


  TVertex VP[VCount];
  //yOz: [VP]:=[V]*[P]
  ApplyTransform(VP, V, P, sizeof(VP));

  //[VP]:=[VP]*[C]
  ApplyTransform(VP, VP, C, sizeof(VP));

  //������������
  NormalizeCoordinates(VP, sizeof(VP));

  Canvas->Pen->Color = clBlack;
  DrawWire(Canvas, VP, E, sizeof(VP), sizeof(E));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   //����������
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
   //����������
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
   //������� ������ ��� �
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
   //������� �� ��� Y - �����
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
   //������� �� ��� y - ������
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
   //������� �� ��� Z - ����
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
   //������� �� ��� Z - �����
   if (Key == VK_UP)
      {
         Transport[3][0] = 0;
         Transport[3][1] = 0;
         Transport[3][2] = d;
         ApplyTransform(V, V, Transport, sizeof(V));
         Refresh();
      }
   //��������� ����������� ����
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
      
   //������������ �������� ������ �
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

   //������������ �������� ������ Y
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

   //������������ �������� ������ Z
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
   //������ ������ ���� ����������� ���� �� ���� � ��� �� ����
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
   //������ ������ �
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
    //������ ������ Y
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
    //������ ������ Z
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

