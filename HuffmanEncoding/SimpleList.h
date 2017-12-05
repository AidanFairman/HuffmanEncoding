#pragma once
#include "SimpleListLink.h"

template <class T>
class SimpleList
{
	//template <class T> friend class SimpleListIterator;
public:
	SimpleList();
	void push_front(T* element);
	void push_back(T* element);
	void pop_front();
	void pop_back();
	T* pull_front();
	T* pull_back();
	T* peek_front();
	T* peek_back();
	long getSize();
	SimpleListLink<T>* begin();
	SimpleListLink<T>* end();
	~SimpleList();
private:
	SimpleListLink<T>* head;
	SimpleListLink<T>* tail;
	long mySize;
};

template <class T>
SimpleList<T>::SimpleList() {
	head = tail = nullptr;
	mySize = 0;
}

template <class T>
void SimpleList<T>::push_front(T* element) {
	SimpleListLink<T>* newlink = new SimpleListLink<T>(element);
	if (!mySize) {
		head = tail = newlink;
		newlink->prev = nullptr;
		newlink->next = nullptr;
	}
	else {
		newlink->setNext(head);
		head->setPrev(newlink);
		head = newlink;
		newlink->setPrev(nullptr);
	}
	++mySize;
}

template<class T>
 void SimpleList<T>::push_back(T* element)
{
	SimpleListLink<T>* newlink = new SimpleListLink<T>(element);
	if (!mySize) {
		head = tail = newlink;
		newlink->setPrev(nullptr);
		newlink->setNext(nullptr);
	}
	else {
		newlink->setPrev(tail);
		tail->setNext(newlink);
		tail = newlink;
		newlink->setNext(nullptr);
	}
	++mySize;
}

template<class T>
 void SimpleList<T>::pop_front()
{
	if (mySize > 1) {
		SimpleListLink<T>* toKill;
		toKill = head;
		head = head->getNext();
		head->setPrev(nullptr);
		delete toKill;
		--mySize;
	}
	else if (mySize == 1) {
		delete head;
		--mySize;
	}
}

template<class T>
 void SimpleList<T>::pop_back()
{
	if (mySize > 1) {
		SimpleListLink<T>* toKill;
		toKill = tail;
		tail = tail->getPrev();
		tail->setNext(nullptr);
		delete toKill;
		--mySize;
	}
	else if (mySize == 1) {
		delete tail;
		--mySize;
	}
}

template<class T>
 T* SimpleList<T>::pull_front()
{
	SimpleListLink<T>* toReturn = peek_front();
	pop_front();
	return toReturn->getData;
}

template<class T>
 T* SimpleList<T>::pull_back()
{
	SimpleListLink<T>* toReturn = peek_back();
	pop_back();
	return toReturn->getData();
}

template<class T>
 T* SimpleList<T>::peek_front()
{
	return head->getData();
}

template<class T>
 T* SimpleList<T>::peek_back()
{
	return tail->getData();
}

 template<class T>
  long SimpleList<T>::getSize()
 {
	 return mySize;
 }

  template<class T>
 SimpleListLink<T>* SimpleList<T>::begin()
  {
	  return head;
  }

  template<class T>
  inline SimpleListLink<T>* SimpleList<T>::end()
  {
	  return tail;
  }

 template <class T>
 SimpleList<T>::~SimpleList() {
	 while (mySize) {
		 pop_front();
	 }
 }