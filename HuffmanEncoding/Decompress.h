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
#include <condition_variable>
#include <iostream>
#include "ProducerConsumerQueue.h"
#include "BinaryTreeNode.h"
#include "OrderedList.h"
#include "CharacterCode.h"
#include "SimpleList.h"
#include "SimpleListIterator.h"
#include "CharWrap.h"
using namespace std;

class Decompress
{
public:
	Decompress(string* file);
	~Decompress();
	bool go();
private:
	bool makeTree(CharacterCode* code);
	bool readFile();
	bool decomp();
	ifstream* inFile;
	ofstream* outFile;
	string* inFileName;
	string* outFileName;
	long charactersInFile;
	SimpleList<CharacterCode>* code_list;
	BinaryTreeNode<CharWrap>* rootNode;
};

