#include "Memory.h"

Memory::Memory(int size)
{
	memory = new unsigned char[size];
}

void Memory::addInstructions(unsigned char * buffer, int bufferSize, int BR)
{
	for (int i = 0; i < bufferSize; i++)
	{
		memory[i] = buffer[BR + i]; //BR eklemeden emin deðilim?!!?!
	}
}

unsigned char * Memory::getInstruction(int PC, int BR)
{
	unsigned char* instruction = new unsigned char[4];

	for (int i = 0; i < 4; i++)
	{
		instruction[i] = memory[BR + PC + i];
	}

	return instruction;
}
