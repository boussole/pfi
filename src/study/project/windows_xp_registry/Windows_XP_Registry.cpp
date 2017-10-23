//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Windows_XP_Registry_Code.cpp", Windows_XP_Registry_Form);
USEFORM("Forms\InformationForm\FormParametr.cpp", ParametrForm);
USEFORM("Forms\SplashForm\SplashForm.cpp", Splash);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->Title = "Windows_XP_Register";
       Application->CreateForm(__classid(TWindows_XP_Registry_Form), &Windows_XP_Registry_Form);
       Application->CreateForm(__classid(TParametrForm), &ParametrForm);
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
