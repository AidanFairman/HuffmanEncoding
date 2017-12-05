#pragma once
class CharWrap
{
public:
	CharWrap(char c);
	CharWrap(unsigned char c);
	~CharWrap();
	char getChar();
	void setChar(char c);
	unsigned char getUChar();
	void setChar(unsigned char c);
private:
	char data;
};

