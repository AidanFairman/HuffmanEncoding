#include "CharacterCode.h"



CharacterCode::CharacterCode(unsigned char character, string* code): character(character)
{
	this->code = code;
}

CharacterCode::CharacterCode(CharacterCode* cc) : character(cc->character) {
	this->code = (cc->code);
}

unsigned char CharacterCode::getCharacter() {
	return character;
}

string* CharacterCode::getCode() {
	return code;
}

CharacterCode::~CharacterCode()
{
	delete code;
}
