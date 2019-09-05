// File: IVTEntry.h
#ifndef _ivtentry_h_
#define _ivtentry_h_

#include "event.h"
#include "system.h"

typedef unsigned char IVTNo;

class IVTEntry{
private:
	pInterrupt oldRoutine;
	IVTNo entry;
	static KernelEv** events;
public:
	IVTEntry(IVTNo entry, pInterrupt newRoutine);
	~IVTEntry();//virtual?
	void callOldRoutine();
	void signal();
protected:
	friend class KernelEv;
};


#endif
