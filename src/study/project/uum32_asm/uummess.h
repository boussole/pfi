#ifndef __UUMMess_h
	#define __UUMMess_h
//-----------------------------------------------------------
//-------------------------
//Коды ошибок исключений
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
//Текст ошибок работы программы (исключений)
static const char NoFileNameText	[] = "Не указано имя входного файла (asm)\n";
static const char OpenAsmFileText	[] = "Невозможно открыть файл входной файл: ";
static const char FileExistsText	[] = "Указанный файл не существует на диске: ";
static const char CreateObjFileText	[] = "Невозможно создать объектный файл: ";
static const char WriteObjFileText	[] = "Невозможно записать данные в объектный файл: ";
static const char HeapErrorText		[] = "Невозможно выделить память\n";
//-----------------------------------------------------------
//Коды ошибок транслятора
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
//Cообщения транслятора
static const char Logo				[] = "UUM32Asm Версия 1.0.0.1\nТрансляция запущена\n";
static const char FirstPassStart	[] = "Запущен первый проход...\n";
static const char FirstPassSucc		[] = "Первый проход успешно завершен...\n";
static const char FirstPassFail		[] = "Ошибки первого прохода: \n";
static const char SecondPassStart	[] = "Запущен второй проход...\n";
static const char SecondPassSucc	[] = "Второй проход успешно завершен...\n";
static const char SecondPassFail	[] = "Ошибки второго прохода: \n";
static const char StopTranslation	[] = "Трансляция приостановлена\n";
static const char SuccTranslation	[] = "Трансляция завершена успешно...\nСоздан объектный файл ";
//-----------------------------------------------------------
//Текст ошибки
static const char UnknownLabelText	[] = "Неизвестная программе команда: ";
static const char NoLabelNameText	[] = "Не указано имя метки";
static const char BadLabelNameText	[] = "Идентификатор содержит недопустимые символы: ";
static const char DefLabelNameText	[] = "Идентификатор с таким именем уже определен в программе: ";
//---------------
static const char NoOperandNameText	[] = "Не указано имя операнда";
//---------------
static const char ResLabelNameText	[] = "Использование зарезервированного слова в качестве имени метки: ";
static const char ResOperandNameText[] = "Использование зарезервированного слова в качестве имени операнда: ";
//---------------
static const char FirstTypeErrorText[] = "Недопустимые операнды или их количество в команде первого типа: ";
static const char SecTypeErrorText	[] = "Недопустимые операнды или их количество в команде второго типа: ";
static const char ThirdTypeErrorText[] = "Недопустимые операнды или их количество в команде третьего типа: ";
static const char FourTypeErrorText	[] = "Недопустимые операнды или их количество в команде четвертого типа: ";
static const char FifthTypeErrorText[] = "Недопустимый операнд в директиве резервирования по значению";
//---------------
static const char UndefSymbolsText	[] = "Недопустимые символы в имени: ";
static const char UknownSymbolsText	[] = "Неизвестные символы: ";
//static const char NotEndLineText	[] = "Предложение не закончено, пропущены идентификаторы рядом с запятой";
static const char NeedRegisterText	[] = "Идентификатор не является регистром: ";
//static const char NoOperBeforeText	[] = "Пропущен идентификатор перед запятой";
//static const char NoOperAfterText	[] = "Пропущен идентифиактор после запятой";
//---------------
static const char BadSymLabelText	[] = "Недопустимые символы в имени метки: ";
static const char BadSymCommandText [] = "Недопустимые символы в имени команды: ";
static const char BadSymOperandText	[] = "Недопустимые символы в имени операнда: ";
static const char BadOperandText	[] = "Недопустимый операнд: ";
//---------------
static const char SingleNotFoundText[] = "В предложении не хватает закрывающего апострофа: ";
static const char DoubleNotFoundText[] = "В предложении не хватает закрывающей кавычки: ";	
//---------------
static const char SecondLabelOperandText[] = "Повторное определение операнда mem: ";
static const char SecondBaseRegisterText[] = "Двойное определение базового регистра в базово-индексной  адресации";
static const char SecondIndexRegText    [] = "Двойное определение индексного регистра в базово-индексной  адресации";
static const char BaseIndexOnlyText		[] = "Недопустимые регистры (только базовый и (или) индексный регистры): ";
static const char IAddressText			[] = "Ошибка при описании операндов непосредственной адресации";
static const char NAddressText			[] = "Ошибка при описании операндов косвенной адресации";
static const char UndeclIDText			[] = "Неопределённый идентификатор: ";
//---------------
static const char NoValueText			[] = "Отсутствует значение числа в непосредственном операнде: ";
static const char OverFlowText			[] = "Переполнение. Указано слишком большое число: ";
static const char OverDispText			[] = "Значение смещения или непосредственного операнда не умешается в поле disp";
//-----------------------------------------------------------
#endif