// File: loopt.cpp
#include "loopt.h"
#include "PCB.h"
#include "thread.h"

LoopThread::LoopThread():Thread(1024, 2){}

void LoopThread::run(){while(1);}

void LoopThread::start(){
lock();
	myPCB->makeStack();
	myPCB->status=ACTIVE;
unlock();
}
