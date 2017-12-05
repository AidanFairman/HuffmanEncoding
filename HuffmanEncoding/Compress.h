#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include <stack>
#include <thread>
#include <mutex>
#include <Windows.h>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <condition_variable>
#include "ProducerConsumerQueue.h"
#include "ReadableStack.h"
#include "BinaryTreeNode.h"
#include "CharFrequency.h"
#include "OrderedList.h"
#include "CharacterCode.h"
#include "SimpleList.h"
#include "SimpleListIterator.h"
using namespace std;

class Compress
{
public:
	Compress(string* file);
	~Compress();
	bool go();
	
private:
	bool getCharacterCounts();
	bool makeTree();
	bool makeCodeTable(BinaryTreeNode<CharFrequency>* node);
	bool performCompress();
	ifstream* inFile;
	ofstream* outFile;
	string* inFileName;
	string* outFileName;
	CharFrequency* charCountList;
	int listSize = UCHAR_MAX + 1;
	long charactersInFile;
	ReadableStack<string> b_code_stack;
	list<BinaryTreeNode<CharFrequency>*> nodeList;
	list<BinaryTreeNode<CharFrequency>*>::iterator iter;
	bool completed;
	SimpleList<CharacterCode>* b_code_list;
	
};

