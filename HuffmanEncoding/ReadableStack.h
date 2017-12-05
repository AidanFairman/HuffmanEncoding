#pragma once
#include <string>
#include <sstream>
#include <mutex>
using namespace std;

/*template <class T>
struct readableLink {
	T* value;
	readableLink<T>* next;
	readableLink<T>* previous;
};*/

template <class T>
class ReadableStack{
public:
	ReadableStack();
	~ReadableStack();
	void push(T* element);
	void pop();
	T* peek();
	int size();
	string* readTopDown();
	string* readBottomUp();
private:
	template <class T>
	struct readableLink {
		T* value;
		readableLink<T>* next;
		readableLink<T>* previous;
	};
	int mySize = 0;
	readableLink<T>* headLink = nullptr;
	readableLink<T>* tailLink = nullptr;
	mutex lock;
};

template <class T>
ReadableStack<T>::ReadableStack() {
	mySize = 0;
}

template <class T>
ReadableStack<T>::~ReadableStack() {

}

template <class T>
void ReadableStack<T>::push(T* element) {
	lock.lock();
	readableLink<T>* newLink = new readableLink<T>();
	newLink->value = element;
	if (mySize) {
		newLink->previous = nullptr;
		newLink->next = headLink;
		headLink->previous = newLink;
		headLink = newLink;
	}
	else {
		headLink = tailLink = newLink;
	}
	++mySize;
	lock.unlock();
}

template <class T>
void ReadableStack<T>::pop() {
	lock.lock();
	if (mySize) {
		readableLink<T>* done = headLink;
		headLink = headLink->next;
		if (headLink != nullptr && headLink != NULL) {
			headLink->previous = nullptr;
		}
		delete done;
		--mySize;
	}
	if (!mySize) {

	}
	lock.unlock();
}

template <class T>
T* ReadableStack<T>::peek() {
	lock.lock();
	if (headLink != nullptr && headLink != NULL) {
		return headLink->value;
	}
	else {
		return nullptr;
	}
	lock.unlock();
}

template <class T>
int ReadableStack<T>::size() {
	return mySize;
}

template <class T>
string* ReadableStack<T>::readTopDown() {
	lock.lock();
	stringstream ss;
	readableLink<T> l = headLink;
	for (int i = 0; i < mySize; ++i) {
		ss << *(l->value);
		l = l->next;
	}
	lock.unlock();
	return new string(ss.str());

}

template <class T>
string* ReadableStack<T>::readBottomUp() {
	lock.lock();
	stringstream ss;
	readableLink<T>* l = tailLink;
	for (int i = 0; i < mySize; ++i) {
		ss << *(l->value);
		l = l->previous;
	}
	lock.unlock();
	return new string(ss.str());
	
}