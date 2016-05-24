#ifndef CPU_H
#define CPU_H

#include "Memory.h"
#include "ProcessImage.h"
#include <cmath>
#include <bitset>

class CPU {

private:

	unsigned int S0;
	unsigned int S1;
	unsigned int S2;
	unsigned int S3;
	unsigned int S4;
	unsigned int S5;
	unsigned int S6;
	unsigned int S7;
	unsigned int $0;
	unsigned int PC;
	unsigned int V;
	unsigned int IR;
	unsigned int BR;
	unsigned int LR;

	Memory* memory;
	unsigned int* findReg(string); //SAÇMALIK

public:
	CPU(Memory*);

	void fetchDecodeExecuteCycle();
	void fetch();
	void decodeExecute(); //OLACAK ÝNÞ

	void transferFromImage(ProcessImage*);
	void transferToImage(ProcessImage*);


};




#endif