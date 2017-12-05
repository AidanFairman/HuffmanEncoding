#pragma once
#include <string>
using namespace std;
class CharacterCode
{
public:
	CharacterCode(unsigned char character, string* code);
	CharacterCode(CharacterCode* CC);
	string* getCode();
	unsigned char getCharacter();
	~CharacterCode();
private:
	unsigned char character;
	string* code;
};

