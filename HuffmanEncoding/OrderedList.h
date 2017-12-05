#pragma once
#include<list>
#include<string>
#include<sstream>

using namespace std;

template <class T>
class OrderedList
{
public:
	OrderedList();
	~OrderedList();
	void add(T* element);
	void print();
	list<T*> theList;
private:
	
	typename list<T*>::iterator iter = theList.begin();

};

template <class T>
OrderedList<T>::OrderedList() {
	
}

template <class T>
void OrderedList<T>::add(T* element) {
	if (theList.size() == 0){
		theList.push_back(element);
	}
	else if (*element < *(theList.front())) {
		theList.push_front(element);
	}
	else if (*element > *(theList.back())) {
		theList.push_back(element);
	}
	else {
		iter = theList.begin();
		while (iter != theList.end()) {
			if (*element > **iter) {
				++iter;
			}
			else {
				theList.insert(iter, element);
				break;
			}
		}
	}
}

template<class T>
void OrderedList<T>::print() {
	stringstream ss;
	iter = theList.begin();
	ss << **iter;
	++iter;
	for (; iter != theList.end(); ++iter) {
		ss << ", "<< **iter;
	}
	cout << ss.str() << endl;
}

template <class T>
OrderedList<T>::~OrderedList() {
	theList.erase(theList.begin(), theList.end());
}