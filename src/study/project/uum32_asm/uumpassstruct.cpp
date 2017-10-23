#include "uumpassstruct.h"
//-----------------------------------------------------------
//�����������-����������
TPassLine :: TPassLine(const TPassLine &rhs) throw (...) : Asm(NULL), Address(rhs.Address), OpTabElement(rhs.OpTabElement), Label(rhs.Label), 
															Operands(NULL), Obj(NULL), ObjSize(rhs.ObjSize), Count(0)
{
	//*this = rhs;
	AddAsm(rhs.Asm);
	try
	{
		if (rhs.Obj && rhs.ObjSize)
			{
				//��������� ������ ��� obj ������ � � �����������
				Obj = (unsigned char *)malloc(rhs.ObjSize);
				memcpy(Obj, rhs.Obj, rhs.ObjSize);	
			}
		if (rhs.Operands && rhs.Count)
			{
				//�������� ������ ������� ��� ��������
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
//����������
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
//���������� ������ ������������� �����
void TPassLine :: AddAsm(const char *asmtext) throw (...)
{
	if (asmtext)
	{
		size_t length;
		length = strlen(asmtext) + 1;
		if (Asm)
		{
			//�������� ������ ������
			delete []Asm;
			Asm = NULL;
		}
		Asm = new char[length];
		Asm[0] = '\0';
		strcpy_s(Asm, length, asmtext);
	}
}
//-------------------------------------------------------------
//�������� ��������� ������ � ������
void TPassLine :: CreateObj(size_t size) throw (...)
{
	if (OpTabElement)
	{
		try
		{
			if (Obj)
			{
				//������� ���������� ������
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
//���������� ��������� ������������
TPassLine TPassLine :: operator =(const TPassLine &rhs) throw (...)
{
	AddAsm(rhs.Asm);
	if (rhs.Obj)
	{
		if (Obj)
			//������� ������ ������
			free(Obj);
		if (rhs.Obj && rhs.ObjSize)
		{
			//�������� � ����������� ������� ������
			Obj = (unsigned char *)malloc(rhs.ObjSize);
			memcpy(Obj, rhs.Obj, rhs.ObjSize);
		}
	}
	Count = rhs.Count;
	if (rhs.Operands && Count)
	{
		//��������� ������ ��� �������� � �� �����������
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
//����������: ���������� ��������� �� �������. �������� ������������ ���������� ���������� �� ��������.
//��������� : ��������� �� �������
//���. ��.  : -
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
//����������: ���������� �������� � ��������� ����� ������
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
//����������: ���������� �������� � ��������� ����� ������
void TPassLine :: SetOperand(TSymTabElement *operand, size_t index)
{
	if (index < Count)
		Operands[index] = operand;
}
//-------------------------------------------------------------
//����������: ������� ��������� �� �������
TSymTabElement * TPassLine :: GetOperand(size_t index)
{
	if (index < Count)
		return Operands[index];
	else
		return NULL;
}
//-------------------------------------------------------------
//����������: �������� � ������ ������ ��� ������� ������ �� 4 �����, � ����������� ����� ������� ������
//����������: �������� ������������ �� ��������� �������. 
//���� � ������ ������� ��������� ���������, ������� �� ����������!!!
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
//����������: ��������� � ������ �������� ���� �������
//����������: ������� ������ ���� ��������
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
			//���������� ������ ���������� ����
			for (size_t i = 1; i < ObjSize; i++)
				Obj[i] = 0;
			if (OpTabElement->Type == 4)
				//�������� �������� ������������ �������
				SetServiceBit('e');
		}
	}
}
//-------------------------------------------------------------
//����������: ��������� � ������ �������� ���� ���
//��������� : flag: true - ��������� �������� �� ������� OpTab, false - �������� �������� ����
//����������: ������� ������ ���� ��������
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
//����������: ��������� � ������ ���������� ����
//��������� : name - �������� ����, �� ��������� �����, ��������� �������; true - ��������� ����, false - �������� ����
//����������: ������� ������ ���� �������� 3 ��� 4 ����
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
//����������: ������ ���������� � ������ ��������, � ������� 2, 3 ��� 4 ����
//����������: ������� ������ ���� ��������� 2, 3 ��� 4 ����, � ������� ���������
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
				//������ �������� � ������� ������� ����
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
					//������ �������� � ������� �������� ��� ���������� ����
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
//����������: ������ ���������� � ������ ��������, � ������� 2 ����
//����������: ������� ������ ���� ��������� 2, � ������� ���������
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
				//������ �������� � ������� ������� ����
				tempvalue = Obj[1] & MaskHiHalfByte;
				Obj[1] = Operands[1]->Address;
				Obj[1] &= ~MaskHiHalfByte;
				Obj[1] |= tempvalue;
			}
		}
	}
}
//-------------------------------------------------------------
//����������: ������ 16 ���������� ����� � ��������, � ������� 3 ����
void TPassLine :: SetDisp(short disp)
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && OpTabElement->Type == 3)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj && ObjSize == 4)
			//������ ����� ����� ����
			RotateWrite(disp, 2);//, 3);
	}
}
//-------------------------------------------------------------
//����������: ������ 32 ���������� ����� � ���� ������� ������, ������� 4 ����
void TPassLine :: SetMem(int mem)
{
	if (OpTabElement && (OpTabElement->GetOperationTypeInfo() == Operation) && OpTabElement->Type == 4)
	{
		if (!Obj)
			SetCommandCode();
		if (Obj && ObjSize == 6)
			//������ ����� ����� ����
			RotateWrite(mem, 2);//, 5);
	}
}
//-------------------------------------------------------------
//����������: �������� ����� � ���������� ��� ��� � ����� ���� ��� x86 ���� � ������
//��������� : value - �������� ��� ������; startpos, lastpos - ��������� � �������� ������� � ������ (Obj)
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
//����������: ��������� ������� ��������� ������ � ������
void TPassLine :: SetObjSize(size_t objsize) throw (...)
{
	if (Obj)
	{	//������� ���������� ������
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