// File: PCB.cpp
#include <dos.h>
#include "PCB.h"
#include "thread.h"
#include "SCHEDULE.H"
#include "slist.h"
#include "loopt.h"
#include "PCBList.h"


ID PCB::prevID = 0;
volatile PCB* PCB::running = 0;
LoopThread* PCB::loopThread = 0;


void PCB::wrapper() {
	((PCB*) PCB::running)->myThread->run();
	lock();
	((PCB*) PCB::running)->status = ENDED;
	PCB* temp;
	while (((PCB*) PCB::running)->waitList->isEmpty() == 0) {
		temp = ((PCB*) PCB::running)->waitList->get();
		temp->status = ACTIVE;
		Scheduler::put(temp);
	}
	unlock();
	dispatch();
}

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* myThread) {
	lock();
	init();
	status = NEW;
	this->myThread = myThread;
	this->timeSlice = timeSlice;
	size = stackSize;
	unlock();
}

void PCB::init() {
	stack = 0;
	waitList = new PCBList;
	id = ++prevID;
	sp = ss = bp = 0;
}

PCB::~PCB() {
	lock();
	delete waitList;
	if (stack != 0)
		delete stack;
	unlock();
}

void PCB::startPCB() {
	lock();
	makeStack();
	status = ACTIVE;
	Scheduler::put(this);
	unlock();
}

void PCB::makeStack() {
	lock();
	stack = new unsigned[size];
	stack[size - 1] = 0x200;

#ifndef BCC_BLOCK_IGNORE
	stack[size-2] = FP_SEG(&(wrapper));
	stack[size-3] = FP_OFF(&(wrapper));

	sp = FP_OFF(stack+size-12);
	ss = FP_SEG(stack+size-12);
	bp = sp;
#endif
	unlock();
}

