// File: ksem.cpp
#include "ksem.h"
#include "system.h"
#include "PCBList.h"
#include "SCHEDULE.H"


KernelSem::KernelSem(int init){
	lock();
	blockedList = new PCBList();
	value=init;
	unlock();
}

KernelSem::~KernelSem(){
	lock();
	delete blockedList;
	unlock();

}

int KernelSem::wait(int toBlock){
	lock();
	if (value<=0){
		if (toBlock!=0){
		value--;
		block();
		unlock();
		return 1;
		}
		else {
			unlock();
			return -1;
		}
	}
	value--;
	unlock();
	return 0;
}

void KernelSem::signal(){
	lock();
	if (value++<0){
		deblock();
	}
	unlock();
}

int KernelSem::val() const{
	return value;
}
void KernelSem::block(){
	PCB::running->status=BLOCKED;
	blockedList->put((PCB*)PCB::running);
	dispatch();
}
void KernelSem::deblock(){
	PCB* deblocking = blockedList->get();
	deblocking->status=ACTIVE;
	Scheduler::put(deblocking);
}
