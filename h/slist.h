// File: slist.h
#ifndef _sleeplist_h_
#define _sleeplist_h_

#include "PCB.h"
typedef unsigned int Time;

class PCB;

class SleepList {
private:

	struct Elem{
		Elem* next;
		PCB* info;
		Time timeLeft;

		Elem(PCB* inf, Time time, Elem* next=0){
			info=inf; this->next=next; timeLeft=time;
		}
		~Elem(){
			info=0; next=0;
		}
	};
	Elem *first;
	unsigned int listSize;

public:

	SleepList();
	~SleepList();
	void put(PCB* pcb, Time timeToSleep);
	PCB* get();
	void time();
	unsigned int size();

};

#endif
