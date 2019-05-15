#include "ACTLRU.h"


ACTLRU::ACTLRU() {
}


ACTLRU::ACTLRU(int maxentry)
{
	head = nullptr;
	tail = nullptr;
	this->maxentry = maxentry;
	currententry = 0;
}


ACTLRU::~ACTLRU()
{
	Item* temp = head;
	while (head != nullptr)
		head = head->next;
		delete temp;
		temp = head;
}

void ACTLRU::Push(unsigned long long row)
{
	Item *i = new Item;
	i->row = row;

	if (head == nullptr){
		head = i;
		head->next = nullptr;
		head->prev = nullptr;
		tail = i;
		tail->next = nullptr;
		tail->prev = nullptr;
		head->index = currententry;
		currententry++;
		return;
	}

	i->next = head;
	i->prev = nullptr;
	head->prev = i;
	head = i;

	if (!is_Full()) {
		i->index = currententry;
		currententry++;
	}
	else {
		i->index = tail->index;
		Pop();
	}
}

void ACTLRU::Pop()
{
	Item *temp = tail->prev;
	temp->next = nullptr;
	delete tail;
	tail = temp;
}

bool ACTLRU::is_Full()
{
	if (currententry == maxentry)
		return true;
	else
		return false;
}

int ACTLRU::Reference(unsigned long long rowAddr)
{
	int ref = -2;
	Item *i = head;
	while(i != nullptr){
				if (i->row == rowAddr) {
					if (i == head)
						return i->index;
					else if (i == tail) {
						tail = i->prev;
						tail->next = nullptr;
						head->prev = i;
						i->next = head;
						head = i;
					}
					else {
						i->prev->next = i->next;
						i->next->prev = i->prev;
						head->prev = i;
						i->next = head;
						head = i;
					}
					ref = i->index;
				}
		i = i->next;
	}
	if (ref == -2) {
		Push(rowAddr);
		return currententry;
	}
	else
		return ref;
}

void ACTLRU::EntryPrint()
{
	Item* i = head;
	//printf("head : %d %llu index : %d\n",head->bank,head->row,head->index);
	//printf("tail : %d %llu index : %d\n",tail->bank,tail->row,tail->index);
	printf("==================================================\n");
	while (i != nullptr) {
		printf("Address : %llu index: %d\n" ,i->row,i->index);
		i = i->next;
	}
	printf("table entry number : %d\n\n", currententry);
	printf("==================================================\n");
}

void ACTLRU::Initial(int maxentry)
{
	head = nullptr;
	tail = nullptr;
	this->maxentry = maxentry;
	currententry = 0;
}
