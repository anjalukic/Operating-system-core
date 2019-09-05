// File: system.h
#ifndef _system_h_
#define _system_h_
#include "slist.h"

typedef void interrupt (*pInterrupt)(...);

static void lock() {
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
}

static void unlock() {
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

class System {
public:
	static volatile int contextSwitchNeeded;
	static volatile unsigned counter;
	static pInterrupt oldRoutine;
	static SleepList* sleepList;

	static void interrupt timer(...);

	static void initialize();
	static void restore();
};


#endif
