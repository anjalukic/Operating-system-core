// File: loopt.h
#ifndef _loopt_h_
#define _loopt_h_

#include "thread.h"

class LoopThread: public Thread {
public:
	LoopThread();
	virtual void run();
	void start();
};

#endif
