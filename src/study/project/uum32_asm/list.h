#ifndef __List_h
	#define __List_h
//-----------------------------------------------------------
#ifndef __UUMMess_h
	#include "uummess.h"
#endif
//-----------------------------------------------------------
template <class T> 
class TList;
//Шаблоны для различных классов
template <class T>
class ListNode
{
public:
	ListNode() : Next(NULL) {}
	~ListNode() {Next = NULL;}
	ListNode(const T &data) : Data(data), Next(NULL) {}
	T Data;
	friend class TList<T>;
private:
	ListNode<T> *Next;
};
//-----------------------------------------------------------
//Класс - шаблон. Формирует в памяти однонаправленный список
template <class T>
class TList
{
public:
	TList() : First(NULL), Last(NULL), Counter(0) {}
	~TList() 
	{
		Clear();
	}
	void Add(const T &data) throw (...)
	{
		try
		{
		if (First)
			{
				Last->Next = new ListNode<T>();
				Last = Last->Next;
			}
			else
			{
				First = new ListNode<T>();
				Last = First;
			}
		//Last->Add(data);
		Last->Data = data;
		Counter++;
		}
		catch (...)
		{
			throw HeapError;
		}
	}
	void Clear() throw(...)
	{
		ListNode<T> *tmp;
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
	//T *operator[] (size_t index)  throw (...)
	T *GetPointer(size_t index)
	{
		ListNode<T> *tmp = NULL;
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
		return &(tmp->Data);
	}
	//-----------------------------------------------------------
	T operator[] (size_t index) throw (...)
	{
		if (index >= Counter)
			throw;
		ListNode<T> *tmp = NULL;
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
		return tmp->Data;
	}
	//-----------------------------------------------------------
	size_t GetCount() {return Counter;}
private:
	ListNode<T> *First, *Last;
	size_t Counter;
};
//-----------------------------------------------------------
#endif