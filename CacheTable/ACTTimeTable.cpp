#include "ACTTimeTable.h"



ACTTimeTable::ACTTimeTable(int pushhistory, int maxhistory, int maxentry)
{
	this->currententrylist = 0;
	this->pushhistory = pushhistory;
	this->maxhistory = maxhistory;
	this->maxentrylist = maxentry;
	this->head = nullptr;
	this->tail = nullptr;
	this->bankTable = new ACTLRU[8];
	for (int i = 0; i < 8; i++) {
		this->bankEntry[i] = 0;
		bankTable[i].Initial(7);
	}
	
}


ACTTimeTable::~ACTTimeTable()
{
}

bool ACTTimeTable::is_Full()
{
	if (currententrylist == maxentrylist)
		return true;
	else
		return false;
}

int ACTTimeTable::Reference(unsigned char bankAddr, unsigned long long rowAddr)
{
	ACTTable* i = head;
	int ref = -2;
	while (i != nullptr) {
		i->history = i->history / 2;
		i = i->next;
	}
	i = head;
	while (i != nullptr) {
			if (i->bank == bankAddr) {
				if (i->row == rowAddr) {
					if (i == head){
						i->history = i->history + maxhistory;
						ref = -1;
					}
					else if (i == tail) {
						i->history = i->history + maxhistory;
						tail = i->prev;
						tail->next = nullptr;
						head->prev = i;
						i->next = head;
						head = i;
						ref = -1;
					}
					else {
						i->history = i->history + maxhistory;
						i->prev->next = i->next;
						i->next->prev = i->prev;
						head->prev = i;
						i->next = head;
						head = i;
						ref = -1;
					}
					if (i->history >= pushhistory) {
						ref=bankTable[bankAddr].Reference(rowAddr);
					}
				}
			}
		i = i->next;
	}
	if (ref == -2) {
		Push(bankAddr, rowAddr);
		return -2;
	}
	else
		return ref;
}

void ACTTimeTable::Push(unsigned char bank, unsigned long long row)
{
	ACTTable* i = new ACTTable;
	i->bank = bank;
	i->row = row;

	if (head == nullptr) {
		head = i;
		head->next = nullptr;
		head->prev = nullptr;
		tail = i;
		tail->next = nullptr;
		tail->prev = nullptr;
		head->history = maxhistory;
		currententrylist++;
		return;
	}

	i->next = head;
	i->prev = nullptr;
	head->prev = i;
	head = i;
	head->history = maxhistory;

	if (is_Full()) {
		Pop();
	}
}

void ACTTimeTable::Pop()
{
	ACTTable* temp = tail->prev;
	temp->next = nullptr;
	tail = temp;
}

void ACTTimeTable::EntryPrint()
{
	ACTTable* i = head;
	//printf("head : %d %llu index : %d\n",head->bank,head->row,head->index);
	//printf("tail : %d %llu index : %d\n",tail->bank,tail->row,tail->index);
	printf("==================================================\n");
	while (i != nullptr) {
		printf("Address : %d %llu %d\n", i->bank, i->row,i->history);
		i = i->next;
	}
	printf("==================================================\n");
}

int main(void) {
	ACTTimeTable table(16,8,10);
	table.Reference(1,17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	table.Reference(1, 17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	table.Reference(1, 17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	table.Reference(1, 17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	table.Reference(1, 17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	table.Reference(1, 17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	table.Reference(1, 17);
	table.EntryPrint();
	table.Reference(2, 17);
	table.EntryPrint();
	return 0;
}