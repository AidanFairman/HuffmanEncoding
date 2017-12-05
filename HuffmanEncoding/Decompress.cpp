#include "Decompress.h"

Decompress::Decompress(string* file)
{
	code_list = new SimpleList<CharacterCode>();
	inFile = new ifstream();
	outFile = new ofstream();
	stringstream ss;
	ss << "decomp-" << *file;
	outFileName = new string(ss.str());
	inFileName = file;
	inFile->open(*file, ios::in | ios::binary);
	inFile->unsetf(ios_base::skipws);
	outFile->open(ss.str(), ios::out | ios::binary);
	rootNode = new BinaryTreeNode<CharWrap>(nullptr, (double)0);
}

bool Decompress::go() {
	if (!readFile()) {
		return false;
	}
	if (!decomp()) {
		return false;
	}
	return true;
}

Decompress::~Decompress()
{
	delete outFileName;
	delete inFile;
	delete outFile;
	delete code_list;
	delete rootNode;
}

bool Decompress::readFile() {
	string gotten;
	int characterCodeCount;
	char character;
	string* code;
	char* charNum;
	char* charCode;
	int preChar;
	if (inFile->is_open()) {
		getline(*inFile, gotten);
		charactersInFile = atol(gotten.c_str());
		getline(*inFile, gotten);
		characterCodeCount = atoi(gotten.c_str());
		for (int i = 0; i < characterCodeCount; ++i) {
			getline(*inFile, gotten);
			charNum = strtok((char*)gotten.c_str(), ",");
			charCode = strtok(NULL, ",");
			preChar = atoi(charNum);
			code = new string(charCode);
			makeTree(new CharacterCode((const unsigned char)preChar,code));
			delete code;
		}
		return true;
	}
	else {
		return false;
	}
}

bool Decompress::makeTree(CharacterCode* code) {
	bool charInserted = false;
	bool lastInsert = false;
	BinaryTreeNode<CharWrap>* currentNode = rootNode;
	string* codePathS = code->getCode();
	char* codePath = (char*)code->getCode()->c_str();
	int length = code->getCode()->length();
	unsigned char i = 0;
	while (!charInserted) {
		switch (codePath[i]) {
		case '0':
			if (currentNode->hasLeftNode()) {
				currentNode = currentNode->getLeftNode();
			}
			else {
				if (!(codePath[i + 1])) {
					currentNode->setLeftNode(new BinaryTreeNode<CharWrap>(new CharWrap(code->getCharacter()), (double)0));
					charInserted = true;
				}
				else {
					currentNode->setLeftNode(new BinaryTreeNode<CharWrap>(nullptr, (double)0));
					currentNode = currentNode->getLeftNode();
				}
			}
			++i;
			break;
		case '1':
			if (currentNode->hasRightNode()) {
				currentNode = currentNode->getRightNode();
			}
			else {
				if (!(codePath[i + 1])) {
					currentNode->setRightNode(new BinaryTreeNode<CharWrap>(new CharWrap(code->getCharacter()), (double)0));
					charInserted = true;
				}
				else {
					currentNode->setRightNode(new BinaryTreeNode<CharWrap>(nullptr, (double)0));
					currentNode = currentNode->getRightNode();
				}
			}
			++i;
			break;
		default:
			return true;
		}
	}
	return true;
	
}

bool Decompress::decomp() {
	char shifts = 8;
	unsigned char firstBit;
	char readChar = 0;
	char code = 0;
	BinaryTreeNode<CharWrap>* node = rootNode;
	if (outFile->is_open() && inFile->is_open()) {
		while (charactersInFile) {
			if (shifts == 8) {
				inFile->get(readChar);
				shifts = 0;
			}
			firstBit = (readChar & 128);
			readChar = readChar << 1;
			++shifts;
			switch (firstBit){
			case 0:
				node = node->getLeftNode();
				break;
			case 128:
				node = node->getRightNode();
				break;
			default:
				break;
			}
			if (node->isLeafNode()) {
				code = node->getValue()->getChar();
				*outFile << code;
				--charactersInFile;
				node = rootNode;
			}
		}
	}
	else {
		return false;
	}
	return true;
}
