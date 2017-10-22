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
//���������
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
//������� ����� ������
void ClearScreen(TImage *_Screen, TColor _Color)
{
   _Screen->Canvas->Brush->Color = _Color;
   _Screen->Canvas->FillRect(Rect(0, 0, Screen->Width, Screen->Height));
}
//��������� ���� ���������
void  PaintAxisMain(TCanvas *_Screen)
{
   _Screen->MoveTo(0, 0);
   _Screen->LineTo(0, 400);
   _Screen->MoveTo(0, 200);
   _Screen->LineTo(200, 200);
   _Screen->MoveTo(0, 0);
   _Screen->TextOutA(190, 205, "X");
}
//��������� ���� ��������� �� ��������������� ���
void PaintAxisHelp(TCanvas *_Screen)
{
   _Screen->MoveTo(0, 200);
   _Screen->LineTo(200, 200);
   _Screen->TextOutA(190, 205, "O");
   _Screen->TextOutA(5, 205, "-X");
   _Screen->TextOutA(185, 385, "-Z");
   _Screen->TextOutA(185, 0, "Z");
}
//���������� �����
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
//����������
unsigned int CountVer;  //���������� ������ �� ���������
unsigned int CountGor;  //���������� ������ �� �����������
unsigned int Count;     //����� ���������� ������
unsigned int FacesNum;   //���������� ����������

//����������������� ������
TLIST *SameArray;
//������ ������
TVertex *Template;
//������� ������������� ������
TVertex *Vertex;
//������� ������������� ������ � ������� �����������
TVertex *ScreenVertex;
//������� ����������
TPlane *PL;
//������� ��������� � ������� ������� ���������
//TPlane *PLM;
//������ ������ �����
TFace *F;
//������ �������� ������� ������ � ������� F
unsigned int *FI;
//����� ����������
double Ys = 1500;
//�������� �����������
Graphics :: TBitmap *Bmp;
//��� �����
TVector  Light = {0.577, 0.577, 0.577, 0};
//����� ����������
TVertex  S = {0, Ys, 0, 1};
//��������� �����������
bool Picture = false;
bool Skeleton = false;
//------------------------
//��������
bool PaintPict = false; //���������
bool CreateObj = false; //������� ���������� �������
bool JustPaint  = false;//������� ��������� ������ ��������� ���������
//---------------------------------------------------------------------------
//�������
//--------
//������� �� �������� � �������, ��� Image1
TTransform ScreenToWorld = {
                              {1,  0,   0, 0},
                              {0,  0,  -1, 0},
                              {0,  -1,  0, 0},
                              {0,  0, 200, 1}
                           };
//������� �� ������� � ��������, ��� Image2
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
//������� �������������� �������������� ����� Zs
TTransform P             = {
                              {1, 0, 0,     0},
                              {0, 0, 0,     -1/Ys},
                              {0, 0, 1,     0},
                              {0, 0, 0,     1}
                           };
//----------------
//������� � ��������� �. �.
TTransform L             = {
                               {1,     0, 0, 0},
                               {0,     1, 0, 0},
                               {0,     0, 1, 0},
                               {0,     0, 0, 1}
                           };
  //----------------
  //������� ������ X
  TTransform Rx = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //������� ������ Y
  TTransform Ry = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
  //----------------
  //������� ������ Z
  TTransform Rz = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
                  };
//����������������� ��������������� �������
TTransform tiRx, tiRy, tiRz, tiL;
//------------------------------------------
//���������
Set <char, 44, 69> SetOfChar;
//---------------------------------------------------------------------------
//��������� ������� Rx
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
//��������� ������� Ry
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
//��������� ������� Rz
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
//������������� ������
bool GetVertex(TLIST *Help, AnsiString _Buff)
{
   unsigned int i = 1;
   bool First = false, Second = false, Third = false, Fourth = false, OpenBracket = false, CloseBracket = false;
   AnsiString Number;
   double Var;
   TVertex _Vertex;

   //����� ����������� ������
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
         Application->MessageBoxA("�� ������� ����������� ������ � ������", "������ ������� ������", MB_OK);
         return false;
      }

   //����� ���������
   while (i <= _Buff.Length())
      {
         if (_Buff[i] != ' ')
            {
               //���������� ���������
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
                     Application->MessageBoxA("������ � ��������� �����, �������� ������� ����� ������� ��������� �������", "������ ������� ������", MB_OK);
                     return false;
                  }
               Number = "";
               //���������� ������ ����������
               if (!First)
                  {
                      _Vertex[0] = Var;
                      First = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //���������� ������ ����������
               if ( (First) && (!Second))
                  {
                     _Vertex[1] = Var;
                      Second = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //���������� ������ ����������
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
   //����� ����������� ������
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
         Application->MessageBoxA("�� ������� ����������� ������ � ������", "������ ������� ������", MB_OK);
         return false;
      }
   if ( (!First) || (!Second) || (!Third) || (!Fourth))
      {
         Application->MessageBoxA("���������� ��������� ������� ������ ���� ����� �������", "������ ������� ������", MB_OK);
         return false;
      }
   Help->Add(_Vertex[0], _Vertex[1], _Vertex[2], _Vertex[3]);
   return true;
}
//---------------------------------------------------------------------------
//������������� ������ ������
bool GetFaces(TLIST *Help, AnsiString _Buff)
{
   unsigned int i = 1;
   bool First = false, Second = false, Third = false, OpenBracket = false, CloseBracket = false;
   AnsiString Number;
   double Var;
   TVertex _Vertex;

   //����� ����������� ������
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
         Application->MessageBoxA("�� ������� ����������� ������ � ������", "������ ������� ������", MB_OK);
         return false;
      }

   //����� ���������
   while (i <= _Buff.Length())
      {
         if (_Buff[i] != ' ')
            {
               //���������� ���������
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
                     Application->MessageBoxA("������ � ��������� �����, �������� ������� ����� ���� �������� �����", "������ ������� ������", MB_OK);
                     return false;
                  }
               Number = "";
               //���������� ������ ����������
               if (!First)
                  {
                      _Vertex[0] = Var;
                      First = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //���������� ������ ����������
               if ( (First) && (!Second))
                  {
                     _Vertex[1] = Var;
                      Second = true;
                      if (i == _Buff.Length())
                        {break;}
                  }
               else
               //���������� ������ ����������
               if ( (First) && (Second) && (!Third) )
                  {
                     _Vertex[2] = Var;
                      Third = true;
                      break;
                  }
            }
         i++;
      }

   //����� ����������� ������
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
         Application->MessageBoxA("�� ������� ����������� ������ � ������", "������ ������� ������", MB_OK);
         return false;
      }
   if ( (!First) || (!Second) || (!Third) )
      {
         Application->MessageBoxA("���������� �������� ������ ������ ���� ����� ����", "������ ������� ������", MB_OK);
         return false;
      }
   Help->Add(_Vertex[0], _Vertex[1], _Vertex[2], 0);
   return true;
}
//---------------------------------------------------------------------------
//�������� �����
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
   Application->MessageBoxA("������� ���������� ����� ������ � I � IV ���������", "��������", MB_OK);
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
if ((CreateObj) && (!JustPaint)) //�������� �������� �� ������� ������� � ��� ������������ ���������
{
if (SameArray->GetCount() == 1)
{
   Application->MessageBoxA("���������� ������� ��� ����� ��� ��������� ����������� ��������", "��������", MB_OK);
   return;
}
   //����������
   double Angle;
   unsigned int k;
   //----------
   //������� ����
   try
      {Angle = StrToFloat(Edit1->Text);}
   catch (...)
      {Application->MessageBoxA("������ � ��������� ����", "��������", MB_OK); return;}
   if (Angle > 10) {Application->MessageBoxA("���� ����� ������� �������, �������� ��������", "��������", MB_OK); return;}
   if (Angle <= 0) {Application->MessageBoxA("���� ������ ���� �������������", "��������", MB_OK); return;}
   CountGor = 360 / Angle;
   //������ �������
   Template = new TVertex[CountVer];
   //����������� ������ � ������ �������
   Copy(Template, SameArray);
   //������ ���� ������ ����������� ��������
   Vertex = new TVertex[CountGor * CountVer];
   //������� �� �������� � ������� �. �.
   ApplyTransform(Template, Template, ScreenToWorld, (CountVer)*32);
   //���������� ������, ������� � ����� ������
   Sort(Template, CountVer);
   //���������� ��������� ������
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
   //���������� ������� ������
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
   //��������� ������� ��������� ����������
   //------------
   PL = new TPlane[FacesNum];
   for (int i = 0; i < FacesNum; i++)
      {
        GetPlaneEquation(Vertex[F[i].VI[0]], Vertex[F[i].VI[1]], Vertex[F[i].VI[2]], PL[i]);
      }
   //------------
   //���������� �������� ����������������� ������� ��������� ������� ���������
//   CalcInverseTransform(L, tiL);
//   TransposeTransformMatrix(tiL, tiL);
   //------------
   //��� �����������
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
   //����� �����������
   PaintPict = true;    //��������� �������� ���������
   OnPaint(this);
}
}
//---------------------------------------------------------------------------
//���������� ������� OnPaint
void __fastcall TMainPanel::FormPaint(TObject *Sender)
{
if (PaintPict)    //�������� �������� �� ����������� ��������
{
   //---------------------------------
   Bmp->Width = Image2->Width;
   Bmp->Height = Image2->Height;
   //---------------------------------
   //������ ������, ��������� �� �����
   TVertex *VP;
   //������ ��������� ���������� � ������� �����������
   TPlane *PLM;
   //---------------------------------
   //�������� ������������ ��������
   VP = new TVertex[Count];
   PLM = new TPlane[FacesNum];
   FI = new unsigned int[FacesNum];
   //---------------------------------
//   ApplyTransform(VP, Vertex, L, Count*32);
 //  ApplyTransform(PLM, PL, tiL, FacesNum*32);
   Copy(VP, Vertex, Count*32);
   //---------------------------------
   //����������� - ������� (���������) ������
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
   //���������� ������ �� ������������ ���������� y
   for (int i = 0; i < Num; i++)
      {
         F[FI[i]].maxX = Maximal(Maximal(VP[F[FI[i]].VI[0]][1], VP[F[FI[i]].VI[1]][1]), VP[F[FI[i]].VI[2]][1]);
      }

   //���������� ������ �� ��������
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
   //����� �� �����
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
   //������������ ������������ ��������
   JustPaint = true;
   //---------------------------------
   //����������� ������������ ��������
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
//����������� ��������
void __fastcall TMainPanel::ClearAllClick(TObject *Sender)
{
   CreateObj = false;   //������� �������� ������� ��������
   JustPaint = false;   //������� ������������� ������� ��������
   PaintPict = false;    //������� �� ��������� �������
   //����������� ������� ������ �������
   delete []Template;
   Template  = NULL;
   //����������� ������� ������ ���� ������
   delete []Vertex;
   Vertex = NULL;
   //����������� ������� ������ ����
   delete []F;
   F = NULL;
   //����������� ������� ��������� ��������
   delete []PL;
   PL = NULL;
   //����������� ������������������� �������
   delete SameArray;
   SameArray = NULL;
   //������� ��������
   ClearScreen(Image1, clWhite);
   PaintAxisMain(Image1->Canvas);
   Bmp->Canvas->Brush->Color = clBlack;
   Bmp->Canvas->FillRect(Rect(0, 0, Image2->ClientWidth, Image2->ClientHeight));
   Image2->Canvas->Draw(0, 0, Bmp);
   //��������� �������� ����������
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
//������� �� X �� �������
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
//������� �� X ������ �������
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
//������� �� Z ������ �������
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
//������� �� Z �� �������
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
//�� ������� ������ ����� ���
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
//������� ���������
void __fastcall TMainPanel::Exit1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
//���������� �����������
void __fastcall TMainPanel::SaveBitMap1Click(TObject *Sender)
{
if (JustPaint)
{
   if (SavePictureDialog1->Execute())
      {
         //���� �� ������
         if (!FileExists(SavePictureDialog1->FileName))
            {
               ofstream OutFile((SavePictureDialog1->FileName).c_str());
               if (OutFile.fail())
                  {
                     Application->MessageBox("���������� ������� ���� �� �����", "������ �������� �����", MB_OK);
                     return;
                  }
               else
               {OutFile.close();}
            }
         //���� ����������
         else
            {
                  if (MessageDlg("���� � ��������� ������ ������������ �� �����, ������ �������� ������������ ����",
                              mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                     {return;}
            }
         try
            {
               Bmp->SaveToFile(SavePictureDialog1->FileName);
            }
         catch (...)
            {
               Application->MessageBox("���������� ��������� ���� �� �����", "������ ������ �� ����", MB_OK);
               return;
            }
      }
}
else
{
   Application->MessageBoxA("������� �� ������", "��������", MB_OK);
}
}
//---------------------------------------------------------------------------
//��������� �������
void __fastcall TMainPanel::LoadBitMap1Click(TObject *Sender)
{
   if (OpenPictureDialog1->Execute())
      {
         if (FileExists(OpenPictureDialog1->FileName))
            {
               try
                  {Bmp->LoadFromFile(OpenPictureDialog1->FileName);}
               catch(...)
                  {Application->MessageBoxA("���������� ������� ����", "������ ������ �����", MB_OK); return;}
               ClearAllClick(Sender);
               Bmp->LoadFromFile(OpenPictureDialog1->FileName);
               Image2->Canvas->Draw(0, 0, Bmp);
            }
         else
            {
               Application->MessageBoxA("��������� ���� ����������� �� �����", "������ ������ �����", MB_OK);
            }
      }
}
//---------------------------------------------------------------------------
//���������� ������ �������
void __fastcall TMainPanel::Savetemplate1Click(TObject *Sender)
{
if (Template != NULL)
{
   if (SaveDialog1->Execute())
      {
         AnsiString Buffer;
         //���� ����������
         if (FileExists(SaveDialog1->FileName))
            {
               if (MessageDlg("���� � ��������� ������ ������������ �� �����, ������ �������� ������������ ����",
                            mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                           {return;}
            }
         //������� ����
         ofstream OutFile((SaveDialog1->FileName).c_str());
         if (OutFile.fail())
            {
               Application->MessageBox("���������� ������� ���� �� �����", "������ �������� �����", MB_OK);
               return;
            }
         //-------------
         //������ � ����
         //-------------
         //������� ������ �������
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
         //�������� �����
         OutFile.close();
      }
}
else
{
   Application->MessageBoxA("������ ����", "��������", MB_OK);
}
}
//---------------------------------------------------------------------------
//���������� ���� ������ � �����
void __fastcall TMainPanel::SaveVertexEdge1Click(TObject *Sender)
{
if (Template != NULL)
{
   if (SaveDialog2->Execute())
      {
         AnsiString Buffer;
         //���� ����������
         if (FileExists(SaveDialog2->FileName))
            {
               if (MessageDlg("���� � ��������� ������ ������������ �� �����, ������ �������� ������������ ����",
                            mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo)
                           {return;}
            }
         //������� ����
         ofstream OutFile((SaveDialog2->FileName).c_str());
         if (OutFile.fail())
            {
               Application->MessageBox("���������� ������� ���� �� �����", "������ �������� �����", MB_OK);
               return;
            }
         //-------------
         //������ � ����
         //-------------
         //������� ���� ������ ������
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
         //������� ����� ������
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
         //�������� �����
         OutFile.close();
      }
}
else
{
   Application->MessageBoxA("������ �� �������", "��������", MB_OK);
}
}
//---------------------------------------------------------------------------
//�������� �� ����� �������
void __fastcall TMainPanel::Loadtemplate1Click(TObject *Sender)
{
   if (OpenDialog1->Execute())
      {
         ifstream LoadFile;
         char *FileName = (OpenDialog1->FileName).c_str();
         LoadFile.open(FileName);
         if (LoadFile.fail())
            {
               Application->MessageBoxA(("���������� ������� ���� " + AnsiString(FileName)).c_str(), "������ �������� �����", MB_OK);
               LoadFile.close();
               return;
            }
         if (Vertex != NULL)
            {
               ClearAllClick(Sender);
            }
         //���� ������
         TLIST *HelpArray = new TLIST;
         char Buffer[255];
         bool Found = false;
         //--------------
         //����� �����
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //������� ��������
               if (AnsiString(Buffer) == "[Template Vertex]")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("������� ������ ������� �� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //����� ������
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //������� ��������
               if (AnsiString(Buffer) == "{")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("�� ������� ������ ������ ���� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //������������� � ������� �����
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               if (AnsiString(Buffer) == "}")
                  {
                     Found = true;
                     break;
                  }
               //������������� ������
               if (!GetVertex(HelpArray, AnsiString(Buffer)))
                  {
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("�� ������� ������ ����� ���� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
//---------------------------------------------------------------------
//���������� ���������
if (HelpArray->GetCount() == 1)
{
   Application->MessageBoxA("���������� ������� ��� ����� ��� ��������� ����������� ��������", "��������", MB_OK);
   return;
}
   CountVer = HelpArray->GetCount();
   //����������
   double Angle;
   unsigned int k;
   //----------
   //������� ����
   try
      {Angle = StrToFloat(Edit1->Text);}
   catch (...)
      {Application->MessageBoxA("������ � ��������� ����", "��������", MB_OK); return;}
   if (Angle > 10) {Application->MessageBoxA("���� ����� ������� �������, �������� ��������", "��������", MB_OK); goto Exit;}
   if (Angle <= 0) {Application->MessageBoxA("���� ������ ���� �������������", "��������", MB_OK); goto Exit;}
   CountGor = 360 / Angle;
   //������ �������
   Template = new TVertex[CountVer];
   //����������� ������ � ������ �������
   Copy(Template, HelpArray);
   //������ ���� ������ ����������� ��������
   Vertex = new TVertex[CountGor * CountVer];
   //���������� ������, ������� � ����� ������
   Sort(Template, CountVer);
   //���������� ��������� ������
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
   //����� �� ����� �������
   ApplyTransform(Template, Template, WorldToImage1, CountVer*32);
   NormalizeCoordinates(Template, CountVer*32);
   for (int i = 0; i < CountVer; i++)
      {
         Image1->Canvas->Ellipse(Template[i][0] - 1, Template[i][1] - 1, Template[i][0] + 1, Template[i][1] + 1);
      }
   //------------
   //���������� ������� ������
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
   //��������� ������� ��������� ����������
   //------------
   PL = new TPlane[FacesNum];
   for (int i = 0; i < FacesNum; i++)
      {
        GetPlaneEquation(Vertex[F[i].VI[0]], Vertex[F[i].VI[1]], Vertex[F[i].VI[2]], PL[i]);
      }
   //------------
   //���������� �������� ����������������� ������� ��������� ������� ���������
//   CalcInverseTransform(L, tiL);
//   TransposeTransformMatrix(tiL, tiL);
   //------------
   //��� �����������
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
   //����� �����������
   CreateObj = true;
   PaintPict = true;    //��������� �������� ���������
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
//�������� ����� ������ ������ � ������
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
               Application->MessageBoxA(("���������� ������� ���� " + AnsiString(FileName)).c_str(), "������ �������� �����", MB_OK);
               LoadFile.close();
               return;
            }
         if (Vertex != NULL)
            {
               ClearAllClick(Sender);
            }
      //------------------------------------------------------------------------
         //������ ������
         TLIST *HelpArray = new TLIST;
         //������ ������ 
         TLIST *HelpFaces = new TLIST;
         char Buffer[255];
         bool Found = false;
      //------------------------------------------------------------------------
      //������� ������
         //--------------
         //����� �����
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //������� ��������
               if (AnsiString(Buffer) == "[Vertex]")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("������� ������ ������ �� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //���������� ������� ������
         //------------
         //����� ������
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //������� ��������
               if (AnsiString(Buffer) == "{")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("�� ������� ������ ������ ���� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //������������� � ������� �����
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               if (AnsiString(Buffer) == "}")
                  {
                     Found = true;
                     break;
                  }
               //������������� ������
               if (!GetVertex(HelpArray, AnsiString(Buffer)))
                  {
                     Error = true;
                     break;
                  }
            }
         if (Error)
            {
               Application->MessageBoxA("���� ������ ������ �� ������������� ���������, ��������������� ����������", "��������", MB_OK);
               goto Exit;               
            }
         if (!Found)
            {
               Application->MessageBoxA("�� ������� ������ ����� ���� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
      //------------------------------------------------------------------------
      LoadFile.close();
      Error = false;
      LoadFile.open(FileName);
      //-------------
      //�����
        //����� �����
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //������� ��������
               if (AnsiString(Buffer) == "[Faces]")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("������� ������ ������ �� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //���������� ������� ������
         //------------
         //����� ������
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               //������� ��������
               if (AnsiString(Buffer) == "{")
                  {
                     Found = true;
                     break;
                  }
            }
         if (!Found)
            {
               Application->MessageBoxA("�� ������� ������ ������ �������� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
         else {Found = false;}
         //------------
         //������������� � ������� �����
         while (!LoadFile.eof())
            {
               LoadFile.getline(Buffer, sizeof(Buffer));
               if (AnsiString(Buffer) == "}")
                  {
                     Found = true;
                     break;
                  }
               //������������� ������
               if (!GetFaces(HelpFaces, AnsiString(Buffer)))
                  {
                     Error = true;
                     break;
                  }
            }
         if (Error)
            {
               Application->MessageBoxA("���� ������ ������ �� ������������� ���������, ��������������� ����������", "��������", MB_OK);
               goto Exit;
            }
         if (!Found)
            {
               Application->MessageBoxA("�� ������� ������ ����� �������� ������, �������� ������ ������ ����",
                                        "������ ������� �����", MB_OK);
               goto Exit;
            }
//---------------------------------------------------------------------
//���������� ���������
   Count = HelpArray->GetCount();
   FacesNum = HelpFaces->GetCount();
   //------------------------------
   //������ ���� ������ ����������� ��������
   Vertex = new TVertex[Count];
   //������� ������
   F = new TFace[FacesNum];
   //����������� ������ � ������
   Copy(Vertex, HelpArray);
   //����������� ������
   for (int i = 0; i < FacesNum; i++)
      {
         F[i].VI[0] = HelpFaces->GetValue(i, 0);
         F[i].VI[1] = HelpFaces->GetValue(i, 1);
         F[i].VI[2] = HelpFaces->GetValue(i, 2);
         F[i].R = 1;
         F[i].G = 1;
         F[i].B = 1;
      }
   //���������� ������, ������� � ����� ������
//   Sort(Vertex, CountVer);
   //------------
   //��������� ������� ��������� ����������
   //------------
   PL = new TPlane[FacesNum];
   for (int i = 0; i < FacesNum; i++)
      {
        GetPlaneEquation(Vertex[F[i].VI[0]], Vertex[F[i].VI[1]], Vertex[F[i].VI[2]], PL[i]);
      }
   //------------
   //���������� �������� ����������������� ������� ��������� ������� ���������
//   CalcInverseTransform(L, tiL);
//   TransposeTransformMatrix(tiL, tiL);
   //------------
   //��� �����������
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
   //����� �����������
   CreateObj = true;
   PaintPict = true;    //��������� �������� ���������
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
