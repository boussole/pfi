#ifndef __UUMTableStruct_h
	#define __UUMTableStruct_h
//-----------------------------------------------------------
#ifndef __STRING_H
	#include <string.h>
	#define __STRING_H
#endif

#ifndef __UUMMess_h
	#include "uummess.h"
#endif
//-----------------------------------------------------------
//#define OPERATIONNAMESIZE	10
#define LABELNAMESIZE       10
#define USERREGCOUNT		12
//-----------------------------------------------------------
//Структуры
//-----------------
#include <pshpack1.h>
//-----------------
#define MaskEOPInfo				3
#define MaskOperandsInfo		28
#define MaskOperationTypeInfo	96
//#define MaskOperandsInfo		7
//#define MaskOperationTypeInfo	24
//#define MaskEOPInfo				192
//-----------------
//Коды операций таблицы OpTab
enum EOPInfo			{ZeroEOP = 0, ByteEOP = 1, HalfEOP = 2, WordEOP = 3};		//0 - 1 биты
enum OperandsInfo		{NoOperands = 0, JustRegister = 4, JustMemory = 8, RegisterRegister = 12, RegisterMemory = 16, ValueOpSize = 20, LengthOpSize = 24};	//2 - 4 биты
enum OperationTypeInfo	{Operation = 32, Directive = 64};	//
//----------------
//enum OperandsInfo		{NoOperands, JustRegister, JustMemory, RegisterRegister, RegisterMemory, ValueOpSize, LengthOpSize};
//enum OperationTypeInfo	{Operation = 8, Directive = 16};
//enum EOPInfo			{ZeroEOP = 0, ByteEOP = 64, HalfEOP = 128, WordEOP = 192};//{ByteEOP = 8, HalfEOP = 16, WordEOP = 24};
//-----------------
struct TOpTabElement
{
	TOpTabElement()  : Name(NULL), Code(0), Type(0), Length(0), UUMLite(false), InfoField(0) {}
	//-----------------------------------------------------------
	TOpTabElement(const TOpTabElement &rhs) : Name(NULL), Code(0), Type(0), Length(0)
	{
		Add(rhs.Name, rhs.Code, rhs.Type, rhs.Length, rhs.UUMLite, rhs.InfoField);		
	}
	//-----------------------------------------------------------
	unsigned char GetOperandsInfo()
	{
		return (InfoField & MaskOperandsInfo);
	}
	//-----------------------------------------------------------
	unsigned char GetEOPInfo()
	{
		return (InfoField & MaskEOPInfo);
	}
	//-----------------------------------------------------------
	unsigned char GetOperationTypeInfo()
	{
		return (InfoField & MaskOperationTypeInfo);
	}
	//-----------------------------------------------------------
	TOpTabElement operator = (const TOpTabElement &rhs)
	{
		Add(rhs.Name, rhs.Code, rhs.Type, rhs.Length, rhs.UUMLite, rhs.InfoField);
		return *this;
	}
	//-----------------------------------------------------------
	~TOpTabElement() 
	{
		if (Name) 
		{
			delete []Name;
			Name = NULL;
		}
	}
	//-----------------------------------------------------------
	void Add(const char *name, unsigned int code, unsigned char type, unsigned int length, bool uumlite, unsigned char infofield) throw(...)
		{
			if (!name)
				throw;
			size_t len = strlen(name);
		try
			{		
				if (Name)
				{
					delete []Name;
					Name = NULL;
				}
				Name = new char[len + 1];
			}
		catch (...)
			{
				throw HeapError;
			}
		strcpy_s(Name, len + 1, name);
		Code = code;
		Type = type;
		Length = length;
		UUMLite = uumlite;
		InfoField = infofield;
		}
	//-----------------------------------------------------------
	//char			Name[OPERATIONNAMESIZE]	;			//Название команды
	char *			Name					;
	unsigned int	Code					;			//Код операции (HEX)
	unsigned char	Type					;			//Тип команды
	unsigned int	Length					;			//Длина команды
	bool			UUMLite					;			//Признак принадлежности к упрощенному набору команд
	unsigned char	InfoField				;			//Поле со служебной информацией:
};
//-----------------
#define MaskRegInfo	7
enum TSymInfo {AccumulatorRegister = 1, BaseRegister, IndexRegister, SWRegister, RONRegister};
//Структура таблицы имен SymTab
struct TSymTabElement
{
	TSymTabElement() : Name(NULL), Address(0), Reg(0) {}
	//-----------------------------------------------------------
	TSymTabElement(const TSymTabElement &rhs) : Name(NULL), Address(0), Reg(0)
	{
		Add(rhs.Name, rhs.Address, rhs.DefineLabel, rhs.Reg);
	}
	//-----------------------------------------------------------
	TSymTabElement operator = (const TSymTabElement &rhs)
	{
		Add(rhs.Name, rhs.Address, rhs.DefineLabel, rhs.Reg);
		return *this;
	}
	//-----------------------------------------------------------
	~TSymTabElement() 
	{
		if (Name) 
		{
			delete []Name;
			Name = NULL;
		}
	}
	//-----------------------------------------------------------
	unsigned char GetRegInfo()
	{
		return (Reg & MaskRegInfo);
	}
	//-----------------------------------------------------------
	void Add(const char *name, int address, bool definelabel, unsigned char reg) throw(...)
		{
			if (!name)
				throw;
			size_t length = strlen(name);
		try
			{		
				if (Name)
				{
					delete []Name;
					Name = NULL;
				}
				Name = new char[length + 1];
			}
		catch (...)
			{
				throw HeapError;
			}
			strcpy_s(Name, length + 1, name);
			Address = address;
			DefineLabel = definelabel;
			Reg = reg;
		}
	//-----------------------------------------------------------}
	//char			Name	[LABELNAMESIZE];			//Название метки
	char *			Name;
	unsigned int	Address;							//Адрес метки
	bool			DefineLabel;						//Признак разрешимости метки
	unsigned char	Reg;								//Признак регистра
};
//-----------------
//Структура таблицы литералов
//struct TLitTabElement
//{
//};
//-----------------
#include <poppack.h>
//-----------------------------------------------------------
#endif