#ifndef __Assembler_h
	#define __Assembler_h
//-----------------------------------------------------------
#ifndef __SHLWAPI_H
#pragma comment (lib, "shlwapi.lib")
	#include "shlwapi.h"
	#define __SHLWAPI_H
#endif

#ifndef __WINDOWS_H
	#include <windows.h>
	#define __WINDOWS_H
#endif

#ifndef __STDIO_H
	#include <stdio.h>
#endif

#ifndef __UUMTableStruct_h
	#include "uumtablestruct.h"
#endif

#ifndef __BinTree_h
	#include "bintree.h"
#endif

#ifndef __UUMErrorStruct_h
	#include "uumerrorstruct.h"
#endif

#ifndef __UUMPassStruct_h
	#include "uumpassstruct.h"
#endif

#ifndef __List_h
	#include "list.h"
#endif

#ifndef __ERRNO_H
	#include <errno.h>
	#define __ERRNO_H
#endif
//-----------------
TOpTabElement *AddToOpTab(BinTree<TOpTabElement> &optab, const char *name, unsigned int code, unsigned char type, unsigned int length, bool uumlite, unsigned char info);
TSymTabElement *AddToSymTab(BinTree<TSymTabElement> &symtab, const char *name, unsigned int address, bool definelabel, unsigned char reg = 0);
//-----------------
int operator < (const TOpTabElement &, const TOpTabElement &);
int operator < (const char *, TOpTabElement &);
//-----------------
int operator < (const TSymTabElement &, const TSymTabElement &);
int operator < (const char *, const TSymTabElement &);
//-----------------------------------------------------------
typedef FILE * UUMASMFILEHANDLE;
typedef void * UUMOBJFILEHANDLE;
typedef unsigned char UUMMode;
//-----------------------------------------------------------
#define	MAXSTRINGLENGTH	255
//-----------------------------------------------------------
enum FindLex {NOLEX, LABEL, OPERATION};
//-----------------------------------------------------------
//Имя по умолчанию выходного файла
//static const char DefaultInputName[]  = "UUM32.asm";
static const char DefaultOutputName[] = "UUM32.obj";
//-----------------------------------------------------------
//Режим работы транслятора
#define	CASE		1					//распознование регистра букв		-	0 бит
#define LITE		2					//совместимость с УУМ lite			-	1 бит
#define SUBOBJ		4					//распечатка промежуточного файла	-	2 бит
#define	LST			8					//распечатка файла листинга			-	3 бит
//#define	
//-----------------------------------------------------------
class UUMAsm
{
public:
	UUMAsm() throw(...) 
		: OpTab(NULL),
		  SymTab(NULL),
		  AsmFile(NULL),
		  ObjFile(INVALID_HANDLE_VALUE),
		  SubObjFile(INVALID_HANDLE_VALUE),
		  Error(false),
		  Counter(1),
		  Length(0),
		  LocCtr(0),
		  Ready(false),
		  FirstPassSuccess(false),
		  Mode(0)
	{
		InputFileName[0] = NULL, 
		OutputFileName[0] = NULL, 
		Buffer[0] = NULL;
	}
	~UUMAsm();
	//---------------------------------
	void StartFirstPass() throw (...);
	void StartSecondPass() throw (...);
	//---------------------------------
	TErrorList *GetErrorList() {return &ErrorList;}
	void SetValue(const char *, const char *, BinTree<TOpTabElement> &, BinTree<TSymTabElement> &, UUMMode) throw (...);
private:
	//---------------------------------
	void CutSubString(size_t pos, size_t count, char *cutstring, char *pastestring = NULL, size_t sizeofpaste = 0) throw(...);
	void Decode();
	void DeleteSpacesBefore(char *string) throw (...);
	void DeleteSpacesAfter(char *string) throw (...);
	void RemoveComments(char *string) throw (...);
	void UpCase(char *) throw ();
	void FirstTypeObjRecord(TPassLine &passline)  throw (...);
	void SecondTypeObjRecord(TPassLine &passline) throw (...);
	void ThirdTypeObjrecord(TPassLine &passline)  throw (...);
	void FourthTypeObjRecord(TPassLine &passline) throw (...);
	void FifthTypeObjRecord(TPassLine &passline) throw (...);
	void WriteSubObj() throw(...);
	void WriteHead()   throw(...);
	void WriteObj()    throw(...);
	void SetSpecMemOperand(TPassLine &passline, char *string) throw (...);
	void SetMemoryOperand(TPassLine &passline, TSymTabElement *symtabelement, char *string) throw (...);
	void SetBaseRegister(TPassLine &passline, TSymTabElement *symtabelement) throw (...);
	void SetIndexRegister(TPassLine &passline, TSymTabElement *symtabelement) throw (...);
	size_t ReadSubString(char *string, char advancestop = '\0') throw(...);
	FindLex SearchOperands(TPassLine &temp, char *string) throw (...);
	FindLex SearchLabel(char *string, TPassLine &temp) throw (...);
	FindLex SearchOperation(char *string, TPassLine &temp) throw (...);
	FindLex DecodeOperand(TPassLine &temp, char *string) throw(...);
	FindLex SearchNoOperands(TPassLine &temp, char *string) throw (...);
	FindLex SearchRegOperands(TPassLine &temp, char *string, size_t index = 0) throw (...);
	FindLex SearchRegRegOperands(TPassLine &temp, char *string) throw (...);
	FindLex SearchMemOperands(TPassLine &temp, char *string) throw (...); 
	FindLex SearchRegMemOperands(TPassLine &temp, char *string) throw (...);
	FindLex SearchValueOpSize(TPassLine &temp, char *string) throw (...);
	bool TestSymbol(const char *string) throw ();
	bool ConvertInteger(const char *string, int *pValue = NULL) throw(...);
	bool SearchNext(char * string, char searchsymbol = '\0');		
	int Abs(int value) {if (value < 0) value *= -1; return value;}
	//void SearchOperand();
	//void DeleteAllSpaces(char *string) throw(...);
	//void DownCase(char *); не используется в данной версии программы
	//---------------------------------
	UUMASMFILEHANDLE AsmFile;
	UUMOBJFILEHANDLE ObjFile;
	UUMOBJFILEHANDLE SubObjFile;
	char InputFileName[MAX_PATH], OutputFileName[MAX_PATH];
	BinTree<TOpTabElement> *OpTab;
	BinTree<TSymTabElement> *SymTab;
	TErrorList ErrorList;
	TList<TPassLine> Pass;
	unsigned int Counter, Length, LocCtr;
	char Buffer[MAXSTRINGLENGTH];
	bool Error;
	bool Ready;
	bool FirstPassSuccess;
	//-----------------------------------------------------
	//Служебная информация, связанная с особенностями работы транслятора
	UUMMode Mode;
};
//-----------------------------------------------------------
#endif