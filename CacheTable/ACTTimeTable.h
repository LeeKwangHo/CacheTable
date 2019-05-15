#pragma once
#include "ACTLRU.h"

struct ACTTable {
	int history;
	unsigned char bank;
	unsigned long long row;
	struct ACTTable* next;
	struct ACTTable* prev;
};

class ACTTimeTable
{
private:
	int currententrylist;
	int maxentrylist;
	int maxhistory;
	int pushhistory;
	unsigned char bankEntry[8];
	ACTTable* head;
	ACTTable* tail;
public:
	ACTTimeTable(int pushhistory, int maxhistory, int maxentry);
	~ACTTimeTable();
	bool is_Full();
	int Reference(unsigned char bank, unsigned long long row);
	void Push(unsigned char bank, unsigned long long row);
	void Pop();
	void EntryPrint();
	ACTLRU* bankTable;
};

