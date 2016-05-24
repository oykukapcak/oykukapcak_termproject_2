#include "Assembler.h"
#include "ProcessImage.h"
#include "CPU.h"
#include "Memory.h"
#include <bitset>
#include <cmath>
using namespace std;

unsigned char* transformTochar(int i)
{
	int byte1, byte2, byte3, byte4;

	byte1 = i / pow(2, 24);
	byte2 = (i % (int)pow(2, 24)) / pow(2, 16);
	byte3 = (i % (int)pow(2, 16)) / pow(2, 8);
	byte4 = i % (int)pow(2, 8);

	unsigned char ch1 = (unsigned  char)byte1;
	unsigned char ch2 = (unsigned char)byte2;
	unsigned char ch3 = (unsigned char)byte3;
	unsigned char ch4 = (unsigned char)byte4;

	unsigned char* chptr = new unsigned char[4];

	chptr[0] = ch1;
	chptr[1] = ch2;
	chptr[2] = ch3;
	chptr[3] = ch4;

	return chptr;
}


int main()
{
	ifstream input;
	ofstream output;
	string line;

	input.open("assemblyInput.asm");
	output.open("assemblyCode.bin");


	while (getline(input, line))
	{
		int x = (EncodeLine(line));
		unsigned char* charRepres = transformTochar(x);

		for (int i = 0; i < 4; i++)
		{
			output << charRepres[i];
		}
	}

	output.close();

	//Create a process image 
	ProcessImage processImage;

	ifstream input2;
	input2.open("assemblyCode.bin");

	unsigned char* memoryBuffer = new unsigned char[1000];

	int bufferSize;
	input2.read((char*)memoryBuffer, 100);
	if (!input2) {
		// An error occurred!
		bufferSize = input2.gcount();// returns the number of bytes read.
		input2.clear();// will reset the stream state
		// so it is usable again.
	}
	

	Memory memory(1000);
	memory.addInstructions(memoryBuffer, bufferSize, 0);

	processImage.BR = 0;
	processImage.LR = bufferSize;

	CPU theCPU(&memory);
	theCPU.transferFromImage(&processImage);

	theCPU.fetchDecodeExecuteCycle();
	theCPU.transferToImage(&processImage);
	processImage.dumpToDisk();

	system("pause");
	return 0;
}