#ifndef __BinTree_h
	#define __BinTree_h
//-----------------------------------------------------------
#ifndef __TreeNode_h
	#include "treenode.h"
#endif

#ifndef __UUMTableStruct_h
	#include "uumtablestruct.h"
#endif
//-----------------------------------------------------------
//Класс описывает все действия с бинарным деревом поиска
template <class NodeType>
class BinTree
{
	public:
		//--------------
		BinTree()
			:Root (NULL)
		{}
		//--------------
		~BinTree()
		{
			Clear();
		}
		//--------------
		NodeType* Add(const NodeType &data) throw (...);
		NodeType* Search(const NodeType &data);
		NodeType* Search(const char *data);
		void Clear();
		void DeleteTree(TreeNode<NodeType> * &temp);
		//--------------
	protected:
		TreeNode<NodeType> *Root;

};
//-----------------------------------------------------------
//Назначение: Функция полной очистки бинарного дерева
//Параметры:  -
//Возвр. зн.: -
template <class NodeType>
void BinTree<NodeType> :: Clear() 
{
	DeleteTree(Root);
}
//-----------------------------------------------------------
//Назначение: Удаление поддеревьев более нижних уровней, начиная от текщуго узла
//Параметры : Узел, начало удаления
//Возвр. зн.: -
template <class NodeType>
void BinTree<NodeType> :: DeleteTree(TreeNode<NodeType> * &temp)
{
	if (temp)
	{
		DeleteTree(temp->Left);
		DeleteTree(temp->Right);
		delete (temp);
		temp = NULL;
	}
}
//-----------------------------------------------------------
//Назначение: Добавление элемента в бинарное дерево с одновременной сортировкой
//Параметры : Вставляемое значение
//Возв. зн. : -
template <class NodeType>
NodeType *BinTree<NodeType> :: Add(const NodeType &data) throw (...)
{
	try
	{
	if (!Root)
	{	
		Root = new TreeNode<NodeType>(data);	
	}
	else
	{
		TreeNode<NodeType> *parent = Root, *current = Root;
		while (current)
		{
			parent = current;
			int result;
			switch (result = (data < parent->Data))
			{
			case (-1):
					if (parent->Left)
						{
							current = parent->Left;
						}
						else
						{
							parent->Left = new TreeNode<NodeType>(data);
							return &parent->Left->Data;
							//current = NULL;
						}
					break;
			//---------------------------
			case (1):
					if (parent->Right)
						{
							current = parent->Right;
						}
						else
						{
							parent->Right = new TreeNode<NodeType>(data);
							return &parent->Right->Data;
							//current = NULL;
						}
					break;
			//---------------------------
			case (0):
					parent->Data = data;
					return &parent->Data;
					break;
			}
		}
	}
	}
	//---------
	catch (...)
	{
		throw HeapError;
	}
	return NULL;
}
//-----------------------------------------------------------
//Назначение: Поиск записи в бинарном дереве
//Параметры : Структура для поиска
//Воз. зн.  : Указатель на запись
template <class NodeType>
NodeType* BinTree<NodeType> :: Search(const NodeType &data)
{
	if (Root)
	{
		TreeNode<NodeType> *temp = Root;
		while (temp)
		{
			switch (data < temp->Data)
			{
			case (-1):	temp = temp->Left;
						break;
			case (1) :	temp = temp->Right;
						break;
			case (0) :	return &temp->Data;
						break;
			}
		}
		return NULL;
	}
}
//-----------------------------------------------------------
/*template <class NodeType>
class UUMBinTree : public BinTree<NodeType>
{
	public:
			NodeType *Search(const char *);
};*/
//-----------------------------------------------------------
template <class NodeType>
NodeType* BinTree<NodeType> :: Search(const char *data)
{
	if (Root)
	{
		TreeNode<NodeType> *temp = Root;
		while (temp)
		{
			switch (data < temp->Data)
			{
			case (-1):	temp = temp->Left;
						break;
			case (1) :	temp = temp->Right;
						break;
			case (0) :	return &temp->Data;
						break;
			}
		}
	}
	return NULL;
}
//-----------------------------------------------------------
#endif
//-----------------------------------------------------------