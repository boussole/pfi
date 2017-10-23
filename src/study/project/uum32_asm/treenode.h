#ifndef __TreeNode_h
	#define __TreeNode_h
//-----------------------------------------------------------
//����� ��������� ���� ������� ��������� ������ ������
template <class NodeType>
class TreeNode
{
public:
	//--------------
	//����������� �� ���������
	TreeNode() 
		:	
			Data(0), 
			Left(NULL), 
			Right(NULL) 
	{}
	//--------------
	//�����������
	TreeNode(const NodeType &data, TreeNode<NodeType> *lptr = NULL, TreeNode<NodeType> *rptr = NULL);
	//--------------
	//����������
	~TreeNode() 
	{
		Left  = NULL;
		Right = NULL;
	}
	//--------------
	//���������� ��������� ->
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
