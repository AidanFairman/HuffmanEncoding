// HuffmanEncoding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include "Compress.h"
#include "Decompress.h"

using namespace std;

char* convertWStringToASCIIString(const wstring input);

int _tmain(int argc, _TCHAR* argv[]) {
	char* inputFile;
	string compDecomp;
	string inputFileStr;

	if (argc == 3) {
		inputFile = convertWStringToASCIIString(argv[1]);
		compDecomp = convertWStringToASCIIString(argv[2]);
		inputFileStr = inputFile;
		
	}
	else if (argc == 1) {
		inputFileStr = "test.txt";
		compDecomp = "-c";
	}
	else {
		cout << "Wrong number of parameters." << endl;
		cout << "Proper use is [programName.exe] [file.txt] [-c]" << endl;
		cout << "-c is compress, -d is decompress" << endl;
		cout << "Quitting execution..." << endl;
		return 0;
	}


	if (compDecomp == "-c") {
		Compress* comp = new Compress(&inputFileStr);
		comp->go();
		delete comp;
	}
	else if (compDecomp == "-d") {
		Decompress* dec = new Decompress(&inputFileStr);
		dec->go();
		delete dec;
	}
	else {
		cout << "improper command. proper use is -c for compress or -d for decompress" << endl;
	}
	return 0;
}

//copied from an answer in stackoverflow: http://stackoverflow.com/questions/18645874/converting-stdwsting-to-char-with-wcstombs-s
char* convertWStringToASCIIString(const wstring input) {
	char* output;
	size_t outputSize = (input.length() + 1);
	output = new char[outputSize];
	size_t charsConverted = 0;
	const wchar_t* inputW = input.c_str();
	wcstombs_s(&charsConverted, output, outputSize, inputW, input.length());
	return output;
}