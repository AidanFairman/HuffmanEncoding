#include "Compress.h"



int compare(const void* a, const void* b) {
	return ((*(CharFrequency*)a).getFrequency() - ((*(CharFrequency*)b).getFrequency()));
}

bool readIn(ProducerConsumerQueue<string>* buffer, ifstream* inFile, SimpleList<CharacterCode>* codeList);
bool writeOut(ProducerConsumerQueue<string>* buffer, ofstream* outFile);

Compress::Compress(string* file)
{
	
	b_code_list = new SimpleList<CharacterCode>();
	inFile = new ifstream();
	inFile->unsetf(ios_base::skipws);
	outFile = new ofstream();
	stringstream ss;
	ss << "comp-" << *file;
	outFileName = new string(ss.str());
	inFileName = file;
	inFile->open(*file, ios::in | ios::binary);
	outFile->open(ss.str(), ios::out | ios::binary);
	charCountList = (new CharFrequency[listSize]);
	CharFrequency CF;
	for (unsigned char i = 0; i < listSize - 1; ++i) {
		CF = *(new CharFrequency(i));
		charCountList[i] = CF;
	}
	charCountList[UCHAR_MAX] = *(new CharFrequency(UCHAR_MAX));
	charactersInFile = 0;
}

bool Compress::go() {
	if (!getCharacterCounts()) {
		return false;
	}
	if (!makeTree()) {
		return false;
	}
	if (!makeCodeTable(nodeList.front())) {
		return false;
	}
	if (!performCompress()) {
		return false;
	}
	return true;
	
}

bool Compress::getCharacterCounts() {
	char inChar;
	if (inFile->is_open()) {
		while (!inFile->eof()) {
			inFile->get(inChar);
			++(charCountList[inChar]);
			++charactersInFile;
		}
	}
	else {
		return false;
	}
	qsort(this->charCountList, (this->listSize - 1), sizeof(CharFrequency), compare);
	for (int i = 0; i < listSize; ++i) {
		std::cout << charCountList[i].getCharacter() << "   " << charCountList[i].getFrequency() << std::endl;
	}
	//inFile->close();
	return true;
}

bool Compress::makeTree() {
	BinaryTreeNode<CharFrequency>* left;
	BinaryTreeNode<CharFrequency>* right;
	BinaryTreeNode<CharFrequency>* newNode;
	for (unsigned short i = 0; i < listSize; ++i) {
		if (charCountList[i].getFrequency() > 0) {
			nodeList.push_back(new BinaryTreeNode<CharFrequency>(&(charCountList[i]), charCountList[i].getFrequency()));
		}
	}
	while (nodeList.size() > 1) {
		

		left = nodeList.front();
		nodeList.pop_front();

		right = nodeList.front();
		nodeList.pop_front();

		newNode = new BinaryTreeNode<CharFrequency>(left, right, (left->getNVal() + right->getNVal()));
		iter = nodeList.begin();
		if (!nodeList.size()) {
			nodeList.push_front(newNode);
			break;
		}
		else {
			while (iter != nodeList.end()) {

				if (newNode->getNVal() > nodeList.back()->getNVal()) {
					nodeList.push_back(newNode);
					break;
				}
				else if (newNode->getNVal() > iter._Mynode()->_Myval->getNVal()) {
					++iter;
				}
				else {
					nodeList.insert(iter, newNode);
					break;
				}
			}
		}
	}
	return true;
}

bool Compress::makeCodeTable(BinaryTreeNode<CharFrequency>* node) {
	string one("1");
	string zero("0");
	if (node->isLeafNode()) {
		b_code_list->push_back(new CharacterCode(node->getValue()->getCharacter(), b_code_stack.readBottomUp()));
		return true;
	}
	else {
		bool hasLeft, hasRight;
		hasLeft = hasRight = true;
		if (node->hasLeftNode()) {
			b_code_stack.push(&zero);
			makeCodeTable(node->getLeftNode());
			node->removeLeft();
			b_code_stack.pop();
		}
		else {
			hasLeft = false;
		}
		if (node->hasRightNode()) {
			b_code_stack.push(&one);
			makeCodeTable(node->getRightNode());
			node->removeRight();
			b_code_stack.pop();
		}
		else {
			hasRight = false;
		}
		return (hasRight || hasLeft);
	}
}

bool Compress::performCompress() {
	if (outFile->is_open()) {
		*outFile << charactersInFile << endl;
		*outFile << b_code_list->getSize() << endl;
		SimpleListIterator<CharacterCode> iter = b_code_list->begin();
		string* code;
		for (long i = 0; i < b_code_list->getSize(); ++i) {
			code = iter->getCode();
			*outFile << (short)(iter->getCharacter()) << "," << *code << endl;
			++iter;

		}
	}
	else {
		return false;
	}
	
	ProducerConsumerQueue<string> queue(20);
	//outFile->open(*outFileName, ios::out | ios::app );
	thread produce(readIn, &queue, inFile, b_code_list);

	thread consume(writeOut, &queue, outFile);

	produce.join();
	consume.join();
	return true;
}

bool readIn(ProducerConsumerQueue<string>* buffer, ifstream* inFile, SimpleList<CharacterCode>* codeList) {
	mutex mtx;
	unique_lock<mutex> lck(mtx);
	condition_variable CV;
	buffer->RegisterProducer(&CV, &lck);
	unsigned char readChar = 0;
	char* code;
	bool codeFound = false;
	SimpleListIterator<CharacterCode>* iter = new SimpleListIterator<CharacterCode> (codeList->begin());
	inFile->clear();
	inFile->seekg(0, ios::beg);
	if (inFile->is_open()) {
		while (!inFile->eof()) {
			while (buffer->isFull()) {
				chrono::time_point<chrono::system_clock> timeNow = chrono::system_clock::now();
				CV.wait_until(lck, timeNow + 5ms);
			}
			*inFile >> readChar;
			codeFound = false;
			*iter = codeList->begin();
			while (!codeFound) {
				if (iter->peek()->getCharacter() == readChar) {
					buffer->push(iter->peek()->getCode());
					codeFound = true;
				}
				else {
					++(*iter);
				}
			}
		}
	}
	else {
		return false;
	}
	buffer->setProducerFinished();
	buffer->UnregisterProducer();
//	delete code;
	delete iter;
	return true;
}

bool writeOut(ProducerConsumerQueue<string>* buffer, ofstream* outFile) {
	mutex mtx;
	unique_lock<mutex> lck(mtx);
	condition_variable CV;
	outFile->clear();
	flush(*outFile);
	buffer->RegisterConsumer(&CV, &lck);
	unsigned char toWrite = 0;
	ZeroMemory(&toWrite, sizeof(char));
	unsigned char bitsShifted = 0;
	string* pulled;
	char* code = new char[1];
	code[0] = (char)0;
	unsigned int i = 0;
	if (outFile->is_open()) {
		while (!(buffer->isEmpty() && buffer->isProducerFinished())) {
			switch (code[i]) {
			case '0':
				toWrite = (toWrite << 1);
				++bitsShifted;
				++i;
				break;
			case '1':
				
				toWrite = (toWrite << 1);
				toWrite = (toWrite | 1);
				++bitsShifted;
				++i;
				break;
			default:
				while(buffer->isEmpty()) {
					chrono::time_point<chrono::system_clock> timeNow = chrono::system_clock::now();
					CV.wait_until(lck, timeNow + 5ms);
				}
				pulled = buffer->pull();
				code = (char*)(pulled->c_str());
				i = 0;
			}
			if (bitsShifted == 8) {
				*outFile << toWrite;
				ZeroMemory(&toWrite, sizeof(unsigned char));
				bitsShifted = 0;
			}
		}
		for (bitsShifted; bitsShifted < 8; ++bitsShifted) {
			toWrite = (toWrite << 1);
		}
		*outFile << toWrite;
	}
	else {
		return false;
	}
//	delete code;
	buffer->UnregisterConsumer();
	return true;
}

Compress::~Compress()
{
	inFile->close();
	outFile->close();
	//delete inFile;
	//delete outFile;
	//delete inFileName;
	delete outFileName;
	delete[] charCountList;
	delete b_code_list;
}
