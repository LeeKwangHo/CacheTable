#pragma once
#include <stdio.h>
struct Item {
	unsigned long long row;
	unsigned char index;
	Item *prev;
	Item *next;
};

class ACTLRU
{
private:
	Item *head = nullptr;
	Item *tail = nullptr;
	int maxentry = 7;
	int currententry = 0;
public:
	ACTLRU();
	ACTLRU(int maxentry);
	~ACTLRU();
	void Push(unsigned long long row);
	void Pop();
	bool is_Full();
	int Reference(unsigned long long rowAddr);
	void EntryPrint();
	void Initial(int maxentry);
};