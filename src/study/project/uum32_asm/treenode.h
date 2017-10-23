#ifndef __TreeNode_h
	#define __TreeNode_h
//-----------------------------------------------------------
//Класс описывает один элемент бинарного дерева поиска
template <class NodeType>
class TreeNode
{
public:
	//--------------
	//Конструктор по умолчанию
	TreeNode() 
		:	
			Data(0), 
			Left(NULL), 
			Right(NULL) 
	{}
	//--------------
	//Конструктор
	TreeNode(const NodeType &data, TreeNode<NodeType> *lptr = NULL, TreeNode<NodeType> *rptr = NULL);
	//--------------
	//Деструктор
	~TreeNode() 
	{
		Left  = NULL;
		Right = NULL;
	}
	//--------------
	//Перегрузка оператора ->
	/*NodeType* operator->()
	{
		return &Data;
	}*/
	//--------------
	NodeType Data;
	TreeNode<NodeType> *Left;
	TreeNode<NodeType> *Right;
	
};
//-----------------------------------------------------------
template <class NodeType>
TreeNode<NodeType> :: TreeNode(const NodeType &data, TreeNode<NodeType> *lptr, TreeNode<NodeType> *rptr) 
	:Data(data), 
	Left(lptr), 
	Right(rptr)
{}
//-----------------------------------------------------------
#endif
