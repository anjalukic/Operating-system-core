// File: semaphor.cpp
#include "semaphor.h"
#include "ksem.h"

Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init);
}

Semaphore::~Semaphore() {
	delete myImpl;
	myImpl = 0;
}

int Semaphore::wait(int toBlock) {
	return myImpl->wait(toBlock);
}

void Semaphore::signal() {
	myImpl->signal();
}

int Semaphore::val() const {
	return myImpl->val();
}
