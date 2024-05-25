#pragma once
#include <array>
#include <bitset>

class Memory;
enum Instruction;
enum Params;

class CPU
{
public:
	using Byte = unsigned char;
	using Word = unsigned short;
	using Dword = unsigned int;

public:

	void Reset(Memory& mem);
	void Dispatch(Memory& mem);

	void Fetch(Memory& memory);

	void Execute(const CPU::Dword& opcode, const Instruction& inst, const std::array<Params, 2>& params, Memory& memory);


	std::string ToString();


private:

	// just ptr for reg file
	Dword st;
	Dword R0;
	Dword R1;
	Dword R2;
	Dword R3;
	Dword R4;
	Dword R5;
	Dword R6;
	Dword R7;
	Dword R8;
	Dword IP;
	Dword SP;
	Dword RP;
	std::bitset<sizeof(Dword)> FLAGS;
	// 0 - reserved
	// 1 - zero flag
	// 2 - reserved

	Byte Cycle = 0;
};