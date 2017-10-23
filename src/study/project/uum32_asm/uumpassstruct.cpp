#include "uumpassstruct.h"
//-----------------------------------------------------------
//Конструктор-копировщик
TPassLine :: TPassLine(const TPassLine &rhs) throw (...) : Asm(NULL), Address(rhs.Address), OpTabElement(rhs.OpTabElement), Label(rhs.Label), 
															Operands(NULL), Obj(NULL), ObjSize(rhs.ObjSize), Count(0)
{
	//*this = rhs;
	AddAsm(rhs.Asm);
	try
	{
		if (rhs.Obj && rhs.ObjSize)
			{
				//выделение памяти под obj запись и её копирование
				Obj = (unsigned char *)malloc(rhs.ObjSize);
				memcpy(Obj, rhs.Obj, rhs.ObjSize);	
			}
		if (rhs.Operands && rhs.Count)
			{
				//создание нового массива под операнды
				Count = rhs.Count;
				Operands = new TSymTabElement *[Count];
				for (size_t i = 0; i < rhs.Count; i++)
					Operands[i] = rhs.Operands[i];
			}
	}
	//-------------------------------------------------------
	catch (...)
		{
			throw HeapError;
		}
}
//-----------------------------------------------------------
//Деструктор
TPassLine :: ~TPassLine()
{
	if (Asm)
		delete []Asm;
	if (Obj)
		free(Obj);
	if (Operands)
		delete []Operands;
}
//-----------------------------------------------------------
//Добавление строки ассемблерного файла
void TPassLine :: AddAsm(const char *asmtext) throw (...)
{
	if (asmtext)
	{
		size_t length;
		length = strlen(asmtext) + 1;
		if (Asm)
		{
			//удаление старой строки
			delete []Asm;
			Asm = NULL;
		}
		Asm = new char[length];
		Asm[0] = '\0';
		strcpy_s(Asm, length, asmtext);
	}
}
//-------------------------------------------------------------
//Создание объектной записи в памяти
void TPassLine :: CreateObj(size_t size) throw (...)
{
	if (OpTabElement)
	{
		try
		{
			if (Obj)
			{
				//очистим предыдущую память
				free(Obj);
				Obj = NULL;
				ObjSize = size;
			}
			if (OpTabElement->GetOperationTypeInfo() == Operation)
				ObjSize = OpTabElement->Length;
			if (OpTabElement->GetOperationTypeInfo() == Directive && size)
				ObjSize = OpTabElement->Length * size;
			if (ObjSize)
				Obj = (unsigned char *)malloc(ObjSize);
		}
		catch (...)
		{
			throw HeapError;
		}
	}
}
//-------------------------------------------------------------
//Перегрузка оператора присваивания
TPassLine TPassLine :: operator =(const TPassLine &rhs) throw (...)
{
	AddAsm(rhs.Asm);
	if (rhs.Obj)
	{
		if (Obj)
			//очистка старой памяти
			free(Obj);
		if (rhs.Obj && rhs.ObjSize)
		{
			//создание и копирование участка памяти
			Obj = (unsigned char *)malloc(rhs.ObjSize);
			memcpy(Obj, rhs.Obj, rhs.ObjSize);
		}
	}
	Count = rhs.Count;
	if (rhs.Operands && Count)
	{
		//выделение памяти под операнды и их копирование
		Operands = new TSymTabElement *[Count];
		for (size_t i = 0; i < Count; i++)
			Operands[i] = rhs.Operands[i];
	}
	else
		Operands = NULL;
	Address = rhs.Address;
	OpTabElement = rhs.OpTabElement;
	Label = rhs.Label; 
	ObjSize = rhs.ObjSize;
	return *this;
}
//-------------------------------------------------------------
//Назначение: Добавление указателя на команду. Создание необходимого количества указателей на операнды.
//Параметры : Указатель на команду
//Воз. зн.  : -
void TPassLine :: SetCommand(TOpTabElement *command)
{
	{
		OpTabElement = command;
		if (OpTabElement && OpTabElement->GetOperationTypeInfo() == Operation)
		{
			ObjSize = OpTabElement->Length;
			if (Operands)
			{
				delete []Operands;
				Operands = NULL;
			}
			switch (OpTabElement->Type)
			{
			case(2):	Count = 2;
						break;
			case(3):	Count = 4;
						break;
			case(4):	Count = 4;
						break;
			default:	Count = 0;
						break;
			}
			if (Count)
			{
				Operands = new TSymTabElement *[Count];
				for (size_t i = 0; i < Count; i ++)
					Operands[i] = NULL;
			}
		}
	}
}
//-------------------------------------------------------------
//Назначение: Добавление операнда в свободное место записи
void TPassLine :: AddOperand(TSymTabElement *operand)
{
	for (size_t i = 0; i < Count; i++)
	{
		if (!Operands[i])
		{
			Operands[i]	= operand;
			break;
		}
	}
}
//-------------------------------------------------------------
//Назначение: Добавление операнда в указанное место записи
void TPassLine :: SetOperand(TSymTabElement *operand, size_t index)
{
	if (index < Count)
		Operands[index] = operand;
}
//-------------------------------------------------------------
//Назначение: Возврат указателя на операнд
TSymTabElement * TPassLine :: GetOperand(size_t index)
{
	if (index < Count)
		return Operands[index];
	else
		return NULL;
}
//-------------------------------------------------------------
//Назначение: Создание в памяти записи под команду одного из 4 типов, с заполнением всего размера нулями
//Примечание: Создание производится на основании команды. 
//Если в данной лексеме находится директива, команда не выполнится!!!
void TPassLine :: CreateCommand() throw (...)
{
	if (OpTabElement && OpTabElement->GetOperationTypeInfo() == Operation)
	{
		CreateObj();
		if (Obj)
		{
			for (size_t i = 0; i < ObjSize; i++)
				Obj[i] = 0;
		}
	}
}
//--------------------------------------------------------------
//Назначение: Установка в памяти значения кода команды
//Примечание: Лексема должна быть командой
void TPassLine :: SetCommandCode() throw(...)
{
	if (OpTabElement && OpTabElement->GetOperationTypeInfo() == Operation)
	{
		if (!Obj)
			CreateCommand();
		if (Obj && ObjSize)
		{
			Obj[0] = OpTabElement->Code;
			Obj[0] <<= 2;
			//Заполнение нулями оставшиеся поля
			for (size_t i = 1; i < ObjSize; i++)
				Obj[i] = 0;
			if (OpTabElement->Type == 4)
				//устновка признака расширенного формата
				SetServiceBit('e');
		}
	}
}
//-------------------------------------------------------------
//Назначение: Установка в памяти значения поля ЕОП
//Параметры : flag: true - выставить значение из таблицы OpTab, false - сбросить значение поля
//Примечание: Лексема должна быть командой
void TPassLine :: SetEOPField(bool flag) throw (...)
{
	if (OpTabElement && OpTabElement->GetOperationTypeInfo() == Operation)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj && ObjSize)
			flag ? Obj[0] |= OpTabElement->GetEOPInfo() : Obj[0] &= ~MaskEOPInfo;
	}
}
//-------------------------------------------------------------
//Назначение: Установка в памяти служебного бита
//Параметры : name - название бита, на латинском языке, строчными буквами; true - выставить флаг, false - сбросить флаг
//Примечание: Лексема должна быть командой 3 или 4 типа
void TPassLine :: SetServiceBit(char name, bool flag) throw (...)
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && (OpTabElement->Type > 2))
	{
		if (!Obj)
			SetCommandCode();
		if (Obj && (ObjSize > 1))
		{
			unsigned char mask = 0;
			switch (name)
			{
			case('e'):	mask  = MaskBitE;
						break;
			//case('E'):	mask = MaskBitE;
			//			break;
			case('b'):	mask = MaskBitB;
						break;
			//case('B'):	mask = MaskBitB;
			//			break;
			case('n'):	mask = MaskBitN;
						break;
			//case('N'):	mask = MaskBitN;
			//			break;
			case('x'):	mask = MaskBitX;
						break;
			//case('X'):	mask = MaskBitX;
			//			break;
			}
			if (mask)
				flag ? Obj[1] |= mask : Obj[1] &= ~mask;
		}
	}
}
//-------------------------------------------------------------
//Назначение: Запись информации о первом операнде, в команду 2, 3 или 4 типа
//Примечание: Лексема должна быть операцией 2, 3 или 4 типа, а операнд регистром
void TPassLine :: SetReg_1()
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && (OpTabElement->Type > 1) 
		&& 
		Operands[0] && Operands[0]->GetRegInfo() && Operands[0]->DefineLabel)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj)
		{
			unsigned char tempvalue;
			if ((OpTabElement->Type == 2) && (ObjSize > 1))
			{
				//запись регистра в команду второго типа
				tempvalue = Obj[1] & MaskLowHalfByte;
				Obj[1] = Operands[0]->Address;
				Obj[1] <<= 4;
				Obj[1] &= ~MaskLowHalfByte;
				Obj[1] |= tempvalue;
			}
			else
			{
				if ((OpTabElement->Type == 3 || (OpTabElement->Type == 4)) && (ObjSize > 1))
				{
					//запись регистра в команду третьего или четвертого типа
					tempvalue = Obj[1] & MaskHiHalfByte;
					Obj[1] = Operands[0]->Address;
					Obj[1] &= ~MaskHiHalfByte;
					Obj[1] |= tempvalue;
				}
			}
		}
	}
}
//-------------------------------------------------------------
//Назначение: Запись информации о втором операнде, в команду 2 типа
//Примечание: Лексема должна быть операцией 2, а операнд регистром
void TPassLine :: SetReg_2()
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && (OpTabElement->Type > 1) 
		&& 
		Operands[1] && Operands[1]->GetRegInfo() && Operands[1]->DefineLabel)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj)
		{
			unsigned char tempvalue;
			if ((OpTabElement->Type == 2) && (ObjSize > 1))
			{
				//запись регистра в команду второго типа
				tempvalue = Obj[1] & MaskHiHalfByte;
				Obj[1] = Operands[1]->Address;
				Obj[1] &= ~MaskHiHalfByte;
				Obj[1] |= tempvalue;
			}
		}
	}
}
//-------------------------------------------------------------
//Назначение: Запись 16 разрядного числа в смещение, в команду 3 типа
void TPassLine :: SetDisp(short disp)
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && OpTabElement->Type == 3)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj && ObjSize == 4)
			//запись числа через жопу
			RotateWrite(disp, 2);//, 3);
	}
}
//-------------------------------------------------------------
//Назначение: Запись 32 разрядного числа в поле полного адреса, команды 4 типа
void TPassLine :: SetMem(int mem)
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && OpTabElement->Type == 4)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj && ObjSize == 6)
			//запись числа через жопу
			RotateWrite(mem, 2);//, 5);
	}
}
//-------------------------------------------------------------
//Назначение: Записать число в нормальном для УУМ и через жопу для x86 виде в память
//Параметры : value - значение для записи; startpos, lastpos - начальная и конечная позиция в памяти (Obj)
template <class Type>
void TPassLine :: RotateWrite(Type value, size_t startpos)//, size_t lastpos)
{
	size_t typesize = sizeof(Type);
	size_t lastpos = startpos + typesize - 1;
//	if (size_t startpos, size_t lastpos(index + typesize - 1) < ObjSize)
	if ((lastpos < ObjSize) && (typesize <= lastpos - startpos + 1))
	{
		Type *pValue = &value;
		for (size_t sourceindex = 0, destindex = lastpos; sourceindex < typesize; sourceindex++, destindex--)
		{
			Obj[destindex] = ((unsigned char *)pValue)[sourceindex];
		}
	}
}
//-------------------------------------------------------------
//Назначение: Установка размера объектной записи в памяти
void TPassLine :: SetObjSize(size_t objsize) throw (...)
{
	if (Obj)
	{	//очистка предыдущей памяти
		free(Obj);
		Obj = NULL;
		if (objsize)
		{
			//Obj = (unsigned char *)malloc(objsize);
			CreateObj(objsize);
		}
	}
	else
	{
		if (OpTabElement->GetOperationTypeInfo() == Operation)
			ObjSize = OpTabElement->Length;
		if (OpTabElement->GetOperationTypeInfo() == Directive)
			ObjSize = OpTabElement->Length * objsize;
	}
}
//-------------------------------------------------------------