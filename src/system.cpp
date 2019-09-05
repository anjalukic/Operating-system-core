// File: system.cpp
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include "slist.h"
#include "thread.h"
#include "loopt.h"
#include "system.h"


extern void tick();
SleepList* System::sleepList = new SleepList();
volatile int System::contextSwitchNeeded=0;
pInterrupt System::oldRoutine=0;
volatile unsigned System::counter=1;
volatile unsigned tsp, tss, tbp;

void interrupt System::timer(...){

	//if it's really a hardware interrupt
	if (!System::contextSwitchNeeded) {
		counter--;
		tick();
		asm int 60h;
		System::sleepList->time();

	}


	//software interrupt or time's up for a thread - context switch
	if ((PCB::running->timeSlice!=0 && counter == 0 ) || contextSwitchNeeded) {

#ifndef BCC_BLOCK_IGNORE
		asm {

			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif
		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;


		if(PCB::running->status ==ACTIVE && PCB::running->myThread != PCB::loopThread)
			Scheduler::put((PCB*)PCB::running);


		PCB::running= Scheduler::get();
		if(PCB::running==0){
			PCB::running= PCB::loopThread->myPCB;
		}

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		counter=PCB::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
#endif

		System::contextSwitchNeeded=0;
	}


}


void System::initialize(){
	lock();
	PCB::running=new PCB();
	PCB::running->status=ACTIVE;
	PCB::loopThread= new LoopThread();
	PCB::loopThread->start();

#ifndef BCC_BLOCK_IGNORE

	oldRoutine = getvect(0x08);
	setvect(0x60,oldRoutine);
	setvect(0x08, timer);

#endif

unlock();
}

void System::restore(){
	lock();
	delete System::sleepList;
	delete PCB::loopThread;
	delete PCB::running;

#ifndef BCC_BLOCK_IGNORE
	setvect(0x08, oldRoutine);
#endif

	unlock();
}

