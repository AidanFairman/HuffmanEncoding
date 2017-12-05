#pragma once


template <class T>
class BinaryTreeNode
{
public:
	BinaryTreeNode(T* contents, double numericValue);
	BinaryTreeNode(BinaryTreeNode* LeftNodePtr, BinaryTreeNode* RightNodePtr, double numericValue);
	~BinaryTreeNode();
	void setRightNode(BinaryTreeNode* right);
	BinaryTreeNode* getRightNode();
	void removeRight();
	bool hasRightNode();
	void setLeftNode(BinaryTreeNode* left);
	BinaryTreeNode* getLeftNode();
	void removeLeft();
	bool hasLeftNode();
	double getNVal();
	T* getValue();
	bool isLeafNode();
private:
	bool isLeaf;
	bool hasLeft;
	bool hasRight;
	BinaryTreeNode* leftNode;
	BinaryTreeNode* rightNode;
	T* value;
	double nVal;
};

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(T* contents, double numericValue)
{
	isLeaf = true;
	value = contents;
	leftNode = nullptr;
	rightNode = nullptr;
	hasLeft = false;
	hasRight = false;
	nVal = numericValue;
}

template<class T>
BinaryTreeNode<T>::BinaryTreeNode(BinaryTreeNode* LeftNodePtr, BinaryTreeNode* RightNodePtr, double numericValue)
{
	leftNode = LeftNodePtr;
	hasLeft = true;
	rightNode = RightNodePtr;
	hasRight = true;
	isLeaf = false;
	value = nullptr;
	nVal = numericValue;
}

template<class T>
BinaryTreeNode<T>::~BinaryTreeNode()
{
	/*if (value != nullptr && value != NULL) {
		delete value;
	}*/
	if (leftNode != nullptr && leftNode != NULL) {
		delete leftNode;
	}
	if (rightNode != nullptr && rightNode != NULL) {
		delete rightNode;
	}
}

template<class T>
void BinaryTreeNode<T>::setRightNode(BinaryTreeNode * right)
{
	rightNode = right;
	hasRight = true;
	isLeaf = false;
}

template<class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getRightNode()
{
	if (hasRight) {
		return rightNode;
	}
	else {
		return nullptr;
	}
}

template<class T>
void BinaryTreeNode<T>::removeRight()
{
	delete rightNode;
	rightNode = nullptr;
	hasRight = false;
	if (!hasLeft) {
		isLeaf = true;
	}
}

template<class T>
bool BinaryTreeNode<T>::hasRightNode() {
	return hasRight;
}

template<class T>
void BinaryTreeNode<T>::setLeftNode(BinaryTreeNode * left)
{
	leftNode = left;
	hasLeft = true;
	isLeaf = false;
}

template<class T>
BinaryTreeNode<T>* BinaryTreeNode<T>::getLeftNode()
{
	if (hasLeft) {
		return leftNode;
	}
	else {
		return nullptr;
	}
}

template<class T>
void BinaryTreeNode<T>::removeLeft()
{
	delete leftNode;
	leftNode = nullptr;
	hasLeft = false;
	if (!hasRight) {
		isLeaf = true;
	}
}

template<class T>
bool BinaryTreeNode<T>::hasLeftNode() {
	return hasLeft;
}

template <class T>
T* BinaryTreeNode<T>::getValue() {
	return value;
}

template <class T>
bool BinaryTreeNode<T>::isLeafNode() {
	return isLeaf;
}

template <class T>
double BinaryTreeNode<T>::getNVal() {
	return nVal;
}