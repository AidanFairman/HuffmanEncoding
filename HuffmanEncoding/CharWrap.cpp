#include "CharWrap.h"

CharWrap::CharWrap(char c)
{
	data = c;
}

CharWrap::CharWrap(unsigned char c)
{
	data = (char)c;
}

CharWrap::~CharWrap()
{
}

char CharWrap::getChar()
{
	return data;
}

void CharWrap::setChar(char c)
{
	data = c;
}

unsigned char CharWrap::getUChar()
{
	return (unsigned char)data;
}

void CharWrap::setChar(unsigned char c)
{
	data = (char)c;
}
