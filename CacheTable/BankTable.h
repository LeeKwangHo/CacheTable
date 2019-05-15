#pragma once

class BankTable
{
private:
	unsigned char maxentry;
	unsigned long long *index;
public:
	BankTable(int maxentry);
	~BankTable();
	void Push(unsigned char index, unsigned long long row);
	unsigned long long Reference(unsigned char index);
};

