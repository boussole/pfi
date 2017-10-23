#ifndef __UUMErrorStruct_h
	#define __UUMErrorStruct_h
//-----------------------------------------------------------
#ifndef __STRING_H
	#include <string.h>
	#define __STRING_H
#endif

#ifndef __UUMMess_h
	#include "uummess.h"
#endif
//-----------------------------------------------------------
// ласс, описывающий ошибки в ходе трансл€ции
//—одержит пол€:
//				- Text - строка характеризующа€ ошибочный параметр
//				- line - строка в исходном файле, где была обнаружена ошибка
//				- ErrorCode - код ошибки, необходим дл€ поиска полного текста сообщени€, выводимого трансл€тором
class TError
{
	public:
		TError() : ErrorCode(0), Line(0), Text(NULL), Next(NULL) {}
		//-----------------------------------------------------------
		TError(const TError &rhs) : ErrorCode(0), Line(0), Text(NULL), Next(NULL)
		{
			Add(rhs.Text, rhs.Line, rhs.ErrorCode);
		}
		//-----------------------------------------------------------
		TError operator = (TError &rhs)
		{
			Add(rhs.Text, rhs.Line, rhs.ErrorCode);
			return *this;
		}
		//-----------------------------------------------------------
		~TError() 
		{
			if (Text) 
			{
				delete []Text;
				Text = NULL;
			}
		}
		//-----------------------------------------------------------
		void Add(const char *text, size_t line, int errorcode) throw(...)
		{
		size_t length = 0;
		if (text)
			length = strlen(text);
		try
		{		
			if (Text)
			{
				delete []Text;
				Text = NULL;
			}
			Text = new char[length + 1];
		}
		catch (...)
		{
			throw HeapError;
		}
			if (text)
				strcpy_s(Text, length + 1, text);
			else
				Text[0] = '\0';
			ErrorCode = errorcode;
			Line = line;
		}
		//-----------------------------------------------------------
		const char * GetText() 
		{
			return Text;
		}
		//-----------------------------------------------------------
		const int GetErrorCode()
		{
			return ErrorCode;
		}
		//-----------------------------------------------------------
		const size_t GetLine()
		{
			return Line;
		}
		//-----------------------------------------------------------
	friend class TErrorList;
	private:
		char *Text;
		int ErrorCode;
		size_t Line;
		TError *Next;
};
//-----------------------------------------------------------
// ласс, сохран€ющий ошибки трансл€ции в пам€ти
//—одержит указатель на структуру ошибки. —оздает и заполн€ет новый объект ошибки
class TErrorList
{
public:
	TErrorList() : First(NULL), Last(NULL), Counter(0) {}
	~TErrorList() 
	{
		Clear();
	}
	void Add(const char *text, size_t line, int errorcode) throw (...)
	{
		try
		{
		if (First)
			{
				Last->Next = new TError();
				Last = Last->Next;
			}
			else
			{
				First = new TError();
				Last = First;
			}
		Last->Add(text, line, errorcode);
		Counter++;
		}
		catch (...)
		{
			throw HeapError;
		}
	}
	void Clear() throw(...)
	{
		TError *tmp;
		try
		{	
			while (First)
				{
					tmp = First;
					First = First->Next;
					delete tmp;
					Counter--;
				}
			Last = NULL;
		}
		catch (...)
		{
			throw HeapError;
		}
	}
	//-----------------------------------------------------------
	TError *GetError(size_t index)
	{
		TError *tmp = NULL;
		if (First && (index < Counter))
		{
			size_t i = 0;
			tmp = First;
			while ((tmp) && (i != index))
			{
				tmp = tmp->Next;
				i++;
			}
		}
		return tmp;
	}
	//-----------------------------------------------------------
	TError operator[] (size_t index) throw (...)
	{
		if (index >= Counter)
			throw;
		TError *tmp = NULL;
		if (First && (index < Counter))
		{
			size_t i = 0;
			tmp = First;
			while ((tmp) && (i != index))
			{
				tmp = tmp->Next;
				i++;
			}
		}
		return *tmp;
	}
	//-----------------------------------------------------------
	size_t GetCount() {return Counter;}
private:
	TError *First, *Last;
	size_t Counter;
};
//-----------------------------------------------------------
#endif