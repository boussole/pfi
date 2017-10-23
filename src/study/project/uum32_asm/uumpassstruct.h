#ifndef __UUMPassStruct_h
	#define __UUMPassStruct_h
//-----------------------------------------------------------
#ifndef __MALLOC_H
	#include <malloc.h>
#endif

#ifndef __UUMTableStruct_h
	#include "uumtablestruct.h"
#endif

#ifndef __UUMMess_h
	#include "uummess.h"
#endif
//-----------------------------------------------------------
#define	UUMBYTE		1
#define UUMHALF		2
#define UUMWORD		4
//-----------------------------------------------------------
#define MaskBitE	128
#define	MaskBitB	64
#define	MaskBitN	32
#define	MaskBitX	16
//-----------------------------------------------------------
#define MaskHiHalfByte	0xF0
#define MaskLowHalfByte	0x0F
//-----------------------------------------------------------
//Класс, содержащий всю информацию об одной строке в обрабатываемой программе
//Назначение: Хранение информации одной строки. Формирование объектного кода и файла листинга
class TPassLine
{
public:
	TPassLine() throw (...) : Asm(NULL), Address(0), OpTabElement(NULL), Label(NULL), Operands(NULL), Obj(NULL), ObjSize(0), Count(0) {}
	TPassLine(const TPassLine &) throw (...);
	~TPassLine();
	TPassLine operator = (const TPassLine &) throw (...);
	void AddAsm(const char *) throw (...);
	void AddOperand(TSymTabElement *operand);
	void CreateObj(size_t size = 0) throw (...);
	//------------------------------------------
	void CreateCommand() throw (...);
	void SetCommandCode() throw (...);
	void SetEOPField(bool flag = true) throw (...);
	void SetServiceBit(char name, bool flag = true) throw (...);
	void SetReg_1();
	void SetReg_2();
	void SetDisp(short disp);
	void SetMem(int mem);
	void SetObjSize(size_t objsize) throw (...);
	//------------------------------------------
	void SetAddress(size_t address) {Address = address;}
	void SetCommand(TOpTabElement *command);
	void SetLabel(TSymTabElement *label) {Label = label;}
	void SetOperand(TSymTabElement *operand, size_t index);
	void SetBaseOperand(TSymTabElement *base) {if (Count > 2) Operands[2] = base;}
	void SetIndexOperand(TSymTabElement *index) {if (Count > 2) Operands[3] = index;}
	//unsigned char *GetObj() {return Obj;}
	unsigned char *GetObj() const {return Obj;}
	TSymTabElement *GetOperand(size_t index);
	TSymTabElement *GetLabel() {return Label;}
	TSymTabElement *GetReg1Operand() {if (Count) return Operands[0]; return NULL;}
	TSymTabElement *GetReg2Operand() {if (Count > 1) return Operands[1]; return NULL;}
	TSymTabElement *GetMemOperand() {if (Count > 1) return Operands[1]; return NULL;}
	TSymTabElement *GetBaseOperand() {if (Count > 2) return Operands[2]; return NULL;}
	TSymTabElement *GetIndexOperand() {if (Count > 2) return Operands[3]; return NULL;}
	//-------------------------------------------
	TOpTabElement *GetCommand() {return OpTabElement;}
	size_t GetOperandsCount() {return Count;}
	size_t GetObjSize() {return ObjSize;}
private:
	template <class Type>
	void RotateWrite(Type value, size_t startpos);//, size_t lastpos);
	char *Asm;									//Строка кода в файле asm
	size_t Address;								//Адрес предложения
	TOpTabElement *OpTabElement;				//Указатель на информацию в таблице операций и директив
	TSymTabElement *Label;						//Указатель на информацию о метке
	TSymTabElement **Operands;					//Указатель на информацию об операндах
	unsigned char *Obj;							//Данные для выходного файла
	size_t ObjSize;								//Размер объектной записи (в соответсвии с форматом команды или величиной директивы)
	size_t Count;								//Количество операндов
};
//-----------------------------------------------------------
#endif