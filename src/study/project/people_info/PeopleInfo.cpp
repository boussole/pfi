//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("PeopleInfoCode.cpp", PeopleInfoForm);
USEFORM("OtherForm\FileName\FileName.cpp", FileNameForm);
USEFORM("OtherForm\NewWay\NewWay.cpp", NewWayForm);
USEFORM("OtherForm\InfoError\InfoError.cpp", InfoErrorForm);
USEFORM("OtherForm\AboutProgram\AboutProgram.cpp", AboutProgramForm);
USEFORM("OtherForm\SplashForm\SplashForm.cpp", Splash);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->Title = "Info";
       Application->CreateForm(__classid(TPeopleInfoForm), &PeopleInfoForm);
       Application->CreateForm(__classid(TFileNameForm), &FileNameForm);
       Application->CreateForm(__classid(TNewWayForm), &NewWayForm);
       Application->CreateForm(__classid(TInfoErrorForm), &InfoErrorForm);
       Application->Run();
   }
   catch (Exception &exception)
   {
       Application->ShowException(&exception);
   }
   catch (...)
   {
       try
       {
          throw Exception("");
       }
       catch (Exception &exception)
       {
          Application->ShowException(&exception);
       }
   }
   return 0;
}
//---------------------------------------------------------------------------
