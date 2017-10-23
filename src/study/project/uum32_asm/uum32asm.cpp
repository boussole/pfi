#include "UUM32Asm.h"
//-----------------------------------------------------------
//Параметры командной строки (необязательные  и обязательные):
//								- имя входного файла *.asm
//								- имя выходного файла *.obj
//								- режим трансляции (полный или сокращенный набор команд, по умолчанию полный)
//								- чувствительность к регистру букв
//								- создание файла листинга
//								- видимость комментариев в дебагере
int main(int arc, char* arv[])
{
	//-----------------------
	setlocale(LC_ALL, "Rus");
	//-----------------------
	unsigned char mode = 0;
	if (!ReadCMD(arc, arv, mode))
		return 0;
	//-----------------------
	try
	{
		Translation(arv[1], NULL, mode);
	//	Translation("1.asm", NULL, mode);
	}
	catch (...)
	{
		printf(StopTranslation);
		return Fail;
	}
	printf(SuccTranslation);
	return Success;
}
//-----------------------------------------------------------
//Назначение: Чтение данных передаваемых через командную строку
bool ReadCMD(int arc, char* arv[], unsigned char &mode) throw (...)
{
	bool Result = true;
	mode = CASE + LITE;
	for (short i = 1; i < arc; i++)
	{
		if (!strcmp(arv[i], "/c"))
			mode = mode & ~CASE;
		if (!strcmp(arv[i], "/l"))
			mode = mode & ~LITE;
		if (!strcmp(arv[i], "/?"))
		{
			PrintInfo(arv[0]);
			Result = false;
			break;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Печать помощи в стандартный файл вывода
//Параметры : Строка, имя программы
void PrintInfo(char *string)
{
	printf_s("\nЗапуск трансляции команд ассемблера в их объектное представление\n");
	printf_s("%s [/c] [/l] [/?]\n", string);
	printf_s("/c - работа транслятора с учетом регистра букв\n");
	printf_s("/l - работа транслятора с упрощенным набором команд\n");
	printf_s("/? - вывод справки в стандартный файл вывода\n");
}
//-----------------------------------------------------------
//Назначение: обработка файла с мнемокодом в файл с объектным кодом
//Параметры : путь к файлу с мнемокодом
//Возв. знач: -
void Translation(const char *inputfilename, const char *outputfilename, unsigned char mode) throw (...)
{
	//-------------
	printf_s(Logo);
	//-------------
	BinTree<TOpTabElement> optab;
	BinTree<TSymTabElement> symtab;
	UUMAsm assembler;
	try
	{
		CreateOperationTable(optab);
		CreateRegisterTable(symtab);
		assembler.SetValue(inputfilename, outputfilename, optab, symtab, mode);
		FirstPass(assembler);
		SecondPass(assembler);
	}
	catch (UUMException Exception)
	{
		switch (Exception)
		{
			case (OpenAsmFile):		printf_s("%s %s\n", OpenAsmFileText, inputfilename);
									break;
			case (NoFileName):		printf_s(NoFileNameText);
									break;
			case (FileExists):		printf_s("%s %s\n", FileExistsText, inputfilename);
									break;
			case (CreateObjFile):	printf_s(CreateObjFileText);
									break;
			case (WriteObjFile):	printf_s(WriteObjFileText);
									break;
			case (HeapError):		printf_s(HeapErrorText);
									break;
			case (AsmError):		PrintTranslateError(assembler.GetErrorList());
									break;
		}
		throw;
	}
	//-------------
}
//===========================================================
//Назначение: сравнение ключевых полей таблицы операций
//Параметры : элементы таблиц операций (структуры) 
//Воз. зн.  : -
int operator < (const TOpTabElement &left, const TOpTabElement &right)
{
	return strcmp(left.Name, right.Name);
}
//-----------------------------------------------------------
int operator < (const char *left, TOpTabElement &right)
{
	return strcmp(left, right.Name);
}
//-----------------------------------------------------------
int operator < (const TSymTabElement &left, const TSymTabElement &right)
{
	return strcmp(left.Name, right.Name);
}
//-----------------------------------------------------------
int operator < (const char *left, const TSymTabElement &right)
{
	return strcmp(left, right.Name);
}
//===========================================================
//Назначение: Создание таблицы операции UUM/DC (UUM Lite)
//Параметры : Ссылка на таблицу
//Возв. зн. : -
//Примечание: В даной версии программы данные зашиты в код, в дальнейшем возможно считывание 
//			  из внешнего файла, к примеру *.ini.
//			  Дання таблица заполняется вначале работы транслятора и не подлежит изменению 
//			  в процессе работы!!!
//			  Расширенные форматы команд так же располагаются в данной таблице, в дальнейшем
//            возможно сокращение таблицы...
//            Команды располагаются в верхнем регистре
void CreateOperationTable(BinTree<TOpTabElement> &optab)
{
	
	//№0 +
	AddToOpTab(optab, "NOP", 0x0, 1, 1, true, NoOperands + ZeroEOP + Operation);
	//№1 +
	AddToOpTab(optab, "ADDB", 0x1, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "ADDH", 0x1, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "ADDW", 0x1, 3, 4, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "ADD", 0x1, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//- +
	AddToOpTab(optab, "+ADDB", 0x1, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+ADDH", 0x1, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+ADDW", 0x1, 4, 6, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+ADD", 0x1, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№2 +
	AddToOpTab(optab, "SUBB", 0x2, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "SUBH", 0x2, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "SUBW", 0x2, 3, 4, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "SUB", 0x2, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+SUBB", 0x2, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+SUBH", 0x2, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+SUBW", 0x2, 4, 6, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+SUB", 0x2, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№3 +
	AddToOpTab(optab, "COMPB", 0x3, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "COMPH", 0x3, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "COMPW", 0x3, 3, 4, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "COMP", 0x3, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+COMPB", 0x3, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+COMPH", 0x3, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+COMPW", 0x3, 4, 6, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+COMP", 0x3, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№4 
	AddToOpTab(optab, "COMPR", 0x4, 2, 2, true, RegisterRegister + Operation);
	//№5 +
	AddToOpTab(optab, "LDB", 0x5, 3, 4, true, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "LDH", 0x5, 3, 4, true, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "LDW", 0x5, 3, 4, true, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "LD", 0x5, 3, 4, true, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+LDB", 0x5, 4, 6, true, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+LDH", 0x5, 4, 6, true, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+LDW", 0x5, 4, 6, true, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+LD", 0x5, 4, 6, true, RegisterMemory + WordEOP + Operation);
	//№6 +
	AddToOpTab(optab, "STB", 0x6, 3, 4, true, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "STH", 0x6, 3, 4, true, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "STW", 0x6, 3, 4, true, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "ST", 0x6, 3, 4, true, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+STB", 0x6, 4, 6, true, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+STH", 0x6, 4, 6, true, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+STW", 0x6, 4, 6, true, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+ST", 0x6, 4, 6, true, RegisterMemory + WordEOP + Operation);
	//№7 +
	AddToOpTab(optab, "PUSHB", 0x7, 2, 2, true, JustRegister + ByteEOP + Operation);
	AddToOpTab(optab, "PUSHH", 0x7, 2, 2, true, JustRegister + HalfEOP + Operation);
	AddToOpTab(optab, "PUSHW", 0x7, 2, 2, true, JustRegister + WordEOP + Operation);
	AddToOpTab(optab, "PUSH", 0x7, 2, 2, true, JustRegister + WordEOP + Operation);
	AddToOpTab(optab, "PUSH", 0x7, 2, 2, true, JustRegister + WordEOP + Operation);
	//№8 +
	AddToOpTab(optab, "POPB", 0x8, 2, 2, true, JustRegister + ByteEOP + Operation);
	AddToOpTab(optab, "POPH", 0x8, 2, 2, true, JustRegister + HalfEOP + Operation);
	AddToOpTab(optab, "POPW", 0x8, 2, 2, true, JustRegister + WordEOP + Operation);
	AddToOpTab(optab, "POP", 0x8, 2, 2, true, JustRegister + WordEOP + Operation);
	//№9
	AddToOpTab(optab, "CLEAR", 0x9, 2, 2, true, JustRegister + Operation);
	//№10 +
	AddToOpTab(optab, "MULB", 0xA, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "MULH", 0xA, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "MULW", 0xA, 3, 4, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "MUL", 0xA, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+MULB", 0xA, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+MULH", 0xA, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+MULW", 0xA, 4, 6, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+MUL", 0xA, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№11 +
	AddToOpTab(optab, "DIVB", 0xB, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "DIVH", 0xB, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "DIVW", 0xB, 3, 4, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "DIV", 0xB, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+DIVB", 0xB, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+DIVH", 0xB, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+DIVW", 0xB, 4, 6, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+DIV", 0xB, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№12 +
	AddToOpTab(optab, "INCMB", 0xC, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "INCMH", 0xC, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "INCMW", 0xC, 3, 4, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "INCM", 0xC, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+INCMB", 0xC, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+INCMH", 0xC, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+INCMW", 0xC, 4, 6, false, RegisterMemory + WordEOP + Operation);
	AddToOpTab(optab, "+INCM", 0xC, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№13
	AddToOpTab(optab, "TDB", 0xD, 3, 4, true, JustMemory + ByteEOP + Operation);
	AddToOpTab(optab, "TDH", 0xD, 3, 4, true, JustMemory + HalfEOP + Operation);
	AddToOpTab(optab, "TDW", 0xD, 3, 4, true, JustMemory + WordEOP + Operation);
	AddToOpTab(optab, "TD", 0xD, 3, 4, true, JustMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+TDB", 0xD, 4, 6, true, JustMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+TDH", 0xD, 4, 6, true, JustMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+TDW", 0xD, 4, 6, true, JustMemory + WordEOP + Operation);
	AddToOpTab(optab, "+TD", 0xD, 4, 6, true, JustMemory + WordEOP + Operation);
	//№14
	AddToOpTab(optab, "RDB", 0xE, 3, 4, true, JustMemory + ByteEOP + Operation);
	AddToOpTab(optab, "RDH", 0xE, 3, 4, true, JustMemory + HalfEOP + Operation);
	AddToOpTab(optab, "RDW", 0xE, 3, 4, true, JustMemory + WordEOP + Operation);
	AddToOpTab(optab, "RD", 0xE, 3, 4, true, JustMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+RDB", 0xE, 4, 6, true, JustMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+RDH", 0xE, 4, 6, true, JustMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+RDW", 0xE, 4, 6, true, JustMemory + WordEOP + Operation);
	AddToOpTab(optab, "+RD", 0xE, 4, 6, true, JustMemory + WordEOP + Operation);
	//№15
	AddToOpTab(optab, "WDB", 0xF, 3, 4, true, JustMemory + ByteEOP + Operation);
	AddToOpTab(optab, "WDH", 0xF, 3, 4, true, JustMemory + HalfEOP + Operation);
	AddToOpTab(optab, "WDW", 0xF, 3, 4, true, JustMemory + WordEOP + Operation);
	AddToOpTab(optab, "WD", 0xF, 3, 4, true, JustMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+WDB", 0xF, 4, 6, true, JustMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+WDH", 0xF, 4, 6, true, JustMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+WDW", 0xF, 4, 6, true, JustMemory + WordEOP + Operation);
	AddToOpTab(optab, "+WD", 0xF, 4, 6, true, JustMemory + WordEOP + Operation);
	//----------------------------------------
	//16-18 - неизвестный формат, неизвестный размер
	/*AddToOpTab(optab, "SIO", 0x10, 0, 0, true, NoOperands + Operation);
	AddToOpTab(optab, "HIO", 0x11, 0, 0, true, NoOperands + Operation);
	AddToOpTab(optab, "TIO", 0x12, 0, 0, true, NoOperands + Operation);*/
	//№19
	AddToOpTab(optab, "JMP", 0x13, 4, 6, true, JustMemory + Operation);
	//AddToOpTab(optab, "+JMP", 0x13, 4, 6, true, JustMemory + Operation);
	//№20
	AddToOpTab(optab, "JEQ", 0x14, 4, 6, true, JustMemory + Operation);
	//AddToOpTab(optab, "+JEQ", 0x14, 4, 6, true, JustMemory + Operation);
	//№21
	AddToOpTab(optab, "JLT", 0x15, 4, 6, true, JustMemory + Operation);
	//AddToOpTab(optab, "+JLT", 0x15, 4, 6, true, JustMemory + Operation);
	//№22
	AddToOpTab(optab, "JGT", 0x16, 4, 6, true, JustMemory + Operation);
	//AddToOpTab(optab, "+JGT", 0x16, 4, 6, true, JustMemory + Operation);
	//№23
	AddToOpTab(optab, "CALL", 0x17, 4, 6, true, JustMemory + Operation);
	//AddToOpTab(optab, "+CALL", 0x17, 4, 6, true, JustMemory + Operation);
	//№24
	AddToOpTab(optab, "RET", 0x18, 1, 1, true, NoOperands + Operation);
	//№25
	AddToOpTab(optab, "INCR", 0x19, 2, 2, true, RegisterRegister + Operation);
	//№26
	AddToOpTab(optab, "ADDR", 0x1A, 2, 2, true, RegisterRegister + Operation);
	//№27
	AddToOpTab(optab, "MOV", 0x1B, 2, 2, true, RegisterRegister + Operation);
	//№28
	/*AddToOpTab(optab, "SHLB", 0x1C, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "SHLH", 0x1C, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "SHLW", 0x1C, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+SHLB", 0x1C, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+SHLH", 0x1C, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+SHLW", 0x1C, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№29
	AddToOpTab(optab, "SHRB", 0x1D, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "SHRH", 0x1D, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "SHRW", 0x1D, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+SHRB", 0x1D, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+SHRH", 0x1D, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+SHRW", 0x1D, 4, 6, false, RegisterMemory + WordEOP + Operation);*/
	//№30
	AddToOpTab(optab, "MULR", 0x1E, 2, 2, true, RegisterRegister + Operation);
	//№31
	AddToOpTab(optab, "DIVR", 0x1F, 2, 2, true, RegisterRegister + Operation);
	//№32
	/*AddToOpTab(optab, "SBB", 0x20, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "SBH", 0x20, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "SBW", 0x20, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+SBB", 0x20, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+SBH", 0x20, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+SBW", 0x20, 4, 6, false, RegisterMemory + WordEOP + Operation);
	//№33
	AddToOpTab(optab, "RSBB", 0x21, 3, 4, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "RSBH", 0x21, 3, 4, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "RSBW", 0x21, 3, 4, false, RegisterMemory + WordEOP + Operation);
	//-
	AddToOpTab(optab, "+RSBB", 0x21, 4, 6, false, RegisterMemory + ByteEOP + Operation);
	AddToOpTab(optab, "+RSBH", 0x21, 4, 6, false, RegisterMemory + HalfEOP + Operation);
	AddToOpTab(optab, "+RSBW", 0x21, 4, 6, false, RegisterMemory + WordEOP + Operation);*/
	//№34
	AddToOpTab(optab, "SUBR", 0x22, 2, 2, true, RegisterRegister + Operation);
	//№35
	AddToOpTab(optab, "ANDR", 0x23, 2, 2, true, RegisterRegister + Operation);
	//№36
	AddToOpTab(optab, "ORR", 0x24, 2, 2, true, RegisterRegister + Operation);
	//№37
	AddToOpTab(optab, "XORR", 0x25, 2, 2, true, RegisterRegister + Operation);
	//-------------------------------------------------------
	//Директивы
	//AddToOpTab(optab, "BYTE", 0, 6, UUMBYTE, true, LengthOpSize + Directive);
	//AddToOpTab(optab, "HALF", 0, 6, UUMHALF, true, LengthOpSize + Directive);
	//AddToOpTab(optab, "WORD", 0, 6, UUMWORD, true, LengthOpSize + Directive);
	AddToOpTab(optab, "RESB", 0, 5, UUMBYTE, true, ValueOpSize + Directive);
	AddToOpTab(optab, "RESH", 0, 5, UUMHALF, true, ValueOpSize + Directive);
	AddToOpTab(optab, "RESW", 0, 5, UUMWORD, true, ValueOpSize + Directive);
}
//-----------------------------------------------------------
//Назначение: Создание таблицы регистров досутпных в УУМ
//Параметры : Ссылка на таблицу
//Возв. зн. : -
//Примечание: Таблица используется для сохранения ссылок используемых в программе. Помимо ссылок она хранит в себе имена
//			  и значения регистров учебной машины. Значения регистров заполняются в начале работы программы и не подлежат
//			  изменению в процессе ее работы. Названия регистров располагаются в таблице в верхнем регистре.
//			  В дальнейшем значения регистров можно будет держать во внешнем файле.
void CreateRegisterTable(BinTree<TSymTabElement> &symtab)
{
	AddToSymTab(symtab, "A", 0, true, AccumulatorRegister);
	AddToSymTab(symtab, "B", 1, true, BaseRegister);
	AddToSymTab(symtab, "X", 2, true, IndexRegister);
	AddToSymTab(symtab, "SW", 3, true, SWRegister);
	char regname[LABELNAMESIZE];
	regname[0] = NULL;
	for (unsigned int i = 0, j = 4; i < USERREGCOUNT; i++, j++)
	{
		sprintf_s(regname, LABELNAMESIZE, "R%d", i);
		AddToSymTab(symtab, regname, j, true, RONRegister);
	}
}
//-----------------------------------------------------------
TOpTabElement *AddToOpTab(BinTree<TOpTabElement> &optab, const char *name, unsigned int code, unsigned char type, unsigned int length, bool uumlite, unsigned char infofield)
{
	TOpTabElement temp;
	temp.Add(name, code, type, length, uumlite, infofield);
	return optab.Add(temp);
}
TSymTabElement *AddToSymTab(BinTree<TSymTabElement> &symtab, const char *name, unsigned int address, bool definelabel, unsigned char reg)
{
	TSymTabElement temp;
	temp.Add(name, address, definelabel, reg);
	return symtab.Add(temp);
}
//-----------------------------------------------------------
//Назначение: Первый проход транслятора по входному файлу
//Параметры :
//Возв. зн. : -
void FirstPass(UUMAsm &assembler) throw (...)
{
	printf(FirstPassStart);
	try
	{
		assembler.StartFirstPass();
	}
	catch (...)
	{
		printf_s(FirstPassFail);
		throw;
	}
	printf(FirstPassSucc);
}
//------------------------------------------------------------
//Назначение: Второй проход транслятора, создание выходного (объектного) файла
//Параметры :
//Возв. зн. : -
void SecondPass(UUMAsm &assembler) throw(...)
{
	printf(SecondPassStart);
	try
	{
		assembler.StartSecondPass();
	}
	catch(...)
	{
		printf_s(SecondPassFail);
		throw;
	}
	printf(SecondPassSucc);
}
//------------------------------------------------------------
//Назначение: Печать ошибок, произошедших в ходе трансляции
//Параметры : Спиок ошибок
//Возв. зн. : -
void PrintTranslateError(TErrorList *errorlist)
{
	if (!errorlist)
		return;
	const char *tmp = NULL;
	TError *error;
	for (size_t i = 0; i < errorlist->GetCount(); i++)
	{
		error = errorlist->GetError(i);
		switch (error->GetErrorCode())
		{
		case(NoLabelName):		tmp = NoLabelNameText;
								break;
		case(BadLabelName):		tmp = BadLabelNameText;
								break;
		case(DefLabelName):		tmp = DefLabelNameText;
								break;
		case(ResLabelName):		tmp = ResLabelNameText;
								break;
		case(UnknownLabel):		tmp = UnknownLabelText;
								break;
		case(UndefSymbols):		tmp = UndefSymbolsText;
								break;
		/*case(NotEndLine) :		tmp = NotEndLineText;
								break;*/
		/*case(NoOperBefore):		tmp = NoOperBeforeText;
								break;
		case(NoOperAfter):		tmp = NoOperAfterText;
								break;*/
		case(NeedRegister):		tmp = NeedRegisterText;
								break;
		case(BadSymOperand):	tmp = BadSymOperandText;
								break;
		//-------------------
		case(FirstTypeError):	tmp = FirstTypeErrorText;
								break;
		case(SecTypeError):		tmp = SecTypeErrorText;
								break;
		case(ThirdTypeError):	tmp = ThirdTypeErrorText;
								break;
		case(FourTypeError):	tmp = FourTypeErrorText;
								break;
		//-------------------
		case(SingleNotFound):	tmp = SingleNotFoundText;
								break;
		case(DoubleNotFound):	tmp = DoubleNotFoundText;
								break;
		//-------------------
		case(ResOperandName):	tmp = ResOperandNameText;
								break;
		//-------------------
		case(UknownSymbols) :	tmp = UknownSymbolsText;
								break;
		//-------------------
		case(SecondLabelOperand): tmp = SecondLabelOperandText;
								break;
		//-------------------
		case(SecondBaseRegister): tmp = SecondBaseRegisterText;
								break;
		//-------------------
		case(SecondIndexReg):	tmp = SecondIndexRegText;
								break;
		//-------------------
		case(BaseIndexOnly):	tmp = BaseIndexOnlyText;
								break;
		//-------------------
		case(NoOperandName):	tmp = NoOperandNameText;
								break;
		//-------------------
		case(IAddress):			tmp = IAddressText;
								break;
		//-------------------
		case(NAddress):			tmp = NAddressText;
								break;
		//-------------------
		case(UndeclID):			tmp = UndeclIDText;
								break;
		//-------------------
		case(NoValue):			tmp = NoValueText;
								break;
		//-------------------
		case(BadOperand):		tmp = BadOperandText;
								break;
		//-------------------
		case(OverFlow):			tmp = OverFlowText;
								break;
		//-------------------
		case(OverDisp):			tmp = OverDispText;
								break;
		//-------------------
		case(FifthTypeError):	tmp = FifthTypeErrorText;
								break;
		//-------------------
		default:				tmp = NULL;
								break;
		}
		printf_s("(%d) %s %s\n", error->GetLine(), tmp, error->GetText());
	}
}
//------------------------------------------------------------