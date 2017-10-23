#ifndef __UUM32Asm_h
	#define __UUM32Asm_h
//-----------------------------------------------------------
//Подключаемые заголовочные файлы
//-----------------
#ifndef __LOCALE_H
	#include <locale.h>
	#define __LOCALE_H
#endif

#ifndef __STDIO_H
	#include <stdio.h>
	#define __STDIO_H
#endif

#ifndef __STRING_H
	#include <string.h>
	#define __STRING_H
#endif

#ifndef __UUMMess_h
	#include "uummess.h"
#endif

#ifndef __BinTree_h
	#include "bintree.h"
#endif

#ifndef __UUMTableStruct_h
	#include "uumtablestruct.h"
#endif

#ifndef __Assembler_h
	#include "assembler.h"
#endif
//-----------------------------------------------------------
//#define UUMOpTab	BinTree<TOpTabElement>
//#define UUMSymTab	BinTree<TSymTabElement>
//#define UUMRegTab	BinTree<TSymTabElement>
//-----------------------------------------------------------
//Коды ошибок возврата из программы
//-----------------
#define Success 0
#define Fail	1
//-----------------------------------------------------------
//Прототипы функций
//-----------------
void Translation(const char *, const char *, unsigned char mode) throw (...);
void CreateOperationTable(BinTree<TOpTabElement> &);
void CreateRegisterTable(BinTree<TSymTabElement> &);
bool ReadCMD(int arc, char* arv[], unsigned char &mode) throw (...);
void PrintInfo(char *string);
//TOpTabElement *AddToOpTab(BinTree<TOpTabElement> &optab, const char *name, unsigned int code, unsigned char type, unsigned int length, bool uumlite, unsigned char info);
//TSymTabElement *AddToSymTab(BinTree<TSymTabElement> &symtab, const char *name, unsigned int address, bool definelabel, bool reg = false);
//-----------------
int operator < (const TOpTabElement &, const TOpTabElement &);
int operator < (const char *, TOpTabElement &);
//-----------------
int operator < (const TSymTabElement &, const TSymTabElement &);
int operator < (const char *, const TSymTabElement &);
//-----------------
void FirstPass(UUMAsm &) throw (...);
void SecondPass(UUMAsm &)throw(...);
//-----------------
void PrintTranslateError(TErrorList *);
//-----------------------------------------------------------
#endif