#include "assembler.h"
//-----------------------------------------------------------
//Назначение: Деструктор - освобождение ресурсов
UUMAsm :: ~UUMAsm ()
{
	OpTab = NULL;
	SymTab = NULL;
	_fcloseall( );
}
//-----------------------------------------------------------
//Назначение: Конструктор - инициализация переменных значениями, проверка наличия входного файла... изменить на конструктор (ЛУЧШЕ)
//Параметры : 
//Возвр. зн : -
void UUMAsm :: SetValue(const char *input, const char *output, BinTree<TOpTabElement> &optab, BinTree<TSymTabElement> &symtab, UUMMode mode) throw(...)
{
	OpTab = &optab;
	SymTab = &symtab;
	Ready = true;
	Mode = mode;
	//-------------------------------------------------------
	//Проверка введеного имени входного файла 
	if (!input)
		throw NoFileName;
	else
		strcpy_s(InputFileName, MAX_PATH, input);
	//Проверка наличия файла на диске
	char fullway[MAX_PATH]; char *lpFilePart;
	if (GetFullPathName(InputFileName, MAX_PATH, fullway, &lpFilePart))
	{
		if (!PathFileExists(fullway))
		{
			throw FileExists;
		}
		else
		{
			strcpy_s(InputFileName, MAX_PATH, fullway);
		}
	}
	else
	{
		throw;
	}
	//Заполнение имени выходного файла значением по умолчанию
	//Слишком по пижонски, может работать не правильно, ИЗМЕНИТЬ позже!!!
	if (!output)
	{
		size_t index = 0;
		while (lpFilePart[index] && (lpFilePart[index] != '.'))
		{
			index++;
		}
		lpFilePart[index] = 0;
		strcpy_s(OutputFileName, MAX_PATH, fullway);
		//strcat_s(OutputFileName, MAX_PATH, 
		/*fullway[strlen(fullway) - strlen(lpFilePart)] = '\0';
		strcpy_s(OutputFileName, MAX_PATH, fullway); 
		strcat_s(OutputFileName, MAX_PATH, DefaultOutputName);*/
	}
	//-------------------------------
}
//-----------------------------------------------------------
//Назначение: Запуск первого прохода ассемблера
//			  - поиск команд, сохранение ссылок
//Параметры : -
//Воз. зн.  : - 
void UUMAsm :: StartFirstPass() throw (...)
{
	if (!Ready)
		throw;
	errno_t errorfile = 0;
	if ( (errorfile = fopen_s(&AsmFile, InputFileName, "r") != 0))
	{
		throw OpenAsmFile;
	}
	while(fgets(Buffer, MAXSTRINGLENGTH, AsmFile))
	{
		//Пропуск пустой строки
		if ((strcmp(Buffer, "\n")) != 0)
			Decode();
		Counter++;
	}
	fclose(AsmFile);
	if (ErrorList.GetCount())
		throw AsmError;
	else
	{
		FirstPassSuccess = true;
		Length = LocCtr;
		LocCtr = 0;
		Counter = 0;
	}
}
//-----------------------------------------------------------
//Назначение: Второй проход трансляции. Создание объектной записи, запись в файл.
//Параметры :
//Возв. зн. :
void UUMAsm :: StartSecondPass() throw (...)
{
	if (FirstPassSuccess)
	{
		
		TPassLine *passline = NULL;
		for (size_t i = 0; i < Pass.GetCount(); i++)
		{
			Counter++;
			passline = Pass.GetPointer(i);
			if (passline && passline->GetCommand())
			{
				if (passline->GetCommand()->GetOperationTypeInfo() == Operation)
					LocCtr = LocCtr + passline->GetCommand()->Length;
				switch (passline->GetCommand()->Type)
				{
				case(1):	FirstTypeObjRecord(*passline);
							break;
				case(2):	SecondTypeObjRecord(*passline);
							break;
				case(3):	ThirdTypeObjrecord(*passline);
							break;
				case(4):	FourthTypeObjRecord(*passline);
							break;
				//----------------
				//Директивы
				//----------------
				//Резервирование памяти по значению аргумента
				case(5):	FifthTypeObjRecord(*passline);
							break;
				//----------------
				//Резервирование памяти по величине аргументов
				case(6):
							break;
				}
			}
		}
		if (ErrorList.GetCount())
			throw AsmError;
		else
			WriteObj();
		if (Mode & SUBOBJ)
			WriteSubObj();
	}
}
//-----------------------------------------------------------
//Назначение: Создание в памяти объектного кода команды первого типа для дальнейшей записи в файл
//Параметры : Структура обработанной строки
//Возв. зн. :
void UUMAsm :: FirstTypeObjRecord(TPassLine &passline) throw (...)
{
	if (&passline)
		passline.SetEOPField();
}
//-----------------------------------------------------------
//Назначение: Создание в памяти объектного кода команды второго типа  для дальнейшей записи в файл
//Параметры : Структура обработанной строки
//Возв. зн. :
void UUMAsm :: SecondTypeObjRecord(TPassLine &passline) throw (...)
{
	if (&passline)
	{
		passline.SetEOPField();
		passline.SetReg_1();
		passline.SetReg_2();
	}
}
//-----------------------------------------------------------
//Назначение: Создание в памяти объектного кода команды третьего типа  для дальнейшей записи в файл
//Параметры : Структура обработанной строки
//Возв. зн. :
void UUMAsm :: ThirdTypeObjrecord(TPassLine &passline)  throw (...)
{
if (&passline)
	{
		passline.SetCommandCode();
		passline.SetEOPField();
		if (passline.GetBaseOperand())
			passline.SetServiceBit('b');
		if (passline.GetIndexOperand())
			passline.SetServiceBit('x');
		passline.SetReg_1();
		TSymTabElement *symtabelement = passline.GetMemOperand();
		if (symtabelement && symtabelement->DefineLabel)	
		{
			short disp = 0;
			int value = 0;
			TSymTabElement *original = NULL;
			if (symtabelement && symtabelement->Name[0] == '#' || symtabelement->Name[0] == '@')
				{
					symtabelement->Name[0] == '#' ? passline.SetEOPField(false) : passline.SetServiceBit('n');
					if (TestSymbol(symtabelement->Name + 1))
					{	//метка в поле операнда
						original = SymTab->Search(symtabelement->Name + 1);
						if (original && original->DefineLabel)
						{
							value = original->Address - LocCtr;
							if (abs(value) <= 65535)
								{
									disp = (short)value;
									passline.SetDisp(disp);
								}
							else
								ErrorList.Add(NULL, Counter, OverDisp);
						}
						else
							ErrorList.Add(symtabelement->Name + 1, Counter, UndeclID);
					}
					else
					{	//число в поле операнда
						ConvertInteger(symtabelement->Name + 1, &value);
						if (abs(value) <= 65535)
						{
							disp = (short)value;
							passline.SetDisp(disp);
						}
						else
							ErrorList.Add(NULL, Counter, OverDisp);
					}
				}
			else
				{	//обычная адресация
					value = symtabelement->Address - LocCtr;
					if (abs(value) <= 65535)
						{
							disp = (short)value;
							passline.SetDisp(disp);
						}
					else
						ErrorList.Add(NULL, Counter, OverDisp);
				}
			}
		else
			ErrorList.Add(symtabelement->Name, Counter, UndeclID);
	}
}
//-----------------------------------------------------------
//Назначение: Создание в памяти объектного кода команды четвертого типа для дальнейшей записи в файл
//Параметры : Структура обработанной строки
//Возв. зн. :
void UUMAsm :: FourthTypeObjRecord(TPassLine &passline) throw(...)
{
	if (&passline)
	{
		passline.SetCommandCode();
		passline.SetEOPField();
		if (passline.GetBaseOperand())
			passline.SetServiceBit('b');
		if (passline.GetIndexOperand())
			passline.SetServiceBit('x');
		passline.SetReg_1();
		TSymTabElement *symtabelement = passline.GetMemOperand();
		if (symtabelement && symtabelement->DefineLabel)	
		{
			if (symtabelement && symtabelement->Name[0] == '#' || symtabelement->Name[0] == '@')
				{
					symtabelement->Name[0] == '#' ? passline.SetEOPField(false) : passline.SetServiceBit('n');
					if (TestSymbol(symtabelement->Name + 1))
					{	//метка в поле операнда
						TSymTabElement *original = SymTab->Search(symtabelement->Name + 1);
						if (original && original->DefineLabel)
							passline.SetMem(original->Address - LocCtr);	
						else
							ErrorList.Add(symtabelement->Name + 1, Counter, UndeclID);
					}
					else
					{	//число в поле операнда
						int value = 0;
						ConvertInteger(symtabelement->Name + 1, &value);
						if (!passline.GetCommand()->GetEOPInfo())
							value -= LocCtr;
						passline.SetMem(value);
					}
				}
			else//обычная адресация
				passline.SetMem(symtabelement->Address - LocCtr);
		}
		else
			ErrorList.Add(symtabelement->Name, Counter, UndeclID);
	}
}
//-----------------------------------------------------------
//Назначение: Создание в памяти объектного кода директивы четвертого типа для дальнейшей записи в файл
//Параметры : Структура обработанной строки
//Возв. зн. :
void UUMAsm :: FifthTypeObjRecord(TPassLine &passline) throw (...)
{
	if (&passline && passline.GetCommand())
	{
		passline.CreateObj();
		LocCtr = LocCtr + passline.GetObjSize();
	}
}
//-----------------------------------------------------------
//Назначение: Запись объектной записи в открытый ранее файл
//Параметры : Структура строки прохода
void UUMAsm :: WriteObj() throw(...)
{
	char objway[MAX_PATH];
	strcpy_s(objway, MAX_PATH, OutputFileName);
	strcat_s(objway, MAX_PATH, ".obj");
	if ((ObjFile = CreateFile(objway, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
			throw CreateObjFile;
	try
	{
		if (ObjFile != INVALID_HANDLE_VALUE)
		{
			TPassLine *passline = NULL;
			DWORD lpNumberOfBytesWritten;
			for (size_t i = 0; i < Pass.GetCount(); i++)
			{
				passline = Pass.GetPointer(i);
				if (passline && passline->GetCommand() && passline->GetObjSize())
				{
					WriteFile(ObjFile, passline->GetObj(), (DWORD)passline->GetObjSize(), &lpNumberOfBytesWritten, NULL);
					if (lpNumberOfBytesWritten != passline->GetObjSize())
						throw WriteObjFile;
				}
			}
		}
	}
	catch (...)
	{
		CloseHandle(ObjFile);
		throw;
	}
	CloseHandle(ObjFile);
}
//-----------------------------------------------------------
//Назначение: Запись промежуточного объектного файла на диск
void UUMAsm :: WriteSubObj() throw(...)
{
		if ((SubObjFile = CreateFile("C:\\12.bin", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
			throw CreateObjFile;
	try
	{
		if (SubObjFile != INVALID_HANDLE_VALUE)
		{
			WriteHead();
			/*TPassLine *passline = NULL;
			DWORD lpNumberOfBytesWritten;
			for (size_t i = 0; i < Pass.GetCount(); i++)
			{
				passline = Pass.GetPointer(i);
				if (passline && passline->GetCommand() && passline->GetObjSize())
				{
					WriteFile(ObjFile, passline->GetObj(), (DWORD)passline->GetObjSize(), &lpNumberOfBytesWritten, NULL);
					if (lpNumberOfBytesWritten != passline->GetObjSize())
						throw WriteObjFile;
				}
			}*/
		}
	}
	catch (...)
	{
		CloseHandle(SubObjFile);
		throw;
	}
	CloseHandle(SubObjFile);
}
//-----------------------------------------------------------
//Назначение: Запись заголовка в промежуточный объектный файл
void UUMAsm :: WriteHead() throw(...)
{
	if (SubObjFile != INVALID_HANDLE_VALUE)
	{
		DWORD lpNumberOfBytesWritten = 0;
		const char ProgramName [] = "Тест";
		WriteFile(SubObjFile, &ProgramName, (DWORD)strlen(ProgramName), &lpNumberOfBytesWritten, NULL);
	}
}
//-----------------------------------------------------------
//Назначение: Раскодирование строки на лексемы, метки, операции, операнды
//Параметры : -
//Возв. зн. : -
void UUMAsm :: Decode() throw (...)
{
	RemoveComments(Buffer);
	DeleteSpacesBefore(Buffer);
	DeleteSpacesAfter(Buffer);
	TPassLine temp;
	temp.SetAddress(LocCtr);
	Error = false;
	FindLex Result = NOLEX;
	while (Buffer[0] && !Error)
	{
		if ((Result = SearchLabel(Buffer, temp)) == LABEL)
			SearchOperation(Buffer, temp);
	}
	if (temp.GetCommand() || temp.GetLabel())
	{
		Pass.Add(temp);
		if (temp.GetCommand())
			LocCtr = LocCtr + temp.GetObjSize();
	}
}
//-----------------------------------------------------------
//Назначение: Поиск первого предложения в строке, окончанием является разделитель или символ advancestop
//Параметры : Строка для обработки
//Воз. зн.  : Размер подстроки, исключая нулевой (конечный) символ
//Примечание: Возврат нуля подразумевает ошибку
size_t UUMAsm :: ReadSubString(char *string, char advancestop) throw(...)
{
	size_t index = 0;
	if (string && string[0])
	{
		DeleteSpacesBefore(string);
		bool singleflag = false, doubleflag = false;
		while (string[index] && ((string[index] != ' ' && string[index] != '\t' && string[index] != '\n') || (singleflag || doubleflag)))
		{
			if (string[index] == '"' && !singleflag)
				doubleflag = (doubleflag ? false : true);
			if (string[index] == '\'' && !doubleflag)
				singleflag = (singleflag ? false : true);
			//Выход по нахождению дополнительного параметра
			if (string[index++] == advancestop && !singleflag && !doubleflag)
				break;
			//index++;
		}
		if (singleflag)
		{
			ErrorList.Add(string, Counter, SingleNotFound);
			index = 0;
		}
		if (doubleflag)
		{
			ErrorList.Add(string, Counter, DoubleNotFound);
			index = 0;
		}
	}
	return index;
}
//-----------------------------------------------------------
//Назначение: Удаление строк не использующихся при генерации объектного кода
//Примечание: Комментарии в данной версии транслятора двух типов
//            - ";" - встретив данный символ, транслятор будет игнорировать всю строку следующую за ним
//			  - "." - данный символ позволяет выделить некоторый участок строки, заключенный между двумя такими символами,
//            если символ один, значит будет действовать, как предыдущий
//Предложение: В дальнейшем в этой процедуре можно будет добавлять комментарии в код, так, чтобы они были видны в дебагере
void UUMAsm :: RemoveComments(char *string) throw (...)
{
	if ((string) && (string[0]))
	{ 
	bool singleflag = false, doubleflag = false, firstdot = false;
	size_t index = 0, pos = 0, length = strlen(string);
	while (string[index])
	{
		switch (string[index])
		{
			case (';'): {
							if (!singleflag && !doubleflag && !firstdot)
							{
								CutSubString(index, length - index, string);
								return;
							}
							break;
						}
			case ('.'):
						{
							if (!singleflag && !doubleflag)
							{
								if (!firstdot)
								{
									pos = index;
									firstdot = true;
								}
								else
								{
									firstdot = false;
									CutSubString(pos, index - pos + 1, string);
									length -= index - pos + 1;
									index = pos;
									continue;
								}
							}
							break;
						}
			case ('"'):	
							if (!firstdot && !singleflag)
								doubleflag = (doubleflag) ? false : true; 
							break;
			case ('\''):
							if (!firstdot && !doubleflag)
								singleflag = (singleflag) ? false : true;
							break;
		}
		index++;
	}
		if (!singleflag && !doubleflag & firstdot)
		{
			CutSubString(pos, length - pos, string);
		}
	}
	}
//-----------------------------------------------------------
//Назначение: Перевод всех строчных букв в заглавные
//Примечание: Данная версия УУМ транслятора, хранит все команды и метки в верхнем регистре
//            В дальнейшем будет возможность указывать режим работы транслятора, с / без учета регистра
void UUMAsm :: UpCase(char *string) throw ()
{
	if (string && (Mode & CASE))
	{
		unsigned int index = 0;
		int codechar;
		while (string[index])
		{
			codechar = (int)string[index];
			//Английский диапазон ANSII
			if ((97 <= codechar) && (codechar <= 122))
			{
				codechar -= 32;
			}
			else
			{
			//Русский диапазон
				if ((-32 <= codechar) && (codechar <= -1))
				{
					codechar -= 32;
				}
				else
				{
					//Буква 'ё'
					if (codechar == -72)
					{
						codechar = -88;
					}
				}
			}
			string[index] = (char)codechar;
			index++;
		}
	}
}
//-----------------------------------------------------------
//Назначение: Удаление пробелов, табуляций, переносов строки, начиная с первой позиции позиции, заканчивая первым другим символом
//Парамеры  : -
//Воз. зн.  : -
void UUMAsm :: DeleteSpacesBefore(char *string) throw (...)
{
	if ((string) && (string[0]))
	{
		unsigned int count = 0;
		while ((string[count]) && ((string[count] == ' ') || (string[count] == '\t') || (string[count] == '\n')))
		{
			count++;
		}
		if (count)
			CutSubString(0, count, string);
	}
}
//-----------------------------------------------------------
//Назначение: Удаление пробелов, табуляций, переносов строки, начиная с конечной позиции позиции, заканчивая первым другим символом
//Парамеры  : -
//Воз. зн.  : -
void UUMAsm :: DeleteSpacesAfter(char *string) throw (...)
{
	if ((string) && (string[0]))
	{
		size_t length = strlen(string), count = 0;
		size_t pos = length - 1;
		while ((string[pos]) && ((string[pos] == ' ') || (string[pos] == '\t') || (string[pos] == '\n')))
		{
			string[pos--] = 0;
		}
		/*{
			count++;
			if (pos)
				pos--;
			else
				break;
		}
		if (count)
			CutSubString(length - count, count, string);*/
	}
}
//-----------------------------------------------------------
//Назначение: Удаление из строки, подстроки, с возможной вставкой в другую строку
//Параметры : Начальная позиция, количество элементов, строка для редактирования, строка для вставки
//Воз. зн.  : -
void UUMAsm :: CutSubString(size_t pos, size_t count, char *cutstring, char *pastestring, size_t sizeofpaste) throw(...)
{
	if ((cutstring) && (cutstring[0]))
	{
		size_t length = strlen(cutstring);
		char *newstring = NULL;
		if ((pos + count) <= length)
		{
			try
			{
				newstring = new char[count + 1];	
			}
			catch (...)
			{
				throw HeapError;
			}
			unsigned int index = 0;
			while ((cutstring[pos + index]) && (index < count)) 
			{
				newstring[index] = cutstring[pos + index];
				++index;
			}
			newstring[index] = '\0';
			do
			{
				cutstring[pos] = cutstring[pos + count];
			}
			while (cutstring[pos++]);
			if ((pastestring) && (sizeofpaste >= count))
			{
				try
				{
					strcpy_s(pastestring, sizeofpaste, newstring);
				}
				catch (...)
				{
					throw;
				}
			}
			delete []newstring;
			newstring = NULL;
		}
	}
}
//-----------------------------------------------------------
//Назначение : Поиск метки (операции) в предложении ассемблера
//Параметры  : Строка для поиска, структура прохода
//Воз. зн.   : Тип найденной лексемы
//Предложение: описание меток в программе должно находится начале строки, 
//			   в конце имени метки должен находится символ - :
//			   запрещается использование в имени метки служебных символов - 
FindLex UUMAsm :: SearchLabel(char *string, TPassLine &temp) throw (...)
{
	FindLex Result = NOLEX;
	DeleteSpacesBefore(string);
	size_t symbolcount = ReadSubString(string, ':');
	if (symbolcount > 0)
	{
		bool label = false;
		char *tempstring = new char[symbolcount + 1];
		CutSubString(0, symbolcount, string, tempstring, symbolcount + 1);
		UpCase(tempstring);
		if (tempstring[symbolcount - 1] == ':')
		{
			label = true;
			tempstring[--symbolcount] = '\0';
			if (!symbolcount)
			{
				//Не указано имя метки
				ErrorList.Add(tempstring, Counter, NoLabelName);
				Error = true;
				goto EndSearchLabel;
			}
			if (OpTab->Search(tempstring))
			{
				//Использование зарезервированного слова в качестве метки
				ErrorList.Add(tempstring, Counter, ResLabelName);
				Error = true;
				goto EndSearchLabel;
			}
		}
		if (!TestSymbol(tempstring))
			//Запрещенные символы в метке
			ErrorList.Add(tempstring, Counter, BadLabelName);
		else
		{
			if (label)
			{
				//Поиск в таблице меток
				TSymTabElement *symtabelement = NULL;
				symtabelement = SymTab->Search(tempstring);
				if (symtabelement && symtabelement->DefineLabel)
				{
					//Двойное определение метки
					ErrorList.Add(tempstring, Counter, DefLabelName);
					Error = true;
				}
				else
				{
					//Добавить информацию о метке в таблицу SymTab
					symtabelement = AddToSymTab(*SymTab, tempstring, LocCtr, true);
					temp.SetLabel(symtabelement);
					Result = LABEL;
				}
			}
			else
				//Поиск в таблице операций
				Result = SearchOperation(tempstring, temp);
		}
EndSearchLabel:
		delete []tempstring;
		tempstring = NULL;
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операции и операндов в строке
//Параметры : Строка для поиска
//Возв. зн. : Тип лексемы
FindLex UUMAsm :: SearchOperation(char *string, TPassLine &temp) throw (...)
{
	FindLex Result = NOLEX;
	DeleteSpacesBefore(string);
	if (string && string[0])
	{
		size_t symbolcount = ReadSubString(string);
		if (symbolcount > 0)
		{
			char *tempstring = new char[symbolcount + 1];
			CutSubString(0, symbolcount, string, tempstring, symbolcount + 1);
			if (!TestSymbol(tempstring))
				//Запрещенные символы в идентификаторе
				ErrorList.Add(tempstring, Counter, BadLabelName);
			else
			{
				UpCase(tempstring);
				TOpTabElement *optabelement = NULL;
				if (!(optabelement = OpTab->Search(tempstring)) || (!(Mode & LITE) && !(optabelement->UUMLite)))
					//Неизвестная операция
					{ErrorList.Add(tempstring, Counter, UnknownLabel); Error = true;}
				else
				{
					temp.SetCommand(optabelement);
					//Поиск операндов
					if (!(Result = SearchOperands(temp, Buffer)))
						{
							int errortype;
							switch (temp.GetCommand()->Type)
							{
							case (1):	errortype = FirstTypeError;
										break;
							case (2):	errortype = SecTypeError;
										break;
							case (3):	errortype = ThirdTypeError;
										break;
							case (4):	errortype = FourTypeError;
										break;
							case (5):	errortype = FifthTypeError;
										break;
							}
							ErrorList.Add(temp.GetCommand()->Name, Counter, errortype);
							Error = true;
							temp.SetCommand(NULL);
						}
				}
			}
			delete []tempstring;
			tempstring = NULL;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операндов команд
//Параметры : Указатель на информацию команды, структура строки прохода
//Возв. зн. : Тип найденой лексемы
FindLex UUMAsm :: SearchOperands(TPassLine &temp, char *string) throw (...)
{
	FindLex Result = NOLEX;
	//
	if (&temp && temp.GetCommand())
	{
		switch (temp.GetCommand()->GetOperandsInfo())
		{
		case (NoOperands):			Result = SearchNoOperands(temp, string);
									break;
		case (JustRegister):		Result = SearchRegOperands(temp, string);
									break;
		case (JustMemory):			Result = SearchMemOperands(temp, string);
									break;
		case (RegisterRegister):	Result = SearchRegRegOperands(temp, string);
									break;
		case (RegisterMemory):		Result = SearchRegMemOperands(temp, string);
									break;
		case (ValueOpSize):			Result = SearchValueOpSize(temp, string);
									break;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операндов в команде без операндов
//Параметры :
//Возв. зн. :
FindLex UUMAsm :: SearchNoOperands(TPassLine &temp, char *string) throw (...)
{
	FindLex Result = NOLEX;
	DeleteSpacesBefore(string);
	if (!string[0])
		Result = OPERATION;
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск одного операнда
//Параметры : Структура прохода, строка для обработки
//Возвр. зн.: Тип найденной лексемы
FindLex UUMAsm :: DecodeOperand(TPassLine &temp, char *string) throw(...)
{
	FindLex Result = NOLEX;
	DeleteSpacesBefore(string);
	if (string)// && string[0])
	//если в строке ещё есть что - то
	{
		size_t symbolcount = ReadSubString(string, ',');
		if (symbolcount)
		//если строка или хотя бы запятая найдена
		{
			char *tempstring = new char[symbolcount + 1];
			CutSubString(0, symbolcount, string, tempstring, symbolcount + 1);
			if (tempstring[symbolcount - 1] != ',')
			{
				DeleteSpacesBefore(string);
				if (!string[0])
				//строка окончена
				{
					if (TestSymbol(tempstring))
					{
						UpCase(tempstring);
						if (!OpTab->Search(tempstring))
						{
							TSymTabElement *symtabelement = NULL;
							symtabelement = SymTab->Search(tempstring);
							if (!symtabelement)
								//метка или регистр еще не определены
								symtabelement = AddToSymTab(*SymTab, tempstring, 0, false);
							temp.AddOperand(symtabelement);
							Result = OPERATION;
						}
						else
						//в качестве имени операнда указано зарезервированное слово
						{ErrorList.Add(tempstring, Counter, ResOperandName); Error = true;}
					}
					else
					//операнд содержит недопустимые символы
					ErrorList.Add(tempstring, Counter, BadSymOperand);
				}
				else
					ErrorList.Add(string, Counter, UknownSymbols);
			}
			delete []tempstring;
			tempstring = NULL;
		}
		else
			ErrorList.Add(NULL, Counter, NoOperandName);
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операндов в команде c операндом регистром
//Параметры :
//Возв. зн. :
FindLex UUMAsm :: SearchRegOperands(TPassLine &temp, char *string, size_t index) throw (...)
{
	FindLex Result = DecodeOperand(temp, string);
	if (Result)
	{
		if (temp.GetOperand(index) && !(temp.GetOperand(index)->GetRegInfo()))
		{
			ErrorList.Add(temp.GetOperand(index)->Name, Counter, NeedRegister);
			Result = NOLEX;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операндов в команде c операндами регистр регистр
//Параметры :
//Возв. зн. :
FindLex UUMAsm :: SearchRegRegOperands(TPassLine &temp, char *string) throw (...)
{
	FindLex Result = NOLEX;
	DeleteSpacesBefore(string);
	if (string)// && string[0])
	{
		//Поиск первого регистра
		size_t symbolcount = 0;
		symbolcount = ReadSubString(string, ',');
		if (symbolcount)
		{
			char *tempstring = new char[symbolcount + 1];
			bool NextOperand = true;
			CutSubString(0, symbolcount, string, tempstring, symbolcount + 1);
			if (tempstring[symbolcount - 1] == ',')
				tempstring[--symbolcount] = '\0';
			else
				NextOperand = SearchNext(string, ',');
			if (NextOperand)
				//поиск первого операнда
				Result = SearchRegOperands(temp, tempstring);
				if (Result)
					//поиск второго операнда
					Result = SearchRegOperands(temp, string, 1);
			delete []tempstring;
			tempstring = NULL;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операндов в команде c операндами регистр память
//Параметры : 
//Возв. зн. :
FindLex UUMAsm :: SearchRegMemOperands(TPassLine &temp, char *string) throw (...)
{
	FindLex Result = NOLEX;
	DeleteSpacesBefore(string);
	if (string)// && string[0])
	{
		//Поиск первого регистра
		size_t symbolcount = 0;
		symbolcount = ReadSubString(string, ',');
		if (symbolcount)
		{
			char *tempstring = new char[symbolcount + 1];
			bool NextOperand = true;
			CutSubString(0, symbolcount, string, tempstring, symbolcount + 1);
			if (tempstring[symbolcount - 1] == ',')
				tempstring[--symbolcount] = '\0';
			else
				NextOperand = SearchNext(string, ',');
			if (NextOperand)
				//поиск первого операнда
				Result = SearchRegOperands(temp, tempstring);
				if (Result)
					//поиск второго операнда
					Result = SearchMemOperands(temp, string);
			delete []tempstring;
			tempstring = NULL;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск разделителя и его удаление
bool UUMAsm :: SearchNext(char * string, char searchsymbol)
{
	if (string && string[0])
	{
		DeleteSpacesBefore(string);
		if (string[0] == searchsymbol)
		{
			CutSubString(0, 1, string);
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------
//Назначение: Поиск операндов команды, использующей только память (базу, индекс) или непосредственный операнд
//УМЕНЬШИТЬ, РАЗБИТЬ НА ПОДПРОГРАММЫ, СЛИШКОМ БОЛЬШАЯ ФУНКЦИЯ!!!!!!!!!! ИЗМЕНИТЬ АЛГОРИТМ
FindLex UUMAsm :: SearchMemOperands(TPassLine &temp, char *string) throw (...)
{
	FindLex Result = NOLEX;
	if (string)
	{
		size_t symbolcount = 0;
		char *tempstring = NULL;
		TSymTabElement *symtabelement = NULL;
		bool Next = true;
		size_t stringlen = strlen(string);
		tempstring = new char[stringlen + 1];
		try
		{
			while (Next)
			{
				DeleteSpacesBefore(string);
				Next = false;
				symbolcount = ReadSubString(string, ',');
				if (symbolcount)
				{
					CutSubString(0, symbolcount, string, tempstring, stringlen + 1);
					//проверка наличия следующего операнда
					Next = (tempstring[symbolcount - 1] == ',' ? true : SearchNext(string, ','));
					if (tempstring[symbolcount - 1] == ',')
						tempstring[--symbolcount] = '\0';
					if (tempstring[0])
					{	//обработка операнда, если есть имя
						UpCase(tempstring);
						if (tempstring[0] == '@' || tempstring[0] == '#')
							SetSpecMemOperand(temp, tempstring);
						else
						{
							symtabelement = SymTab->Search(tempstring);
							if (symtabelement && symtabelement->GetRegInfo())
							{	//Найден регистр
								switch (symtabelement->GetRegInfo())
								{
								case(BaseRegister):		SetBaseRegister(temp, symtabelement);
														break;
								case(IndexRegister):	SetIndexRegister(temp, symtabelement);
														break;
								default:				ErrorList.Add(tempstring, Counter, BaseIndexOnly);
														throw AsmError;
								}
							}
							else//найдена метка
								SetMemoryOperand(temp, symtabelement, tempstring);
						}
//						tempstring[0] = '\0';
						Result = OPERATION;
						continue;
					}
				}
				//не указано имя операнда, ошибка
				ErrorList.Add(NULL, Counter, NoOperandName);
				throw AsmError;
			}
		}
		catch (...)
		{
			Result = NOLEX;
		}
		delete []tempstring;
		tempstring = NULL;
		if (Result)
		{
			//проверка на наличие оставшихся символов в строке
			DeleteSpacesBefore(string);
			if (string[0])
				{
					ErrorList.Add(string, Counter, UknownSymbols);
					Result = NOLEX;
				}
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Установка базового регистра в структуру прохода
//Параметры : Структура прохода, указатель на элемент таблицы SymTab
//Возв. зн. : -
//Примечание: В выражении с базово-индексной адресацией не может быть указано два базовых регистра
void UUMAsm :: SetBaseRegister(TPassLine &passline, TSymTabElement *symtabelement) throw (...)
{
	if (&passline)
	{
		if (!passline.GetBaseOperand())
		{
			passline.SetBaseOperand(symtabelement);
			return;
		}
		ErrorList.Add(NULL, Counter, SecondBaseRegister);
	}
	throw AsmError;
}
//-----------------------------------------------------------
//Назначение: Установка индексного регистра в структуру прохода
//Параметры : Структура прохода, указатель на элемент таблицы SymTab
//Возв. зн. : -
//Примечание: В выражении с базово-индексной адресацией не может быть указано два индексных регистра
void UUMAsm :: SetIndexRegister(TPassLine &passline, TSymTabElement *symtabelement) throw (...)
{
	if (&passline)
	{
		if (!passline.GetIndexOperand())
		{
			passline.SetIndexOperand(symtabelement);
			return;
		}
		ErrorList.Add(NULL, Counter, SecondIndexReg);
	}
	throw AsmError;
}
//-----------------------------------------------------------
//Назначение: Установка операнда в памяти
//Параметры : Структура прохода, указатель на элемент в в таблице SymTab, строка с именем метки
//Возв. зн. : -
void UUMAsm :: SetMemoryOperand(TPassLine &passline, TSymTabElement *symtabelement, char *string) throw (...)
{
	if (&passline)
	{
		if (!passline.GetMemOperand())
		{
			if (!symtabelement)
			{
				//метка ещё не разрешима
				if (TestSymbol(string))
					symtabelement = AddToSymTab(*SymTab, string, 0, false);
				else
				{
					ErrorList.Add(string, Counter, BadSymOperand);
					throw AsmError;
				}
			}
			passline.SetOperand(symtabelement, 1);
			return;
		}
		ErrorList.Add(string, Counter, SecondLabelOperand);
	}
	throw AsmError;
}
//-----------------------------------------------------------
//Назначение: Установка специального операнда в памяти, используя непосредственную или косвенную адресацию
//Параметры : Структура прохода, указатель на элемент в в таблице SymTab, строка с именем метки, ключ - тип адресации
//Возв. зн. : -
void UUMAsm :: SetSpecMemOperand(TPassLine &passline, char *string) throw (...)
{
	if (&passline && !passline.GetMemOperand() && string && (string[0] == '@' || string[0] == '#'))
	{
		if (string[0])
		{
			if (TestSymbol(string + 1) || ConvertInteger(string + 1))
			{
				TSymTabElement *symtabelement = AddToSymTab(*SymTab, string, 0, true);
				passline.SetOperand(symtabelement, 1);
				return;
			}
			else
			{
				ErrorList.Add(string, Counter, BadOperand);
				throw AsmError;
			}
		}
		ErrorList.Add(NULL, Counter, NoOperandName);
	}
	throw AsmError;
}
//-----------------------------------------------------------
//Назначение: Тестирование имени метки на наличие служебных символов
//Параметры : Строка для проверки
//Возв. зн  : True - строка прошла тест, false - не прошла
//Оптимизация: Добавить дополнительный параметр, номер ошибки и добавлять ошибку в этой функции
bool UUMAsm :: TestSymbol(const char *string) throw ()
{
	bool Result = false;
	Error = true;
	if (string && string[0])
	{
		try
		{
			//любой идентификатор в программе должен начинаться с допустимого символа, иначе ошибка
			if ((string[0]) && (string[0] >= 48) && (string[0] <= 57))
				throw AsmError;
			size_t index = 0;
			if (string[index] == '+')
				index++;
			while (string[index])
			{
				if 	(
					((33 <= string[index]) && (string[index] <= 47))
					||
					((58 <= string[index]) && (string[index] <= 64))
					||
					((91 <= string[index]) && (string[index] <= 96) && (string[index] != 95))
					||
					((123 <= string[index]) && (string[index] <= 126))
					)
					throw AsmError;
				index++;
			}
			Result = true;
			Error = false;
		}
		catch(...)
		{
			Result = false;
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Тестирование строки на принадлежность к целому числу
//Параметры : Строка для тестирования, адрес переменной для возврата значения (необязательно)
//Возв. зн. : Результат конвертирования
bool UUMAsm :: ConvertInteger(const char *string, int *pValue) throw(...)
{
	bool Result = false;
	Error = true;
	if (string && string[0])
	{
		size_t length = strlen(string);
		char *tempstring = new char[length + 1];
		strcpy_s(tempstring, length + 1, string);
		short base = 0;
		switch (tempstring[strlen(string) - 1])
		{
		case('H'):	base = 16;
					break;
		case('h'):	base = 16;
					break;
		case('B'):	base = 2;
					break;
		case('b'):	base = 2;
					break;
		case('O'):	base = 8;
					break;
		case('o'):	base = 8;
					break;
		default:	base = 10;
		}
		if (base != 10)
			tempstring[--length] = '\0';
		if (tempstring[0])
		{
			char *buffer = NULL;
			errno_t err = 0;
			_set_errno(err);
			int value = strtol(tempstring, &buffer, base);
			_get_errno(&err);
			if (err == ERANGE)
			{
				ErrorList.Add(tempstring, Counter, OverFlow);
				throw AsmError;
			}
			if (!buffer[0])
			{
				Error = false;
				Result = true;
				if (pValue)
					*pValue = value;
			}
		}
		else//число отсутствует
			ErrorList.Add(string, Counter, NoValue);
		delete []tempstring;
		tempstring = NULL;
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Поиск операнда числа для резервирования памяти
FindLex UUMAsm :: SearchValueOpSize(TPassLine &temp, char *string) throw(...)
{
	FindLex Result = NOLEX;
	Error = true;
	DeleteSpacesBefore(string);
	DeleteSpacesAfter(string);
	if (string && string[0])
	{
		int opsize = 0;
		if (ConvertInteger(string, &opsize) && opsize > 0)
		{
			temp.SetObjSize((size_t) opsize);
			Error = false;
			Result = OPERATION;
			string[0] = '\0';
		}
	}
	return Result;
}
//-----------------------------------------------------------
//Назначение: Перевод всех заглавных букв в cтрочные
//Примечание: Не используется в данной версии транслятора и находится в перспективе, но метод протестирован(!)
//-----------------------------------------------------------
/*void UUMAsm :: DownCase(char *string)
{
	if (string)
	{
		unsigned int index = 0;
		int codechar;
		while (string[index])
		{
			codechar = (int)string[index];
			//Английский диапазон ANSII
			if ((65 <= codechar) && (codechar <= 90))
			{
				codechar += 32;
			}
			else
			{
			//Русский диапазон
				if ((-64 <= codechar) && (codechar <= -32))
				{
					codechar += 32;
				}
				else
				{
					//Буква 'Ё'
					if (codechar == -88)
					{
						codechar = -72;
					}
				}
			}
			string[index] = (char)codechar;
			index++;
		}
	}
}*/
//-----------------------------------------------------------
/*//Назначение: Удаление всех пробелов из строки
//Параметры : Обрабатываемая строка
//Воз. зн.  : -
void UUMAsm :: DeleteAllSpaces(char *string) throw(...)
{
	size_t length = strlen(string);
	if (length)
	{
		size_t sourceindex = 0, destindex = 0;
		char *tempstring = new char[length + 1];
		while (string[sourceindex])
		{
			if ((string[sourceindex] != ' ') && (string[sourceindex] != '\t') && (string[sourceindex] != '\n'))
			{
				tempstring[destindex++] = string[sourceindex];
			}
			sourceindex++;
		}
		tempstring[destindex++] = '\0';
		strcpy_s(string, length + 1, tempstring);
		delete []tempstring;
		tempstring = NULL;
	}
}*/