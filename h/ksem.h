// File: ksem.h
#ifndef _kernelsem_h_
#define _kernelsem_h_

#include "PCBList.h"

class KernelSem {

public:
	KernelSem(int init);
	virtual ~KernelSem();
	virtual int wait(int toBlock);
	virtual void signal();
	int val() const;

private:
	int value;
	PCBList* blockedList;
	void block();
	void deblock();

};

#endif
