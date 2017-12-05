#pragma once
class CharFrequency
{
public:
	CharFrequency();
	CharFrequency(const unsigned char newCharacter);
	CharFrequency(const unsigned char newCharacter, const int newFrequency);
	CharFrequency(const CharFrequency &charFreq);
	unsigned char getCharacter()const;
	void setCharacter(const unsigned char newCharacter);
	int getFrequency()const;
	void setFrequency(const int newFrequency);
	void increment();
	bool operator ==(const CharFrequency& rhCharfreq);
	bool operator ==(const unsigned char rhCharacter);
	bool operator !=(const CharFrequency& rhCharfreq);
	bool operator !=(const unsigned char rhCharacter);
	CharFrequency* operator++(int);//postfix
	CharFrequency* operator++();//prefix
	~CharFrequency();
private:
	unsigned char character;
	unsigned int frequency;
};

