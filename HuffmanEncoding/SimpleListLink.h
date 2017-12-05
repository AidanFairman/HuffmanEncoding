#pragma once

template <class T>
class SimpleListLink
{
public:
	SimpleListLink(T* element);
	~SimpleListLink();
	T& operator*();
	SimpleListLink<T>* getNext();
	SimpleListLink<T>* getPrev();
	void setNext(SimpleListLink<T>* element);
	void setPrev(SimpleListLink<T>* element);
	T* getData();
	void setData(T* element);
private:
	T* data;
	SimpleListLink<T>* next;
	SimpleListLink<T>* prev;
};

template<class T>
SimpleListLink<T>::SimpleListLink(T* element)
{
	data = element;
}

template<class T>
SimpleListLink<T>::~SimpleListLink()
{
}

template<class T>
T& SimpleListLink<T>::operator*()
{
	return *data;
}

template<class T>
SimpleListLink<T>* SimpleListLink<T>::getNext()
{
	return next;
}

template<class T>
SimpleListLink<T>* SimpleListLink<T>::getPrev()
{
	return prev;
}

 template<class T>
 void SimpleListLink<T>::setNext(SimpleListLink<T>* element)
 {
	 next = element;
 }

 template<class T>
 void SimpleListLink<T>::setPrev(SimpleListLink<T>* element)
 {
	 prev = element;
 }

 template<class T>
 T* SimpleListLink<T>::getData()
 {
	 return data;
 }

 template<class T>
 void SimpleListLink<T>::setData(T * element)
 {
	 data = element;
 }
