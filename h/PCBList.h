// File: PCBList.h
#ifndef _pcblist_h_
#define _pcblist_h_

class PCB;

class PCBList {

private:

	struct Elem {
	public:
		PCB* info;
		Elem* next;
		Elem(PCB* inf, Elem* n = 0) {
			info = inf;
			next = n;
		}
		~Elem() {
			info = 0;
			next = 0;
		}
	};
	Elem *first, *last;

public:
	PCBList();
	~PCBList();
	void put(PCB* info);
	PCB* get();
	int isEmpty();

};

#endif
