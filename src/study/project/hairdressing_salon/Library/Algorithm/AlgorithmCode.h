#ifndef _Algorithm_dll
#define _Algorithm_dll
//---------------------------------------
#ifdef __DLL__
   #define DLL_Type __declspec(dllexport)
#else
   #define DLL_Type __declspec(dllimport)
#endif
//---------------------------------------
//---------------------------------------
#endif