//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("ChangeSubTitles.cpp", ChangeSubTitlesForm);
USEFORM("Forms\InfoForm\InfoForm.cpp", ChangeSubTitlesInfoForm);
USEFORM("Forms\SplashForm\SplashForm.cpp", Splash);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
   try
   {
       Application->Initialize();
       Application->CreateForm(__classid(TChangeSubTitlesForm), &ChangeSubTitlesForm);
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
