// File: event.cpp
#include "event.h"
#include "kernelEv.h"

Event::Event(IVTNo ivtNo){
	myImpl=new KernelEv(ivtNo);
}
Event::~Event(){
	delete myImpl;
	myImpl=0;

}
void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
