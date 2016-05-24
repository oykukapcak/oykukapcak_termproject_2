#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>

using namespace std;

class Memory {

private:
	unsigned char* memory;
public:
	Memory(int size);
	void addInstructions(unsigned char* buffer, int bufferSize, int BR);
	unsigned char* getInstruction(int PC, int BR);

};

#endif