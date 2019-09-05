// File: kernelEv.cpp
#include "kernelEv.h"
#include "IVTEntry.h"
#include "SCHEDULE.H"


KernelEv::KernelEv(IVTNo ivtNo) {
	lock();
	value = 0;
	blocked = 0;
	makerPCB = (PCB*) PCB::running;
	entry = ivtNo;
	IVTEntry::events[ivtNo] = this;
	unlock();
}

KernelEv::~KernelEv() {
	lock();
	IVTEntry::events[entry] = 0;
	blocked = 0;
	unlock();
}

void KernelEv::wait() {
	lock();
	if (makerPCB == PCB::running) {
		if (value)
			value = 0;
		else {
			PCB::running->status = BLOCKED;
			blocked = (PCB*)PCB::running;
			dispatch();
		}
	}
	unlock();
}

void KernelEv::signal() {
	lock();
	if (blocked) {
		blocked->status = ACTIVE;
		Scheduler::put(blocked);
		blocked = 0;
	} else
		value = 1;
	unlock();
}

