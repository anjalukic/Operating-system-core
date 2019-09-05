// File: IVTEntry.cpp
#include "IVTEntry.h"
#include <dos.h>
#include "kernelEv.h"

KernelEv** IVTEntry::events = new KernelEv*[256];

IVTEntry::IVTEntry(IVTNo entry, pInterrupt newRoutine) {
	lock();
	this->entry = entry;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine=getvect(entry);
	setvect(entry,newRoutine);
#endif
	unlock();
}

IVTEntry::~IVTEntry() {
	lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(entry,oldRoutine);
#endif
	unlock();
}

void IVTEntry::callOldRoutine() {
	oldRoutine();
}

void IVTEntry::signal() {
	if (events[entry] != 0)
		events[entry]->signal();
}
