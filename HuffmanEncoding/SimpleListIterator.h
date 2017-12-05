#pragma once
#include "SimpleListLink.h"

template<class T>
class SimpleListIterator
{
public:
	SimpleListIterator();
	SimpleListIterator(SimpleListLink<T>* link);
	SimpleListIterator(SimpleListIterator<T>* iter);
	T* peek();
	SimpleListIterator<T>* operator++();//prefix
	SimpleListIterator<T>* operator++(int);//postfix
	SimpleListIterator<T>* operator--();//prefix
	SimpleListIterator<T>* operator--(int);//postfix
	SimpleListIterator<T>* operator=(SimpleListLink<T>* listLink);
	SimpleListIterator<T>* operator=(SimpleListIterator<T>* iter);
	T& operator*();
	T* operator->();
	~SimpleListIterator();
private:
	SimpleListLink<T>* currentLink;
};

template<class T>
 SimpleListIterator<T>::SimpleListIterator()
{
	
	currentLink = nullptr;
}

 template<class T>
 inline SimpleListIterator<T>::SimpleListIterator(SimpleListLink<T>* link)
 {
	 currentLink = link;
 }

 template<class T>
 inline SimpleListIterator<T>::SimpleListIterator(SimpleListIterator<T>* iter)
 {
	 this->currentLink = iter->currentLink;
 }

template<class T>
 T* SimpleListIterator<T>::peek()
{
	return currentLink->getData();
}

template<class T>
 SimpleListIterator<T>* SimpleListIterator<T>::operator++()//prefix
{
	currentLink = currentLink->getNext();
	return this;
}

template<class T>
 SimpleListIterator<T>* SimpleListIterator<T>::operator++(int)//postfix
{
	SimpleListIterator<T> temp = this;
	currentLink = currentLink->getNext();
	return temp;
}

template<class T>
 SimpleListIterator<T>* SimpleListIterator<T>::operator--()//prefix
{
	currentLink = currentLink->getPrev();
	return this;
}

template<class T>
 SimpleListIterator<T>* SimpleListIterator<T>::operator--(int)//postfix	
{
	SimpleListIterator<T> temp = this;
	currentLink = currentLink->getPrev();
	return temp;
}

 template<class T>
 SimpleListIterator<T>* SimpleListIterator<T>::operator=(SimpleListLink<T>* listLink)
 {
	 currentLink = listLink;
	 return this;
 }

 template<class T>
 SimpleListIterator<T>* SimpleListIterator<T>::operator=(SimpleListIterator<T>* iter)
 {
	 this->currentLink = iter->currentLink;
	 return this;
 }

template<class T>
 T& SimpleListIterator<T>::operator*()
{
	return *(currentLink->getData());
}

template<class T>
 T* SimpleListIterator<T>::operator->()
{
	return currentLink->getData();
}

template<class T>
 SimpleListIterator<T>::~SimpleListIterator()
{
}
