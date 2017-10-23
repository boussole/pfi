#ifndef __UUMMess_h
	#define __UUMMess_h
//-----------------------------------------------------------
//-------------------------
//���� ������ ����������
//-------------------------
#define UUMException	int
//-------------------------
#define NoFileName		0x00000001
#define OpenAsmFile		0x00000002
#define FileExists		0x00000003
#define CreateObjFile	0x00000004
#define WriteObjFile	0x00000005
#define HeapError		0x00000006
#define AsmError		0x00000007
//-------------------------
//����� ������ ������ ��������� (����������)
static const char NoFileNameText	[] = "�� ������� ��� �������� ����� (asm)\n";
static const char OpenAsmFileText	[] = "���������� ������� ���� ������� ����: ";
static const char FileExistsText	[] = "��������� ���� �� ���������� �� �����: ";
static const char CreateObjFileText	[] = "���������� ������� ��������� ����: ";
static const char WriteObjFileText	[] = "���������� �������� ������ � ��������� ����: ";
static const char HeapErrorText		[] = "���������� �������� ������\n";
//-----------------------------------------------------------
//���� ������ �����������
#define UnknownLabel	0x00000008
#define NoLabelName		0x00000009
#define BadLabelName	0x00000010
#define DefLabelName	0x00000011
#define ResLabelName	0x00000012
//--------------------------------
#define FirstTypeError	0x00000013
#define SecTypeError	0x00000014
#define ThirdTypeError	0x00000015
#define FourTypeError	0x00000017
//--------------------------------
//#define NotEndLine		0x00000016
#define UndefSymbols	0x00000018
#define NeedRegister	0x00000019
#define NoOperBefore	0x00000020
#define NoOperAfter		0x00000021
#define BadSymLabel		0x00000022
#define BadSymCommand	0x00000023
#define BadSymOperand	0x00000024
#define SingleNotFound	0x00000025
#define DoubleNotFound	0x00000026
#define ResOperandName	0x00000027
#define UknownSymbols	0x00000028
#define SecondLabelOperand 0x00000029
#define SecondBaseRegister 0x00000030
#define SecondIndexReg	   0x00000031
#define BaseIndexOnly	0x00000032
//--------------------------------
#define	NoOperandName	0x00000033
#define IAddress		0x00000034
#define NAddress		0x00000035
//--------------------------------
#define NoValue			0x00000036
#define	UndeclID		0x00000037
#define BadOperand		0x00000038
#define OverFlow		0x00000039
#define OverDisp		0x00000040
#define FifthTypeError  0x00000041
//-----------------------------------------------------------
//C�������� �����������
static const char Logo				[] = "UUM32Asm ������ 1.0.0.1\n���������� ��������\n";
static const char FirstPassStart	[] = "������� ������ ������...\n";
static const char FirstPassSucc		[] = "������ ������ ������� ��������...\n";
static const char FirstPassFail		[] = "������ ������� �������: \n";
static const char SecondPassStart	[] = "������� ������ ������...\n";
static const char SecondPassSucc	[] = "������ ������ ������� ��������...\n";
static const char SecondPassFail	[] = "������ ������� �������: \n";
static const char StopTranslation	[] = "���������� ��������������\n";
static const char SuccTranslation	[] = "���������� ��������� �������...\n������ ��������� ���� ";
//-----------------------------------------------------------
//����� ������
static const char UnknownLabelText	[] = "����������� ��������� �������: ";
static const char NoLabelNameText	[] = "�� ������� ��� �����";
static const char BadLabelNameText	[] = "������������� �������� ������������ �������: ";
static const char DefLabelNameText	[] = "������������� � ����� ������ ��� ��������� � ���������: ";
//---------------
static const char NoOperandNameText	[] = "�� ������� ��� ��������";
//---------------
static const char ResLabelNameText	[] = "������������� ������������������ ����� � �������� ����� �����: ";
static const char ResOperandNameText[] = "������������� ������������������ ����� � �������� ����� ��������: ";
//---------------
static const char FirstTypeErrorText[] = "������������ �������� ��� �� ���������� � ������� ������� ����: ";
static const char SecTypeErrorText	[] = "������������ �������� ��� �� ���������� � ������� ������� ����: ";
static const char ThirdTypeErrorText[] = "������������ �������� ��� �� ���������� � ������� �������� ����: ";
static const char FourTypeErrorText	[] = "������������ �������� ��� �� ���������� � ������� ���������� ����: ";
static const char FifthTypeErrorText[] = "������������ ������� � ��������� �������������� �� ��������";
//---------------
static const char UndefSymbolsText	[] = "������������ ������� � �����: ";
static const char UknownSymbolsText	[] = "����������� �������: ";
//static const char NotEndLineText	[] = "����������� �� ���������, ��������� �������������� ����� � �������";
static const char NeedRegisterText	[] = "������������� �� �������� ���������: ";
//static const char NoOperBeforeText	[] = "�������� ������������� ����� �������";
//static const char NoOperAfterText	[] = "�������� ������������� ����� �������";
//---------------
static const char BadSymLabelText	[] = "������������ ������� � ����� �����: ";
static const char BadSymCommandText [] = "������������ ������� � ����� �������: ";
static const char BadSymOperandText	[] = "������������ ������� � ����� ��������: ";
static const char BadOperandText	[] = "������������ �������: ";
//---------------
static const char SingleNotFoundText[] = "� ����������� �� ������� ������������ ���������: ";
static const char DoubleNotFoundText[] = "� ����������� �� ������� ����������� �������: ";	
//---------------
static const char SecondLabelOperandText[] = "��������� ����������� �������� mem: ";
static const char SecondBaseRegisterText[] = "������� ����������� �������� �������� � ������-���������  ���������";
static const char SecondIndexRegText    [] = "������� ����������� ���������� �������� � ������-���������  ���������";
static const char BaseIndexOnlyText		[] = "������������ �������� (������ ������� � (���) ��������� ��������): ";
static const char IAddressText			[] = "������ ��� �������� ��������� ���������������� ���������";
static const char NAddressText			[] = "������ ��� �������� ��������� ��������� ���������";
static const char UndeclIDText			[] = "������������� �������������: ";
//---------------
static const char NoValueText			[] = "����������� �������� ����� � ���������������� ��������: ";
static const char OverFlowText			[] = "������������. ������� ������� ������� �����: ";
static const char OverDispText			[] = "�������� �������� ��� ����������������� �������� �� ��������� � ���� disp";
//-----------------------------------------------------------
#endif