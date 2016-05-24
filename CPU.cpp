#include "CPU.h"
#include <string>

int transformToInt(unsigned char* chptr)
{
	unsigned char byte0, byte1, byte2, byte3;

	byte0 = chptr[0];
	byte1 = chptr[1];
	byte2 = chptr[2];
	byte3 = chptr[3];

	return (byte0 * pow(2, 24) + byte1 * pow(2, 16) + byte2 * pow(2, 8) + byte3);

}

unsigned int binaryStringToInt(string bits)
{
	unsigned int tempInt;
	unsigned int num = 0;
	for (int i = 0; i<bits.length(); i++) {
		tempInt = bits[i] - '0';
		num = num + tempInt * pow(2, (bits.length() - 1 - i));
	}

	return num;
}

string intToBinary(unsigned int val)
{
	unsigned int mask = 1 << (sizeof(int) * 8 - 1);
	string s = "";

	for (int i = 0; i < sizeof(int) * 8; i++)
	{
		if ((val & mask) == 0)
			s += '0';
		else
			s += '1';

		mask >>= 1;
	}
	return s;
}

CPU::CPU(Memory * m)
{
	memory = m;
}

void CPU::fetchDecodeExecuteCycle()
{
	while (PC != LR)
	{
		fetch();
		decodeExecute();
	}
}

void CPU::fetch()
{
	unsigned char* instruction = new unsigned char[4];

	instruction = memory->getInstruction(PC, BR);

	IR = transformToInt(instruction);

	PC += 4;

}

unsigned int* CPU::findReg(string bits)
{
	if (bits == "00000")
		return &PC;

	else if (bits == "00010")
		return &V;

	else if (bits == "00011")
		return &S0;

	else if (bits == "00100")
		return &S1;

	else if (bits == "00101")
		return &S2;

	else if (bits == "00110")
		return &S3;

	else if (bits == "00111")
		return &S4;

	else if (bits == "01000")
		return &S5;

	else if (bits == "01001")
		return &S6;

	else if (bits == "01010")
		return &S7;

	else if (bits == "01011")
		return &BR;

	else if (bits == "01100")
		return &$0;

}

void CPU::decodeExecute()
{

	string bitIR = intToBinary(IR);
	
	if (bitIR == "00000000000000000000000000000000")  //SYSCALL
	{
		if (V == 0)
		{
			int input;
			cin >> input;
			V = input;
		}

		else
		{
			cout << V << endl;
		}

	}

	else
	{
		string operation = bitIR.substr(0,6);
		string reg1 = bitIR.substr(6,5);
		string reg2 = bitIR.substr(11, 5);
		string reg3 = bitIR.substr(16,5);
		string constant = bitIR.substr(16, 16);;


		unsigned int* reg1_ptr = findReg(reg1);
		unsigned int* reg2_ptr = findReg(reg2);
		unsigned int* reg3_ptr = findReg(reg3);
		unsigned int constant_int = binaryStringToInt(constant);

		if (operation == "010000") //ADD
		{
			*reg1_ptr = *reg2_ptr + *reg3_ptr;
		}

		else if (operation == "010001") //SUB
		{
			*reg1_ptr = *reg2_ptr - *reg3_ptr;
		}

		else if (operation == "000010") //ADDI
		{
			*reg1_ptr = *reg2_ptr + constant_int;
		}

		else if (operation == "000011") //SUBI
		{
			*reg1_ptr = *reg2_ptr - constant_int;
		}

		else if (operation == "011111") //ORI
		{
			*reg1_ptr = *reg2_ptr | constant_int;
		}

		else if (operation == "000111") //BEQ
		{
			if (*reg1_ptr == *reg2_ptr)
			{
				PC = constant_int;
			}
		}

		else if (operation == "001000") //LUI
		{
			*reg1_ptr = constant_int*pow(2, 16);
		}

		else if (operation == "001001") //LW
		{
			*reg1_ptr = *reg2_ptr;
		}

		else if (operation == "001010") // SW
		{
			*reg2_ptr = *reg1_ptr;
		}
	}
}

void CPU::transferFromImage(ProcessImage * image)
{
	S0 = image->S0;
	S1 = image->S1;
	S2 = image->S2;
	S3 = image->S3;
	S4 = image->S4;
	S5 = image->S5;
	S6 = image->S6;
	S7 = image->S7;
	$0 = image->$0;
	PC = image->PC;
	V = image->V;
	IR = image->IR;
	BR = image->BR;
	LR = image->LR;

}

void CPU::transferToImage(ProcessImage * image)
{
	image->S0 = S0;
	image->S1 = S1;
	image->S2 = S2;
	image->S3 = S3;
	image->S4 = S4;
	image->S5 = S5;
	image->S6 = S6;
	image->S7 = S7;
	image->$0 = $0;
	image->PC = PC;
	image->V = V;
	image->IR = IR;
	image->BR = BR;
	image->LR = LR;
}
