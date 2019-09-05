// File: kernelEv.h
#ifndef _kernelev_h_
#define _kernelev_h_

#include "PCB.h"
#include "event.h"

class IVTEntry;

class KernelEv{
private:
	PCB* makerPCB;
	PCB* blocked;
	int value;
	IVTNo entry;
	
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();
};

#endif
