// File: thread.cpp
#include "thread.h"
#include "PCB.h"
#include "PCBList.h"
#include "SCHEDULE.H"
#include "system.h"

void Thread::start() {
	lock();
	if (myPCB->status != NEW) {
		unlock();
		return;
	}
	myPCB->makeStack();
	myPCB->status = ACTIVE;
	Scheduler::put(myPCB);
	unlock();
}

void Thread::waitToComplete() {
	lock();
	if ((PCB*) PCB::running == this->myPCB || myPCB->status == ENDED
			|| myPCB->status == NEW || this == PCB::loopThread) {
		unlock();
		return;
	}
	PCB::running->status = BLOCKED;
	if (myPCB->waitList != 0)
		myPCB->waitList->put((PCB*) PCB::running);
	unlock();
	dispatch();
}

Thread::~Thread() {
	lock();
	waitToComplete();
	delete myPCB;
	unlock();
}

void Thread::sleep(Time timeToSleep) {
	lock();
	if (timeToSleep <= 0) {
		unlock();
		return;
	}
	System::sleepList->put((PCB*) PCB::running, timeToSleep);
	PCB::running->status = BLOCKED;
	unlock();
	dispatch();
}

Thread::Thread(StackSize stackSize, Time timeSlice) {
	myPCB = new PCB(stackSize, timeSlice, this);
}

void dispatch() {
	lock();
	System::contextSwitchNeeded = 1;
	System::timer();
	unlock();
}
