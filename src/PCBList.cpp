//File: PCBList.cpp
#include "PCBList.h"
#include "PCB.h"

PCBList::PCBList() {
	lock();
	first = 0;
	last = 0;
	unlock();
}

PCBList::~PCBList() {
	lock();
	Elem *deleting;
	while (!isEmpty()) {
		deleting = first;
		first = deleting->next;
		delete deleting;
	}
	unlock();
}

void PCBList::put(PCB* info) {
	lock();
	Elem* newEl = new Elem(info);
	if (first == 0)
		first = newEl;
	else
		last->next = newEl;
	last = newEl;
	unlock();
}

PCB* PCBList::get() {
	lock();
	if (first == 0) return 0;
	Elem* deleting = first;
	PCB* ret = first->info;
	first = first->next;
	delete deleting;
	if (first == 0) last = 0;
	unlock();
	return ret;
}

int PCBList::isEmpty() {
	if (first == 0)
		return 1;
	else
		return 0;
}

