// File: slist.cpp
#include <DOS.H>
#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"

SleepList::SleepList() {
	first = 0;
	listSize = 0;
}

SleepList::~SleepList() {
	if (first==0) return;
	Elem* deleting;
	while (first!=0){
		deleting=first;
		first=first->next;
		delete deleting;
	}
	listSize = 0;
}

void SleepList::put(PCB* pcb, Time time) {
	lock();
	pcb->status = BLOCKED;
	listSize++;

	if (first == 0) {
		first = new Elem(pcb, time);
		unlock();
		return;
	}
	Time timeToSleep = time;
	if (timeToSleep > first->timeLeft) {
		Elem* cur = first, *prev = 0;
		while (cur != 0 && timeToSleep > 0) {
			if ((int) timeToSleep - (int) cur->timeLeft < 0)
				break;
			prev = cur;
			timeToSleep = timeToSleep - cur->timeLeft;
			cur = cur->next;
		}
		prev->next = new Elem(pcb, timeToSleep, cur);
	} else {
		first->timeLeft -= timeToSleep;
		first = new Elem(pcb, timeToSleep, first);
	}

	unlock();
}

PCB* SleepList::get() {
	if (first && first->timeLeft == 0) {
		Elem* temp = first;
		PCB* ret = temp->info;
		first = first->next;
		listSize--;
		delete temp;
		return ret;
	} else
		return 0;
}

void SleepList::time() {
	lock();
	if (first == 0) {
		unlock();
		return;
	}
	first->timeLeft -= 1;
	PCB* cur;
	while ((cur = get()) != 0) {
		cur->status = ACTIVE;
		Scheduler::put(cur);
	}
	unlock();
}

unsigned int SleepList::size() {
	return listSize;
}

