// File: PCB.h
#ifndef _pcb_h_
#define _pcb_h_

#include "system.h"
#include "thread.h"

class PCBList;
class SleepList;
class LoopThread;
class KernelSem;
class KernelEv;

enum Status {
	NEW, ACTIVE, ASLEEP, BLOCKED, ENDED
};


class PCB {

private:
	Thread *myThread;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned* stack;
	StackSize size;
	unsigned timeSlice;
	static ID prevID;
	ID id;

	PCBList* waitList;
	Status status;

	static void wrapper();
	PCB(StackSize stackSize = 0, Time timeSlice = defaultTimeSlice, Thread* myThread = 0);
	~PCB();

	void init();
	void makeStack();
	void startPCB();



	static volatile PCB* running;
	static LoopThread* loopThread;


protected:
	friend class Thread;
	friend class LoopThread;
	friend class System;
	friend class SleepList;
	friend class KernelSem;
	friend class KernelEv;

};

#endif
