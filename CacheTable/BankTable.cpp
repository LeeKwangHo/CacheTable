#include "BankTable.h"



BankTable::BankTable(int maxentry)
{
	unsigned char cnt = 0;
	this->maxentry = maxentry;
	index = new unsigned long long[maxentry];
}

BankTable::~BankTable()
{
	delete index;
}

void BankTable::Push(unsigned char index, unsigned long long row)
{
	this->index[index] = row;
}


unsigned long long BankTable::Reference(unsigned char index)
{
	return this->index[index];
}
