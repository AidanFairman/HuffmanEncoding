#pragma once
#include<thread>
#include<condition_variable>
#include<mutex>
#include"SimpleListLink.h"
using namespace std;

template <class T>
class ProducerConsumerQueue
{
public:
	ProducerConsumerQueue(const unsigned int sizeLimit);
	~ProducerConsumerQueue();
	void RegisterProducer(condition_variable* CV, unique_lock<mutex>* lck);
	void RegisterConsumer(condition_variable* CV, unique_lock<mutex>* lck);
	void UnregisterProducer();
	void UnregisterConsumer();
	void push(T* element);
	void pop();
	T* peek();
	T* pull();
	void setProducerFinished();
	bool isProducerFinished();
	unsigned int getSize();
	bool isFull();
	bool isEmpty();
private:
	/*struct queueLink {
		T* value;
		queueLink* next;
	};*/
	SimpleListLink<T>* head;
	SimpleListLink<T>* tail;
	bool registeredP;
	bool registeredC;
	bool full;
	bool isEmptyQ;
	bool doneProducing;
	unsigned int listSize;
	const unsigned int maxSize;
	condition_variable* producerCV;
	unique_lock<mutex>* producerLck;
	condition_variable* consumerCV;
	unique_lock<mutex>* consumerLck;
	mutex mtx;
};

template <class T>
ProducerConsumerQueue<T>::ProducerConsumerQueue(const unsigned int sizeLimit): maxSize(sizeLimit) {
	listSize = 0;
	head = tail = nullptr;
	registeredC = registeredP = false;
	full = false;
	isEmptyQ = true;
	doneProducing = false;
}

template <class T>
void ProducerConsumerQueue<T>::RegisterProducer(condition_variable* CV, unique_lock<mutex>* lck) {
	this->producerCV = CV;
	this->producerLck = lck;
	registeredP = true;
}

template <class T>
void ProducerConsumerQueue<T>::RegisterConsumer(condition_variable* CV, unique_lock<mutex>* lck) {
	this->consumerCV = CV;
	this->consumerLck = lck;
	registeredC = true;
}

template <class T>
void ProducerConsumerQueue<T>::UnregisterProducer() {
	this->producerCV = nullptr;
	this->producerLck = nullptr;
	registeredP = false;
}

template <class T>
void ProducerConsumerQueue<T>::UnregisterConsumer() {
	this->consumerCV = nullptr;
	this->consumerLck = nullptr;
	registeredC = false;
}

template <class T>
void ProducerConsumerQueue<T>::push(T* element) {
	mtx.lock();
	SimpleListLink<T>* addLink = new SimpleListLink<T>(element);
	if (listSize == 0) {
		head = tail = addLink;
	}
	else {
		tail->setNext(addLink);
		tail = tail->getNext();
		
	}
	++listSize;
	isEmptyQ = false;
	/*if (registeredC) {
		//consumerLck->unlock();
		consumerCV->notify_all();
	}*/
	if (listSize >= maxSize) {
		full = true;
	}
	if (registeredC) {
		//consumerLck->unlock();
		consumerCV->notify_all();
	}
	mtx.unlock();
}

template <class T>
void ProducerConsumerQueue<T>::pop() {
	mtx.lock();
	if (listSize) {
		SimpleListLink<T>* temp = head;
		head = head->getNext();
		delete temp;
		--listSize;
		full = false;
		/*if (registeredP) {
			//producerLck->unlock();
			producerCV->notify_all();
		}*/
	}
	if(!listSize) {
		isEmptyQ = true;
	}
	if (registeredP) {
		//producerLck->unlock();
		producerCV->notify_all();
	}
	mtx.unlock();
}

template <class T>
T* ProducerConsumerQueue<T>::peek() {
	mtx.lock();
	T* temp = head->getData();
	mtx.unlock();
	return temp;
	
}

template <class T>
T* ProducerConsumerQueue<T>::pull() {
	T* element = peek();
	pop();
	return element;
}

template<class T>
 void ProducerConsumerQueue<T>::setProducerFinished()
{
	doneProducing = true;
}

template<class T>
 bool ProducerConsumerQueue<T>::isProducerFinished()
{
	return doneProducing;
}

template<class T>
 unsigned int ProducerConsumerQueue<T>::getSize()
{
	return listSize;
}

template<class T>
bool ProducerConsumerQueue<T>::isFull()
{
	return full;
}

template<class T>
bool ProducerConsumerQueue<T>::isEmpty()
{
	return isEmptyQ;
}

template <class T>
ProducerConsumerQueue<T>::~ProducerConsumerQueue() {
	while (listSize) {
		pop();
	}
}