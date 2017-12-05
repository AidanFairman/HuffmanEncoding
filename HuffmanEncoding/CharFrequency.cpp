#include "CharFrequency.h"


CharFrequency::CharFrequency()
{
	character = 0;
	frequency = 0;

}

CharFrequency::CharFrequency(const unsigned char newCharacter)
{
	character = newCharacter;
	frequency = 0;
}

CharFrequency::CharFrequency(const unsigned char newCharacter, const int newFrequency)
{
	character = newCharacter;
	frequency = newFrequency;
}

CharFrequency::CharFrequency(const CharFrequency &newCharFreq)
{
	this->character = newCharFreq.character;
	this->frequency = newCharFreq.frequency;
}

unsigned char CharFrequency::getCharacter()const
{
	return character;
}

void CharFrequency::setCharacter(const unsigned char newCharacter)
{
	if (newCharacter != character)
	{
		character = newCharacter;
	}

}

int CharFrequency::getFrequency()const
{
	return frequency;
}

void CharFrequency::setFrequency(const int newFrequency)
{
	if (newFrequency <= 0)
	{
		frequency = newFrequency;
	}
}

void CharFrequency::increment()
{
	++frequency;
}

bool CharFrequency::operator==(const CharFrequency& rhCharFreq)
{
	if (rhCharFreq.character == this->character && rhCharFreq.frequency == this->frequency)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CharFrequency::operator==(const unsigned char rhCharacter)
{
	if (this->character == rhCharacter)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CharFrequency::operator!=(const CharFrequency& rhCharfreq) {
	return !(this == &rhCharfreq);
}


bool CharFrequency::operator!=(const unsigned char rhCharacter) {
	if (this->character == rhCharacter) {
		return false;
	}
	else {
		return true;
	}
}

CharFrequency* CharFrequency::operator++(int) {//postfix
	CharFrequency* temp = this;
	++frequency;
	return temp;
}
CharFrequency* CharFrequency::operator++()//prefix
{
	++frequency;
	return this;
}
CharFrequency::~CharFrequency() {

}