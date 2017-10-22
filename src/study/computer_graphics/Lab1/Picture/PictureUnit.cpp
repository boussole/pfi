//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PictureUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*/Координаты фигур/*/

   /*/Небо/*/
   TRect Sky = Rect(0, 0, 415, 100);

   /*/Земля/*/
   TRect Land = Rect(0, 100, 415, 400);

   /*/Забор/*/
   //Нижняя часть
   TRect WallLow[16] = {
         Rect(0, 360, 20, 400),     //Первый слева элемент забора
         Rect(20, 360, 40, 400),    //Второй слева элемент забора
         Rect(40, 360, 60, 400),
         Rect(60, 360, 80, 400),
         Rect(80, 360, 100, 400),
         Rect(100, 360, 120, 400),
         Rect(120, 360, 140, 400),
         Rect(140, 360, 160, 400),
         Rect(160, 360, 180, 400),
         Rect(180, 360, 200, 400),
         Rect(200, 360, 220, 400),
         Rect(220, 360, 240, 400),
         Rect(240, 360, 260, 400),
         Rect(260, 340, 300, 400),  //Дверь
         Rect(300, 360, 320, 400),
         Rect(320, 360, 340, 400)   //16
                       };
   //Верхняя часть - другим способом
   TRect WallHigh = Rect(0, 140, 400, 180);

   //Боковая сторона  - объявлена в подпрограмме

   /*/Домик/*/
   //Передняя часть
   TRect FrontPart = Rect(40, 200, 180, 340);

   //Боковая часть
   TPoint SidePart[4] =
      {
         Point(180, 200),
         Point(200, 180),
         Point(200, 320),
         Point(180, 340)
      };

   /*/Крыша/*/
   //Передняя часть
   TPoint RoofFront[4] =
      {
         Point(40, 200),
         Point(80, 140),
         Point(140, 140),
         Point(180, 200)
      };
   //Боковая часть
   TPoint RoofSide[4] =
      {
         Point(140, 140),
         Point(160, 120),
         Point(200, 180),
         Point(180, 200)
      };
   //Верхняя часть
   TPoint RoofUp[4] =
      {
         Point(80, 140),
         Point(100, 120),
         Point(160, 120),
         Point(140, 140)
      };

   /*/Труба/*/
   TRect Pipe = Rect(130, 100, 140, 130);
   //Дырка в трубе
   TPoint Hole[4] =
      {
         Point(130, 100),
         Point(130, 95),
         Point(140, 95),
         Point(140, 100)
      };
   //Дым
   TPoint Smoke[6] =
      {
         Point(133, 100),
         Point(150, 80),
         Point(133, 60),
         Point(130, 40),
         Point(133, 20),
         Point(150, 0)
      };

   //Окно в доме
   TRect WindowHome = Rect(60, 240, 100, 280);

   //Дверь
   TRect Door = Rect(120, 260, 160, 320);

   //Окно на чердаке
   TPoint WindUp[4] =
      {
         Point(80, 180),
         Point(100, 140),
         Point(120, 140),
         Point(140, 180)
      };

   //Ступеньки к дому
   TRect StageUp = Rect(118, 320, 162, 324);
   TRect StageMiddle_1 = Rect(116, 324, 164, 328);
   TRect StageMiddle_2 = Rect(114, 328, 166, 332);
   TRect StageMiddle_3 = Rect(112, 332, 168, 336);
   TRect StageDown = Rect(110, 336, 170, 340);

   /*/Месяц/*/
   TPoint Moon_1[4] =
      {
         Point(340, 20),
         Point(380, 40),
         Point(360, 80),
         Point(320, 80)
      };
   TPoint Moon_2[4] =
      {
         Point(340, 20),
         Point(360, 40),
         Point(360, 60),
         Point(320, 80)
      };

   /*/Звёзды/*/
   TPoint Star_1[4] =
      {
         Point(10, 10),
         Point(5, 15),
         Point(10, 20),
         Point(15, 15),
      };

   TPoint Star_2[4] =
      {
         Point(50, 50),
         Point(45, 55),
         Point(50, 60),
         Point(55, 55),
      };

   TPoint Star_3[4] =
      {
         Point(85, 85),
         Point(80, 90),
         Point(85, 95),
         Point(90, 90),
      };

   TPoint Star_4[4] =
      {
         Point(310, 10),
         Point(305, 15),
         Point(310, 20),
         Point(315, 15),
      };

   TPoint Star_5[4] =
      {
         Point(240, 50),
         Point(235, 55),
         Point(240, 60),
         Point(245, 55),
      };

   TPoint Star_6[4] =
      {
         Point(200, 10),
         Point(195, 15),
         Point(200, 20),
         Point(205, 15),
      };

   TPoint Star_7[4] =
      {
         Point(160, 45),
         Point(155, 50),
         Point(160, 55),
         Point(165, 50),
      };

   TPoint Star_8[4] =
      {
         Point(125, 10),
         Point(120, 15),
         Point(125, 20),
         Point(130, 15),
      };
/*/-----------------------------------------------------------------------/*/
/*/Обработчик события OnPaint/*/
void __fastcall TMainForm::FormPaint(TObject *Sender)
{
/*/----------------------------------------------------------------------/*/
/*/Данная переменная объявлена здесь, так как её значение меняется в данной п/п/*/
/*/----------------------------------------------------------------------/*/
  //Боковая сторона
   TPoint Side[4] =
      {
         Point(340, 400),
         Point(340, 360),
         Point(346, 338),
         Point(346, 378)
      };
/*/----------------------------------------------------------------------/*/
   /*/Создание голубого неба/*/
   Canvas->Pen->Color = clSkyBlue;
   Canvas->Pen->Width = 1;
   Canvas->Brush->Color = clSkyBlue;
   Canvas->FillRect(Sky);

   /*/Создание зеленой земли/*/
   Canvas->Pen->Color = clGreen;
   Canvas->Pen->Width = 1;
   Canvas->Brush->Color = clGreen;
   Canvas->FillRect(Land);

   /*/Создание забора/*/
   //Нижняя часть
   Canvas->Pen->Color = clBlack;
   Canvas->Pen->Width = 1;
   Canvas->Brush->Color = clWhite;
   for (int i = 0; i < 16; i++)
      {
         if (i == 13)
            {
               Canvas->Brush->Color = clBlack;
               Canvas->Rectangle(WallLow[i]);
               Canvas->Brush->Color = clWhite;
            }
         else
         {Canvas->Rectangle(WallLow[i]);}
      }
   Canvas->Ellipse(265, 370, 268, 363);

   //Верхняя часть
   Canvas->Rectangle(WallHigh);
   for (int i = 0; i < 400; i += 10)
      {
         Canvas->MoveTo(i, 140);
         Canvas->LineTo(i, 180);
      }

   //Боковая часть
   for (int i = 0; i < 10; i++)
      {
            Canvas->Polygon(Side, 4 - 1);
            Side[0].x = Side[0].x + 6;
            Side[0].y = Side[0].y - 22;
            Side[1].x = Side[1].x + 6;
            Side[1].y = Side[1].y - 22;
            Side[2].x = Side[2].x + 6;
            Side[2].y = Side[2].y - 22;
            Side[3].x = Side[3].x + 6;
            Side[3].y = Side[3].y - 22;
      }

   /*/Создание домика/*/
   Canvas->Brush->Color = clGray;
   //Перед
   Canvas->Rectangle(FrontPart);
   //Бок
   Canvas->Polygon(SidePart, 4 - 1);
   //Крыша
   Canvas->Brush->Color = clMaroon;
   Canvas->Polygon(RoofFront, 4 - 1);
   Canvas->Polygon(RoofSide, 4 - 1);
   Canvas->Polygon(RoofUp, 4 - 1);
   //Труба
   Canvas->Brush->Color = 0x2F2F2F;
   Canvas->Rectangle(Pipe);
   Canvas->Pen->Color = clBlack;
   Canvas->Ellipse(130, 105, 140, 100);
   //Дым
   Canvas->Pen->Color = clGray;
   Canvas->Pen->Width = 5;
   Canvas->PolyBezier(Smoke, 3);
   //Окно в доме
   Canvas->Pen->Color = clBlack;
   Canvas->Pen->Width = 1;
   Canvas->Brush->Color = clYellow;
   Canvas->Rectangle(WindowHome);
   //Ставни
   Canvas->MoveTo(80, 240);
   Canvas->LineTo(80, 280);
   Canvas->MoveTo(60, 260);
   Canvas->LineTo(100, 260);
   //Дверь
   Canvas->Brush->Color = clBlack;
   Canvas->Rectangle(Door);
   //Ручка на двери
   Canvas->Brush->Color = clWhite;
   Canvas->Ellipse(122, 285, 128, 290);
   //Окно на чердаке
   Canvas->Brush->Color = clYellow;
   Canvas->Chord(80, 160, 140, 200, 140, 180, 80, 180);
   Canvas->MoveTo(110, 160);
   Canvas->LineTo(110, 180);
   Canvas->MoveTo(85, 170);
   Canvas->LineTo(136, 170);
   //Ступеньки
   Canvas->Brush->Color = clWhite;
   Canvas->Rectangle(StageUp);
   Canvas->Rectangle(StageMiddle_1);
   Canvas->Rectangle(StageMiddle_2);
   Canvas->Rectangle(StageMiddle_3);
   Canvas->Rectangle(StageDown);
   //Пруд
   Canvas->Pen->Width = 1;
   Canvas->Pen->Color = clBlue;
   Canvas->Brush->Color = clBlue;
   Canvas->Ellipse(220, 220, 340, 260);

   /*/Небо/*/
   //Месяц
   Canvas->Pen->Color = clYellow;
   Canvas->Brush->Color = clYellow;
   Canvas->PolyBezier(Moon_1, 3);
   Canvas->PolyBezier(Moon_2, 3);
   Canvas->FloodFill(355, 40, clYellow, fsBorder);

   //Самолёт
   Canvas->Font->Color = clBlack;
   Canvas->Brush->Style = bsClear;
   Canvas->Brush->Color = clSkyBlue;
   Canvas->Font->Name = "WebDings";
   Canvas->Font->Size = 30;
   Canvas->TextOutA(250, 40, "j");

   //Звёзды
   Canvas->Brush->Color = clYellow;
   Canvas->Polygon(Star_1, 3);
   Canvas->Polygon(Star_2, 3);
   Canvas->Polygon(Star_3, 3);
   Canvas->Polygon(Star_4, 3);
   Canvas->Polygon(Star_5, 3);
   Canvas->Polygon(Star_6, 3);
   Canvas->Polygon(Star_7, 3);
   Canvas->Polygon(Star_8, 3);
}
//---------------------------------------------------------------------------
